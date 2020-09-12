//
// Created by Abdulmajid, Olivier NASSER on 23/08/2020.
//

#ifndef CODETRACKER_CODE_TRACKER_HPP
#define CODETRACKER_CODE_TRACKER_HPP

#include <cmath>
#include <iostream>
#include <functional>


namespace CodeTracker {
#define TWOPI 6.283185307
#define MASTER_VOLUME 1.f

    struct Key;
    struct ADSR;
    class Oscillator;
    class PSG;
    class Instrument;
    struct Instruction;
    struct Pattern;
    class Track;
    class Channel;

    struct Key{Key(); Key(uint8_t n, uint8_t o); uint8_t note, octave;};
    namespace Notes {
        enum {C, C_S, D, D_S, E, F, F_S, G, G_S, A, A_S, B, PITCHES_PER_OCTAVE, OCTAVE_PITCH_OFFSET = 4, NOTE_PITCH_OFFSET = A};

        float pitch(float p);
        float key2freq(uint8_t note , uint8_t octave);
        float key2freq(Key key);
    }

    struct ADSR{
        ADSR(float A, float D, float S, float R);
        float attack, decay, sustain, release;
    };

    enum{SINUS, SQUARE, TRIANGLE, SAW, WHITENOISE, WAVETYPES};

    class Oscillator{
    public :
        explicit Oscillator(uint8_t wavetype);
        explicit Oscillator(uint8_t wavetype, float dc);
        explicit Oscillator(uint8_t wavetype, float dc, float p);
        virtual ~Oscillator();
        void setWavetype(uint8_t wavetype); uint8_t getWavetype();
        void setDutycycle(float dc); float getDutycycle();
        void setPhase(float p); float getPhase();

        virtual float oscillate(float a, float f, float t, float dc, float p);
        virtual float oscillate(float a, float f, float t, float rt, float dc, float p) = 0;
        virtual ADSR* getAmpEnvelope() = 0;
        virtual void setRelease(bool r) = 0;
        virtual bool isReleased() = 0;
    private:
        uint8_t wavetype = SINUS; float dutycycle = 0.5f; float phase = 0.0f;
        float sinus(float a, float f, float t, float dc, float FMfeed);
        float square(float a, float f, float t, float dc, float FMfeed);
        float triangle(float a, float f, float t, float dc, float FMfeed);
        float saw(float a, float f, float t, float dc, float FMfeed);
        float whitenoise(float a, float f, float t, float dc, float FMfeed);
        //function table
        std::vector<std::function<float(Oscillator&, float, float, float, float, float)>> wavefunc_table =
            {&Oscillator::sinus, &Oscillator::square, &Oscillator::triangle, &Oscillator::saw, &Oscillator::whitenoise};

        virtual float handleAmpEnvelope(float t, float rt) = 0;


    };

    class PSG : public Oscillator{
    public:
        explicit PSG(uint8_t wavetype);
        PSG(uint8_t wavetype, ADSR amp_enveloppe);
        PSG(uint8_t wavetype, float dc, ADSR amp_enveloppe);
        PSG(uint8_t wavetype, float dc, float p, ADSR amp_enveloppe);
        ~PSG() override;

        float oscillate(float a, float f, float t, float dc, float p) override;
        float oscillate(float a, float f, float t, float rt, float dc, float p) override;
        ADSR* getAmpEnvelope() override;
        void setRelease(bool r) override;
        bool isReleased() override;
    private:
        ADSR amp_envelope = ADSR(100.f, 0.0f, 1.0f, 1.0f);
        float handleAmpEnvelope(float t, float rt) override;
    protected:
        bool release = false;
        float current_envelope_amplitude = 0.f;
    };

    class Instrument{
    public:
        Instrument();
        explicit Instrument(Oscillator* osc);
        Instrument(Oscillator* osc, float global_volume);
        ~Instrument();
        [[nodiscard]] Oscillator* get_oscillator() const;
        float play(float a, Key k,float t);
        float play(float a, uint8_t note, uint8_t octave, float t);
        float play(float a, Key k,float t, float rt);
        float play(float a, uint8_t note, uint8_t octave, float t, float rt);

    private:
        float global_volume = 1.0f;
        Oscillator* osc = nullptr;
    };

    enum{RELEASE = 244, CONTINUE};
    struct Instruction{
        uint8_t instrument_index{}; Key key; float volume{}; uint32_t* effects{};//efect tab
        Instruction();
        Instruction(uint8_t instrument, Key k, float vol);
        Instruction(uint8_t instrument, uint8_t note, uint8_t octave, float vol);
        Instruction(uint8_t instrument, Key k, float vol, uint32_t* effects);
        Instruction(uint8_t instrument, uint8_t note, uint8_t octave, float vol, uint32_t *effects);
        ~Instruction();
    };

    struct Pattern{
        Instruction** instructions; uint8_t rows;
        explicit Pattern(uint8_t rows);
        ~Pattern();
    };



    class Track{
    public:
        Track(float clk, float basetime, float speed, uint8_t rows, uint8_t frames, uint8_t channels,
              Instrument** instruments_bank, uint8_t numb_of_instruments, Pattern** track_patterns, uint8_t** pattern_indices);
        ~Track();
        float play(float t, Channel* chan);
    private:
        float clk , basetime, speed, step;
        uint8_t  rows, frames;
        uint8_t channels;
        float volume = 1.0f, pitch = 1.0f;
        Instrument** instruments_bank;
        uint8_t instruments;
        Pattern** track_patterns;
        uint8_t** pattern_indices;//new uint_8[channels*frames]
        float duration;
    };

    class Channel{
    public:
        Channel();
        explicit Channel(uint8_t number);
        [[nodiscard]] uint8_t getNumber() const;
        [[nodiscard]] bool isEnable() const; void enable(); void disable();
        [[nodiscard]] float getSpeed() const; void setSpeed(float speed);
        [[nodiscard]] float getPitch() const; void setPitch(float pitch);
        [[nodiscard]] float getVolume() const; void setVolume(float volume);
        [[nodiscard]] Instruction *getLastInstruction() const; void setLastInstruction(Instruction *lastInstruction);
        [[nodiscard]] Track *getTrack() const; void setTrack(Track *track);
        [[nodiscard]] float getTime() const; void setTime(float time);
        [[nodiscard]] float getTimeRelease() const; void setTimeRelease(float time);
        [[nodiscard]] bool isReleased() const; void setRelease(bool r);
    private:
        static uint8_t chancount;
        bool enable_sound = true;
        float volume = 1.0f, pitch = 1.0f, speed = 1.0f;
        Instruction* last_instruction = nullptr;
        Track* track = nullptr;
        float time = 0.0;
        bool released = false;
        float time_release = 0.0;
        uint8_t number;
    };
}

#endif //CODETRACKER_CODE_TRACKER_HPP
