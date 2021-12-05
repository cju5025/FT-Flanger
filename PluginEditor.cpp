#include "PluginProcessor.h"
#include "PluginEditor.h"

FTFlangerAudioProcessorEditor::FTFlangerAudioProcessorEditor (FTFlangerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (MAIN_PANEL_WIDTH, MAIN_PANEL_HEIGHT);
    mMainPanel = std::make_unique<FTFlangerMainPanel>(&audioProcessor);
    addAndMakeVisible(mMainPanel.get());
}

FTFlangerAudioProcessorEditor::~FTFlangerAudioProcessorEditor()
{
        setLookAndFeel(nullptr);
}

//==============================================================================
void FTFlangerAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.setFont(font_3);
}

void FTFlangerAudioProcessorEditor::resized()
{

}
