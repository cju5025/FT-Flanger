#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "MainPanel.h"


class FTFlangerAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    FTFlangerAudioProcessorEditor (FTFlangerAudioProcessor&);
    ~FTFlangerAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    FTFlangerAudioProcessor& audioProcessor;
    
    std::unique_ptr<FTFlangerMainPanel> mMainPanel;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FTFlangerAudioProcessorEditor)
};
