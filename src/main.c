#include <stdio.h>
#include <unistd.h>
#include "impedance.h"

int main(void) {
    printf("[Impedance DAW] Initializing GPU/CPU Hybrid DAW...\n");

    Impedance daw;
    if (!Impedance_init(48000.0, 2, &daw)) {
        fprintf(stderr, "Failed to initialize Impedance DAW\n");
        return 1;
    }

    uint32_t track0 = Impedance_add_track("Synth Lead", IMPEDANCE_COMPUTE_CPU, &daw);
    uint32_t track1 = Impedance_add_track("Turntable Scratch Deck", IMPEDANCE_COMPUTE_CPU, &daw);

    printf("[Impedance DAW] Created tracks: %u, %u\n", track0, track1);

    // Play C4 and E4 chord
    Impedance_note_on(track0, 60, 0.8f, &daw); // C4
    Impedance_note_on(track0, 64, 0.7f, &daw); // E4

    // Apply turntable scratch rate (1.2x pitch speed)
    Impedance_set_track_scratch_speed(track1, 1.2f, &daw);

    // Render 512 frames offline to test DSP buffer rendering
    float buffer[1024];
    Impedance_render(&daw, buffer, 512, 2);

    float max_sample = 0.0f;
    for (int i = 0; i < 1024; i++) {
        float abs_val = (buffer[i] < 0.0f) ? -buffer[i] : buffer[i];
        if (abs_val > max_sample) {
            max_sample = abs_val;
        }
    }

    printf("[Impedance DAW] Offline render test: 512 stereo frames generated, peak amplitude: %f\n", max_sample);

    Impedance_destroy(&daw);
    printf("[Impedance DAW] Smoke test complete: SUCCESS\n");
    return 0;
}
