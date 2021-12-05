#pragma once
#include "JuceHeader.h"
#include "InterfaceDefines.h"
#include "DialLookAndFeel.h"

class FTFlangerParameterSlider
:   public Slider
{
public:
    
    FTFlangerParameterSlider(AudioProcessorValueTreeState& stateToControl,
                        const String& parameterID);
    
    ~FTFlangerParameterSlider();
        
private:
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mAttachment;
    FTFlangerDial mDialLookAndFeel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FTFlangerParameterSlider);
};
