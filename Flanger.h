#pragma once
#include "AudioHelpers.h"
#include "JuceHeader.h"

class FTFlangerFlanger
{
public:
    FTFlangerFlanger();
    ~FTFlangerFlanger();
    
    void setSampleRate(double inSampleRate);
    
    void reset();
    
    void process(float* inAudio,
                 float inFeedback,
                 float inWetDry,
                 float* inModulationBuffer,
                 float* outAudio,
                 int inNumSamplesToRender);
    
private:
    
    double getInterpolatedSample(float inDelayTimeInSamples);
    
    double mSampleRate;
    double mBuffer[maxBufferSize];
    double mFeedbackSample;
    
    float mTimeSmoothed;
    
    int mDelayIndex;
};
