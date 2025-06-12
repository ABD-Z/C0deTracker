//
// Created by Abdulmajid, Olivier NASSER on 02/01/2021.
//
#include "examples.hpp"

FZERO_MenuTheme::FZERO_MenuTheme() : Track_Data(
        NAME, CLOCK, SPEED, BASETIME, ROWS, FRAMES, CHANNELS, fx_per_chan, INSTRUMENTS
        ) {}

void FZERO_MenuTheme::load_data() {
    Track_Data::load_data();

#define SETINSTRDAT setInstrumentData
#define VOLM selectVolume
#define CHANL selectChannel
#define PATRN selectPattern
#define INSTR selectInstrument
#define I enterInstruction
#define R enterRelease
#define P enterPatternIndex
#define K Key
#define UI32 uint_fast32_t

    using C0deTracker::Key;
    using namespace C0deTracker::Notes;

    SETINSTRDAT(TRUMPET, C0deTracker::SQUARE, C0deTracker::ADSR(40.f,10.f,0.0f,4.f), 0.3f, 0.1f, .08f, 0.5f);
    SETINSTRDAT(SNARE, C0deTracker::WHITENOISE, C0deTracker::ADSR(100000.f, 15.0f, 0.0f, 1.f), .9f, 2.5f, .00015f, 0);
    SETINSTRDAT(BASS, C0deTracker::TRIANGLE, C0deTracker::ADSR(100.0f, 6.f, 0.0f, 5.33f), .8f, .0f, .6f, .5f);
    SETINSTRDAT(BRASS, C0deTracker::TRIANGLE, C0deTracker::ADSR(33.f,3.33f,0.4f,2.f), .6f, 0.f, .12f, .5f);
    SETINSTRDAT(MAIN, C0deTracker::SQUARE, C0deTracker::ADSR(10.f,0.f,0.0f,10.f), .25f, .0f, .5f, .0f);


    CHANL(0);
    INSTR(TRUMPET);
    VOLM(0.25f);
    PATRN(0);
    I(0, K(D_S,5), UI32(0x18FFFFFF));
    I(1, K(D_S,5));
    I(2, K(D_S,5));

    I(6, K(D_S,5));
    I(7, K(D_S,5));
    I(8, K(D_S,5));

    I(10, K(D_S,5));
    I(11, K(D_S,5));
    I(12, K(D_S,5));
    I(13, K(D_S,5));
    I(14, K(D_S,5));
    I(15, K(D_S,5));

    P(0, 1, 0); P(0, 2, 0); P(0, 3, 0); P(0, 4, 0); P(0, 5, 0); P(0, 6, 0); P(0, 7, 0);

    CHANL(1);
    INSTR(TRUMPET);
    VOLM(0.33f);
    PATRN(0);
    I(0, K(D_S,4));
    I(1, K(D_S,4));
    I(2, K(D_S,4));

    I(6, K(D_S,4));
    I(7, K(D_S,4));
    I(8, K(D_S,4));

    I(10, K(D_S,4));
    I(11, K(D_S,4));
    I(12, K(D_S,4));
    I(13, K(D_S,4));
    I(14, K(D_S,4));
    I(15, K(D_S,4));

    P(1, 1, 0); P(1, 2, 0); P(1, 3, 0); P(1, 4, 0); P(1, 5, 0); P(1, 6, 0); P(1, 7, 0);

    CHANL(2);
    INSTR(SNARE);
    VOLM(0.25f);
    PATRN(0);
    I(0, K(D_S,2));
    I(1, K(D_S,2));
    I(2, K(D_S,2));

    I(6, K(D_S,2));
    I(7, K(D_S,2));
    I(8, K(D_S,2));

    I(10, K(D_S,2));
    I(11, K(D_S,2));
    I(12, K(D_S,2));
    I(13, K(D_S,2));
    I(14, K(D_S,2));
    I(15, K(D_S,2));

    P(2, 1, 0); P(2, 2, 0); P(2, 3, 0); P(2, 4, 0); P(2, 5, 0); P(2, 6, 0); P(2, 7, 0);

    CHANL(3);
    INSTR(BASS);
    VOLM(0.75f);
    PATRN(0);
    I(0, K(D_S,3));
    I(2, K(D_S,2));
    I(4, K(A_S,2));
    I(6, K(D_S,3));

    I(0+8, K(D_S,3));
    I(2+8, K(D_S,2));
    I(4+8, K(A_S,2));
    I(6+8, K(D_S,3));

    P(3, 1, 0); P(3, 2, 0); P(3, 3, 0); P(3, 4, 0); P(3, 5, 0); P(3, 6, 0); P(3, 7, 0);

    CHANL(4);
    INSTR(BRASS);
    VOLM(0.28f);
    PATRN(0);
    I(0, K(G,4), UI32(0x18000000));
    R(10);
    I(12, K(D_S,4));
    I(14, K(C_S,4));

    PATRN(1);
    R(14);

    PATRN(2);
    I(0, K(G_S,3));
    R(10);
    I(12, K(G_S,3));
    I(14, K(A_S,3));

    P(4, 3, 1); P(4, 4, 0); P(4, 5, 1); P(4, 6, 2); P(4, 7, 3);

    CHANL(5);
    INSTR(BRASS);
    VOLM(0.28f);
    PATRN(0);
    I(0, K(A_S,3), UI32(0x18FFFFFF));
    R(10);
    I(12, K(G,3));
    I(14, K(F,3));

    PATRN(1);
    R(14);

    PATRN(2);
    I(0, K(C,3));
    R(10);
    I(12, K(C,3));
    I(14, K(D,3));

    P(5, 3, 1); P(5, 4, 0); P(5, 5, 1); P(5, 6, 2); P(5, 7, 3);

    CHANL(6);
    INSTR(MAIN);
    VOLM(.25f);
    PATRN(4);
    I(0, K(G,4), UI32(0x18000000));
    //R(1);
    I(2, K(G_S,4));
    //R(3);
    I(4, K(A_S,4));
    //R(5);
    I(6, K(D_S, 5));
    //R(9);
    I(10, K(F, 5));
    //R(11);
    I(12, K(G,5));
    PATRN(5);
    //R(9);
    I(10, K(G_S,5));
    //R(11);
    I(12, K(A_S,5));
    //R(13);
    I(14, K(F,5));
    PATRN(6);
    R(11);
    I(12, K(D_S,5));
    //R(13);
    I(14, K(G,5));
    PATRN(7);
    R(15);
}
