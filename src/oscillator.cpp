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
    uint_fast8_t Oscillator::custom_wave_counter = 0;

    Oscillator::WaveCallback Oscillator::wavefunctable[MAX_CUSTOM_WAVE] = {nullptr};

    void Oscillator::registerCustomWaveFunc(uint_fast8_t id, WaveCallback wave_func) {
        if (Oscillator::custom_wave_counter < MAX_CUSTOM_WAVE && id - WAVETYPES < MAX_CUSTOM_WAVE) {
            Oscillator::wavefunctable[id - WAVETYPES] = std::move(wave_func);
            ++Oscillator::custom_wave_counter;
        }
    }

    void Oscillator::registerCustomWaveFunc(uint_fast8_t id, MathFxCallback fx, double bound0, double bound1) {
        if (Oscillator::custom_wave_counter < MAX_CUSTOM_WAVE && id - WAVETYPES < MAX_CUSTOM_WAVE) {
            float m = FLT_MAX;
            float M = FLT_MIN;

            assert(bound1 > bound0 && "bound1 must be greater than bound0");

            double bounddif = bound1 - bound0;
            double steps = 100000;
            for(int i = 0; i <= steps; ++i) {
                float r = fx((i/steps) * bounddif + bound0);
                if (r < m)
                    m = r;
                if (r > M)
                    M = r;
            }

            assert(M > m && "The portion of function must have different values of minimum and maximum");

            float num = (M + m)/2;
            float denom = (M - m) / 2;

            Oscillator::registerCustomWaveFunc(id,
                                               [fx, bound0, bounddif, num, denom](float a, float f, double t, float dc, float FMfeed) -> float {
                double frac_ft = f * t + FMfeed - floor(f * t + FMfeed);
                return a * (fx(frac_ft * bounddif + bound0) - num) / denom;
            });

        }
    }

    void Oscillator::setWavetype(uint_fast8_t wavetype) { this->wavetype = wavetype;}
    uint_fast8_t Oscillator::getWavetype() const {return this->wavetype;}

    void Oscillator::setDutycycle(float dc) { this->dutycycle = dc;}
    float Oscillator::getDutycycle() const {return this->dutycycle;}

    void Oscillator::setPhase(float p) { this->phase = p;}
    float Oscillator::getPhase() const {return this->phase;}

    void Oscillator::setPitch(float p){ this->pitch = p;}
    float Oscillator::getPitch() const {return this->pitch;}

    void Oscillator::setVolume(float v) { this->volume = v;}
    float Oscillator::getVolume() const {return this->volume;}

    void Oscillator::setFeedbackLevel(float fb) { this->feedback_level = fb;}
    float Oscillator::getFeedbackLevel() const {return this->feedback_level;}


    float Oscillator::oscillate(float a, float p, double t, float FMfeed) {
        float amp = a * this->getVolume();
        if(amp == MIN_VOLUME){return MIN_VOLUME;}
        float frq = this->pitch2freq(p, t) * this->mul_freq;
        float dc = this->getDutycycle();
        float phs = this->current_phase;
        double x = t - this->time_offset - phs*1./frq;
        switch(this->wavetype){
            case SINUS:
                return Oscillator::sinus(amp, frq, x, dc, FMfeed);
            case SQUARE:
                return Oscillator::square(amp, frq, x, dc, FMfeed);
            case TRIANGLE:
                return Oscillator::triangle(amp, frq, x, dc, FMfeed);
            case TRIANGLE2:
                return Oscillator::triangle2(amp, frq, x, dc, FMfeed);
            case SAW:
                return Oscillator::saw(amp, frq, x, dc, FMfeed);
            case WHITENOISE:
                return this->getVolume() * Oscillator::whitenoise(a, frq, x, dc, FMfeed);
            case WHITENOISE2:
                return this->getVolume() * Oscillator::whitenoise2(a, frq, x, dc, FMfeed);
            default:
                if (this->wavetype >= WAVETYPES && this->wavetype - WAVETYPES < Oscillator::custom_wave_counter) {
                    return Oscillator::wavefunctable[this->wavetype - WAVETYPES](a, frq, x, dc, FMfeed);
                }
                return MIN_VOLUME;
        }
    }

    float Oscillator::oscillate(float a, float p, double t) {
        return this->oscillate(a,p,t,-1,0);
    }

    float Oscillator::oscillate(float a, float p, double t, double rt) {
        return this->oscillate(a,p,t,rt,0);
    }

    float Oscillator::oscillate(float a, float p, double t, double rt, float FMfeed) {
        this->feedback_val = this->handleAmpEnvelope(t, rt) * this->oscillate(a, p, t, this->feedback_level*this->feedback_val + FMfeed);
        return this->feedback_val;
    }

    float Oscillator::sinus(float a, float f, double t, float dc, float FMfeed) {
        double frac_ft = f * t - floor(t*f);
        return (frac_ft - dc < 0) ? a * sinf(TWOPI * f * t + FMfeed) : - a * (sinf(TWOPI * f * t + FMfeed));
    }

    float Oscillator::square(float a, float f, double t, float dc, float FMfeed) {
        float frac_ft = (f * t + FMfeed) - floor(f * t + FMfeed);
        return (frac_ft -dc < 0) ?  a : -a;
    }

    float Oscillator::triangle(float a, float f, double t, float dc, float FMfeed) {
        //t-T*floor(t/T)  <=> mod(t,T)
        float frac_ft = (f * t + FMfeed) - floor(f * t + FMfeed);
        float s;
        if (frac_ft < 0.5f) {
            s = (frac_ft - 0.5f*(1 - dc) > 0) ? (frac_ft - 0.5f*(1 - dc))/dc: 0;
        } else{
            s =  (-frac_ft + 0.5f*(1 + dc) > 0) ? (-frac_ft + 0.5f*(1 + dc))/dc: 0;
        }
        return a * (4 * s - 1);
    }

    float Oscillator::triangle2(float a, float f, double t, float dc, float FMfeed) {
        //t-T*floor(t/T)  <=> mod(t,T)
        float frac_ft = (f * t + FMfeed) - floor(f * t + FMfeed);
        float s;
        if (frac_ft < 0.5f) {
            s = (frac_ft - 0.5f*(1 - dc) > 0) ? frac_ft: 0;
        } else{
            s =  (-frac_ft + 0.5f*(1 + dc) > 0) ? -frac_ft+1: 0;
        }
        return a * (4 * s - 1);
    }

    float Oscillator::saw(float a, float f, double t, float dc, float FMfeed) {
        //t-T*floor(t/T)  <=> mod(t,T)
        float frac_ft = (f * t + FMfeed) - floor(f * t + FMfeed);
        double s = (frac_ft - dc < 0) ? frac_ft/dc : 0.f;
        return a * (2 * s - 1);
    }

    float Oscillator::whitenoise(float a, float f, double t, float dc, float FMfeed) {
        float s = Oscillator::sinus(a * 0.5f, f, t, 0.f, FMfeed) / (dc * 0.5);
        return  2*a * (s - floor(s) - 0.5f);
    }

    float Oscillator::whitenoise2(float a, float f, double t, float dc, float FMfeed) {
        float s = Oscillator::sinus(a * 0.5f, f, t / (dc), 0.f, FMfeed);
        return  2*a * (s - floor(s) - 0.5f);
    }

    const ADSR *Oscillator::getAmpEnvelope() {
        return &this->amp_envelope;
    }

    void Oscillator::setAttack(float A) {
        this->amp_envelope.A.speed = A;
    }

    void Oscillator::setDecay(float D) {
        this->amp_envelope.D.speed = D;
    }

    void Oscillator::setSustain(float S) {
        this->amp_envelope.S = S;
    }

    void Oscillator::setRelease(float R) {
        this->amp_envelope.R.speed = R;
    }

    void Oscillator::setRelease(bool r) {
        this->release = r;
    }

    bool Oscillator::isReleased() const {
        return this->release;
    }

    float Oscillator::handleAmpEnvelope(double t, double rt) {
        if (this->release && rt >= 0) {
            // Release state
            float R = this->amp_envelope.R.speed;
            float ceildlvl = (ceil(this->current_envelope_amplitude*100))/100;
            return (rt <= ceildlvl/R) ? fmax(MIN_VOLUME, this->current_envelope_amplitude - this->amp_envelope.R.easing(rt * R * 1/ceildlvl) * ceildlvl) : MIN_VOLUME;
        } else {

            float A = this->amp_envelope.A.speed;
            double A_end = MAX_VOLUME/A;

            if (t < A_end) {
                // Attack phase
                this->current_envelope_amplitude = fmin(MAX_VOLUME, this->amp_envelope.A.easing(t * A));
            } else {
                float D = this->amp_envelope.D.speed;
                float S = this->amp_envelope.S;
                double D_end = A_end + (MAX_VOLUME - S)/D;
                if (t < D_end) {
                    // Decay phase
                    this->current_envelope_amplitude = fmax(S, MAX_VOLUME - this->amp_envelope.D.easing((t - A_end) * D * 1/(MAX_VOLUME - S)) * (MAX_VOLUME - S));
                } else {
                    // Sustain phase
                    return S;
                }
            }
        }
        return this->current_envelope_amplitude;
    }

    void Oscillator::setOscillatorData(const Oscillator_Data* oscd) {
        this->current_envelope_amplitude = 0.0f;
        this->amp_envelope = oscd->amp_envelope;
        this->setWavetype(oscd->wavetype); this->setDutycycle(oscd->duty_cycle);
        this->setVolume(oscd->volume); this->setPitch(oscd->pitch);
        this->setFeedbackLevel(oscd->feedback_level);
        this->setMulFreq(oscd->mul_freq);
        switch (oscd->wavetype) {
            case TRIANGLE:
            case TRIANGLE2:
                this->setPhase(oscd->phase - 0.25f);
                break;
            default:
                this->setPhase(oscd->phase);
        }
        this->current_phase = this->getPhase();
        this->setRelease(false);
    }

    float Oscillator::pitch2freq(float pitch, double time) {
        pitch += this->getPitch();
        if(this->current_pitch == pitch) {
            return this->current_frequency;
        }
        else {
            if (time > 0) {
                double ft = this->current_frequency * (time - this->time_offset);
                double frac_ft = ft - floor(ft);
                this->current_phase = this->current_phase - frac_ft - floor( this->current_phase - frac_ft);
                this->time_offset = time;
            }
            this->current_pitch = pitch;
            this->current_frequency = Notes::pitch2freq(pitch);
            return this->current_frequency;
        }
    }

    void Oscillator::resetPhaseTimeOffset() {
        this->current_phase = this->getPhase();
        this->time_offset = 0;
    }

    void Oscillator::setMulFreq(float mul_f) {
        this->mul_freq = mul_f;
    }

}