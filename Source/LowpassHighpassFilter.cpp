/*
  ==============================================================================

    LowpassHighpassFilter.cpp
    Created: 25 Jan 2023 10:20:36am
    Author:  Carmelo Fascella

  ==============================================================================
*/

#include "LowpassHighpassFilter.h"


void LowpassHighpassFilter::setHighpass(bool highpass) {
  this->highpass = highpass;
}

void LowpassHighpassFilter::setCutoffFrequency(float cutoffFrequency) {
  this->cutoffFrequency = cutoffFrequency;
}

void LowpassHighpassFilter::setSamplingRate(float samplingRate) {
  this->samplingRate = samplingRate;
}

void LowpassHighpassFilter::processBlock(juce::AudioBuffer<float>& buffer,
                                         juce::MidiBuffer&) {
  // pi value copied from the web
  constexpr auto PI = 3.14159265359f;

  // resize the allpass buffers to the number of channels and
  // zero the new ones
  dnBuffer.resize(buffer.getNumChannels(), 0.f);

  // if we perform highpass filtering, we need to
  // invert the output of the allpass (multiply it
  // by -1)
  const auto sign = highpass ? -1.f : 1.f;

  // helper variable
  const auto tan = std::tan(PI * cutoffFrequency / samplingRate);
  // allpass coefficient is constant while processing
  // a block of samples
  const auto a1 = (tan - 1.f) / (tan + 1.f);

  //for each each channel separately
  for (auto channel = 0; channel < buffer.getNumChannels(); ++channel) {
    // we need a write pointer to the channel because we need to modify it
    auto channelSamples = buffer.getWritePointer(channel);

    // for each sample in the channel
    for (auto i = 0; i < buffer.getNumSamples(); ++i) {
      const auto inputSample = channelSamples[i];

      // allpass filtering
      const auto allpassFilteredSample = a1 * inputSample +
                                            dnBuffer[channel];
      dnBuffer[channel] = inputSample - a1 * allpassFilteredSample;

      // here the final filtering occurs
      // we scale by 0.5 to stay in the [-1, 1] range
      const auto filterOutput =
          0.5f * (inputSample + sign * allpassFilteredSample);

      // assign to the output
      channelSamples[i] = filterOutput;
    }
  }
}
