//
// Created by Abdulmajid, Olivier NASSER on 04/11/2021.
//

#ifndef C0DETRACKER_DUSHMAN_REMOVER_HPP
#define C0DETRACKER_DUSHMAN_REMOVER_HPP
#include "../../include/c0de_tracker.hpp"
#include "global_instruments.hpp"

class Nokia3310_DUSHMAN_REMOVER_Menu : public C0deTracker::Track_Data{
private:
    constexpr static const char* NAME = "MenuTheme";
    static const uint_fast8_t ROWS = 16;
    static const uint_fast8_t FRAMES = 4;
    static const uint_fast8_t CHANNELS = 1;
    constexpr static const uint_fast8_t FX_per_CHAN[CHANNELS] = {1};
    constexpr static const float CLOCK = 60.f;
    constexpr static const float SPEED = 3.f;
    constexpr static const float BASETIME = 3.f;
    static const uint_fast8_t INSTRUMENTS = 1;
public:
    Nokia3310_DUSHMAN_REMOVER_Menu();
    void load_data() override;
};

class Nokia3310_DUSHMAN_REMOVER_GameOver : public C0deTracker::Track_Data{
private:
    constexpr static const char* NAME = "GameOver";
    static const uint_fast8_t ROWS = 8;
    static const uint_fast8_t FRAMES = 2;
    static const uint_fast8_t CHANNELS = 1;
    constexpr static const uint_fast8_t FX_per_CHAN[CHANNELS] = {1};
    constexpr static const float CLOCK = 60.f;
    constexpr static const float SPEED = 3.f;
    constexpr static const float BASETIME = 3.f;
    static const uint_fast8_t INSTRUMENTS = 1;
public:
    Nokia3310_DUSHMAN_REMOVER_GameOver();
    void load_data() override;
};

class Nokia3310_DUSHMAN_REMOVER_Battle : public C0deTracker::Track_Data{
private:
    constexpr static const char* NAME = "Battle";
    static const uint_fast8_t ROWS = 12;
    static const uint_fast8_t FRAMES = 32;
    static const uint_fast8_t CHANNELS = 1;
    constexpr static const uint_fast8_t FX_per_CHAN[CHANNELS] = {1};
    constexpr static const float CLOCK = 60.f;
    constexpr static const float SPEED = 3.f;
    constexpr static const float BASETIME = 2.f;
    static const uint_fast8_t INSTRUMENTS = 1;
public:
    Nokia3310_DUSHMAN_REMOVER_Battle();
    void load_data() override;
};

#endif //C0DETRACKER_DUSHMAN_REMOVER_HPP
