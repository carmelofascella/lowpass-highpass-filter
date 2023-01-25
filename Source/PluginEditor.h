/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class LowPassHighPassFilterAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    // altered constructor to receive the value tree state object
    LowPassHighPassFilterAudioProcessorEditor(LowPassHighPassFilterAudioProcessor&,juce::AudioProcessorValueTreeState&vts);
    ~LowPassHighPassFilterAudioProcessorEditor() override;
    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
private:
    LowPassHighPassFilterAudioProcessor& audioProcessor;
    juce::Slider cutoffFrequencySlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
        cutoffFrequencyAttachment;
    juce::Label cutoffFrequencyLabel;

    juce::ToggleButton highpassButton;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>
        highpassAttachment;
    juce::Label highpassButtonLabel;

    // given by JUCE by default
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(
        LowPassHighPassFilterAudioProcessorEditor)
};
