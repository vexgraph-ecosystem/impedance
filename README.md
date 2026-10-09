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

## Current State

**Draft — not finalized.** The current C shell is not a finished DAW.

**Role:** R5 interactable — a GPU/CPU hybrid Digital Audio Workstation (DAW)
targeting high-concurrency multi-track mixing and low-latency playback.

**Implemented:** a small C shell — `src/impedance.c`, `src/impedance.h`,
`src/main.c`. `main.c` initializes the engine, adds two CPU tracks, plays a C4/E4
chord, applies a turntable scratch rate and renders 512 stereo frames offline as
a smoke test. It includes Vexspoke headers (`audio/audio_hal.h`,
`input/piano_key.h`, `input/turntable.h`).

**Not yet implemented:** live CoreAudio output, the GPU/Vulkan DSP path, any UI,
mixing beyond the shell, and persistence.

**Proven:** nothing — the shell's files carry no executed owner test in
`tests/test-checklist.md`; no platform or audio output is proven.

## Architecture

The pipeline below is a design target, not implemented audio/GPU capability.
R2 is split between Vexspoke CPU computation/behavior and Relational Engine
memory/storage, stable rows, bindings and native C search; migration is staged
with the retained Vexspoke ABI/default allocator. R1 owns lifetimes/residency;
GPU DSP shaders/dispatch remain Graphvex R3. No C/Rust atomic-layout equivalence,
automatic schema migration or engine integration is implied. Read the
[constitution](https://gist.github.com/vex-graph/4132a6c45cb6d3797c3e8eff2e94035a)
and ecosystem readiness Gist before treating any target as shipped behavior.

- **Audio DSP Engine (`samplerate`, R3)**: Audio policy and CPU DSP; any GPU shader/dispatch implementation belongs to Graphvex R3.
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

## Scope and Limitations

**Scope (intended):** the end-user DAW — multi-track mixing, voice allocation,
expressive input (MIDI/turntable/pad) and a GPU/CPU hybrid DSP path, built on the
`samplerate` R3 audio driver, presented through `darling-framework`, supervised
as an R1 `Application`.

**Deliberately not covered:** no audio device driver of its own (`samplerate`
owns CoreAudio/WASAPI/ALSA); no GPU shader/dispatch (`graphvex` owns it); no
connector or session transport (`api-haven`/`sesh` own them).

**Known limits and gaps:** the shell is not a DAW and has no owner test; the
pipeline above is a design target. No GPU path, UI or persistence exists. Read
the constitution and readiness Gist before treating any target as shipped.
