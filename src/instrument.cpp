//
// Created by Administrateur on 27/08/2020.
//

#include "code_tracker.hpp"

namespace CodeTracker{
    Instrument::Instrument(Oscillator *osc) {this->osc = osc;}
    Instrument::Instrument(Oscillator* osc, float global_volume){this->osc = osc; this->global_volume = global_volume;}

    Instrument::~Instrument() {delete this->osc;}

    Oscillator *Instrument::get_oscillator() {return this->osc;}

    float Instrument::play(float a, Key k, float t) {
        return this->global_volume * this->osc->oscillate(a, Notes::key2freq(k), t, this->osc->getDutycycle(),
                                                          this->osc->getPhase());
    }

    float Instrument::play(float a, char note, char octave, float t) {
        return this->global_volume * this->osc->oscillate(a, Notes::key2freq(note, octave), t, this->osc->getDutycycle(),
                                                          this->osc->getPhase());
    }
}
