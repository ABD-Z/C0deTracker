//
// Created by Abdulmajid, Olivier NASSER on 27/08/2020.
//

#include "../include/c0de_tracker.hpp"

/**
 * @file instrument.cpp
 * @brief Instrument class code
 * @see code_tracker.hpp
 * @author Abdulmajid, Olivier NASSER
 * @version 0.1
 * @date 27/08/2020
 */

namespace C0deTracker{

    Instrument::Instrument() = default;

    Instrument::Instrument(Oscillator *osc) {this->osc = osc;}
    Instrument::Instrument(Oscillator* osc, float global_volume){this->osc = osc; this->global_volume = global_volume;}

    Instrument::~Instrument() {delete this->osc;}

    Oscillator *Instrument::get_oscillator() const {return this->osc;}

    float Instrument::play_key(float a, Key k, double t) {
        return this->global_volume * this->osc->oscillate(a, Notes::key2freq(k), t, this->osc->getDutycycle(),
                                                          this->osc->getPhase());
    }
    float Instrument::play(float a, float note, double octave, double t) {
        return this->global_volume * this->osc->oscillate(a, Notes::key2freq(note, octave), t, this->osc->getDutycycle(),
                                                          this->osc->getPhase());
    }

    float Instrument::play_key(float a, Key k, double t, double rt) {
        return this->global_volume * this->osc->oscillate(a, Notes::key2freq(k), t, rt, this->osc->getDutycycle(),
                                                                 this->osc->getPhase());
    }

    float Instrument::play(float a, float note, float octave, double t, double rt) {
        return this->global_volume * this->osc->oscillate(a, Notes::key2freq(note, octave), t, rt, this->osc->getDutycycle(),
                                                          this->osc->getPhase());
    }

    float Instrument::play_pitch(float a, float p, double t) {
        return this->global_volume * this->osc->oscillate(a, Notes::pitch2freq(p), t, this->osc->getDutycycle(),
                                                          this->osc->getPhase());
    }

    float Instrument::play_pitch(float a, float p, double t, double rt) {
        return this->global_volume * this->osc->oscillate(a, Notes::pitch2freq(p), t, rt, this->osc->getDutycycle(),
                                                          this->osc->getPhase());
    }

    Instrument *Instrument::clone() {
        return new Instrument(this->osc->clone(), this->global_volume);
    }

    Instrument_Data::Instrument_Data(uint_fast8_t wavetype, ADSR amp_envelope, float volume, float pitch,float duty_cycle, float phase) {
        this->wavetype = wavetype;
        this->amp_envelope = amp_envelope;
        this->volume = volume; this->pitch = pitch; this->duty_cycle = duty_cycle; this->phase = phase;
    }
}

