cmake_minimum_required(VERSION 3.22)

project(VelocityManipulator VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Path to JUCE - adjust if needed
set(JUCE_PATH "$ENV{HOME}/JUCE")
add_subdirectory(${JUCE_PATH} ${CMAKE_BINARY_DIR}/JUCE)

juce_add_plugin(VelocityManipulator
    COMPANY_NAME "ALDEN HAMMERSMITH"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT TRUE
    IS_MIDI_EFFECT TRUE
    PLUGIN_MANUFACTURER_CODE AldH
    PLUGIN_CODE VelM
    FORMATS VST3 AU Standalone
    PRODUCT_NAME "ALDENHammersmith_Velocity Manipulator"
)

target_sources(VelocityManipulator
    PRIVATE
        Source/PluginProcessor.cpp
        Source/PluginEditor.cpp
)

target_compile_definitions(VelocityManipulator
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
)

target_link_libraries(VelocityManipulator
    PRIVATE
        juce::juce_audio_utils
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
