#include "PanelBase.h"

FTFlangerPanelBase::FTFlangerPanelBase(FTFlangerAudioProcessor* inProcessor)
:   mProcessor(inProcessor)
{
    
}

FTFlangerPanelBase::~FTFlangerPanelBase()
{
    
}

void FTFlangerPanelBase::paint (Graphics& g)
{
    g.setColour(Colour(67, 76, 80));
    g.fillAll();    
}
