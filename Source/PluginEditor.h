#pragma once

#include "PluginProcessor.h"

class VelocityManipulatorEditor : public juce::AudioProcessorEditor
{
public:
    explicit VelocityManipulatorEditor(VelocityManipulatorProcessor&);
    ~VelocityManipulatorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    VelocityManipulatorProcessor& processorRef;

    juce::Slider scaleSlider;
    juce::Slider offsetSlider;
    juce::Slider minSlider;
    juce::Slider maxSlider;

    juce::Label scaleLabel;
    juce::Label offsetLabel;
    juce::Label minLabel;
    juce::Label maxLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> scaleAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> offsetAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> minAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> maxAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VelocityManipulatorEditor)
};
