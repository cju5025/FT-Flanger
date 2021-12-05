#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "InterfaceDefines.h"

class FTFlangerPanelBase
:   public Component
{
public:
    
    FTFlangerPanelBase(FTFlangerAudioProcessor* inProcessor);
    ~FTFlangerPanelBase();
    
    void paint (Graphics& g) override;
    
protected:
    
    FTFlangerAudioProcessor* mProcessor;
    
};
