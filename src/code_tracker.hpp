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
        explicit Oscillator(char wavetype, float dc);
        explicit Oscillator(char wavetype, float dc, float p);
        void set_wavetype(char wavetype); char get_wavetype();
        void set_dutycycle(float dc); float get_dutycycle();
        void set_phase(float p); float get_phase();
        virtual float oscillate(float a, float f, float t, float dc);
        virtual float oscillate(float a, float f, float t, float dc, float p);
        virtual ADSR* get_amp_envelope() = 0;
    private:
        char wavetype = SINUS; float dutycycle = 0.5f; float phase = 0.0f;
        float sinus(float a, float f, float t, float dc, float FMfeed);
        float square(float a, float f, float t, float dc, float FMfeed);
        float triangle(float a, float f, float t, float dc, float FMfeed);
        float saw(float a, float f, float t, float dc, float FMfeed);
        float whitenoise(float a, float f, float t, float dc, float FMfeed);
        //function table
        std::vector<std::function<float(Oscillator&, float, float, float, float, float)>> wavefunc_table =
            {&Oscillator::sinus, &Oscillator::square, &Oscillator::triangle, &Oscillator::saw, &Oscillator::whitenoise};

        virtual float handle_amp_envelope(float t) = 0;
        virtual void set_release(bool r) = 0;

    };

    class PSG : public Oscillator{
    public:
        PSG(char wavetype, ADSR amp_enveloppe);
        PSG(char wavetype, float dc, ADSR amp_enveloppe);
        PSG(char wavetype, float dc, float p, ADSR amp_enveloppe);
        float oscillate(float a, float f, float t, float dc) override;
        float oscillate(float a, float f, float t, float dc, float p) override;
        ADSR* get_amp_envelope() override;
    private:
        ADSR amp_envelope = ADSR(100.f, 0.0f, 1.0f, 1.0f);
        float handle_amp_envelope(float t) override;
        void set_release(bool r) override;
    protected:
        bool release = false;
    };

    class Instrument{
    public:
        explicit Instrument(Oscillator* osc);
        Instrument(Oscillator* osc, float global_volume);
        Oscillator* get_oscillator();
        float play(float a, Key k,float t);
        float play(float a, char note, char octave, float t);
    private:
        float global_volume = 1.0f;
        Oscillator* osc;
    };

    struct Instruction{
        uint8_t instrument_index; Key key; float volume; uint32_t* effects;//efect tab
        Instruction(uint8_t instrument, Key k, float vol);
        Instruction(uint8_t instrument, char note, char octave, float vol);
        Instruction(uint8_t instrument, Key k, float vol, uint32_t* effects);
        Instruction(uint8_t instrument, char note, char octave, float vol, uint32_t *effects);
    };
}

#endif //CODETRACKER_CODE_TRACKER_HPP
