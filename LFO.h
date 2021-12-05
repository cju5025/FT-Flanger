#pragma once
#include "AudioHelpers.h"
#include "JuceHeader.h"

class FTFlangerLFO
{
public:
    FTFlangerLFO();
    ~FTFlangerLFO();
    
    void reset();
    
    void setSampleRate(double inSampleRate);
    
    void getHostBPM();
    
    void process(float inRate, float inDepth, int inNumSamples);
    
    float* getBuffer();
    
private:
    
    double mSampleRate;
    
    float mPhase;
    
    float mBuffer[maxBufferSize];
    
    AudioPlayHead::CurrentPositionInfo mHostInfo;
};
