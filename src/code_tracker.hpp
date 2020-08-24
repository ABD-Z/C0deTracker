//
// Created by Abdulmajid NASSER on 23/08/2020.
//

#ifndef CODETRACKER_CODE_TRACKER_HPP
#define CODETRACKER_CODE_TRACKER_HPP

#include <cmath>
#include <iostream>

namespace CodeTracker {
#define TWOPI 6.283185307

    struct Key{int note, octave;};

    namespace Notes {
        enum {
            C, C_S, D, D_S, E, F, F_S, G, G_S, A, A_S, B, PITCHES_PER_OCTAVE, OCTAVE_PITCH_OFFSET = 4, NOTE_PITCH_OFFSET = A
        };


        float pitch(float p);
        float key2freq(int note , int octave);
        float key2freq(Key key);
    }

    float SINUS(float f, float t);
    float SQUARE(float f, float t, float dc);
    float TRIANGLE(float f, float t, float dc);
    float SAW(float f, float t, float dc);
    float WHITENOISE(float f, float t, float dc);

}

#endif //CODETRACKER_CODE_TRACKER_HPP
