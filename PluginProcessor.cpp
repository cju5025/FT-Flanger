#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Parameters.h"

AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
{
    std::vector<std::unique_ptr<AudioParameterFloat>> params;
    
    for (int i = 0; i < kFTFlangerParameter_TotalNumParameters; i++)
    {
        params.push_back(std::make_unique<AudioParameterFloat>(FTFlangerParameterID[i],
                                                               FTFlangerParameterLabel[i],
                                                               NormalisableRange<float> (0.0f, 1.0f, 0.001f),
                                                               FTFlangerParameterDefaultValue[i]));
    }
    return { params.begin(), params.end() };
}


FTFlangerAudioProcessor::FTFlangerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
                       parameters(*this,
                                    nullptr,
                                    Identifier("FTFlanger"),
                                    createParameterLayout())
#endif
{
    initializeDSP();
}

FTFlangerAudioProcessor::~FTFlangerAudioProcessor()
{
}

//==============================================================================
const juce::String FTFlangerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FTFlangerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FTFlangerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FTFlangerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FTFlangerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FTFlangerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FTFlangerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FTFlangerAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String FTFlangerAudioProcessor::getProgramName (int index)
{
    return {};
}

void FTFlangerAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void FTFlangerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    for (int i = 0; i < getTotalNumInputChannels(); i++)
    {
        mFlanger[i]->setSampleRate(sampleRate);
        mLFO[i]->setSampleRate(sampleRate);
    }
    
    mDryWetSmoothed.reset(sampleRate, 0.004f);
    mFeedbackSmoothed.reset(sampleRate, 0.004f);
}

void FTFlangerAudioProcessor::releaseResources()
{
    for (int i = 0; i < getTotalNumInputChannels(); i++)
    {
        mFlanger[i]->reset();
        mLFO[i]->reset();
    }
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FTFlangerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void FTFlangerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        
        //TODO: phase offset on/off box, phase offset invert toggle
        
        float rate = *parameters.getRawParameterValue(FTFlangerParameterID[kFTFlangerParameter_ModulationRate]) + *parameters.getRawParameterValue(FTFlangerParameterID[kFTFlangerParameter_PhaseOffset]);
        
        if (channel > 0)
        {
            rate = *parameters.getRawParameterValue(FTFlangerParameterID[kFTFlangerParameter_ModulationRate]);
        }
        
        mLFO[channel]->process(rate,
                               *parameters.getRawParameterValue(FTFlangerParameterID[kFTFlangerParameter_ModulationDepth]),
                               buffer.getNumSamples());
        
        mDryWetSmoothed.setTargetValue(*parameters.getRawParameterValue(FTFlangerParameterID[kFTFlangerParameter_WetDry]));
        mFeedbackSmoothed.setTargetValue(*parameters.getRawParameterValue(FTFlangerParameterID[kFTFlangerParameter_Feedback]));
        
        mFlanger[channel]->process(channelData,
                                 mFeedbackSmoothed.getNextValue(),
                                 mDryWetSmoothed.getNextValue(),
                                 mLFO[channel]->getBuffer(),
                                 channelData,
                                 buffer.getNumSamples());
        
    }
}

//==============================================================================
bool FTFlangerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* FTFlangerAudioProcessor::createEditor()
{
    return new FTFlangerAudioProcessorEditor (*this);
}

//==============================================================================
void FTFlangerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
   auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void FTFlangerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (parameters.state.getType()))
            parameters.replaceState (juce::ValueTree::fromXml (*xmlState));
}

void FTFlangerAudioProcessor::initializeDSP()
{
    for (int i = 0; i < getTotalNumInputChannels(); i++)
    {
        mFlanger[i] = std::make_unique<FTFlangerFlanger>();
        mLFO[i] = std::make_unique<FTFlangerLFO>();
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FTFlangerAudioProcessor();
}
