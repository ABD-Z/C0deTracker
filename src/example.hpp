//
// Created by Administrateur on 30/08/2020.
//

#ifndef CODETRACKER_EXAMPLE_HPP
#define CODETRACKER_EXAMPLE_HPP
#include "code_tracker.hpp"


namespace ssf2_credit_theme{
    const uint8_t ROWS = 64;
    const uint8_t FRAMES = 4;
    const uint8_t CHANNELS = 5;
    const float CLOCK = 60.f;
    const float SPEED = 3.f;
    const float BASETIME = 2.f;
    const uint8_t INSTRUMENTS = 5;
    enum instrument_name{KICK, SNARE, STRING, BASS, MAIN2};

    CodeTracker::Track* init_track();

    CodeTracker::Instrument** gen_instrubank();
    uint8_t**  gen_track_patterns_indices();
    CodeTracker::Pattern** gen_patterns();


}

#endif //CODETRACKER_EXAMPLE_HPP
