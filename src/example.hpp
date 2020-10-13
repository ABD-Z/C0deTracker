//
// Created by Abdulmajid, Olivier NASSER on 30/08/2020.
//

#ifndef CODETRACKER_EXAMPLE_HPP
#define CODETRACKER_EXAMPLE_HPP
#include "code_tracker.hpp"


namespace ssf2_credit_theme{
    const uint_fast8_t ROWS = 64;
    const uint_fast8_t FRAMES = 4;
    const uint_fast8_t CHANNELS = 5;
    const float CLOCK = 60.f;
    const float SPEED = 3.f;
    const float BASETIME = 2.f;
    const uint_fast8_t INSTRUMENTS = 5;
    const uint_fast8_t fx_per_chan[CHANNELS] = {2,1,1,1,1};
    enum instrument_name{KICK, SNARE, STRING, BASS, MAIN2};

    CodeTracker::Track* init_track();

    CodeTracker::Instrument** gen_instrubank();
    uint_fast8_t**  gen_track_patterns_indices();
    CodeTracker::Pattern** gen_patterns();


}

#endif //CODETRACKER_EXAMPLE_HPP
