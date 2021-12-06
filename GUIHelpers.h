#pragma once
#include "JuceHeader.h"

inline void paintComponentLabel(Graphics& g, Component* inComponent)
{
    const int x = inComponent->getX() - (inComponent->getWidth() * 0.25f);
    const int y = inComponent->getY() - (inComponent->getHeight() / 3.5);
    const int w = inComponent->getWidth() * 1.5f;
    const int h = 20;
    
    const String label = inComponent->getName();
    
    g.setColour(Colour(255, 218, 5));
    g.drawFittedText(label, x, y, w, h, Justification::centred, 1);
}
