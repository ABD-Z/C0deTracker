//
// Created by Administrateur on 25/08/2020.
//

#include "code_tracker.hpp"

namespace CodeTracker {

    Oscillator::Oscillator(char wavetype){
        this->wavetype = wavetype;
    }

    void Oscillator::setWavetype(char wavetype) {
        this->wavetype = wavetype;
    }

    float Oscillator::oscillate(float a, float f, float t, float dc) {
        return this->wavefunc_table[this->wavetype](*this, a, f, t, dc);
    }

    float Oscillator::oscillate(float a, float f, float t, float dc, float p) {
        return this->wavefunc_table[this->wavetype](*this, a, f, t - p*1./f, dc);
    }

    float Oscillator::sinus(float a, float f, float t, float dc) {
        return a * sinf(TWOPI * f * t);
    }

    float Oscillator::square(float a, float f, float t, float dc) {
        float T = 1.f / f;
        //t-T*floor(t/T)  <=> mod(t,T)
        return (t - T * floor(t / T) < dc * T) ?  a * .5f :  a * -.5f;
    }

    float Oscillator::triangle(float a, float f, float t, float dc) {
        float T = 1.f / f;
        //t-T*floor(t/T)  <=> mod(t,T)
        float s = (t - T * floor(t / T) < dc * T * .5) ? t : -t;
        return  a * (std::fmax(-(s - T * floor(s / T)) / (dc * T * 0.5f) + 1.f, -0.f) - 0.5f);
    }

    float Oscillator::saw(float a, float f, float t, float dc) {
        float T = 1.f / f;
        //t-T*floor(t/T)  <=> mod(t,T)
        float s = (t - T * floor(t / T) < dc * T) ? t : 0.f;
        return  a * ((s - T * floor(s / T)) / (dc * T) - 0.5f);
    }

    float Oscillator::whitenoise(float a, float f, float t, float dc) {
        float s = this->sinus(a, f, t, 0) / dc;
        return  a * (s - floor(s) - 0.5f);
    }



}