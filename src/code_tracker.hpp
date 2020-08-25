//
// Created by Abdulmajid NASSER on 23/08/2020.
//

#ifndef CODETRACKER_CODE_TRACKER_HPP
#define CODETRACKER_CODE_TRACKER_HPP

#include <cmath>
#include <iostream>
#include <functional>

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

    enum{
        SINUS, SQUARE, TRIANGLE, SAW, WHITENOISE, WAVETYPES
    };

    class Oscillator{
    public :
        explicit Oscillator(char wavetype);
        float oscillate(float a, float f, float t, float dc);
        void setWavetype(char wavetype);
    private:
        char wavetype = SINUS;
        float sinus(float a, float f, float t, float dc);
        float square(float a, float f, float t, float dc);
        float triangle(float a, float f, float t, float dc);
        float saw(float a, float f, float t, float dc);
        float whitenoise(float a, float f, float t, float dc);

        //function table
        std::vector<std::function<float(Oscillator&, float, float, float, float)>> wavefunc_table =
            {&Oscillator::sinus, &Oscillator::square, &Oscillator::triangle, &Oscillator::saw, &Oscillator::whitenoise};



    };
}

#endif //CODETRACKER_CODE_TRACKER_HPP
