#include "LFO.h"
#include "JuceHeader.h"

FTFlangerLFO::FTFlangerLFO()
{
    reset();
}

FTFlangerLFO::~FTFlangerLFO()
{
    
}

void FTFlangerLFO::reset()
{
    mPhase = 0.0f;
    zeromem(mBuffer, sizeof(float) * maxBufferSize);
}

void FTFlangerLFO::setSampleRate(double inSampleRate)
{
    mSampleRate = inSampleRate;
}

void FTFlangerLFO::getHostBPM()
{
    DBG(mHostInfo.bpm);
}

void FTFlangerLFO::process(float inRate, float inDepth, int inNumSamples)
{
    getHostBPM();
    
    const float rate = jmap(inRate, 0.0f, 1.0f, 0.001f, 50.0f);
    
    for (int i = 0; i < inNumSamples; i++)
    {
        mPhase += (rate / mSampleRate);
        
        if (mPhase > 1)
        {
            mPhase -= 1.0f;
        }
        
        const float LFOPosition = sinf(mPhase * TWO_PI) * inDepth;
        
        mBuffer[i] = LFOPosition;
    }
}

float* FTFlangerLFO::getBuffer()
{
    return mBuffer;
}
