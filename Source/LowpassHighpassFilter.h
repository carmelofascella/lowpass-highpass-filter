/*
  ==============================================================================

    LowpassHighpassFilter.h
    Created: 25 Jan 2023 10:20:36am
    Author:  Carmelo Fascella

  ==============================================================================
*/

#pragma once
#include <vector>
#include "JuceHeader.h"

class LowpassHighpassFilter
{
public:
    void setHighpass(bool highpass);
    void setCutoffFrequency(float cutoffFrequency);
    void setSamplingRate(float samplingRate);
    void processBlock(juce::AudioBuffer<float>&,juce::MidiBuffer&);
    
private:
    bool highpass;
    float cutoffFrequency;
    float samplingRate;
    std::vector<float> dnBuffer;
    
};

