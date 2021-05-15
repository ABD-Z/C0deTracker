//
// Created by Abdulmajid, Olivier NASSER on 30/08/2020.
//

#ifndef CODETRACKER_EXAMPLES_HPP
#define CODETRACKER_EXAMPLES_HPP
#include "../include/c0de_tracker.hpp"

class SuperStreetFighterII_CreditTheme : public C0deTracker::Track{
private:
    static const uint_fast8_t ROWS = 64;
    static const uint_fast8_t FRAMES = 16;
    static const uint_fast8_t CHANNELS = 9;
    constexpr static const uint_fast8_t FX_per_CHAN[CHANNELS] = {2,1,2,1,1,2,1,1,1};
    constexpr static const float CLOCK = 60.f;
    constexpr static const float SPEED = 3.f;
    constexpr static const float BASETIME = 2.f;
    static const uint_fast8_t INSTRUMENTS = 13;
    enum instrument_name{KICK, SNARE, STRING, BASS, MAIN2, MAIN, TRIANGLE, WOOD, HITHAT, CRASH, COWBELL, BASSGUITAR, TOM};
public:
    SuperStreetFighterII_CreditTheme();
    void init() override;

};

class FrereJacques : public C0deTracker::Track{
private:
    static const uint_fast8_t ROWS = 16;
    static const uint_fast8_t FRAMES = 10;
    static const uint_fast8_t CHANNELS = 4;
    constexpr static const uint_fast8_t fx_per_chan[CHANNELS] = {1,1,1,1};
    constexpr static const float CLOCK = 60.f;
    constexpr static const float SPEED = 4.f;
    constexpr static const float BASETIME = 2.f;
    static const uint_fast8_t INSTRUMENTS = 2;
    enum instrument_name{MAIN, BASS};
public:
    FrereJacques();
    void init() override;
};


class FZERO_MenuTheme : public C0deTracker::Track{
private:
    static const uint_fast8_t ROWS = 16;
    static const uint_fast8_t FRAMES = 8;
    static const uint_fast8_t CHANNELS = 7;
    constexpr static const uint_fast8_t fx_per_chan[CHANNELS] = {1,1,1,1,1,1,1};
    constexpr static const float CLOCK = 60.f;
    constexpr static const float SPEED = 6.f;
    constexpr static const float BASETIME = 1.f;
    static const uint_fast8_t INSTRUMENTS = 5;
    enum instrument_name{TRUMPET, SNARE, BASS, BRASS, MAIN};

public:
    FZERO_MenuTheme();
    void init() override;
};

class SuperMarioBros_OverworldTheme : public C0deTracker::Track{
private:
    static const uint_fast8_t ROWS = 64;
    static const uint_fast8_t FRAMES = 10;
    static const uint_fast8_t CHANNELS = 5;
    constexpr static const uint_fast8_t fx_per_chan[CHANNELS] = {1,1,1,1,1};
    constexpr static const float CLOCK = 60.f;
    constexpr static const float SPEED = 9.f;
    constexpr static const float BASETIME = 1.f;
    static const uint_fast8_t INSTRUMENTS = 4;
    enum instrument_name{BASS, MAIN, DRUMS, SNARE};
public:
    SuperMarioBros_OverworldTheme();
    void init() override;
};


class KirbysDreamland_GreenGreensTheme : public C0deTracker::Track {
private:
    static const uint_fast8_t ROWS = 16;
    static const uint_fast8_t FRAMES = 24;
    static const uint_fast8_t CHANNELS = 5;
    constexpr static const uint_fast8_t fx_per_chan[CHANNELS] = {1,1,1,1,1};
    constexpr static const float CLOCK = 60.f;
    constexpr static const float SPEED = 5.f;
    constexpr static const float BASETIME = 1.f;
    const uint_fast8_t INSTRUMENTS = 16;
    enum instrument_name{SQ25, SQ50, TRIMAIN, SQ125_LONG,
        SQ125_SHORT, SQ50_0A, SQ50_10, SQ50_0B,
        SQ50_0C, SQ50_0D, SQ50_0E, SQ50_0F,
        DRUM1, DRUM2, DRUM3, DRUM4};
    enum chan_name{PULSE0, PULSE1, TRIANGLE2, NOISE3, DPCM};

public:
    KirbysDreamland_GreenGreensTheme();
    void init() override;
};

class Sonic_GreenHillZoneTheme : public C0deTracker::Track{
private:
    static const uint_fast8_t ROWS = 32;
    static const uint_fast8_t FRAMES = 33;
    static const uint_fast8_t CHANNELS = 10;
    constexpr static const uint_fast8_t fx_per_chan[CHANNELS] = {1,1,1,1,1,1,1,1,1,1};
    constexpr static const float CLOCK = 60.f;
    constexpr static const float SPEED = 3.f;
    constexpr static const float BASETIME = 1.f;
    static const uint_fast8_t INSTRUMENTS = 8;
    enum instrument_name{HITHAT, SNARE, KICK, SQUARE, BELL, LEAD, ACCOMP, BASS};
    enum chan_name{FM0, FM1, FM2, FM3, FM4, FM5, SN0, SN1, SN2, SN3};

public:
    Sonic_GreenHillZoneTheme();
    void init() override;

};

#endif //CODETRACKER_EXAMPLES_HPP
