//
// Created by Abdulmajid, Olivier NASSER on 23/08/2020.
//

/* C0deTracker - Copyright (c) Abdulmajid, Olivier NASSER
 * C0deTracker header file containing everything you need yo create your music :
 * Keys, ADSR, Oscillator classes, Instrument, Pattern, Track and Channel.
 * See the example.hpp for more details about how to use C0deTracker.
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from
 * the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not claim
 * that you wrote the original software. If you use this software in a product,
 * an acknowledgment in the product documentation would be appreciated
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 */

/**
 * @file code_tracker.hpp
 * @brief C0deTracker header. Include it in your project to use all functionalities.
 * @author Abdulmajid, Olivier NASSER
 * @version 0.1
 * @date 23/08/2020
 */

#ifndef CODETRACKER_C0DE_TRACKER_HPP
#define CODETRACKER_C0DE_TRACKER_HPP

#include <cmath>
#include <cstdio>
#include <cstdint>
#include <vector>


namespace C0deTracker {
#define TWOPI 6.283185307
#define MAX_VOLUME 1.f
#define MIN_VOLUME 0.f
#define MIN_PITCH -57 // K(C, 0) = 16.352 Hz
#define MAX_PITCH 50 // K(B, 8) = 7902.133 Hz


    struct Key;
    struct ADSR;
    class Osc;
    struct Instrument_Data;
    struct Instruction;
    struct Pattern;
    class Track_Data;
    class Track;
    class Channel;
    class Editor;
    class GlobalFXs;
    class ChannelFXs;
    struct SlideFX;
    struct SpeedDepthFX;
    struct TransposeFX;
    struct PortamentoFX;

    /**
     * @brief This structure represents a piano key which is represented by its note (C, C#, D, D#, E, F, F#, G, G#, A, A#, B ; see Notes enumeration)
     * and its octave (from 0 to 8).
     * @see Notes
     */
    struct Key{
        /**
         * @brief Default constructor of Key. Create an empty key of value 255 (CONTINUE) for the note and the octave.
         */
        Key();
        /**
         * @brief Constructor used to provide the corresponding note and octave of the key instantly.
         * @param n note of the key. See enumeration in Notes namespace.
         * @param o octave of the key, from 0 to 8 (above 8 should not be hearable).
         */
        Key(float n, float o); float note, octave;
    };

    namespace Notes {
        /** @brief Notes enumeration in the American way.
         *  @details Values of semitones go from 0 (C, Do) to 11 (B, Si)\n
         *  C = Do = 0\n
         *  C_S (C#) = Do# = 1\n
         *  D = Ré = 2\n
         *  D_S (D#) = Ré# = 3\n
         *  E = Mi = 4\n
         *  F = Fa = 5\n
         *  F_S (F#) = Fa# = 6\n
         *  G = Sol = 7\n
         *  G_S (G#) = Sol# = 8\n
         *  A = La = 9\n
         *  A_S (A#) = La# = 10\n
         *  B = Si = 11\n
         *  RELEASE, with 244 as value, is used to trigger release state of the instrument.\n
         *  CONTINUE, with 255 as value, is used to fill empty values, such as empty instruments, empty volume and empty key.\n
         *  The other three values in the enumeration are used in function key2freq(uint8_t note, uint8_t octave). You don't have to use them.
         *  @note For each instrument bank, you can create in it (RELEASE -1) different instruments, or 243 maximum.
         */
        enum KeysUtilities{C, C_S, D, D_S, E, F, F_S, G, G_S, A, A_S, B,
                PITCHES_PER_OCTAVE, OCTAVE_PITCH_OFFSET = 4, NOTE_PITCH_OFFSET = A, RELEASE = 244, CONTINUE,
                Do = C, Do_d, Re, Re_d, Mi, Fa, Fa_d, Sol, Sol_d, La, La_d, Si};

        /**
         * @param p pitch2freq
         * @return frequency of the pitch2freq in float
         * @note Pitch 0 corresponds to 440 Hz.
         */
        float pitch2freq(float p);

        /**
         * @brief converts a key in float
         * @param k Key (note)
         * @return pitch of the key in float
         */
        float key2pitch(Key k);

        /**
         * @brief converts a key (note and octave separatly) in float
         * @param note
         * @param octave
         * @return pitch in float
         */
        float key2pitch(float note, float octave);

        /**
         * @brief This function gives the frequency of a given note from a given octave
         * @param note
         * @see KeysUtilities
         * @param octave
         * @return frequency of the note and octave in float
         * @note This function calls pitch(float p). A4 (440 Hz) corresponds to pitch2freq 0.
         */
        float key2freq(float note , float octave);
        /**
         * @brief This function gives the frequency of a given key
         * @param key (see structure Key)
         * @return frequency of the key in float
         * @note This function calls key2freq(uint8_t note , uint8_t octave)
         */
        float key2freq(Key key);
    }

    /**
     * @brief ADSR structure contains attack, decay, sustain and release components (all in float) used to manipulates waveform's
     * envelope (mainly for amplitude).
     *
     * @see C0deTracker::Oscillator
     */
    struct ADSR{
        ADSR(float A, float D, float S, float R);
        float attack, decay, sustain, release;
    };

    /**
     * @brief This enumeration stores the primitive waveforms values. You should provide to your Oscillator one of these
     * values in order to select the corresponding waveform function
     * @see C0deTracker::Oscillator
     */
    enum Waveforms{SINUS, SQUARE, TRIANGLE, TRIANGLE2, SAW, WHITENOISE, WHITENOISE2, WAVETYPES};


    /**
     * @brief Abstract class used to generate simple waveform such as SINUS, SQUARE, TRIANGLE, SAW and WHITENOISE over
     * time. Oscillator handles basic stuff : amplitude (a), frequency (f), phase (p), duty cycle (dc), and even frequency
     * modulation feed (FMfeed) for FM synth support.
     * @note This class should not be instantiated. PSG class is one of its specialization.
     * @see C0deTracker::PSG, C0deTracker::Waveforms
     */
    class Osc{
    public :
        explicit Osc() = default;
        ~Osc() = default;

        void setOscillatorParams(Instrument_Data* instrdata);

        /**
         * @brief set the wavetype of the oscillator to generate the corresponding waveform
         * @param wavetype 0, 1, 2, 3, 4, 5 => SINUS, SQUARE, TRIANGLE, SAW, WHITENOISE, WHITENOISE2
         * @see Waveforms
         */
        void setWavetype(uint_fast8_t wavetype);

        /**
         * @brief return the value of the corresponding wavetype
         */
        uint_fast8_t getWavetype() const;

        /**
         * @brief set the duty cycle of the waveform
         * @param dc duty cycle of the waveform
         */
        void setDutycycle(float dc);
        /**
         *
         * @return get the duty cycle of the waveform
         */
        float getDutycycle() const;

        /**
         * @brief Set the phase of the waveform. The value set is multiplied by 1/frequency (percentage of waveform period)
         * @param p  phase of the waveform.
         */
        void setPhase(float p);
        /**
         *
         * @return the phase in float
         */
        float getPhase() const;

        void setVolume(float v);

        float getVolume() const;

        void setPitch(float p);

        float getPitch() const;

        /**
         * @brief Generates corresponding waveform selected.
         * @param a Amplitude
         * @param f Frequency
         * @param t Time
         * @return Signal amplitude at time t with the given duty cycle dc and phase p.
         */
        float oscillate(float a, float f, double t);
        /**
         * @brief Same as previous oscillate, but with release time to handle release envelope. This function is fully abstract, it is implemented in PSG.
         * @param a Amplitude
         * @param f Frequency
         * @param rt Release time
         * @param t Time
         * @return Signal amplitude at time t with the given duty cycle dc and phase p.
         */
        float oscillate(float a, float f, double t, double rt);

        void setAttack(float A);
        void setDecay(float D);
        void setSustain(float S);
        void setRelease(float R);

        /**
         * @brief Get pointer to structure holding ADSR values for envelope
         * @return pointer to ADSR struct
         * @see C0deTracker::ADSR
         */
        const ADSR* getAmpEnvelope();
        /**
         * @brief Set release state of the oscillator.
         * @param r boolean to set the release state
         */
        void setRelease(bool r) ;
        /**
         * @brief Check if the oscillator is in release state or not
         * @return release member
         */
        bool isReleased() const;

        float pitch2freq(float pitch, double time);

        void resetPhaseTimeOffset();
    private:
        uint_fast8_t wavetype = SINUS; float dutycycle = 0.5f; float phase = 0.0f; float pitch = 0.0f;
        float volume = 1.0f;
        ADSR amp_envelope = ADSR(100.f, 0.0f, 1.0f, 1.0f);
        bool release = false;
        float current_pitch = -1;
        float current_frequency = -1;
        float current_phase = 0.0f;
        float current_envelope_amplitude = 0.f; /**<Used to calculate envelope notably for release state*/
        double time_offset = 0;

        /**
         * @brief Generates corresponding waveform selected.
         * @param a Amplitude
         * @param f Frequency
         * @param t Time
         * @param FMfeed signal feeding for FM
         * @return Signal amplitude at time t with the given duty cycle dc and phase p.
         */
        float oscillate(float a, float f, double t, float FMfeed);
        /**
         * @brief Same as previous oscillate, but with release time to handle release envelope. This function is fully abstract, it is implemented in PSG.
         * @param a Amplitude
         * @param f Frequency
         * @param rt Release time
         * @param t Time
         * @param FMfeed signal feeding for FM
         * @return Signal amplitude at time t with the given duty cycle dc and phase p.
         */
        float oscillate(float a, float f, double t, double rt, float FMfeed);

        static float sinus(float a, float f, double t, float dc, float FMfeed);
        static float square(float a, float f, double t, float dc, float FMfeed);
        static float triangle(float a, float f, double t, float dc, float FMfeed);
        static float triangle2(float a, float f, double t, float dc, float FMfeed);
        static float saw(float a, float f, double t, float dc, float FMfeed);
        static float whitenoise(float a, float f, double t, float dc, float FMfeed);
        static float whitenoise2(float a, float f, double t, float dc, float FMfeed);
        float handleAmpEnvelope(double t, double rt);
    };


    struct Instrument_Data{
        uint_fast8_t wavetype = SINUS;
        ADSR amp_envelope = ADSR(100.f, 0.0f, 1.0f, 1.0f);
        float volume = 1.0f; float pitch = 0.0f; float duty_cycle = 0.5f; float phase = 0.0f;
        Instrument_Data() = default;
        Instrument_Data(uint_fast8_t wavetype, ADSR amp_envelope, float volume, float pitch, float duty_cycle, float phase);
        void setData(uint_fast8_t wavetype, ADSR amp_envelope, float volume, float pitch, float duty_cycle, float phase);
    };

    /**
     * @brief Instruction structure represents the instruction you type to make your music (instrument index, volume, note,
     * effects). It should be written in Pattern structure.
     *
     * @see Pattern
     */
    struct Instruction{
        uint_fast8_t instrument_index{}; Key key; float volume{}; uint_fast32_t** effects{};//effect tab
        /**
         * @brief Default constructor to create empty instruction
         */
        Instruction();
        Instruction(uint_fast8_t instrument, Key k, float vol);
        Instruction(uint_fast8_t instrument, float note, float octave, float vol);
        Instruction(uint_fast8_t instrument, Key k, float vol, uint_fast32_t** effects);
        Instruction(uint_fast8_t instrument, float note, float octave, float vol, uint_fast32_t** effects);
        /**
         * @brief Destructor.
         */
        ~Instruction() = default;
    };

    /**
     * @brief This structure contains the array of Instructions. Patterns are fed to the Track.
     * @see Instruction , Track
     */
    struct Pattern{
        Instruction* instructions; /**<Array of Instruction*/
        uint_fast8_t rows; /**< Size of the row*/
        uint_fast8_t n_fx;
        /**
         * @brief Pattern initializer
         * @param rows size of the patterns
         * @param number_of_fx max fx supported in this pattern of a corresponding channel
         */
        Pattern(uint_fast8_t rows, uint_fast8_t number_of_fx);

        /**
         * @brief Delete instructions dynamic allocation
         */
        ~Pattern();
    };

    struct AbstractFX {
        float val = 0;

        virtual void process(const double t, const float clock, const float speed) = 0;
        virtual void reset() = 0;
        virtual float getValue() const;
        virtual bool isActive() const = 0;
    };

    struct SlideFX : AbstractFX {
        const float MIN, MAX, INIT_VAL;
        double time_step = 0;
        float slide = 0;

        SlideFX(const float min, const float max, const float init_val);
        void process(const double t, const float clock, const float speed) override;
        void reset() override;
        bool isActive() const override;
    };

    struct SpeedDepthFX : AbstractFX {
        const float MIN;
        double start_time = 0;
        float speed = 0;
        float depth = 0;

        explicit SpeedDepthFX(const float min);
        void process(const double t, const float clock, const float speed) override;
        void reset() override;
        bool isActive() const override;
    };

    struct TransposeFX : SlideFX {
        uint_fast8_t repeat = 0;
        uint_fast8_t semitones = 0;
        uint_fast8_t semitones_counter = 0;
        uint_fast8_t delay = 0;

        TransposeFX(const float min, const float max, const float init_val);
        void process(const double t, const float clock, const float speed) override;
        bool isActive() const override;
    };

    struct PortamentoFX : SlideFX {
        int_fast8_t sign = 0;

        PortamentoFX(const float min, const float max, const float init_val);
        void reset() override;
        float getValue() const override;
    };

    struct ArpeggioFX : SlideFX {
        static const uint_fast8_t SIZE = 6;
        uint_fast8_t tab[SIZE]{0, 0, 0, 0, 0, 0};

        ArpeggioFX(const float min, const float max, const float init_val);
        void process(const double t, const float clock, const float speed) override;
        float getValue() const override;
    };

    struct CountableRepeatableFX : AbstractFX {
        uint_fast8_t delay = 0;
        uint_fast8_t number = 0;
        uint_fast8_t repeat = 0;
        double time_step = 0;
        uint_fast8_t counter = 0;


        void process(const double t, const float clock, const float speed) override;
        bool isActive() const override;
        void reset() override;
    };

    struct RetriegFX : CountableRepeatableFX {
        void process(const double t, const float clock, const float speed) override;
        bool isActive() const override;
    };

    class GlobalFXs {
    public:
        GlobalFXs();
    protected:
        SlideFX volume{MIN_VOLUME, MAX_VOLUME, 1};
        SlideFX panning{MIN_VOLUME, MAX_VOLUME, 0.5};
        SlideFX pitch{MIN_PITCH, MAX_PITCH, 0};
        SpeedDepthFX tremolo{1};
        SpeedDepthFX vibrato{0};
        std::vector<AbstractFX*> effects_table;
        enum fx_indices{PITCH_SLIDE_UP, PITCH_SLIDE_DOWN, VIBRATO, SET_PITCH,
                SET_VOLUME, VOLUME_SLIDE_UP, VOLUME_SLIDE_DOWN, TREMOLO, SET_PANNING,
                PANNING_SLIDE_RIGHT, PANNING_SLIDE_LEFT, GLOBAL_FXS};
        std::vector<uint_fast8_t> fx_codes = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x0D, 0x0E};

        virtual bool decode_fx(const uint_fast32_t fx, const double t);
        virtual void update_fx(const double t, const float clock, const float speed);
        virtual void reset_fxs();

    };

    class ChannelFXs : public GlobalFXs {
    public:
        ChannelFXs();
        void initDelayedFXsBuffer(uint_fast8_t nFX);

        virtual ~ChannelFXs();

    protected:
        TransposeFX transpose{MIN_PITCH, MAX_PITCH, 0};
        PortamentoFX portamento{0, MAX_PITCH - MIN_PITCH, 0};
        ArpeggioFX arpeggio{0, ArpeggioFX::SIZE, 0};
        RetriegFX retrieg;
        CountableRepeatableFX delay;
        CountableRepeatableFX release;

        uint_fast32_t* delayed_fxs = nullptr;
        uint_fast8_t delayed_fx_counter = 0;
        uint_fast8_t delayed_fxs_size = 0;

        enum fx_indices_channel{TRANSPOSE=GLOBAL_FXS, PORTAMENTO, ARPEGGIO, RETRIEG, DELAY_RELEASE, RELEASE};
        bool decode_fx(const uint_fast32_t fx, const double t) override;
    };

    class Track : GlobalFXs {
    public:
        Track() = default;

        explicit Track(Track_Data* td);

        /**
         * @brief free everything related to the track, patterns, patterns indices, instruments
         */
        ~Track();

        /**
         * @brief main function called at each time to calculate the corresponding sample of the track
         * @param double t time in second
         * @param Channel* chan pointers to the channels allocated dynamically by the user
         * @param uint_fast8_t size_of_chans number of channels created by the user, otherwise the size of the array chan
         * @return pointer to array of float for left and right speaker
         */
        float* play(double t);

        void changeTrack(Track_Data* td);

        void resetState();

        float getClock() const;

        float getSpeed() const;

        float getDuration() const;


    private:
        void setTrack_Data(Track_Data* td);
        bool decode_fx(uint_fast32_t fx, double t);
        Track_Data* track_data = nullptr;
        C0deTracker::Channel* chans = nullptr;

        float clk; float speed; float step;
        float duration;

        uint_fast8_t row_counter = 0, frame_counter = 0;
        double time_advance = 0.0;

        bool readFx = true;

        bool branch = false;
        uint_fast8_t frametojump = 0;
        uint_fast8_t rowtojump = 0;

        bool stop = false;

        void inline calcStereoSampleFromChannel(uint_fast8_t index, double time, float* output);

        void inline decodeAllFXsFromChannel(int_fast8_t index, Instruction *current_instruction, double time);

        static bool inline isVolumeValid(float volume);

        static bool inline isNoteReleased(Instruction *instruction);

        void inline calcTracksStereoSample(float *output);

        bool inline isInstrumentValid(uint_fast8_t instru_index);

        bool inline isNewInstrumentFromChannel(int_fast8_t chan_index, Instruction *instru);
    };


    class Track_Data{
    public:
        Track_Data()=default;
        virtual ~Track_Data();
        virtual void load_data();
        void free_data();
        bool is_data_loaded();
        const char* getName();
        friend Track;
    protected:
        void setName(const char* name);
        void setSizeDimensions(const uint_fast8_t rows, const uint_fast8_t frames, const uint_fast8_t channels,  const uint_fast8_t* fx_per_chan);
        void setTimeDimensions(const float clk, const float basetime, const float speed);
        void setInstrumentsDataBank(const Instrument_Data* instruments_data_bank, uint_fast8_t n_instr);
        void setPatterns(const Pattern* const* patterns);
        void setPatternsIndices(const uint_fast8_t* patterns_indices);
        void useGlobalInstruments();
        void setGlobalInstrumentsDataBank(const Instrument_Data *global_instruments_data_bank, uint_fast8_t n_instr);
    private:
        bool data_loaded;
        bool use_global_inst = false;
        char* name = "_";
        float clk = 60.f, basetime = 1.f, speed = 3.f, step;
        uint_fast8_t  rows = 0, frames = 0;
        uint_fast8_t channels = 0;
        Instrument_Data* instruments_data_bank;
        uint_fast8_t instruments;
        Pattern** track_patterns;
        uint_fast8_t* pattern_indices;//new uint_8[channels*frames]
        float duration = 0;
        const uint_fast8_t *fx_per_chan;
    };

    /**
     * @brief This class "processes" sound. It is independent from the track. Each track pattern has its dedicated channel.
     * A channel can be interrupted to generate sound not from the track.
     *
     * @see Track
     */
    class Channel : public ChannelFXs{
    public:
        /**
         * @brief create a channel. Each channel created has it is own number
         */
        Channel()=default;


        ~Channel() override =default;

        /**
         * @return if the channel is enabled to play_single_channel sound
         */
        bool isEnable() const;
        /**
         * @brief enable channel sound processing
         */
        void enable();
        /**
         * @brief disable channel sound processing
         */
        void disable();

        /**
         * @return the pitch of the channel
         */
        float getPitch() const;

        /**
         * @brief set the pitch of the channel
         * @param pitch to set
         */
        void setPitch(float pitch);

        /**
         * @return get the volume of the channel
         */
        float getVolume() const;

        /**
         * @brief set the volume of the channel
         * @param volume to set
         */
        void setVolume(float volume);

        /**
         * @return get the pointer to the last non empty instruction (from the track)
         */
        Instruction *getLastInstructionAddress() const;
        /**
         * @brief store the pointer to the last non empty instruction
         * @param lastInstruction pointer to the instruction in pattern
         */
        void setLastInstructionAddress(Instruction *lastInstructionAddress);

        void setTrack(Track* track);
        Track *getTrack() const;


        /**
         *
         * @return time when the channel encounter a new
         */
        double getTime() const;

        /**
         * @brief set time when channel encounter a new note
         * @param time
         */
        void setTime(double time);

        /**
         *
         * @return time when release is triggered
         */
        double getTimeRelease() const;

        /**
         * @brief set the time when ² is triggered
         * @param time
         */
        void setTimeRelease(double time);
        /**
         *
         * @return a boolean to know if the channel is released or not.
         */
        bool isReleased() const;

        /**
         * @brief set release state to boolean r
         * @param r a boolean (true release)
         */
        void setRelease(bool r);

        /**
         * @return the instruction state copied of the channel (which could be modified without dynamically in exe)
         */
        const Instruction *getInstructionState() const;

        /**
         * @brief copy the current instruction in Channel
         * @param instruc pointer to Instruction from patterns song
         */
        void setInstructionState(Instruction* instruc);

        /**
         * @brief modify the volume of the copied instruction in Channel
         * @param a volume in float
         */
        void setVolumeInstructionState(float a);

        float play_pitch(float a, float p, double t);

        float play_pitch(float a, float p, double t, double rt);

        void resetState();

        friend float* Track::play(double t);

        bool decode_fx(uint_fast32_t fx, double t);

        void setInstrumentParams(Instrument_Data *instrument);

        float calcAmplitude();

        float calcPitch(double time);

        float getPanning() const;

    private:
        Instruction* last_instruct_address = nullptr;
        Track* track = nullptr;

        /**Channel state**/
        double time = 0.0;
        bool enable_sound = true;
        float  speed = 1.0f;
        bool released = false;
        double time_release = 0.0;
        Instruction instruct_state{};
        Osc oscillator = Osc();
        uint_fast8_t instrument_index = Notes::KeysUtilities::CONTINUE;

        Instruction* delayed_instruct_address = nullptr;
        Instrument_Data* delayed_instrument = nullptr;

        void update_fx(double t);

        void initFXs(Instruction *instruction, double time);

    };

    /**
     * @brief Editor class is used to ease the user while writing his song.
     * @note The user can create macros as shortcuts to the Editor's commands
     * @see example.cpp
     */
    class Editor{
    public:
        static void loadTrackProperties(uint_fast8_t number_of_rows, uint_fast8_t number_of_frames, uint_fast8_t number_of_channels, const uint_fast8_t *effects_per_chan);
        static Pattern** loadEmptyPatterns();
        static void prepare(Pattern **p, uint_fast8_t chanindx,  uint_fast8_t patternindx, uint_fast8_t instrumentnindx, float volume);
        static void prepare(uint_fast8_t chanindx, uint_fast8_t patternindx, uint_fast8_t instrumentnindx, float volume);
        static void prepare(uint_fast8_t chanindx, uint_fast8_t patternindx, float volume);
        static void storePatterns(Pattern **p);
        static void storeChannelIndex(uint_fast8_t chanindx);
        static void storePatternIndex(uint_fast8_t patternindx);
        static void storeInstrumentIndex(uint_fast8_t instrumentnindx);
        static void storeVolume(float volume);

        static void enterInstruction(uint_fast8_t instruction_index, C0deTracker::Key key);
        static void enterInstruction(uint_fast8_t instruction_index, uint_fast8_t instrument_index, C0deTracker::Key key);
        static void enterInstruction(uint_fast8_t instruction_index, C0deTracker::Key key, float volume);
        static void enterInstruction(uint_fast8_t instruction_index, uint_fast8_t instrument_index, C0deTracker::Key key, float volume);

        static void enterInstruction(uint_fast8_t instruction_index, C0deTracker::Key key, uint_fast32_t** effects);
        static void enterInstruction(uint_fast8_t instruction_index, C0deTracker::Key key, std::vector<uint_fast32_t> effects);
        static void enterInstruction(uint_fast8_t instruction_index, C0deTracker::Key key, uint_fast32_t effect);

        static void enterInstruction(uint_fast8_t instruction_index, uint_fast8_t instrument_index, C0deTracker::Key key, uint_fast32_t** effects);
        static void enterInstruction(uint_fast8_t instruction_index, uint_fast8_t instrument_index, C0deTracker::Key key, std::vector<uint_fast32_t> effects);
        static void enterInstruction(uint_fast8_t instruction_index, uint_fast8_t instrument_index, C0deTracker::Key key, uint_fast32_t effect);

        static void enterInstruction(uint_fast8_t instruction_index, C0deTracker::Key key, float volume, uint_fast32_t** effects);
        static void enterInstruction(uint_fast8_t instruction_index, C0deTracker::Key key, float volume, std::vector<uint_fast32_t> effects);
        static void enterInstruction(uint_fast8_t instruction_index, C0deTracker::Key key, float volume, uint_fast32_t effect);

        static void enterInstruction(uint_fast8_t instruction_index, uint_fast8_t instrument_index, C0deTracker::Key key, float volume, uint_fast32_t** effects);
        static void enterInstruction(uint_fast8_t instruction_index, uint_fast8_t instrument_index, C0deTracker::Key key, float volume, std::vector<uint_fast32_t> effects);
        static void enterInstruction(uint_fast8_t instruction_index, uint_fast8_t instrument_index, C0deTracker::Key key, float volume, uint_fast32_t effect);

        static void enterInstruction(uint_fast8_t instruction_index, float volume);

        static void enterInstruction(uint_fast8_t instruction_index, uint_fast32_t** effects);
        static void enterInstruction(uint_fast8_t instruction_index, float volume, uint_fast32_t** effects);
        static void enterInstruction(uint_fast8_t instruction_index, std::vector<uint_fast32_t> effects);
        static void enterInstruction(uint_fast8_t instruction_index, float volume, std::vector<uint_fast32_t> effects);
        static void enterInstruction(uint_fast8_t instruction_index, uint_fast32_t effect);
        static void enterInstruction(uint_fast8_t instruction_index, float volume, uint_fast32_t effect);

        static void release(uint_fast8_t instruction_index);
        static void release(uint_fast8_t instruction_index, float volume);
        static void release(uint_fast8_t instruction_index, uint_fast32_t** effects);
        static void release(uint_fast8_t instruction_index, float volume, uint_fast32_t** effects);
        static void release(uint_fast8_t instruction_index, std::vector<uint_fast32_t> effects);
        static void release(uint_fast8_t instruction_index, float volume, std::vector<uint_fast32_t> effects);
        static void release(uint_fast8_t instruction_index, uint_fast32_t effect);
        static void release(uint_fast8_t instruction_index, float volume, uint_fast32_t effect);

        static void storePatternsIndices(uint_fast8_t* pi);
        static uint_fast8_t* loadEmptyPatternsIndices();
        static void enterPatternIndice(uint_fast8_t channel, uint_fast8_t frame, uint_fast8_t pattern_indice);

    private:
        static Pattern **pattern;
        static uint_fast8_t* pattern_indices;
        static uint_fast8_t chan_index, pattern_index, instrument_index, frames;
        static float volume;
        static uint_fast8_t rows;
        static uint_fast8_t channels;
        static const uint_fast8_t *fx_per_chan;
    };


}

#endif //CODETRACKER_C0DE_TRACKER_HPP
