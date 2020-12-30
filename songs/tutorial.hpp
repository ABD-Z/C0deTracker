//
// Created by Abdulmajid, Olivier NASSER on 23/12/2020.
//

#ifndef C0DETRACKER_TUTORIAL_HPP
#define C0DETRACKER_TUTORIAL_HPP
#include "../include/c0de_tracker.hpp"

namespace my_song{
    const uint_fast8_t ROWS = 28;
    const uint_fast8_t FRAMES = 4;
    const uint_fast8_t CHANNELS = 3;
    const uint_fast8_t fx_per_chan[CHANNELS] = {3,1,2};
    const float CLOCK = 60.f;
    const float SPEED = 2.5f;
    const float BASETIME = 3.f;
    const uint_fast8_t INSTRUMENTS = 4;
    enum instrument_name{MAIN, BASS, KICK, SNARE};

    C0deTracker::Track* init_track();
}

#endif //C0DETRACKER_TUTORIAL_HPP
