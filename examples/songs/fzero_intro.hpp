//
// Created by Administrateur on 01/11/2021.
//

#ifndef C0DETRACKER_FZERO_INTRO_HPP
#define C0DETRACKER_FZERO_INTRO_HPP
#include "../../include/c0de_tracker.hpp"

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

#endif //C0DETRACKER_FZERO_INTRO_HPP
