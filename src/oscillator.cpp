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
        return this->wavefunc_table[this->wavetype](*this, a, f, t - p*1./f, dc, 0.f);
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
        float s = this->sinus(a, f, t, 0.f, FMfeed)/(dc*0.5);
        //s = this->sinus(a, f, t/(dc), 0.f, FMfeed);
        return  a * (s - floor(s) - 0.5);
    }

    float Oscillator::whitenoise2(float a, float f, float t, float dc, float FMfeed) {
        float s = this->sinus(a, f, t/dc, 0.f, FMfeed);
        return  a * (s - floor(s) - 0.5);
    }




}