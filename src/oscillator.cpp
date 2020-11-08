//
// Created by Abdulmajid, Olivier NASSER on 25/08/2020.
//

#include "code_tracker.hpp"

namespace CodeTracker {

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
        return a * sinf(TWOPI * f * t + FMfeed);
    }

    float Oscillator::square(float a, float f, double t, float dc, float FMfeed) {
        double frac_ft = f*t - floor(t *f);
        return (frac_ft -dc < 0) ?  a * .5f + FMfeed : a * -.5f + FMfeed;
    }

    float Oscillator::triangle(float a, float f, double t, float dc, float FMfeed) {
        double T = 1.f / f;
        //t-T*floor(t/T)  <=> mod(t,T)
        double s = (t - T * floor(t / T) < dc * T * .5) ? t + FMfeed : -t + FMfeed;
        return  float(double(a) * (std::fmax(-(s - T * floor(s / T)) / (dc * T * 0.5f) + 1.f, -0.f) - 0.5f));
    }

    float Oscillator::saw(float a, float f, double t, float dc, float FMfeed) {
        double T = 1.f / f;
        //t-T*floor(t/T)  <=> mod(t,T)
        double s = (t - T * floor(t / T) < dc * T) ? t + FMfeed : 0.f + FMfeed;
        return  float(double(a) * ((s - T * floor(s / T)) / (dc * T) - 0.5f));
    }

    float Oscillator::whitenoise(float a, float f, double t, float dc, float FMfeed) {
        float s = this->sinus(a, f, t, 0.f, FMfeed)/dc;
        return  a * (s - floor(s) - 0.5f);
    }

    /*float Oscillator::whitenoise2(float a, float f, float t, float dc, float FMfeed) {
        float s = this->sinus(a, f, t/dc, 0.f, FMfeed);
        return  a * (s - floor(s) - 0.5f);
    }*/




}