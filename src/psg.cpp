//
// Created by Administrateur on 26/08/2020.
//
#include "code_tracker.hpp"

namespace CodeTracker {
    PSG::PSG(char wavetype, ADSR amp_enveloppe) : Oscillator(wavetype) {this->amp_envelope = amp_enveloppe;}
    PSG::PSG(char wavetype, float dc, ADSR amp_enveloppe) : Oscillator(wavetype, dc) {this->amp_envelope = amp_enveloppe;}
    PSG::PSG(char wavetype, float dc, float p, ADSR amp_enveloppe) : Oscillator(wavetype, dc, p) {this->amp_envelope = amp_enveloppe;}

    float PSG::handle_amp_envelope(float t) {
        float output = MASTER_VOLUME;
        float attack_amp = fmin(MASTER_VOLUME, t*this->amp_envelope.attack);
        if(attack_amp < MASTER_VOLUME){//attack
            output *= attack_amp;
        }else{
            (this->release) ? output *= fmax(0.f, 1.f - t*this->amp_envelope.release) : output *= fmax(this->amp_envelope.sustain, 1.f - t * this->amp_envelope.decay);
        }
        return output;
    }

    float PSG::oscillate(float a, float f, float t, float dc) {
        return this->handle_amp_envelope(t) * Oscillator::oscillate(a, f, t, dc);
    }

    float PSG::oscillate(float a, float f, float t, float dc, float p) {
        return this->handle_amp_envelope(t) * Oscillator::oscillate(a, f, t, dc, p);
    }

    void PSG::set_release(bool r) {
        this->release = true;
    }

    ADSR* PSG::get_amp_envelope() {
        return (&this->amp_envelope);
    }




}