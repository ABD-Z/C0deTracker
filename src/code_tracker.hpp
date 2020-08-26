//
// Created by Abdulmajid NASSER on 23/08/2020.
//

#ifndef CODETRACKER_CODE_TRACKER_HPP
#define CODETRACKER_CODE_TRACKER_HPP

#include <cmath>
#include <iostream>
#include <functional>

namespace CodeTracker {
#define TWOPI 6.283185307
#define MASTER_VOLUME 1.f


    struct Key{Key(char n, char o); char note, octave;};
    namespace Notes {
        enum {
            C, C_S, D, D_S, E, F, F_S, G, G_S, A, A_S, B, PITCHES_PER_OCTAVE, OCTAVE_PITCH_OFFSET = 4, NOTE_PITCH_OFFSET = A
        };


        float pitch(float p);
        float key2freq(char note , char octave);
        float key2freq(Key key);
    }

    struct ADSR{
        ADSR(float A, float D, float S, float R);
        float attack, decay, sustain, release;};

    enum{
        SINUS, SQUARE, TRIANGLE, SAW, WHITENOISE, WAVETYPES
    };

    class Oscillator{
    public :
        explicit Oscillator(char wavetype);
        virtual float oscillate(float a, float f, float t, float dc);
        virtual float oscillate(float a, float f, float t, float dc, float p);
        void setWavetype(char wavetype);
    private:
        char wavetype = SINUS;
        float sinus(float a, float f, float t, float dc);
        float square(float a, float f, float t, float dc);
        float triangle(float a, float f, float t, float dc);
        float saw(float a, float f, float t, float dc);
        float whitenoise(float a, float f, float t, float dc);
        //function table
        std::vector<std::function<float(Oscillator&, float, float, float, float)>> wavefunc_table =
            {&Oscillator::sinus, &Oscillator::square, &Oscillator::triangle, &Oscillator::saw, &Oscillator::whitenoise};

        virtual float handle_amp_envelope(float t) = 0;
        virtual void set_release(bool r) = 0;


    };

    class PSG : public Oscillator{
    public:
        PSG(char wavetype, ADSR amp_enveloppe);
        float oscillate(float a, float f, float t, float dc) override;
        float oscillate(float a, float f, float t, float dc, float p) override;
    private:
        ADSR amp_envelope = ADSR(100.f, 0.0f, 1.0f, 1.0f);
        float handle_amp_envelope(float t) override;
        void set_release(bool r) override;
    protected:
        bool release = false;
    };
}

#endif //CODETRACKER_CODE_TRACKER_HPP
