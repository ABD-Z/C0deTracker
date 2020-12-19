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

    C0deTracker::Instrument** gen_instrubank();
    uint_fast8_t**  gen_track_patterns_indices();
    C0deTracker::Pattern** gen_patterns();

    C0deTracker::Track* init_track();


}

#endif //CODETRACKER_EXAMPLES_HPP
