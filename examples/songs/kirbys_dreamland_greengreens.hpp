//
// Created by Administrateur on 01/11/2021.
//

#ifndef C0DETRACKER_KIRBYS_DREAMLAND_GREENGREENS_HPP
#define C0DETRACKER_KIRBYS_DREAMLAND_GREENGREENS_HPP
#include "../../include/c0de_tracker.hpp"

class KirbysDreamland_GreenGreensTheme : public C0deTracker::Track {
private:
    static const uint_fast8_t ROWS = 16;
    static const uint_fast8_t FRAMES = 24;
    static const uint_fast8_t CHANNELS = 5;
    constexpr static const uint_fast8_t fx_per_chan[CHANNELS] = {1,1,1,1,1};
    constexpr static const float CLOCK = 60.f;
    constexpr static const float SPEED = 5.f;
    constexpr static const float BASETIME = 1.f;
    const uint_fast8_t INSTRUMENTS = 16;
    enum instrument_name{SQ25, SQ50, TRIMAIN, SQ125_LONG,
        SQ125_SHORT, SQ50_0A, SQ50_10, SQ50_0B,
        SQ50_0C, SQ50_0D, SQ50_0E, SQ50_0F,
        DRUM1, DRUM2, DRUM3, DRUM4};
    enum chan_name{PULSE0, PULSE1, TRIANGLE2, NOISE3, DPCM};

public:
    KirbysDreamland_GreenGreensTheme();
    void init() override;
};

#endif //C0DETRACKER_KIRBYS_DREAMLAND_GREENGREENS_HPP
