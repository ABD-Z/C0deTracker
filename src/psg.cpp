//
// Created by Abdulmajid, Olivier NASSER on 26/08/2020.
//

/**
 * @file psg.cpp
 * @brief PSG (Pulse Sound Generator) class code
 * @see code_tracker.hpp
 * @author Abdulmajid, Olivier NASSER
 * @version 0.1
 * @date 26/08/2020
 */


#include "../include/code_tracker.hpp"

namespace CodeTracker {
    PSG::PSG(uint_fast8_t wavetype) : Oscillator(wavetype) {}
    PSG::PSG(uint_fast8_t wavetype, ADSR amp_enveloppe) : Oscillator(wavetype) { this->amp_envelope = amp_enveloppe;}
    PSG::PSG(uint_fast8_t wavetype, float dc, ADSR amp_enveloppe) : Oscillator(wavetype, dc) { this->amp_envelope = amp_enveloppe;}
    PSG::PSG(uint_fast8_t wavetype, float dc, float p, ADSR amp_enveloppe) : Oscillator(wavetype, dc, p) { this->amp_envelope = amp_enveloppe;}

    PSG::~PSG() {Oscillator::~Oscillator();}

    float PSG::handleAmpEnvelope(double t, double rt) {
        float output = MASTER_VOLUME;
        float attacktime = MASTER_VOLUME / this->amp_envelope.attack;
        float attack_amp = fmin(MASTER_VOLUME, t*this->amp_envelope.attack);
        if(this->release && rt >= 0.f){//release
            output *= fmax(0.f, this->current_envelope_amplitude - (rt) * this->amp_envelope.release);
        }else{
            if(attack_amp < MASTER_VOLUME){//attack
                output *= attack_amp;
                this->current_envelope_amplitude = output;
            }else{//decay sustain
                output *= fmax(this->amp_envelope.sustain, MASTER_VOLUME - (t - attacktime) * this->amp_envelope.decay);
                this->current_envelope_amplitude = output;
            }
        }
        return output;
    }



    float PSG::oscillate(float a, float f, double t, double rt, float dc, float p) {
        return this->handleAmpEnvelope(t, rt) * Oscillator::oscillate(a, f, t, dc, p);;
    }

    float PSG::oscillate(float a, float f, double t, float dc, float p) {
        return this->oscillate(a, f, t, -1.f, dc, p);
    }

    void PSG::setRelease(bool r) {
        this->release = r;
    }

    ADSR* PSG::getAmpEnvelope() {
        return (&this->amp_envelope);
    }

    bool PSG::isReleased() {
        return this->release;
    }

    PSG * PSG::clone() {
        return new PSG(Oscillator::getWavetype(), Oscillator::getDutycycle(), Oscillator::getPhase(), this->amp_envelope);
    }



}