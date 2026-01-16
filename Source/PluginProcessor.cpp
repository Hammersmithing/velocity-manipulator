#include "PluginProcessor.h"
#include "PluginEditor.h"

static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID("scale", 1),
        "Scale",
        juce::NormalisableRange<float>(0.0f, 2.0f, 0.01f),
        1.0f,
        juce::String(),
        juce::AudioProcessorParameter::genericParameter,
        [](float value, int) { return juce::String(int(value * 100)) + "%"; }
    ));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID("offset", 1),
        "Offset",
        juce::NormalisableRange<float>(-127.0f, 127.0f, 1.0f),
        0.0f
    ));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID("min", 1),
        "Min Velocity",
        juce::NormalisableRange<float>(0.0f, 127.0f, 1.0f),
        1.0f
    ));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID("max", 1),
        "Max Velocity",
        juce::NormalisableRange<float>(0.0f, 127.0f, 1.0f),
        127.0f
    ));

    return { params.begin(), params.end() };
}

VelocityManipulatorProcessor::VelocityManipulatorProcessor()
    : AudioProcessor(BusesProperties()
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
      parameters(*this, nullptr, juce::Identifier("VelocityManipulator"), createParameterLayout())
{
    scaleParam = parameters.getRawParameterValue("scale");
    offsetParam = parameters.getRawParameterValue("offset");
    minParam = parameters.getRawParameterValue("min");
    maxParam = parameters.getRawParameterValue("max");
}

VelocityManipulatorProcessor::~VelocityManipulatorProcessor()
{
}

const juce::String VelocityManipulatorProcessor::getName() const
{
    return JucePlugin_Name;
}

bool VelocityManipulatorProcessor::acceptsMidi() const { return true; }
bool VelocityManipulatorProcessor::producesMidi() const { return true; }
bool VelocityManipulatorProcessor::isMidiEffect() const { return true; }
double VelocityManipulatorProcessor::getTailLengthSeconds() const { return 0.0; }

int VelocityManipulatorProcessor::getNumPrograms() { return 1; }
int VelocityManipulatorProcessor::getCurrentProgram() { return 0; }
void VelocityManipulatorProcessor::setCurrentProgram(int) {}
const juce::String VelocityManipulatorProcessor::getProgramName(int) { return {}; }
void VelocityManipulatorProcessor::changeProgramName(int, const juce::String&) {}

void VelocityManipulatorProcessor::prepareToPlay(double, int)
{
}

void VelocityManipulatorProcessor::releaseResources()
{
}

bool VelocityManipulatorProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    juce::ignoreUnused(layouts);
    return true;
}

void VelocityManipulatorProcessor::processBlock(juce::AudioBuffer<float>& buffer,
                                                  juce::MidiBuffer& midiMessages)
{
    buffer.clear();

    const float scale = scaleParam->load();
    const float offset = offsetParam->load();
    const float minVel = minParam->load();
    const float maxVel = maxParam->load();

    juce::MidiBuffer processedMidi;

    for (const auto metadata : midiMessages)
    {
        auto message = metadata.getMessage();
        const auto timestamp = metadata.samplePosition;

        if (message.isNoteOn())
        {
            float velocity = static_cast<float>(message.getVelocity());

            // Apply scale and offset
            velocity = velocity * scale + offset;

            // Clamp to min/max range
            velocity = juce::jlimit(minVel, maxVel, velocity);

            // Ensure valid MIDI range
            velocity = juce::jlimit(1.0f, 127.0f, velocity);

            message.setVelocity(velocity / 127.0f);
        }

        processedMidi.addEvent(message, timestamp);
    }

    midiMessages.swapWith(processedMidi);
}

bool VelocityManipulatorProcessor::hasEditor() const { return true; }

juce::AudioProcessorEditor* VelocityManipulatorProcessor::createEditor()
{
    return new VelocityManipulatorEditor(*this);
}

void VelocityManipulatorProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void VelocityManipulatorProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(parameters.state.getType()))
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VelocityManipulatorProcessor();
}
