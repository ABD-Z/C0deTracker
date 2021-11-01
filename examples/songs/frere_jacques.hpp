//
// Created by Administrateur on 01/11/2021.
//

#ifndef C0DETRACKER_FRERE_JACQUES_HPP
#define C0DETRACKER_FRERE_JACQUES_HPP

#include "../../include/c0de_tracker.hpp"

class FrereJacques : public C0deTracker::Track{
private:
    static const uint_fast8_t ROWS = 16;
    static const uint_fast8_t FRAMES = 10;
    static const uint_fast8_t CHANNELS = 4;
    constexpr static const uint_fast8_t fx_per_chan[CHANNELS] = {1,1,1,1};
    constexpr static const float CLOCK = 60.f;
    constexpr static const float SPEED = 4.f;
    constexpr static const float BASETIME = 2.f;
    static const uint_fast8_t INSTRUMENTS = 2;
    enum instrument_name{MAIN, BASS};
public:
    FrereJacques();
    void init() override;
};

#endif //C0DETRACKER_FRERE_JACQUES_HPP
