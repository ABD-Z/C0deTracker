//
// Created by Administrateur on 01/11/2021.
//

#ifndef C0DETRACKER_SSF2_CREDIT_HPP
#define C0DETRACKER_SSF2_CREDIT_HPP
#include "../../include/c0de_tracker.hpp"

class SuperStreetFighterII_CreditTheme : public C0deTracker::Track{
private:
    static const uint_fast8_t ROWS = 64;
    static const uint_fast8_t FRAMES = 16;
    static const uint_fast8_t CHANNELS = 9;
    constexpr static const uint_fast8_t FX_per_CHAN[CHANNELS] = {2,1,2,1,1,2,1,1,1};
    constexpr static const float CLOCK = 60.f;
    constexpr static const float SPEED = 3.f;
    constexpr static const float BASETIME = 2.f;
    static const uint_fast8_t INSTRUMENTS = 13;
    enum instrument_name{KICK, SNARE, STRING, BASS, MAIN2, MAIN, TRIANGLE, WOOD, HITHAT, CRASH, COWBELL, BASSGUITAR, TOM};
public:
    SuperStreetFighterII_CreditTheme();
    void init() override;

};
#endif //C0DETRACKER_SSF2_CREDIT_HPP
