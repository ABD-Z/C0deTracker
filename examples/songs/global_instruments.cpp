//
// Created by Abdulmajid, Olivier NASSER on 27/11/2021.
//
#include "global_instruments.hpp"
C0deTracker::Instrument_Data GLOBAL_INSTRUMENTS_BANK[GLOBAL_NUMBER_OF_INSTRUMENTS];
bool IS_GLOBAL_INSTRUMENTS_BANK_INITIALISED = false;

void initGlobalInstruments() {
    GLOBAL_INSTRUMENTS_BANK[KICK].setData(C0deTracker::WHITENOISE, C0deTracker::ADSR(10000.f, 50.75f, 0.0f, 0.f), 0.6f, -5.0f, 0.1f, 0.0f);
    GLOBAL_INSTRUMENTS_BANK[SNARE].setData(C0deTracker::WHITENOISE, C0deTracker::ADSR(100000.f, 9.66f, 0.05f, 1.f), .6f, 0.0f, 0.0025f, 0.0f);
    GLOBAL_INSTRUMENTS_BANK[HITHAT].setData(C0deTracker::WHITENOISE, C0deTracker::ADSR(100.f, 20.f, 0.0f, 0.f), 0.7f, 0.0f, 0.00337f, 0.0f);
    GLOBAL_INSTRUMENTS_BANK[CRASH].setData(C0deTracker::WHITENOISE, C0deTracker::ADSR(10000.f, 1.86f, 0.00f, 0.f), .45f, 0.f,0.0055f,0.f);
    GLOBAL_INSTRUMENTS_BANK[WOOD].setData(C0deTracker::WHITENOISE2, C0deTracker::ADSR(10000.f, 50.75f, 0.0f, 0.f), 0.85f, 0.0f, 0.1f, 0.0f);
    GLOBAL_INSTRUMENTS_BANK[AMBIANT_SINE].setData(C0deTracker::SINUS, C0deTracker::ADSR(.5f, 2.f, 0.0f, 3.f), 1.f, 0.0f, 0.f, 0.0f);
    GLOBAL_INSTRUMENTS_BANK[AMBIANT_SINE2].setData(C0deTracker::SINUS, C0deTracker::ADSR(2.f, 1.f, 0.5f, 3.f), 1.f, 0.0f, 0.f, 0.0f);
    GLOBAL_INSTRUMENTS_BANK[DEEP_BASS].setData(C0deTracker::TRIANGLE, C0deTracker::ADSR(25.5f, 2.f, 0.f, 20.f), 1.f, 0.0f, 1.f, 0.5f);
    GLOBAL_INSTRUMENTS_BANK[SHARP_BASS].setData(C0deTracker::SAW, C0deTracker::ADSR(16.f, 16.f, 0.1f, 20.f), .34f, 0.0f, 1.f, .00f);
    GLOBAL_INSTRUMENTS_BANK[AMBIANT_SQU50].setData(C0deTracker::SQUARE, C0deTracker::ADSR(4.f, 4.f, 0.25f, 0.5f), .2f, 0.0f, .5f, 0.f);
    GLOBAL_INSTRUMENTS_BANK[AMBIANT_SINE3].setData(C0deTracker::SINUS, C0deTracker::ADSR(.26f, .045f, 0.0f, 3.f), 1.f, 0.0f, 0.f, 0.0f);
    GLOBAL_INSTRUMENTS_BANK[SQUARE_WAVE].setData(C0deTracker::SQUARE, C0deTracker::ADSR(1000000, 0, 1, 1000000), 1.0f, -0, .5f, 0.f);
    GLOBAL_INSTRUMENTS_BANK[LG].setData(C0deTracker::TRIANGLE, C0deTracker::ADSR(25.5f, .06f, 0.f, 40.f), 1.f, 0.0f, 1.f, 0.5f);

    GLOBAL_INSTRUMENTS_BANK[HOVER_FX].setData(C0deTracker::SINUS, C0deTracker::ADSR(.02f, 0.f, 1.0f, 0.f), .7f, 0.336699f, 0.f, 0.0f);
    GLOBAL_INSTRUMENTS_BANK[TRANS_FX0].setData(C0deTracker::WHITENOISE, C0deTracker::ADSR(0.2f, .2f, 0.00f, 0.f), .35f, 0.f,0.0055f,0.f);
    GLOBAL_INSTRUMENTS_BANK[GAME_OVER_FX0].setData(C0deTracker::SQUARE, C0deTracker::ADSR(10.f, 0.f, 0.f, 0.5f), .1f, 0.0f, .5f, 0.f);
    IS_GLOBAL_INSTRUMENTS_BANK_INITIALISED = true;
}