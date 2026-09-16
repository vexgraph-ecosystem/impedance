# impedance

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
