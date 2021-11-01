//
// Created by Administrateur on 01/11/2021.
//

#ifndef C0DETRACKER_SMB1_OVERWORLD_HPP
#define C0DETRACKER_SMB1_OVERWORLD_HPP
#include "../../include/c0de_tracker.hpp"

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

#endif //C0DETRACKER_SMB1_OVERWORLD_HPP
