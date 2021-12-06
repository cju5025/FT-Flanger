#include "MainPanel.h"
#include "Parameters.h"

FTFlangerMainPanel::FTFlangerMainPanel(FTFlangerAudioProcessor* inProcessor)
:   FTFlangerPanelBase(inProcessor)
{
    setSize(MAIN_PANEL_WIDTH, MAIN_PANEL_HEIGHT);
    
    mTopPanel = std::make_unique<FTFlangerTopPanel>(inProcessor);
    mTopPanel->setTopLeftPosition(0, 0);
    addAndMakeVisible(mTopPanel.get());
    
}

FTFlangerMainPanel::~FTFlangerMainPanel()
{
    mFXSliders.clear();
}

void FTFlangerMainPanel::paint(Graphics& g)
{
    FTFlangerPanelBase::paint(g);
    
    for (int i = 0; i < mFXSliders.size(); i++)
    {
        paintComponentLabel(g, mFXSliders[i]);
    }
    
    const int sliderSize = 75;
    int x = (getWidth() / 2) - (sliderSize * 2.5);
    int y = (getHeight()) - (sliderSize * 1.25);
    
    FTFlangerParameterSlider* feedback =
    new FTFlangerParameterSlider(mProcessor->parameters, FTFlangerParameterID[kFTFlangerParameter_Feedback]);
    feedback->setBounds(x, y, sliderSize, sliderSize);
    addAndMakeVisible(feedback);
    mFXSliders.add(feedback);
    x += sliderSize * 2;
    
    FTFlangerParameterSlider* wetDry =
    new FTFlangerParameterSlider(mProcessor->parameters, FTFlangerParameterID[kFTFlangerParameter_WetDry]);
    wetDry->setBounds(x, y, sliderSize, sliderSize);
    addAndMakeVisible(wetDry);
    mFXSliders.add(wetDry);
    x += sliderSize * 2;
    
    FTFlangerParameterSlider* phaseOffset =
    new FTFlangerParameterSlider(mProcessor->parameters, FTFlangerParameterID[kFTFlangerParameter_PhaseOffset]);
    phaseOffset->setBounds(x, y, sliderSize, sliderSize);
    addAndMakeVisible(phaseOffset);
    mFXSliders.add(phaseOffset);
    x = (getWidth() / 2) - (sliderSize * 2.5);
    y = (getHeight() * 0.75) - (sliderSize * 1.75);
    
    FTFlangerParameterSlider* rate =
    new FTFlangerParameterSlider(mProcessor->parameters, FTFlangerParameterID[kFTFlangerParameter_ModulationRate]);
    rate->setBounds(x, y, sliderSize, sliderSize);
    addAndMakeVisible(rate);
    mFXSliders.add(rate);
    x += sliderSize * 2;
                
    FTFlangerParameterSlider* depth =
    new FTFlangerParameterSlider(mProcessor->parameters, FTFlangerParameterID[kFTFlangerParameter_ModulationDepth]);
    depth->setBounds(x, y, sliderSize, sliderSize);
    addAndMakeVisible(depth);
    mFXSliders.add(depth);
    x += sliderSize * 2;
    
    FTFlangerParameterSlider* rateOffset =
    new FTFlangerParameterSlider(mProcessor->parameters, FTFlangerParameterID[kFTFlangerParameter_RateOffset]);
    rateOffset->setBounds(x, y, sliderSize, sliderSize);
    addAndMakeVisible(rateOffset);
    mFXSliders.add(rateOffset);

                
}
