#include "PluginProcessor.h"
#include "PluginEditor.h"

VelocityManipulatorEditor::VelocityManipulatorEditor(VelocityManipulatorProcessor& p)
    : AudioProcessorEditor(&p), processorRef(p)
{
    // Scale slider
    scaleSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    scaleSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(scaleSlider);

    scaleLabel.setText("Scale", juce::dontSendNotification);
    scaleLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(scaleLabel);

    scaleAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        processorRef.getParameters(), "scale", scaleSlider);

    // Offset slider
    offsetSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    offsetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(offsetSlider);

    offsetLabel.setText("Offset", juce::dontSendNotification);
    offsetLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(offsetLabel);

    offsetAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        processorRef.getParameters(), "offset", offsetSlider);

    // Min velocity slider
    minSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    minSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(minSlider);

    minLabel.setText("Min", juce::dontSendNotification);
    minLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(minLabel);

    minAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        processorRef.getParameters(), "min", minSlider);

    // Max velocity slider
    maxSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    maxSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(maxSlider);

    maxLabel.setText("Max", juce::dontSendNotification);
    maxLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(maxLabel);

    maxAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        processorRef.getParameters(), "max", maxSlider);

    setSize(400, 200);
}

VelocityManipulatorEditor::~VelocityManipulatorEditor()
{
}

void VelocityManipulatorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(0xff2d2d2d));

    g.setColour(juce::Colours::white);
    g.setFont(18.0f);
    g.drawFittedText("Velocity Manipulator", getLocalBounds().removeFromTop(30),
                     juce::Justification::centred, 1);
}

void VelocityManipulatorEditor::resized()
{
    auto area = getLocalBounds().reduced(10);
    area.removeFromTop(30); // Title space

    const int knobWidth = area.getWidth() / 4;
    const int labelHeight = 20;

    auto scaleArea = area.removeFromLeft(knobWidth);
    scaleLabel.setBounds(scaleArea.removeFromTop(labelHeight));
    scaleSlider.setBounds(scaleArea);

    auto offsetArea = area.removeFromLeft(knobWidth);
    offsetLabel.setBounds(offsetArea.removeFromTop(labelHeight));
    offsetSlider.setBounds(offsetArea);

    auto minArea = area.removeFromLeft(knobWidth);
    minLabel.setBounds(minArea.removeFromTop(labelHeight));
    minSlider.setBounds(minArea);

    auto maxArea = area;
    maxLabel.setBounds(maxArea.removeFromTop(labelHeight));
    maxSlider.setBounds(maxArea);
}
