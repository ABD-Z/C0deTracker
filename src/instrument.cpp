//
// Created by Abdulmajid, Olivier NASSER on 27/08/2020.
//

#include "code_tracker.hpp"

namespace CodeTracker{

    Instrument::Instrument() = default;

    Instrument::Instrument(Oscillator *osc) {this->osc = osc;}
    Instrument::Instrument(Oscillator* osc, float global_volume){this->osc = osc; this->global_volume = global_volume;}

    Instrument::~Instrument() {printf("destroying instrument\n");delete this->osc;printf("destroying instrument end\n");}

    Oscillator *Instrument::get_oscillator() const {return this->osc;}

    float Instrument::play(float a, Key k, double t) {
        return this->global_volume * this->osc->oscillate(a, Notes::key2freq(k), t, this->osc->getDutycycle(),
                                                          this->osc->getPhase());
    }
    float Instrument::play(float a, uint_fast8_t note, uint_fast8_t octave, float t) {
        return this->global_volume * this->osc->oscillate(a, Notes::key2freq(note, octave), t, this->osc->getDutycycle(),
                                                          this->osc->getPhase());
    }

    float Instrument::play(float a, Key k, double t, double rt) {
        return this->global_volume * this->osc->oscillate(a, Notes::key2freq(k), t, rt, this->osc->getDutycycle(),
                                                                 this->osc->getPhase());
    }

    float Instrument::play(float a, uint_fast8_t note, uint_fast8_t octave, float t, float rt) {
        return this->global_volume * this->osc->oscillate(a, Notes::key2freq(note, octave), t, rt, this->osc->getDutycycle(),
                                                          this->osc->getPhase());
    }


}
