//
// Created by Abdulmajid, Olivier NASSER on 23/12/2020.
//

#ifndef C0DETRACKER_TUTORIAL_HPP
#define C0DETRACKER_TUTORIAL_HPP
#include "../../include/c0de_tracker.hpp"


class TutoTrack : public C0deTracker::Track_Data{
private:
    constexpr static const char* NAME = "TUTO_TRACK";
    static const uint_fast8_t ROWS = 28;
    static const uint_fast8_t FRAMES = 4;
    static const uint_fast8_t CHANNELS = 3;
    constexpr static const uint_fast8_t FX_per_CHAN[CHANNELS] = {3,1,2};
    constexpr static const float CLOCK = 60.f;
    constexpr static const float SPEED = 2.5f;
    constexpr static const float BASETIME = 3.f;
    static const uint_fast8_t INSTRUMENTS = 4;
    enum instrument_name{MAIN, BASS, KICK, SNARE};
public:
    TutoTrack();
    void load_data() override;

};

#endif //C0DETRACKER_TUTORIAL_HPP
