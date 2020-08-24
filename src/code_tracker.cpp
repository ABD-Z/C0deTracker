//
// Created by Abdulmajid NASSER on 24/08/2020.
//
#include "code_tracker.hpp"

namespace  CodeTracker{

    namespace Notes {
        float pitch(float p){return pow(1.059460646483f, p) * 440.0f;}

        float key2freq(int note , int octave){
            //4A == 440 HZ = pitch 0
            //-12 pitch == 3A == 220 HZ
            //+12
            return pitch(float(PITCHES_PER_OCTAVE
                                  *(octave - OCTAVE_PITCH_OFFSET)
                                  +(note - NOTE_PITCH_OFFSET)
                                  ));
        }

        float key2freq(Key key){
            return pitch(float(PITCHES_PER_OCTAVE
                               *(key.octave - OCTAVE_PITCH_OFFSET)
                               +(key.note - NOTE_PITCH_OFFSET)
                               ));
        }
    }

    float SINUS(float f, float t) {
        return sinf(TWOPI*f*t);
    }

    float SQUARE(float f, float t, float dc){
        float T = 1.f/f;
        //t-T*floor(t/T)  <=> mod(t,T)
        return (t-T*floor(t/T) < dc*T) ? .5 : -.5;
    }

    float TRIANGLE(float f, float t, float dc){
        float T = 1.f/f;
        //t-T*floor(t/T)  <=> mod(t,T)
        float s = (t-T*floor(t/T)  < dc*T*.5) ? t : -t;
        return std::fmax(-(s-T*floor(s/T) )/(dc*T*0.5f) + 1.f, -0.f) - 0.5f;
    }

    float SAW(float f, float t, float dc){
        float T = 1.f/f;
        //t-T*floor(t/T)  <=> mod(t,T)
        float s = (t-T*floor(t/T)  < dc*T) ? t : 0.f;
        return (s-T*floor(s/T) )/(dc*T) -0.5f;
    }

    float WHITENOISE(float f, float t, float dc){
        float s = SINUS(f,t)/dc;
        return s-floor(s) - 0.5f;
    }

}
