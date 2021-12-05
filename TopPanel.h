#pragma once
#include "PanelBase.h"

class FTFlangerTopPanel
:   public FTFlangerPanelBase
{
    
public:
    
    FTFlangerTopPanel(FTFlangerAudioProcessor* inProcessor);
    ~FTFlangerTopPanel();
    
    void paint(Graphics& g) override;

private:
    
};
