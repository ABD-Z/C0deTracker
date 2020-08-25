//
// Created by Abdulmajid NASSER on 24/08/2020.
//
#include "code_tracker.hpp"

namespace  CodeTracker{

    namespace Notes {
        float pitch(float p){return pow(1.059460646483f, p) * 440.0f;}

        float key2freq(int note , int octave){
            //A4 == 440 HZ = pitch 0
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
}
