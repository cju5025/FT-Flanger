#pragma once

#include "PanelBase.h"
#include "TopPanel.h"
#include "Slider.h"
#include "GUIHelpers.h"

class FTFlangerMainPanel
:   public FTFlangerPanelBase
{
public:
    
    FTFlangerMainPanel(FTFlangerAudioProcessor* inProcessor);
    ~FTFlangerMainPanel();
    
    void paint(Graphics& g) override;
    
private:
    
    std::unique_ptr<FTFlangerTopPanel> mTopPanel;
    
    String mLabel;
    
    OwnedArray<FTFlangerParameterSlider> mFXSliders;
};
