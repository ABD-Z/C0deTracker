//
// Created by Abdulmajid, Olivier NASSER on 25/08/2020.
//


/**
 * @file oscillator.cpp
 * @brief Oscillator class code (SINUS, SQUARE, TRIANGLE and WHITENOISE)
 * @see code_tracker.hpp
 * @author Abdulmajid, Olivier NASSER
 * @version 0.1
 * @date 25/08/2020
 */

#include "../include/c0de_tracker.hpp"

namespace C0deTracker {

    Oscillator::Oscillator(uint_fast8_t wavetype){ this->wavetype = wavetype;}
    Oscillator::Oscillator(uint_fast8_t wavetype, float dc) {this->wavetype = wavetype; this->dutycycle = dc;}
    Oscillator::Oscillator(uint_fast8_t wavetype, float dc, float p) {this->wavetype = wavetype; this->dutycycle = dc; this->phase = p;}

    Oscillator::~Oscillator() = default;

    void Oscillator::setWavetype(uint_fast8_t wavetype) { this->wavetype = wavetype;}
    uint_fast8_t Oscillator::getWavetype() {return this->wavetype;}

    void Oscillator::setDutycycle(float dc) { this->dutycycle = dc;}
    float Oscillator::getDutycycle() {return this->dutycycle;}

    void Oscillator::setPhase(float p) { this->phase = p;}
    float Oscillator::getPhase() {return this->phase;}

    float Oscillator::oscillate(float a, float f, double t, float dc, float p) {
        switch(this->wavetype){
            case SINUS:
                return Oscillator::sinus(a, f, t - p*1./f, dc, 0.f);
            case SQUARE:
                return Oscillator::square(a, f, t - p*1./f, dc, 0.f);
            case TRIANGLE:
                return Oscillator::triangle(a, f, t - p*1./f, dc, 0.f);
            case SAW:
                return Oscillator::saw(a, f, t - p*1./f, dc, 0.f);
            case WHITENOISE:
                return Oscillator::whitenoise(a, f, t - p*1./f, dc, 0.f);
            case WHITENOISE2:
                return Oscillator::whitenoise2(a, f, t - p*1./f, dc, 0.f);
            default:
                return 0;
        }
    }

    float Oscillator::sinus(float a, float f, double t, float dc, float FMfeed) {
        double frac_ft = f * t - floor(t/(1.f/f));
        return (frac_ft - dc < 0) ? a * 0.5 * sinf(TWOPI * f * t + FMfeed) : - a * 0.5 *(sinf(TWOPI * f * t + FMfeed));
        //return a * 0.5 * sinf(TWOPI * f * t + FMfeed);
    }

    float Oscillator::square(float a, float f, double t, float dc, float FMfeed) {
        double frac_ft = f * t - floor(t/(1.f/f));
        return (frac_ft -dc < 0) ?  a * .5f + FMfeed : a * -.5f + FMfeed;
    }

    float Oscillator::triangle(float a, float f, double t, float dc, float FMfeed) {
        //t-T*floor(t/T)  <=> mod(t,T)
        double frac_ft = f * t - floor(t*f);
        double s = (frac_ft - dc * .5 < 0) ? t + FMfeed : -t + FMfeed;
        double frac_fs = f*s - floor(f*s);
        return  float(double(a) * (std::fmax(1. - 2*frac_fs/dc, -0.) - 0.5));
    }

    float Oscillator::saw(float a, float f, double t, float dc, float FMfeed) {
        double T = 1.f / f;
        //t-T*floor(t/T)  <=> mod(t,T)
        double frac_ft = f * t - floor( t / (1.f/f));
        double s = (frac_ft - dc < 0) ? t + FMfeed : 0.f + FMfeed;
        double frac_fs = f * s - floor( s / (1.f/f));
        return  float(double(a) * ( frac_fs / (dc) - 0.5));

    }

    float Oscillator::whitenoise(float a, float f, double t, float dc, float FMfeed) {
        float s = Oscillator::sinus(a, f, t, 0.f, FMfeed)/(dc*0.5);
        //s = this->sinus(a, f, t/(dc), 0.f, FMfeed);
        return  a * (s - floor(s) - 0.5);
    }

    float Oscillator::whitenoise2(float a, float f, double t, float dc, float FMfeed) {
        float s = Oscillator::sinus(a, f, t/dc, 0.f, FMfeed);
        return  a * (s - floor(s) - 0.5);
    }


    void Osc::setWavetype(uint_fast8_t wavetype) { this->wavetype = wavetype;}
    uint_fast8_t Osc::getWavetype() const {return this->wavetype;}

    void Osc::setDutycycle(float dc) { this->dutycycle = dc;}
    float Osc::getDutycycle() const {return this->dutycycle;}

    void Osc::setPhase(float p) { this->phase = p;}
    float Osc::getPhase() const {return this->phase;}

    void Osc::setPitch(float p){this->phase = p;}
    float Osc::getPitch() const {return this->pitch;}

    void Osc::setVolume(float v) {this->volume = v;}
    float Osc::getVolume() const {return this->volume;}

    float Osc::oscillate(float a, float f, double t, float dc, float p, float FMfeed) {
        float amp = a * this->getVolume();
        float frq = f + Notes::pitch2freq(this->getPitch());
        float phs = p + this->getPhase();
        switch(this->wavetype){
            case SINUS:
                return Osc::sinus(amp, frq, t - phs*1./frq, dc, FMfeed);
            case SQUARE:
                return Osc::square(amp, frq, t - phs*1./frq, dc, FMfeed);
            case TRIANGLE:
                return Osc::triangle(amp, frq, t - phs*1./frq, dc, FMfeed);
            case SAW:
                return Osc::saw(amp, frq, t - phs*1./frq, dc, FMfeed);
            case WHITENOISE:
                return Osc::whitenoise(amp, frq, t - phs*1./frq, dc, FMfeed);
            case WHITENOISE2:
                return Osc::whitenoise2(amp, frq, t - phs*1./frq, dc, FMfeed);
            default:
                return 0;
        }
    }

    float Osc::oscillate(float a, float f, double t, float dc, float p) {
        return this->oscillate(a,f,t,dc,p,0);
    }

    float Osc::oscillate(float a, float f, double t, double rt, float dc, float p, float FMfeed) {
        return this->handleAmpEnvelope(t, rt) * this->oscillate(a, f, t, dc, p, FMfeed);
    }

    float Osc::oscillate(float a, float f, double t, double rt, float dc, float p) {
        return this->oscillate(a,f,t,rt,dc,p,0);
    }

    float Osc::sinus(float a, float f, double t, float dc, float FMfeed) {
        double frac_ft = f * t - floor(t/(1.f/f));
        return (frac_ft - dc < 0) ? a * 0.5 * sinf(TWOPI * f * t + FMfeed) : - a * 0.5 *(sinf(TWOPI * f * t + FMfeed));
        //return a * 0.5 * sinf(TWOPI * f * t + FMfeed);
    }

    float Osc::square(float a, float f, double t, float dc, float FMfeed) {
        double frac_ft = f * t - floor(t/(1.f/f));
        return (frac_ft -dc < 0) ?  a * .5f + FMfeed : a * -.5f + FMfeed;
    }

    float Osc::triangle(float a, float f, double t, float dc, float FMfeed) {
        //t-T*floor(t/T)  <=> mod(t,T)
        double frac_ft = f * t - floor(t*f);
        double s = (frac_ft - dc * .5 < 0) ? t + FMfeed : -t + FMfeed;
        double frac_fs = f*s - floor(f*s);
        return  float(double(a) * (std::fmax(1. - 2*frac_fs/dc, -0.) - 0.5));
    }

    float Osc::saw(float a, float f, double t, float dc, float FMfeed) {
        double T = 1.f / f;
        //t-T*floor(t/T)  <=> mod(t,T)
        double frac_ft = f * t - floor( t / (1.f/f));
        double s = (frac_ft - dc < 0) ? t + FMfeed : 0.f + FMfeed;
        double frac_fs = f * s - floor( s / (1.f/f));
        return  float(double(a) * ( frac_fs / (dc) - 0.5));

    }

    float Osc::whitenoise(float a, float f, double t, float dc, float FMfeed) {
        float s = Osc::sinus(a, f, t, 0.f, FMfeed)/(dc*0.5);
        //s = this->sinus(a, f, t/(dc), 0.f, FMfeed);
        return  a * (s - floor(s) - 0.5);
    }

    float Osc::whitenoise2(float a, float f, double t, float dc, float FMfeed) {
        float s = Osc::sinus(a, f, t/dc, 0.f, FMfeed);
        return  a * (s - floor(s) - 0.5);
    }

    const ADSR *Osc::getAmpEnvelope() {
        return &this->amp_envelope;
    }

    void Osc::setAttack(float A) {
        this->amp_envelope.attack = A;
    }

    void Osc::setDecay(float D) {
        this->amp_envelope.decay = D;
    }

    void Osc::setSustain(float S) {
        this->amp_envelope.sustain = S;
    }

    void Osc::setRelease(float R) {
        this->amp_envelope.release = R;
    }

    void Osc::setRelease(bool r) {
        this->release = r;
    }

    bool Osc::isReleased() const {
        return this->release;
    }

    float Osc::handleAmpEnvelope(double t, double rt) {
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

    void Osc::setOscillatorParams(Instrument_Data *instrdata) {
        this->setAttack(instrdata->amp_envelope.attack); this->setDecay(instrdata->amp_envelope.decay);
        this->setRelease(instrdata->amp_envelope.release); this->setSustain(instrdata->amp_envelope.sustain);
        this->setWavetype(instrdata->wavetype); this->setDutycycle(instrdata->duty_cycle);
        this->setPhase(instrdata->phase); this->setVolume(instrdata->volume); this->setPitch(instrdata->pitch);
        this->current_envelope_amplitude = 0.0f;
        this->setRelease(false);
    }


}