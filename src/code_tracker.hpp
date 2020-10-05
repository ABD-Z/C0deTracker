//
// Created by Abdulmajid, Olivier NASSER on 23/08/2020.
//

/* CodeTracker - Copyright (c) Abdulmajid, Olivier NASSER
 * CodeTracker header file containing everything you need yo create your music :
 * Key, ADSR, Oscillator classes, Instrument, Pattern, Track and Channel.
 * See the example.hpp for more details about how to use CodeTracker.
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
 * an acknowledgment in the product documentation would be appreciated but is
 * not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 */

/**
 * @file code_tracker.hpp
 * @brief CodeTracker header. Include it in your project to use all functionalities.
 * @author Abdulmajid, Olivier NASSER
 * @version 0.1
 * @date 23/08/2020
 */

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
        Key(uint_fast8_t n, uint_fast8_t o); uint_fast8_t note, octave;
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
        enum KeysUtilities{C, C_S, D, D_S, E, F, F_S, G, G_S, A, A_S, B, PITCHES_PER_OCTAVE, OCTAVE_PITCH_OFFSET = 4, NOTE_PITCH_OFFSET = A, RELEASE = 244, CONTINUE};

        /**
         * @param p pitch
         * @return frequency of the pitch in float
         * @note Pitch 0 corresponds to 440 Hz.
         */
        float pitch(float p);

        /**
         * @brief This function gives the frequency of a given note from a given octave
         * @param note
         * @see KeysUtilities
         * @param octave
         * @return frequency of the note and octave in float
         * @note This function calls pitch(float p). A4 (440 Hz) corresponds to pitch 0.
         */
        float key2freq(uint_fast8_t note , uint_fast8_t octave);
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
     * @see CodeTracker::Oscillator
     */
    struct ADSR{
        ADSR(float A, float D, float S, float R);
        float attack, decay, sustain, release;
    };

    /**
     * @brief This enumeration stores the primitive waveforms values. You should provide to your Oscillator one of these
     * values in order to select the corresponding waveform function
     * @see CodeTracker::Oscillator
     */
    enum Waveforms{SINUS, SQUARE, TRIANGLE, SAW, WHITENOISE, WAVETYPES};

    /**
     * @brief Abstract class used to generate simple waveform such as SINUS, SQUARE, TRIANGLE, SAW and WHITENOISE over
     * time. Oscillator handles basic stuff : amplitude (a), frequency (f), phase (p), duty cycle (dc), and even frequency
     * modulation feed (FMfeed) for FM synth support.
     * @note This class should not be instantiated. PSG class is one of its specialization.
     * @see CodeTracker::PSG, CodeTracker::Waveforms
     */
    class Oscillator{
    public :
        /**
         * @brief Basic constructor. By default, duty cycle is equal to 0.5 and phase to 0
         * @param wavetype of the oscillator
         */
        explicit Oscillator(uint_fast8_t wavetype);
        /**
         * @brief Second constructor.
         * @param wavetype of the oscillator
         * @param dc duty cycle
         */
        explicit Oscillator(uint_fast8_t wavetype, float dc);
        /**
         * @brief Second constructor.
         * @param wavetype of the oscillator
         * @param dc duty cycle
         * @param p phase
         */
        explicit Oscillator(uint_fast8_t wavetype, float dc, float p);
        virtual ~Oscillator();
        void setWavetype(uint_fast8_t wavetype); uint_fast8_t getWavetype();
        void setDutycycle(float dc); float getDutycycle();
        void setPhase(float p); float getPhase();
        /**
         * @brief Generates corresponding waveform selected.
         * @param a Amplitude
         * @param f Frequency
         * @param t Time
         * @param dc Duty cycle
         * @param p Phase
         * @return Signal amplitude at time t with the given duty cycle dc and phase p.
         */
        virtual float oscillate(float a, float f, double t, float dc, float p);
        /**
         * @brief Same as previous oscillate, but with release time to handle release envelope. This function is fully abstract, it is implemented in PSG.
         * @param a Amplitude
         * @param f Frequency
         * @param rt Release time
         * @param t Time
         * @param dc Duty cycle
         * @param p Phase
         * @return Signal amplitude at time t with the given duty cycle dc and phase p.
         */
        virtual float oscillate(float a, float f, double t, double rt, float dc, float p) = 0;
        /**
         * @brief Get pointer to structure holding ADSR values for envelope
         * @return pointer to ADSR struct
         * @see CodeTracker::ADSR
         */
        virtual ADSR* getAmpEnvelope() = 0;
        /**
         * @brief Set release state of the oscillator.
         * @param r boolean to set the release state
         */
        virtual void setRelease(bool r) = 0;
        /**
         * @brief Check if the oscillator is in release state or not
         * @return release member
         */
        virtual bool isReleased() = 0;
    private:
        uint_fast8_t wavetype = SINUS; float dutycycle = 0.5f; float phase = 0.0f;
        float sinus(float a, float f, double t, float dc, float FMfeed);
        float square(float a, float f, double t, float dc, float FMfeed);
        float triangle(float a, float f, double t, float dc, float FMfeed);
        float saw(float a, float f, double t, float dc, float FMfeed);
        float whitenoise(float a, float f, double t, float dc, float FMfeed);
        //function table
        std::vector<std::function<float(Oscillator&, float, float, double, float, float)>> wavefunc_table =
            {&Oscillator::sinus, &Oscillator::square, &Oscillator::triangle, &Oscillator::saw, &Oscillator::whitenoise};

        virtual float handleAmpEnvelope(double t, double rt) = 0;
    };

    /**
     * @brief PSG class inherit from Oscillator. This class is the specification of simple sound generator, Pulse Sound
     * Generator, used in old systems. FM operators are based on this class.
     *
     * @see Oscillator
     */
    class PSG : public Oscillator{
    public:
        explicit PSG(uint_fast8_t wavetype);
        PSG(uint_fast8_t wavetype, ADSR amp_enveloppe);
        PSG(uint_fast8_t wavetype, float dc, ADSR amp_enveloppe);
        PSG(uint_fast8_t wavetype, float dc, float p, ADSR amp_enveloppe);
        ~PSG() override;
        float oscillate(float a, float f, double t, float dc, float p) override;
        float oscillate(float a, float f, double t, double rt, float dc, float p) override;
        ADSR* getAmpEnvelope() override;
        void setRelease(bool r) override;
        bool isReleased() override;
    private:
        ADSR amp_envelope = ADSR(100.f, 0.0f, 1.0f, 1.0f);
        float handleAmpEnvelope(double t, double rt) override;
    protected:
        bool release = false;
        float current_envelope_amplitude = 0.f; /**<Used to calculate envelope notably for release state*/
    };

    /**
     * @brief Instrument class is a wrapper for one Oscillator (PSG, or FM). You will basically create your instruments
     * in a bank (simple array) that you give to your track.
     *
     * @see Track
     */
    class Instrument{
    public:
        Instrument();
        /**
         * @brief Creates an instrument which is based on an Oscillator (PSG, FM...)
         * @param osc Oscillator
         */
        explicit Instrument(Oscillator* osc);
        /**
         * @brief Creates an instrument which is based on an Oscillator (PSG, FM...)
         * @param osc Oscillator
         * @param global_volume specifies instrument global volume
         */
        Instrument(Oscillator* osc, float global_volume);
        /**
         * @brief Destructor
         */
        ~Instrument();
        /**
         * @brief Gets instrument core, which is the Oscillator
         * @return a pointer to Oscillator
         */
        [[nodiscard]] Oscillator* get_oscillator() const;
        /**
         * @brief Plays sounds at t time with a given key and amplitude
         * @param a Amplitude
         * @param k Structure Key (note, octave)
         * @param t Time
         * @return The signal
         */
        float play(float a, Key k, double t);
        float play(float a, uint_fast8_t note, uint_fast8_t octave, float t);
        /**
         * @brief Plays sounds at t time and rt release time with a given key and amplitude
         * @param a Amplitude
         * @param k Structure Key (note, octave)
         * @param t Time
         * @return The signal
         */
        float play(float a, Key k, double t, double rt);
        float play(float a, uint_fast8_t note, uint_fast8_t octave, float t, float rt);

    private:
        float global_volume = 1.0f;
        Oscillator* osc = nullptr;
    };

    /**
     * @brief Instruction structure represents the instruction you type to make your music (instrument index, volume, note,
     * effects). It should be written in Pattern structure.
     *
     * @see Pattern
     */
    struct Instruction{
        uint_fast8_t instrument_index{}; Key key; float volume{}; uint_fast32_t * effects{};//efect tab
        /**
         * @brief Default constructor to create empty instruction
         */
        Instruction();
        Instruction(uint_fast8_t instrument, Key k, float vol);
        Instruction(uint_fast8_t instrument, uint_fast8_t note, uint_fast8_t octave, float vol);
        Instruction(uint_fast8_t instrument, Key k, float vol, uint_fast32_t* effects);
        Instruction(uint_fast8_t instrument, uint_fast8_t note, uint_fast8_t octave, float vol, uint_fast32_t *effects);
        /**
         * @brief Destructor.
         */
        ~Instruction();
    };

    /**
     * @brief This structure contains the array of pointers of Instructions. Patterns are fed to the Track.
     * @see Instruction , Track
     */
    struct Pattern{
        Instruction** instructions; /**<Array of Instruction pointers*/
        uint_fast8_t rows; /**< Size of the row*/
        /**
         * @brief Pattern initializer
         * @param rows size of the patterns
         */
        explicit Pattern(uint_fast8_t rows);
        /**
         * @brief Delete instructions dynamic allocation.
         */
        ~Pattern();
    };

    /**
     * @brief Main class containing all the data needed to run a music. It should works in parallel with Channel.
     *
     * @see Channel
     */
    class Track{
    public:
        /**
         *@brief Track constructor which recquires all the needed parameters below
         * @param clk Clock frequency in Hz (60 in NTSC, 50 in PAL)
         * @param basetime the base time of the track, it multiplies the speed
         * @param speed the speed of the track, the tempo = speed * basetime / clk
         * @param rows Size of a pattern. Number of instructions in each pattern
         * @param frames Number of patterns
         * @param channels Number of channel related to polyphony
         * @param instruments_bank Pointer to the array containing the pointers to instruments
         * @param numb_of_instruments Size of instruments_bank
         * @param track_patterns Pointer to the array containing the pointers to the patterns which contains the instructions of the music
         * @param pattern_indices Pointer to the array containing the pointers to the indices of the patterns (to avoid writing several time same pattern)
         */
        Track(float clk, float basetime, float speed, uint_fast8_t rows, uint_fast8_t frames, uint_fast8_t channels,
              Instrument** instruments_bank, uint_fast8_t numb_of_instruments, Pattern** track_patterns, uint_fast8_t** pattern_indices);
        /**
         * @brief free everything related to the track, patterns, patterns indices, instruments
         */
        ~Track();
        /**
         * @brief main function called to play sound from a single channel from the track
         * @param t time
         * @param chan pointer to a Channel
         * @return the music at time t from the specific channel
         */
        float play_single_channel(double t, Channel* chan);

        float play(double t, Channel* chan);

        /**
         * @return number of channels dedicated fo the track
         */
        uint_fast8_t getNumberofChannels();
        /**
         * @return duration of the track
         */
        float getDuration();
    private:
        float clk , basetime, speed, step;
        uint_fast8_t  rows, frames;
        uint_fast8_t channels;
        float volume = 1.0f, pitch = 1.0f;
        Instrument** instruments_bank;
        uint_fast8_t instruments;
        Pattern** track_patterns;
        uint_fast8_t** pattern_indices;//new uint_8[channels*frames]
        float duration;
    };

    /**
     * @brief This class "processes" sound. It is independent from the track. Each track pattern has its dedicated channel.
     * A channel can be interrupted to generate sound not from the track.
     *
     * @see Track
     */
    class Channel{
    public:
        /**
         * @brief create a channel. Each channel created ha it is own number
         */
        Channel();
        /**
         * @brief create a channel with a specified number
         * @param number the number of the channel
         */
        explicit Channel(uint_fast8_t number);
        /**
         * @return number of the channel
         */
        [[nodiscard]] uint_fast8_t getNumber() const;
        /**
         * @return if the channel is enabled to play_single_channel sound
         */
        [[nodiscard]] bool isEnable() const;
        /**
         * @brief enable channel sound processing
         */
        void enable();
        /**
         * @brief disable channel sound processing
         */
        void disable();
        [[nodiscard]] float getSpeed() const; void setSpeed(float speed);
        [[nodiscard]] float getPitch() const; void setPitch(float pitch);
        [[nodiscard]] float getVolume() const; void setVolume(float volume);
        /**
         * @return get the pointer to the last non empty instruction (from the track)
         */
        [[nodiscard]] Instruction *getLastInstructionAddress() const;
        /**
         * @brief store the pointer to the last non empty instruction
         * @param lastInstruction pointer to the instruction in pattern
         */
        void setLastInstructionAddress(Instruction *lastInstructionAddress);
        [[nodiscard]] Track *getTrack() const; void setTrack(Track *track);
        [[nodiscard]] double getTime() const; void setTime(double time);
        [[nodiscard]] double getTimeRelease() const; void setTimeRelease(double time);
        [[nodiscard]] bool isReleased() const; void setRelease(bool r);

        [[nodiscard]] const Instruction *getInstructionState() const;
        void setInstructionState(Instruction* instruc);
        void setVolumeInstructionState(float a);
    private:
        static uint_fast8_t chancount;
        Instruction* last_instruct_address = nullptr;
        Track* track = nullptr;

        /**Channel state**/
        uint_fast8_t number;
        double time = 0.0;
        bool enable_sound = true;
        float volume = 1.0f, pitch = 1.0f, speed = 1.0f;
        bool released = false;
        double time_release = 0.0;
        Instruction instruct_state{};
    };
}

#endif //CODETRACKER_CODE_TRACKER_HPP
