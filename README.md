# impedance

## CLion: CMake is IDE metadata only

Open this repository root as a CMake project. `CMakeLists.txt` provides C23
source targets, include paths and flags for navigation, diagnostics and inlay
hints. Targets are excluded from the default build; no linking, dependency
downloads or application runner are wired into it. Set `VEXSPOKE_SOURCE_DIR`
to a local Vexspoke `src/`. Missing headers stay real IDE errors; no fake
declarations are generated. IDE appearance is user-verified.

Build with [b](https://github.com/vex-graph/b), not this adapter. From the
Vexgraph workspace root: `./tools/b build impedance`. This indexes the current
C shell; it does not prove a finished DAW or standalone runtime dependency closure.

**Impedance** is a next-generation GPU/CPU hybrid Digital Audio Workstation (DAW) engineered for high-concurrency multi-track mixing and ultra-low-latency real-time playback.

## Architecture
- **Audio DSP Engine (`samplerate`)**: Offloads high-density polyphony, convolution reverb, and non-linear filter models to Vulkan compute shaders.
- **Hardware & HAL Presentation (`vexspoke`)**: Utilizes `vexspoke` CoreAudio low-latency HAL engine (`AudioHal`), lock-free ring buffers, and hardware event multiplexers.
- **Specialized Input Support**: Seamlessly accepts expressive input from piano keyboards (MIDI velocity/aftertouch), DJ turntables (jog-wheel scratch deltas and crossfaders), trackpad multi-touch gestures, and game controllers.
- **Unified Caching**: Zero-redownload asset cache for samples, soundfonts, and IR models.

## Hybrid Audio Pipeline
```
[ MIDI / Turntable / Controller Input ]
                │
                ▼
      [ Track & Voice Graph ]
        ├── CPU Mixing & Voice Allocation
        └── GPU Compute Dispatches (samplerate Vulkan Shaders)
                │
                ▼
      [ CoreAudio HAL Output ] (Low-latency AudioUnit stream)
```
