#include "TopPanel.h"
#include "InterfaceDefines.h"

FTFlangerTopPanel::FTFlangerTopPanel(FTFlangerAudioProcessor* inProcessor)
:   FTFlangerPanelBase(inProcessor)
{
    setSize(TOP_PANEL_WIDTH, TOP_PANEL_HEIGHT);
}

FTFlangerTopPanel::~FTFlangerTopPanel()
{
    
}

void FTFlangerTopPanel::paint(Graphics& g)
{    
    FTFlangerPanelBase::paint(g);
    
    g.setColour(Colour(255, 218, 5));
    g.setFont(font_1);
    g.drawFittedText("FT Flanger", 0, 0, getWidth() - 10, getHeight(), Justification::centred, 1);
}
