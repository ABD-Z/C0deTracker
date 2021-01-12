//
// Created by Abdulmajid, Olivier NASSER on 30/08/2020.
//

#ifndef CODETRACKER_EXAMPLES_HPP
#define CODETRACKER_EXAMPLES_HPP
#include "../include/c0de_tracker.hpp"

namespace ssf2_credit_theme{
    const uint_fast8_t ROWS = 64;
    const uint_fast8_t FRAMES = 15;
    const uint_fast8_t CHANNELS = 8;
    const uint_fast8_t fx_per_chan[CHANNELS] = {2,1,2,1,1,2,1,1};
    const float CLOCK = 60.f;
    const float SPEED = 3.f;
    const float BASETIME = 2.f;
    const uint_fast8_t INSTRUMENTS = 11;
    enum instrument_name{KICK, SNARE, STRING, BASS, MAIN2, MAIN, TRIANGLE, WOOD, HITHAT, CRASH, COWBELL};

    C0deTracker::Track* init_track();
}

namespace  frere_jacques{
    const uint_fast8_t ROWS = 16;
    const uint_fast8_t FRAMES = 10;
    const uint_fast8_t CHANNELS = 4;
    const uint_fast8_t fx_per_chan[CHANNELS] = {1,1,1,1};
    const float CLOCK = 60.f;
    const float SPEED = 4.f;
    const float BASETIME = 2.f;
    const uint_fast8_t INSTRUMENTS = 2;
    enum instrument_name{MAIN, BASS};

    C0deTracker::Track* init_track();
}

namespace  fzero_intro{
    const uint_fast8_t ROWS = 16;
    const uint_fast8_t FRAMES = 8;
    const uint_fast8_t CHANNELS = 7;
    const uint_fast8_t fx_per_chan[CHANNELS] = {1,1,1,1,1,1,1};
    const float CLOCK = 60.f;
    const float SPEED = 6.f;
    const float BASETIME = 1.f;
    const uint_fast8_t INSTRUMENTS = 5;
    enum instrument_name{TRUMPET, SNARE, BASS, BRASS, MAIN};

    C0deTracker::Track* init_track();
}

namespace  smb1_overworld{
    const uint_fast8_t ROWS = 64;
    const uint_fast8_t FRAMES = 10;
    const uint_fast8_t CHANNELS = 5;
    const uint_fast8_t fx_per_chan[CHANNELS] = {1,1,1,1,1};
    const float CLOCK = 60.f;
    const float SPEED = 9.f;
    const float BASETIME = 1.f;
    const uint_fast8_t INSTRUMENTS = 5;
    enum instrument_name{BASS, MAIN, DRUMS, SNARE};

    C0deTracker::Track* init_track();
}


#endif //CODETRACKER_EXAMPLES_HPP
