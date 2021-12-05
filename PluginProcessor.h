#pragma once

#include <JuceHeader.h>
#include "Flanger.h"
#include "LFO.h"


class FTFlangerAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    FTFlangerAudioProcessor();
    ~FTFlangerAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    AudioProcessorValueTreeState parameters;

private:

    void initializeDSP();
    
    std::unique_ptr<FTFlangerLFO> mLFO[8];
    std::unique_ptr<FTFlangerFlanger> mFlanger[8];
    
    SmoothedValue<float, ValueSmoothingTypes::Linear> mFeedbackSmoothed { 0.0f };
    SmoothedValue<float, ValueSmoothingTypes::Linear> mDryWetSmoothed { 0.0f };
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FTFlangerAudioProcessor)
};
