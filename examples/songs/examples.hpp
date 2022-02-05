//
// Created by Administrateur on 04/11/2021.
//

#ifndef C0DETRACKER_EXAMPLES_HPP
#define C0DETRACKER_EXAMPLES_HPP
#include "../../include/c0de_tracker.hpp"
#include "global_instruments.hpp"

class Nokia3310_Test : public C0deTracker::Track_Data{
private:
    constexpr static const char* NAME = "Nokia3310_Test";
    static const uint_fast8_t ROWS = 16;
    static const uint_fast8_t FRAMES = 1;
    static const uint_fast8_t CHANNELS = 1;
    constexpr static const uint_fast8_t FX_per_CHAN[CHANNELS] = {1};
    constexpr static const float CLOCK = 60.f;
    constexpr static const float SPEED = 3.f;
    constexpr static const float BASETIME = 2.f;
    static const uint_fast8_t INSTRUMENTS = 1;
public:
    Nokia3310_Test();
    void load_data() override;

};

class Track_Test : public C0deTracker::Track_Data{
private:
    constexpr static const char* NAME = "Testotrack";
    static const uint_fast8_t ROWS = 16;
    static const uint_fast8_t FRAMES = 1;
    static const uint_fast8_t CHANNELS = 1;
    constexpr static const uint_fast8_t FX_per_CHAN[CHANNELS] = {1};
    constexpr static const float CLOCK = 60.f;
    constexpr static const float SPEED = 1.f;
    constexpr static const float BASETIME = 1.f;
public:
    Track_Test();
    void load_data() override;

};

class FrereJacques : public C0deTracker::Track_Data{
private:
    constexpr static const char* NAME = "Frere Jacques";
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
    void load_data() override;
};

class FZERO_MenuTheme : public C0deTracker::Track_Data{
private:
    constexpr static const char* NAME = "F-Zero, Menu";
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
    void load_data() override;
};

class KirbysDreamland_GreenGreensTheme : public C0deTracker::Track_Data {
private:
    constexpr static const char* NAME = "Kirby in Dreamland, Green Greens";
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
    void load_data() override;
};

class SuperMarioBros_OverworldTheme : public C0deTracker::Track_Data{
private:
    constexpr static const char* NAME = "Super Mario Bros., Overworld";
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
    void load_data() override;
};

class Sonic_GreenHillZoneTheme : public C0deTracker::Track_Data{
private:
    constexpr static const char* NAME = "Sonic Adventure, Green Hill Zone";
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
    void load_data() override;

};

class SuperStreetFighterII_CreditTheme : public C0deTracker::Track_Data{
private:
    constexpr static const char* NAME = "Super Street Fighter II, Staff roll";
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
    void load_data() override;

};

#endif //C0DETRACKER_EXAMPLES_HPP
