//
// Created by Abdulmajid NASSER on 24/08/2020.
//
#include "code_tracker.hpp"

namespace  CodeTracker{

    Key::Key(char n, char o) {this->note = n; this->octave = o;}
    ADSR::ADSR(float A, float D, float S, float R) { this->attack = A; this->decay = D; this->sustain = S; this->release = R;}


    namespace Notes {
        float pitch(float p){return pow(1.059460646483f, p) * 440.0f;}

        float key2freq(char note , char octave){
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