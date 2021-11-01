//
// Created by Administrateur on 01/11/2021.
//

#ifndef C0DETRACKER_SONIC_GREENHILLZONE_HPP
#define C0DETRACKER_SONIC_GREENHILLZONE_HPP

#include "../../include/c0de_tracker.hpp"

class Sonic_GreenHillZoneTheme : public C0deTracker::Track{
private:
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
    void init() override;

};


#endif //C0DETRACKER_SONIC_GREENHILLZONE_HPP
