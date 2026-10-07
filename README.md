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

**Unfinished application:** the current C shell is not a finished DAW. The
pipeline below is a design target, not implemented audio/GPU capability.
R2 comprises Vexspoke CPU computation/behavior and Relational Engine
memory/storage, stable rows, bindings and native C search. Migration is staged;
existing Vexspoke memory/container ABI and default allocator remain. R1 owns
lifetimes/residency; GPU DSP shaders/dispatch remain Graphvex R3. No C/Rust atomic
layout equivalence, automatic schema migration or engine integration is implied.
Read the [constitution](https://gist.github.com/vex-graph/4132a6c45cb6d3797c3e8eff2e94035a)
and ecosystem readiness wiki before treating any target as shipped behavior.
- **Audio DSP Engine (`samplerate`, planned)**: Audio policy and CPU DSP; any GPU shader/dispatch implementation belongs to Graphvex R3.
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
        └── GPU Compute Dispatches (Graphvex R3, planned DSP pipelines)
                │
                ▼
      [ CoreAudio HAL Output ] (Low-latency AudioUnit stream)
```
