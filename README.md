# Velocity Manipulator

A simple MIDI velocity manipulator VST3/AU plugin built with JUCE.

## Features

- **Scale** (0-200%) - Multiply incoming velocity
- **Offset** (-127 to +127) - Add or subtract from velocity
- **Min/Max** - Clamp output velocity to a range

## Building

### Requirements

- [JUCE](https://github.com/juce-framework/JUCE) (clone to `~/JUCE`)
- CMake 3.22+
- C++17 compiler (Xcode on macOS, Visual Studio on Windows)

### Build Steps

```bash
git clone https://github.com/Hammersmithing/velocity-manipulator.git
cd velocity-manipulator
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

Built plugins will be in `build/VelocityManipulator_artefacts/Release/`.

## Installation

### macOS

```bash
# VST3
cp -r "build/VelocityManipulator_artefacts/Release/VST3/Velocity Manipulator.vst3" ~/Library/Audio/Plug-Ins/VST3/

# AU
cp -r "build/VelocityManipulator_artefacts/Release/AU/Velocity Manipulator.component" ~/Library/Audio/Plug-Ins/Components/
```

### Windows

Copy `Velocity Manipulator.vst3` to `C:\Program Files\Common Files\VST3\`

## License

MIT
