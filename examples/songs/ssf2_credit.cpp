//
// Created by Abdulmajid, Olivier NASSER on 30/08/2020.
//

#include "examples.hpp"

SuperStreetFighterII_CreditTheme::SuperStreetFighterII_CreditTheme() {
    this->setName(NAME);
    this->setSizeDimensions(ROWS,FRAMES,CHANNELS,FX_per_CHAN);
    this->setTimeDimensions(CLOCK, SPEED, BASETIME);
}

void SuperStreetFighterII_CreditTheme::init() {
    //Track::init();
    printf("BANK OF %d INSTRUMENTS INITIALIZING\n", INSTRUMENTS);
    //*******************************************INSTRUMENTS BANK*************************************************//
    auto** instrubank = new C0deTracker::Instrument*[INSTRUMENTS];
    instrubank[COWBELL] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::WHITENOISE, 0.0105f, C0deTracker::ADSR(10000.f, 5.0f, 0.00f, 0.f)), 0.48f);
    instrubank[CRASH] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::WHITENOISE, 0.0055, C0deTracker::ADSR(10000.f, 1.86f, 0.00f, 0.f)), 0.45);
    instrubank[TRIANGLE] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::WHITENOISE2, .0025f, C0deTracker::ADSR(100000.f, 2.66f, 0.00f, 2.f)), 0.22f);
    instrubank[WOOD] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::WHITENOISE2, 0.1f, C0deTracker::ADSR(10000.f, 50.75f, 0.0f, 0.f)), .85f);
    instrubank[HITHAT] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::WHITENOISE, 0.00337f, C0deTracker::ADSR(100.f, 20.f, 0.0f, 0.f)), .7f);
    instrubank[KICK] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::WHITENOISE, 0.1f, C0deTracker::ADSR(10000.f, 50.75f, 0.0f, 0.f)), 0.7f);
    instrubank[TOM] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::WHITENOISE, 0.2f, C0deTracker::ADSR(100000.f, 13.66f, 0.0f, 0.f)), 0.75f);
    instrubank[SNARE] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::WHITENOISE, 0.0025f, C0deTracker::ADSR(100000.f, 9.66f, 0.05f, 1.f)), 1.f);
    instrubank[STRING] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::SAW, 0.5f, C0deTracker::ADSR(100.f, 20., 0.2, 6.0f)), 1.f);
    instrubank[BASS] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::TRIANGLE, .05f, 0.5f, C0deTracker::ADSR(666.0f, 0.3f, 0.2f, 17.75f)), 0.22f);
    instrubank[BASSGUITAR] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::WHITENOISE, 0.66f, 0.0f, C0deTracker::ADSR(20.0f, 0.3f, 0.2f, 500.f)), 0.15f);
    instrubank[MAIN2] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::SINUS, .13, 0.f, C0deTracker::ADSR(10.0f, 1.f, .25f, 6.f)), 0.78f);
    instrubank[MAIN] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::SQUARE, .166f, 0.f, C0deTracker::ADSR(24.f, 6.f, .25f, 6.f)), 0.975f);
    this->setInstrumentsBank(instrubank, INSTRUMENTS);

    auto *instruments_data_bank = new C0deTracker::Instrument_Data[INSTRUMENTS];
    instruments_data_bank[COWBELL].setData(C0deTracker::WHITENOISE, C0deTracker::ADSR(10000.f, 5.0f, 0.00f, 0.f),0.48f,0.f,.0105f,0.f);
    instruments_data_bank[CRASH].setData(C0deTracker::WHITENOISE, C0deTracker::ADSR(10000.f, 1.86f, 0.00f, 0.f), .45f, 0.f,0.0055f,0.f);
    instruments_data_bank[TRIANGLE].setData(C0deTracker::WHITENOISE2, C0deTracker::ADSR(100000.f, 2.66f, 0.00f, 2.f), 0.22f, 0.0f, 0.0025f, 0.0f);
    instruments_data_bank[WOOD].setData(C0deTracker::WHITENOISE2, C0deTracker::ADSR(10000.f, 50.75f, 0.0f, 0.f), 0.85f, 0.0f, 0.1f, 0.0f);
    instruments_data_bank[HITHAT].setData(C0deTracker::WHITENOISE, C0deTracker::ADSR(100.f, 20.f, 0.0f, 0.f), 0.7f, 0.0f, 0.00337f, 0.0f);
    instruments_data_bank[KICK].setData(C0deTracker::WHITENOISE, C0deTracker::ADSR(10000.f, 50.75f, 0.0f, 0.f), 0.7f, 0.0f, 0.1f, 0.0f);
    instruments_data_bank[TOM].setData(C0deTracker::WHITENOISE, C0deTracker::ADSR(100000.f, 13.66f, 0.0f, 0.f), .75f, 0.0f, .2f, 0.0f);
    instruments_data_bank[SNARE].setData(C0deTracker::WHITENOISE, C0deTracker::ADSR(100000.f, 9.66f, 0.05f, 1.f), 1.f, 0.0f, 0.0025f, 0.0f);
    instruments_data_bank[STRING].setData(C0deTracker::SAW, C0deTracker::ADSR(100.f, 20., 0.2, 6.0f), 1.f, 0.f, 0.5f, 0.0);
    instruments_data_bank[BASS].setData(C0deTracker::TRIANGLE, C0deTracker::ADSR(666.0f, 0.3f, 0.2f, 17.75f), 0.22f, 0.0f, 0.05f,0.5f);
    instruments_data_bank[BASSGUITAR].setData(C0deTracker::WHITENOISE, C0deTracker::ADSR(20.0f, 0.3f, 0.2f, 500.f), 0.15f, 0.0f, 0.66f, 0.0f);
    instruments_data_bank[MAIN2].setData(C0deTracker::SINUS, C0deTracker::ADSR(10,1,.25f,6), .78f, .0f, .13f, .0f);
    instruments_data_bank[MAIN].setData(C0deTracker::SQUARE, C0deTracker::ADSR(24,6,.25f,6), .975f, .0f, .166f, 0.f);
    this->setInstrumentsDataBank(instruments_data_bank, INSTRUMENTS);

    printf("PATTERNS OF %d INITIALIZING\n", this->getNumberofChannels() * this->getNumberofFrames());


    using namespace C0deTracker::Notes; using namespace C0deTracker;
#define PREP Editor::prepare
#define PTRN Editor::storePatterns
#define PTRN_INDX Editor::storePatternIndex
#define CHAN_INDX Editor::storeChannelIndex
#define INSTR_INDX Editor::storeInstrumentIndex
#define VOLUME Editor::storeVolume
#define I Editor::enterInstruction
#define R Editor::release
#define k Key
#define ui32 uint_fast32_t

    Editor::loadTrackProperties(ROWS, FRAMES, CHANNELS, FX_per_CHAN); //Load track propreties in the editor
    auto** patterns = Editor::loadEmptyPatterns(); //generate empty patterns for song writing
    auto* pattern_indices = Editor::loadEmptyPatternsIndices(); //generate empty patterns indices for patterns indexing

    Editor::storePatterns(patterns); // store patterns in editor
    Editor::storePatternsIndices(pattern_indices); // store pattern indices in editor

    printf("WRITING PATTERN 0 CHAN 0\n");
    PREP(patterns, 0, 0, KICK, 0.7f);
    I(0, Key(A, 1));
    I(24, Key(A, 1));
    I(32, Key(A, 1));
    I(40, Key(A, 1));
    I(56, Key(A, 1));
    I(62, Key(A, 1));

    PTRN_INDX(15);
    I(0, k(F,1), ui32(0x1C040101));
    I(6, ui32(0x0A001000));

    printf("WRITING PATTERN 1 CHAN 0\n");
    PTRN_INDX(1);
    I(8, Key(A, 1));
    I(24, Key(A, 1));
    I(32, Key(A, 1));
    I(40, Key(A, 1));
    I(46, Key(A, 1));

    I(50, Key(A, 1));
    //I(52, SNARE, Key(G_S, 2), new uint_fast32_t* [fx_per_chan[0]]{new uint_fast32_t(0x1F0005FF)});
    I(52, SNARE, Key(G_S, 2), ui32(0x1F0005FF));
    I(56, Key(A, 1));
    I(58, SNARE, Key(G_S, 2));
    I(60, SNARE, Key(G_S, 3));

    printf("WRITING PATTERN 2 CHAN 0\n");
    PTRN_INDX(2);
    I(0, Key(A, 1));
    //I(4, SNARE, Key(G_S, 2), new uint_fast32_t* [fx_per_chan[0]]{new uint_fast32_t(0x1F0005FF)});
    I(4, SNARE, Key(G_S, 2), ui32(0x1F0005FF));
    I(8, Key(A, 1));
    I(12, SNARE, Key(G_S, 2));
    I(16, Key(A, 1));
    I(20, SNARE, Key(G_S, 2));
    I(24, Key(A, 1));
    I(26, Key(A, 1));
    I(28, SNARE, Key(G_S, 2));

    I(32, Key(A, 1));
    I(36, SNARE, Key(G_S, 2));
    I(40, Key(A, 1));
    I(44, SNARE, Key(G_S, 2));
    I(48, Key(A, 1));
    I(52, SNARE, Key(G_S, 2));
    I(56, Key(A, 1));
    I(58, Key(A, 1));
    I(60, SNARE, Key(G_S, 2));
    I(62, Key(A, 1));

    printf("WRITING PATTERN 3 CHAN 0\n");
    PTRN_INDX(3);
    I(2, Key(A, 1));
    I(4, SNARE, Key(G_S, 2));
    I(8, Key(A, 1));
    I(12, SNARE, Key(G_S, 2));
    I(16, Key(A, 1));
    I(20, SNARE, Key(G_S, 2));
    I(24, Key(A, 1));
    I(26, Key(A, 1));
    I(28, SNARE, Key(G_S, 2));

    I(32, Key(A, 1));
    I(36, SNARE, Key(G_S, 2));
    I(40, Key(A, 1));
    I(44, SNARE, Key(G_S, 2));
    I(46, Key(A, 1));
    I(50, Key(A, 1));
    I(52, SNARE, Key(G_S, 2));
    I(56, Key(A, 1));
    I(58, SNARE, Key(G_S, 2));
    I(60, SNARE, Key(G_S, 3));

    printf("WRITING PATTERN 4 CHAN 0\n");
    PTRN_INDX(4);
    I(0, k(A,1));
    I(4, SNARE, Key(G_S, 2));
    I(8, k(A,1));
    I(12, SNARE, Key(G_S, 2));
    I(14, k(A,1));
    I(18, k(A,1));
    I(20, SNARE, Key(G_S, 2));
    I(24, k(A,1));
    I(28, SNARE, Key(G_S, 2));

    I(32 + 0, k(A,1));
    I(32 + 4, SNARE, Key(G_S, 2));
    I(32 + 8, k(A,1));
    I(32 + 12, SNARE, Key(G_S, 2));
    I(32 + 14, k(A,1));
    I(32 + 18, k(A,1));
    I(32 + 20, SNARE, Key(G_S, 2));
    I(32 + 24, k(A,1));
    I(32 + 28, SNARE, Key(G_S, 2));

    printf("WRITING PATTERN 5 CHAN 0\n");
    PTRN_INDX(5);
    I(0, k(A,1));
    I(4, SNARE, Key(G_S, 2));
    I(8, k(A,1));
    I(12, SNARE, Key(G_S, 2));
    I(14, k(A,1));
    I(18, k(A,1));
    I(20, SNARE, Key(G_S, 2));
    I(24, k(A,1));
    I(28, SNARE, Key(G_S, 2));

    I(32 + 0, k(A,1));
    I(32 + 4, SNARE, Key(G_S, 2));
    I(32 + 8, k(A,1));
    I(32 + 12, SNARE, Key(G_S, 2));
    I(32 + 14, k(A,1));
    I(32 + 18, k(A,1));
    I(32 + 20, SNARE, Key(G_S, 2));
    I(32 + 24, k(A,1));
    I(58, SNARE, Key(G_S, 2));
    I(32 + 28, SNARE, Key(G_S, 3));
    //I(62, k(A,1));

    printf("WRITING PATTERN 8 CHAN 0\n");
    PTRN_INDX(8);
    I(0, k(A,1));
    I(2+2, k(A,1));
    I(2+4, SNARE, Key(G_S, 2));
    I(2+8, k(A,1));
    I(2+12, SNARE, Key(G_S, 2));
    I(2+14, k(A,1));
    I(2+18, k(A,1));
    I(2+20, SNARE, Key(G_S, 2));
    I(2+24, k(A,1));
    I(2+28, SNARE, Key(G_S, 2));
    I(2+30, k(A,1));
    I(2+34, k(A,1));
    I(2+36, SNARE, Key(G_S, 2));
    I(2+40, k(A,1));
    I(2+44, SNARE, Key(G_S, 2));
    I(2+48, k(A,1));
    I(2+52, SNARE, Key(G_S, 2));
    I(2+54, k(A,1));
    I(2+58, k(A,1));
    I(2+60, SNARE, Key(G_S, 2));
    //I(62, k(A,1));

    printf("WRITING PATTERN 9 CHAN 0\n");
    PTRN_INDX(9);
    I(0, k(A,1));
    I(2+2, k(A,1));
    I(2+4, SNARE, Key(G_S, 2));
    I(2+8, k(A,1));
    I(2+12, SNARE, Key(G_S, 2));
    I(2+14, k(A,1));
    I(2+18, k(A,1));
    I(2+20, SNARE, Key(G_S, 2));
    I(2+24, k(A,1));
    I(2+28, SNARE, Key(G_S, 2));
    I(2+30, k(A,1));
    I(2+34, k(A,1));
    I(2+36, SNARE, Key(G_S, 2));
    I(2+40, k(A,1));
    I(2+44, SNARE, Key(G_S, 2));
    I(2+48, SNARE, Key(G_S, 2));
    I(2+50, k(A,1));
    I(2+52, SNARE, Key(G_S, 2));
    I(2+54, k(A,1));
    I(2+56, SNARE, Key(G_S, 2));
    I(2+58, SNARE, Key(G_S, 2));
    I(2+60, SNARE, Key(G_S, 2));

    printf("WRITING PATTERN 10 CHAN 0\n");
    PTRN_INDX(10);
    I(0, k(A,1));
    I(2+2, k(A,1));

    printf("WRITING PATTERN 11 CHAN 0\n");
    PTRN_INDX(11);
    I(2, k(A,1));
    I(4, SNARE, Key(G_S, 2));
    I(8, k(A,1));
    I(12, SNARE, Key(G_S, 2));
    I(16, k(A,1));
    I(20, SNARE, Key(G_S, 2));
    I(24, k(A,1));
    I(26, k(A,1));
    I(28, SNARE, Key(G_S, 2));
    I(32, k(A,1));
    I(36, SNARE, Key(G_S, 2));
    I(40, k(A,1));
    I(44, SNARE, Key(G_S, 2));
    I(46, k(A,1));
    I(50, k(A,1));
    I(52, SNARE, Key(G_S, 2));
    I(56, k(A,1));
    I(58, k(A,1));
    I(60, SNARE, Key(G_S, 2));
    I(62, k(A,1));

    printf("WRITING PATTERN 12 CHAN 0\n");
    PTRN_INDX(12);
    I(0, k(A,1));
    I(4, SNARE, Key(G_S, 2));
    I(8, k(A,1));
    I(12, SNARE, Key(G_S, 2));
    I(16, k(A,1));
    I(20, SNARE, Key(G_S, 2));
    I(24, k(A,1));
    I(26, k(A,1));
    I(28, SNARE, Key(G_S, 2));
    I(32, k(A,1));
    I(36, SNARE, Key(G_S, 2));
    I(40, k(A,1));
    I(44, SNARE, Key(G_S, 2));
    I(46, k(A,1));
    I(50, k(A,1));
    I(52, SNARE, Key(G_S, 2));
    I(56, k(A,1));
    I(58, k(A,1));
    I(60, SNARE, Key(G_S, 2));
    I(62, k(A,1));

    printf("WRITING PATTERN 14 CHAN 0\n");
    PTRN_INDX(14);
    I(0, k(A,1));
    I(4, SNARE, Key(G_S, 2));
    I(8, k(A,1));
    I(12, SNARE, Key(G_S, 2));
    I(16, k(A,1));
    I(32, SNARE, Key(G_S, 2));
    I(34, k(A,1));
    I(36, SNARE, Key(G_S, 2));
    I(38, k(A,1));
    I(40, SNARE, Key(G_S, 2));
    I(42, SNARE, Key(G_S, 2));
    I(44, SNARE, Key(G_S, 2));
    I(46, k(A,1));
    I(50, k(A,1));
    //I(52, SNARE, Key(G_S, 2));

    printf("WRITING PATTERN 0 CHAN 1\n");
    CHAN_INDX(1);
    PTRN_INDX(0);
    INSTR_INDX(MAIN2);
    VOLUME(0.16f);
    //I(4, Key(F, 5), new uint_fast32_t* [fx_per_chan[1]]{new uint_fast32_t(0x189FFFFF)});
    I(4, Key(F, 5), ui32(0x189FFFFF));
    R(6);
    I(8, Key(D_S, 5));
    I(10, Key(F, 5));
    R(12);
    I(14, Key(F_S, 5));
    R(16);

    I(18, Key(F_S, 5));
    I(20, Key(F, 5));
    R(22);
    I(24, Key(D_S, 5));
    I(28, Key(F, 5));
    R(30);

    I(32 + 4, Key(F, 5));
    R(32 + 6);
    I(32 + 8, Key(D_S, 5));
    I(32 + 10, Key(F, 5));
    R(32 + 12);
    I(32 + 14, Key(F_S, 5));
    R(32 + 16);

    I(32 + 18, Key(F_S, 5));
    I(32 + 20, Key(F, 5));
    R(32 + 22);
    I(32 + 24, Key(D_S, 5));
    I(32 + 28, Key(F, 5));
    R(32 + 30);


    printf("WRITING PATTERN 1 CHAN 1\n");
    PTRN_INDX(1);
    I(4, Key(F, 5));
    R(6);
    I(8, Key(D_S, 5));
    I(10, Key(F, 5));
    R(12);
    I(14, Key(F_S, 5));
    R(16);

    I(18, Key(F_S, 5));
    I(20, Key(F, 5));
    R(22);
    I(24, Key(D_S, 5));
    I(28, Key(F, 5));
    R(30);

    I(32 + 0, Key(F_S, 5));
    I(32 + 6, Key(F_S, 5));
    R(32 + 12);
    I(32 + 14, Key(G_S, 5));
    R(32 + 14 + 12);

    printf("WRITING PATTERN 4 CHAN 1\n");
    PTRN_INDX(4);
    I(4, k(F,4));
    I(8, k(D_S,4));
    I(10, k(F,4));
    I(14, k(D_S,4));

    I(32 + 4, k(F,4));
    I(32 + 8, k(D_S,4));
    I(32 + 10, k(F,4));
    I(32 + 14, k(D_S,4));

    printf("WRITING PATTERN 5 CHAN 1\n");
    PTRN_INDX(5);
    I(4, k(F,4));
    I(8, k(D_S,4));
    I(10, k(F,4));
    I(14, k(D_S,4));

    I(32 + 4, k(F,4));
    I(32 + 8, k(D_S,4));
    I(32 + 10, k(F,4));
    I(32 + 14, k(C,4));

    printf("WRITING PATTERN 8 CHAN 1\n");
    PTRN_INDX(8);
    I(0,k(F,4));
    I(16, k(D_S,4));
    I(32, k(C_S,4));
    R(48);
    I(50, k(D_S,4));
    I(56, k(C,4));
    R(62);

    printf("WRITING PATTERN 9 CHAN 1\n");
    PTRN_INDX(9);
    I(0,k(F,4));
    I(16, k(D_S,4));
    I(32, k(C_S,4));
    R(48);
    I(50, k(D_S,4));
    I(54, k(D_S,4));
    I(58, k(D_S,4));
    I(60, k(D_S,4));
    I(62, k(D_S,4));

    printf("WRITING PATTERN 10 CHAN 1\n");
    PTRN_INDX(10);
    I(0,k(F,3));
    R(6);

    printf("WRITING PATTERN 13 CHAN 1\n");
    PTRN_INDX(13);
    I(4, k(F,4));
    I(8, k(D_S,4));
    I(10, k(F,4));
    I(14, k(D_S,4));

    I(32 + 4, k(D_S,4));
    I(32 + 8, k(C_S,4));
    I(32 + 10, k(D_S,4));
    I(32 + 14, k(F,4));

    printf("WRITING PATTERN 14 CHAN 1\n");
    PTRN_INDX(14);
    I(0, k(F_S,4)); R(12);
    I(16, k(D_S,4));
    I(32, k(F_S,4)); R(34);
    I(36, k(F_S,4)); R(38);
    I(40,k(D_S,4));
    I(42,k(D_S,4));
    I(46,k(F,4));
    R(52);

    printf("WRITING PATTERN 0 CHAN 2\n");
    CHAN_INDX(2);
    PTRN_INDX(15);
    VOLUME(1.0f);
    I(0, TOM, Key(C_S, 5),{0x1F060001,0x11200000});
    I(4, ui32(0x11000000));

    PTRN_INDX(0);
    INSTR_INDX(STRING);
    VOLUME(0.2f);
    //I(0, k(G_S, 4), new uint_fast32_t* [fx_per_chan[2]]{new uint_fast32_t(0x13841111), new uint_fast32_t(0x18AA1111)});
    I(0, k(G_S, 4), {0x13841111, 0x18AA1111});
    I(32, k(G_S, 4));
    R(60);
    I(62, k(G_S, 4));

    printf("WRITING PATTERN 1 CHAN 2\n");
    PTRN_INDX(1);
    I(32, k(C_S, 5));
    R(32 + 12);
    I(46, k(C, 5));
    R(62);

    printf("WRITING PATTERN 4 CHAN 2\n");
    PTRN_INDX(4);
    I(0, k(F,3));
    R(12);
    I(14, k(D_S,3));
    I(26, k(G_S,3));
    I(28, k(C,4));
    I(30, k(D_S,4));
    I(32, k(C_S,4));
    R(32+12);
    I(46, k(D_S,3));
    I(56, k(D_S,3));
    I(58, k(G_S,3));
    I(60, k(C,4));

    printf("WRITING PATTERN 5 CHAN 2\n");
    PTRN_INDX(5);
    I(0, k(A_S, 3));
    R(12);
    I(14, k(C,3));
    R(30);
    I(32, k(A_S,3));
    R(32 + 4*3);
    I(32 + 4*3 + 2, k(C,3));
    I(32 + 16 + 4, k(C,4));
    I(32 + 16 + 4*2, k(C_S,4));
    I(32 + 16 + 4*2+2, k(D_S,4));

    printf("WRITING PATTERN 6 CHAN 2\n");
    PTRN_INDX(6);
    I(0, k(F,3));
    R(4*3);
    I(4*3+2, k(D_S,3));
    I(4*4 + 4*2 + 2, k(D_S, 5));
    I(4*4 + 4*3, k(C, 5));
    I(4*4 + 4*3 + 2, k(G_S, 4));

    I(32, k(C_S, 5));
    R(32 + 4*3);
    I(32 + 4*3+2, k(D_S,3));
    I(32 + 4*4 + 4*2 + 2, k(C, 5));
    I(32 + 4*4 + 4*3, k(G_S, 4));
    I(32 + 4*4 + 4*3 + 2, k(F, 4));

    printf("WRITING PATTERN 7 CHAN 2\n");
    PTRN_INDX(7);
    I(0, k(A_S,4));
    R(12);
    I(14, k(C,3));
    R(30);
    I(32, k(A_S,2));
    R(44);
    I(46, k(C,3));
    I(52, k(C,5));
    I(56, k(C_S,5));
    I(58, k(D_S,5));

    printf("WRITING PATTERN 8 CHAN 2\n");
    PTRN_INDX(8);
    INSTR_INDX(MAIN);
    VOLUME(0.2f);
    I(0, k(C_S,5));
    I(6, k(C_S,5));
    I(10,k(D_S,5));
    I(12,k(D_S,5));
    R(14);
    I(16,k(C,5));
    R(22);
    INSTR_INDX(STRING);
    VOLUME(0.2f);
    I(24,k(C,4));
    I(32,k(A_S,3));
    I(48,k(C,4));
    R(50);
    I(54,k(C,4));
    R(58);

    printf("WRITING PATTERN 9 CHAN 2\n");
    PTRN_INDX(9);
    INSTR_INDX(MAIN);
    VOLUME(0.2f);
    I(0,k(C_S,5));
    R(4);
    I(10,k(D_S,5));
    I(16,k(C,5));
    R(28);
    INSTR_INDX(STRING);
    VOLUME(0.2f);
    I(32,k(C,4));
    I(34,k(C_S,4));
    I(50,k(C,4));
    R(52);
    I(54,k(C,4));
    R(56);
    I(58,k(C,4));
    I(60,k(C,4));

    printf("WRITING PATTERN 10 CHAN 2\n");
    PTRN_INDX(10);
    I(0,k(C_S,4));
    R(4);

    printf("WRITING PATTERN 11 CHAN 2\n");
    PTRN_INDX(11);
    INSTR_INDX(MAIN);
    VOLUME(0.2f);
    I(4,k(F,5));
    R(6);
    I(8,k(F,5));
    I(10,k(F,5));
    I(14,k(D_S,5));
    I(22,k(F,5));
    I(26,k(D_S,5));
    I(28,k(C_S,5));
    I(30,k(C,5));
    I(32,k(C_S,5));
    I(36,k(C,5));
    I(40,k(A_S,4));
    I(44,k(C,5));
    I(46,k(F,4));
    INSTR_INDX(STRING);
    VOLUME(0.2f);
    I(54,k(D_S,5));
    I(62,k(C_S,5));
    I(63,k(C,5));

    printf("WRITING PATTERN 12 CHAN 2\n");
    PTRN_INDX(12);
    I(0,k(A_S,4));
    I(16,k(C,3));
    I(32,k(C_S,3));
    R(44);
    I(46,k(C,3));

    I(52,k(C,4));
    I(56,k(C_S,4));
    I(60,k(D_S,4));

    printf("WRITING PATTERN 13 CHAN 2\n");
    PTRN_INDX(13);
    I(0,k(F,3));
    INSTR_INDX(MAIN);
    VOLUME(0.2f);
    I(4,k(F,5));
    I(8,k(F,5));
    I(10,k(F,5));
    I(14,k(F,5));
    R(18);
    I(20,k(D_S,5));
    I(24,k(C_S,5));
    I(28,k(C,5));
    I(30,k(B,4));
    R(34);
    INSTR_INDX(STRING);
    VOLUME(0.2f);
    I(38,k(B,3));
    I(44,k(C_S,4));
    R(62);

    printf("WRITING PATTERN 14 CHAN 2\n");
    PTRN_INDX(14);
    I(0,k(C_S,4));
    I(16,k(C,4));
    I(32,k(C_S,4));
    R(34);
    I(36,k(C_S,4));
    R(38);
    I(40,k(C,4));
    I(42,k(C,4));
    R(44);
    I(46,k(G_S,4));

    printf("WRITING PATTERN 0 CHAN 3\n");
    CHAN_INDX(3);
    PTRN_INDX(0);
    INSTR_INDX(BASS);
    VOLUME(1.f);
    I(0, k(C_S, 2), ui32(0x137E0000)); R(31);
    I(32, k(B, 1)); R(61);
    I(62, k(A_S, 1));

    printf("WRITING PATTERN 1 CHAN 3\n");
    PTRN_INDX(1);
    R(31);
    I(32, k(B, 1)); R(45);
    I(46, k(G_S, 1)); R(63);

    printf("WRITING PATTERN 2 CHAN 3\n");
    PTRN_INDX(2);
    I(0, k(C_S, 2)); R(1);
    I(2, k(C_S, 2)); R(3);
    I(4, k(C_S, 2)); R(5);
    I(6, k(C_S, 2)); R(7);
    I(8, k(C_S, 2)); R(9);
    I(10, k(C_S, 2)); R(11);
    I(12, k(C_S, 2)); R(13);
    I(14, k(C_S, 2)); R(15);
    I(16, k(C_S, 2)); R(17);
    I(18, k(C_S, 2)); R(19);
    I(20, k(C_S, 2)); R(21);
    I(22, k(C_S, 2)); R(23);
    I(24, k(C_S, 2)); R(25);
    I(26, k(C_S, 2)); R(27);
    I(28, k(C_S, 2)); R(29);
    I(30, k(C_S, 2)); R(31);

    I(32, k(B, 1)); R(33);
    I(34, k(B, 1)); R(35);
    I(36, k(B, 1)); R(37);
    I(38, k(B, 1)); R(39);
    I(40, k(B, 1)); R(41);
    I(42, k(B, 1)); R(43);
    I(44, k(B, 1)); R(45);
    I(46, k(B, 1)); R(47);
    I(48, k(B, 1)); R(49);
    I(50, k(B, 1)); R(51);
    I(52, k(B, 1)); R(53);
    I(54, k(B, 1)); R(55);
    I(56, k(B, 1)); R(57);
    I(58, k(F_S, 1)); R(59);
    I(60, k(B, 1)); R(61);
    I(62, k(A_S, 1));


    printf("WRITING PATTERN 3 CHAN 3\n");
    PTRN_INDX(3);
    R(1);
    I(2, k(A_S, 1)); R(3);
    I(4, k(A_S, 1)); R(5);
    I(6, k(A_S, 1)); R(7);
    I(8, k(A_S, 1)); R(9);
    I(10, k(A_S, 1)); R(11);
    I(12, k(A_S, 1)); R(13);
    I(14, k(A_S, 1)); R(15);
    I(16, k(A_S, 1)); R(17);
    I(18, k(A_S, 1)); R(19);
    I(20, k(A_S, 1)); R(21);
    I(22, k(A_S, 1)); R(23);
    I(24, k(A_S, 1)); R(25);
    I(26, k(A_S, 1)); R(27);
    I(28, k(A_S, 1)); R(29);
    I(30, k(A_S, 1)); R(31);

    I(32, k(B, 1)); R(33);
    I(34, k(B, 1)); R(35);
    I(36, k(B, 1)); R(37);
    I(38, k(B, 1)); R(39);
    I(40, k(B, 1)); R(41);
    I(42, k(A_S, 1)); R(43);
    I(44, k(A, 1)); R(45);
    I(46, k(G_S, 1)); R(49);

    I(50, k(G_S, 1)); R(51);
    I(52, k(G_S, 1)); R(53);
    I(54, k(G_S, 1)); R(55);
    I(56, k(G_S, 1)); R(57);
    I(58, k(G_S, 1)); R(59);
    I(60, k(G_S, 1)); R(61);
    I(62, k(G_S, 1)); R(63);

    printf("WRITING PATTERN 4 CHAN 3\n");
    PTRN_INDX(4);
    I(0, k(C_S, 2)); R(1);
    I(2, k(C_S, 2)); R(3);
    I(4, k(C_S, 2)); R(5);
    I(6, k(C_S, 2)); R(7);
    I(8, k(C_S, 2)); R(9);
    I(10, k(C_S, 2)); R(11);
    I(12, k(C_S, 2)); R(13);

    I(14, k(C, 2)); R(17);
    I(18, k(C, 2)); R(19);
    I(20, k(C, 2)); R(21);
    I(22, k(C, 2)); R(23);
    I(24, k(C, 2)); R(25);
    I(26, k(C, 2)); R(27);
    I(28, k(C, 2)); R(29);
    I(30, k(C, 2)); R(31);

    I(32+0, k(A_S, 1)); R(32+1);
    I(32+2, k(A_S, 1)); R(32+3);
    I(32+4, k(A_S, 1)); R(32+5);
    I(32+6, k(A_S, 1)); R(32+7);
    I(32+8, k(A_S, 1)); R(32+9);
    I(32+10, k(A_S, 1)); R(32+11);
    I(32+12, k(A_S, 1)); R(32+13);

    I(32+14, k(G_S, 1)); R(32+17);
    I(32+18, k(G_S, 1)); R(32+19);
    I(32+20, k(G_S, 1)); R(32+21);
    I(32+22, k(G_S, 1)); R(32+23);
    I(32+24, k(G_S, 1)); R(32+25);
    I(32+26, k(G_S, 1)); R(32+27);
    I(32+28, k(G_S, 1)); R(32+29);
    I(32+30, k(G_S, 1)); R(32+31);

    printf("WRITING PATTERN 5 CHAN 3\n");
    PTRN_INDX(5);
    I(0, k(F_S, 1)); R(1);
    I(2, k(F_S, 1)); R(3);
    I(4, k(F_S, 1)); R(5);
    I(6, k(F_S, 1)); R(7);
    I(8, k(F_S, 1)); R(9);
    I(10, k(F_S, 1)); R(11);
    I(12, k(F_S, 1)); R(13);

    I(14, k(F,1)); R(17);
    I(18, k(F,1)); R(19);
    I(20, k(F,1)); R(21);
    I(22, k(F,1)); R(23);
    I(24, k(F,1)); R(25);
    I(26, k(F,1)); R(27);
    I(28, k(F,1)); R(29);
    I(30, k(F,1)); R(31);

    I(32 + 0, k(D_S, 1)); R(32 + 1);
    I(32 + 2, k(D_S, 1)); R(32 + 3);
    I(32 + 4, k(D_S, 1)); R(32 + 5);
    I(32 + 6, k(D_S, 1)); R(32 + 7);
    I(32 + 8, k(D_S, 1)); R(32 + 9);
    I(32 + 10, k(D_S, 1)); R(32 + 11);
    I(32 + 12, k(D_S, 1)); R(32 + 13);

    I(32+14, k(G_S, 1)); R(32+17);
    I(32+18, k(G_S, 1)); R(32+19);
    I(32+20, k(G_S, 1)); R(32+21);
    I(32+22, k(G_S, 1)); R(32+23);
    I(32+24, k(G_S, 1)); R(32+25);
    I(32+26, k(G_S, 1)); R(32+27);
    I(32+28, k(G_S, 1)); R(32+29);
    I(32+30, k(G_S, 1)); R(32+31);


    printf("WRITING PATTERN 8 CHAN 3\n");
    PTRN_INDX(8);
    I(0, k(A_S,1)); R(3);
    I(4, k(A_S,1)); R(5);
    I(6, k(A_S,1)); R(7);
    I(8, k(A_S,1)); R(9);
    I(10, k(A_S,1)); R(11);
    I(12, k(A_S,1)); R(13);
    I(14, k(A_S,1)); R(15);

    I(16 + 0, k(G_S,1)); R(16 + 3);
    I(16 + 4, k(G_S,1)); R(16 + 5);
    I(16 + 6, k(G_S,1)); R(16 + 7);
    I(16 + 8, k(G_S,1)); R(16 + 9);
    I(16 + 10, k(G_S,1)); R(16 + 11);
    I(16 + 12, k(G_S,1)); R(16 + 13);
    I(16 + 14, k(G_S,1)); R(16 + 15);

    I(32 + 0, k(F_S,1)); R(32 + 3);
    I(32 + 4, k(F_S,1)); R(32 + 5);
    I(32 + 6, k(F_S,1)); R(32 + 7);
    I(32 + 8, k(F_S,1)); R(32 + 9);
    I(32 + 10, k(F_S,1)); R(32 + 11);
    I(32 + 12, k(F_S,1)); R(32 + 16);

    I(50, k(G_S,1)); R(53);
    I(54, k(D_S,1)); R(55);
    I(56, k(G_S,1)); R(59);
    I(60, k(D_S,1)); R(61);
    I(62, k(G_S,1)); R(63);

    printf("WRITING PATTERN 9 CHAN 3\n");
    PTRN_INDX(9);
    I(0, k(A_S,1)); R(3);
    I(4, k(A_S,1)); R(5);
    I(6, k(A_S,1)); R(7);
    I(8, k(A_S,1)); R(9);
    I(10, k(A_S,1)); R(11);
    I(12, k(A_S,1)); R(13);
    I(14, k(A_S,1)); R(15);

    I(16 + 0, k(G_S,1)); R(16 + 3);
    I(16 + 4, k(G_S,1)); R(16 + 5);
    I(16 + 6, k(G_S,1)); R(16 + 7);
    I(16 + 8, k(G_S,1)); R(16 + 9);
    I(16 + 10, k(G_S,1)); R(16 + 11);
    I(16 + 12, k(G_S,1)); R(16 + 13);
    I(16 + 14, k(G_S,1)); R(16 + 15);

    I(32 + 0, k(F_S,1)); R(32 + 3);
    I(32 + 4, k(F_S,1)); R(32 + 5);
    I(32 + 6, k(F_S,1)); R(32 + 7);
    I(32 + 8, k(F_S,1)); R(32 + 9);
    I(32 + 10, k(F_S,1)); R(32 + 11);
    I(32 + 12, k(F_S,1)); R(32 + 16);

    I(50, k(G_S,1)); R(51);
    I(52, k(G_S,1)); R(53);
    I(54, k(G_S,1)); R(55);
    I(56, k(G_S,1)); R(57);
    I(58, k(G_S,1)); R(59);
    I(60, k(A_S,1)); R(61);
    I(62, k(C,2)); R(63);

    printf("WRITING PATTERN 10 CHAN 3\n");
    PTRN_INDX(10);
    I(0, k(C_S,2)); R(3);
    I(4, k(C_S,2)); R(5);

    printf("WRITING PATTERN 11 CHAN 3\n");
    PTRN_INDX(11);
    I(0, k(C_S,2)); R(3);
    I(4, k(C_S,2)); R(5);
    I(6, k(C_S,2)); R(7);
    I(8, k(C_S,2)); R(9);
    I(10, k(C_S,2)); R(11);
    I(12, k(C_S,2)); R(13);
    I(14, k(C_S,2)); R(15);

    I(16, k(C,2)); R(17);
    I(18, k(C,2)); R(19);
    I(20, k(C,2)); R(21);
    I(22, k(C,2)); R(23);
    I(24, k(C,2)); R(25);
    I(26, k(C,2)); R(27);
    I(28, k(C,2)); R(29);
    I(30, k(C,2)); R(31);

    I(32, k(A_S,1)); R(33);
    I(34, k(A_S,1)); R(35);
    I(36, k(A_S,1)); R(37);
    I(38, k(A_S,1)); R(39);
    I(40, k(A_S,1)); R(41);
    I(42, k(A_S,1)); R(43);
    I(44, k(A_S,1)); R(45);

    I(46, k(G_S,1)); R(49);
    I(50, k(G_S,1)); R(51);
    I(52, k(G_S,1)); R(53);
    I(54, k(G_S,1)); R(55);
    I(56, k(G_S,1)); R(57);
    I(58, k(G_S,1)); R(59);
    I(60, k(G_S,1)); R(61);
    I(62, k(G_S,1)); R(63);

    printf("WRITING PATTERN 12 CHAN 3\n");
    PTRN_INDX(12);
    I(0, k(F_S,1)); R(1);
    I(2, k(F_S,1)); R(3);
    I(4, k(F_S,1)); R(5);
    I(6, k(F_S,1)); R(7);
    I(8, k(F_S,1)); R(9);
    I(10, k(F_S,1)); R(11);
    I(12, k(F_S,1)); R(13);
    I(14, k(F_S,1)); R(15);

    I(16 + 0, k(F,1)); R(16 + 1);
    I(16 + 2, k(F,1)); R(16 + 3);
    I(16 + 4, k(F,1)); R(16 + 5);
    I(16 + 6, k(F,1)); R(16 + 7);
    I(16 + 8, k(F,1)); R(16 + 9);
    I(16 + 10, k(F,1)); R(16 + 11);
    I(16 + 12, k(F,1)); R(16 + 13);
    I(16 + 14, k(F,1)); R(16 + 15);

    I(32 + 0, k(D_S,1)); R(32 + 1);
    I(32 + 2, k(D_S,1)); R(32 + 3);
    I(32 + 4, k(D_S,1)); R(32 +5);
    I(32 +6, k(D_S,1)); R(32 +7);
    I(32 +8, k(D_S,1)); R(32 +9);
    I(32 +10, k(D_S,1)); R(32 +11);
    I(32 +12, k(D_S,1)); R(32 +13);

    I(46, k(G_S,1)); R(49);
    I(50, k(G_S,1)); R(51);
    I(52, k(G_S,1)); R(53);
    I(54, k(G_S,1)); R(55);
    I(56, k(G_S,1)); R(57);
    I(58, k(G_S,1)); R(59);
    I(60, k(G_S,1)); R(61);
    I(62, k(C,2)); R(63);

    printf("WRITING PATTERN 13 CHAN 3\n");
    PTRN_INDX(13);
    I(0, k(C_S,2)); R(1);
    I(2, k(C_S,2)); R(3);
    I(4, k(C_S,2)); R(5);
    I(6, k(C_S,2)); R(7);
    I(8, k(C_S,2)); R(9);
    I(10, k(C_S,2)); R(11);
    I(12, k(C_S,2)); R(13);
    I(14, k(C_S,2)); R(15);

    I(16 + 0, k(C,2)); R(16 + 1);
    I(16 + 2, k(C,2)); R(16 + 3);
    I(16 + 4, k(C,2)); R(16 + 5);
    I(16 + 6, k(C,2)); R(16 + 7);
    I(16 + 8, k(C,2)); R(16 + 9);
    I(16 + 10, k(C,2)); R(16 + 11);
    I(16 + 12, k(C,2)); R(16 + 13);

    I(30, k(B,1)); R(32 + 1);
    I(32 + 2,  k(B,1)); R(32 + 3);
    I(32 + 4,  k(B,1)); R(32 + 5);
    I(32 + 6,  k(B,1)); R(32 + 7);
    I(32 + 8,  k(B,1)); R(32 + 9);
    I(32 + 10,  k(B,1)); R(32 + 11);
    I(32 + 12,  k(B,1)); R(32 + 13);
    I(32 + 14,  k(B,1)); R(32 + 15);

    I(48, k(A_S,1)); R(48 + 1);
    I(48 + 2,  k(A_S,1)); R(48 + 3);
    I(48 + 4,  k(A_S,1)); R(48 + 5);
    I(48 + 6,  k(A_S,1)); R(48 + 7);
    I(48 + 8,  k(A_S,1)); R(48 + 9);
    I(48 + 10,  k(A_S,1)); R(48 + 11);
    I(48 + 12,  k(A_S,1)); R(48 + 13);
    I(48 + 14,  k(A_S,1)); R(48 + 15);

    printf("WRITING PATTERN 14 CHAN 3\n");
    PTRN_INDX(14);
    I(0, k(F_S,1)); R(1);
    I(2, k(F_S,1)); R(3);
    I(4, k(F_S,1)); R(5);
    I(6, k(F_S,1)); R(7);
    I(8, k(F_S,1)); R(9);
    I(10, k(F_S,1)); R(11);
    I(12, k(F_S,1)); R(13);
    I(14, k(F_S,1)); R(15);

    I(16, k(F,1)); R(31);
    I(32,k(D_S,1)); R(33);
    I(36, k(D_S,1)); R(37);
    I(40, k(G_S,1)); R(41);
    I(42, k(G_S,1)); R(43);

    I(46, k(C_S,2)); R(49);
    I(50, k(C_S,2)); R(51);
    I(52, k(C_S,2)); R(53);
    I(54, k(C_S,2)); R(55);
    I(56, k(C_S,2)); R(57);
    I(58, k(C_S,2)); R(59);
    I(60, k(C_S,2)); R(61);
    I(62, k(C_S,2)); R(63);

    printf("WRITING PATTERN 0 CHAN 4\n");
    CHAN_INDX(4);
    PTRN_INDX(0);
    INSTR_INDX(MAIN2);
    VOLUME(0.133f);
    I(4, k(G_S, 5),  uint_fast32_t(0x18200000));
    R(6);
    I(8, k(G_S, 5));
    I(10, k(G_S, 5));
    R(12);
    I(14, k(G_S, 5));
    R(16);
    I(18, k(G_S, 5));
    I(20, k(G_S, 5));
    R(22);
    I(24, k(G_S, 5));
    I(28, k(G_S, 5));
    R(30);

    I(32 + 4, k(G_S, 5));
    R(32 + 6);
    I(32 + 8, k(G_S, 5));
    I(32 + 10, k(G_S, 5));
    R(32 + 12);
    I(32 + 14, k(G_S, 5));
    R(32 + 16);
    I(32 + 18, k(G_S, 5));
    I(32 + 20, k(G_S, 5));
    R(32 + 22);
    I(32 + 24, k(G_S, 5));
    I(32 + 28, k(G_S, 5));
    R(32 + 30);

    printf("WRITING PATTERN 1 CHAN 4\n");
    PTRN_INDX(1);
    I(4, k(G_S, 5));
    R(6);
    I(8, k(G_S, 5));
    I(10, k(G_S, 5));
    R(12);
    I(14, k(G_S, 5));
    R(16);
    I(18, k(G_S, 5));
    I(20, k(G_S, 5));
    R(22);
    I(24, k(G_S, 5));
    I(28, k(G_S, 5));
    R(30);

    I(32 + 0, k(G_S, 5));
    I(32 + 6, k(G_S, 5));
    R(32 + 12);
    I(32 + 14, k(C, 6));
    R(32 + 14 + 12);


    printf("WRITING PATTERN 4 CHAN 4\n");
    PTRN_INDX(4);
    I(4, k(G_S,4));
    I(8, k(G_S,4));
    I(10, k(G_S,4));
    I(14, k(G_S,4));

    I(32 + 4, k(G_S,4));
    I(32 + 8, k(G_S,4));
    I(32 + 10, k(G_S,4));
    I(32 + 14, k(G_S,4));

    printf("WRITING PATTERN 5 CHAN 4\n");
    PTRN_INDX(5);
    I(4, k(G_S,4));
    I(8, k(G_S,4));
    I(10, k(G_S,4));
    I(14, k(G_S,4));

    I(32 + 4, k(G_S,4));
    I(32 + 8, k(G_S,4));
    I(32 + 10, k(G_S,4));
    I(32 + 14, k(D_S,4));

    printf("WRITING PATTERN 8 CHAN 4\n");
    PTRN_INDX(8);
    I(0,k(G_S,4));
    I(16,k(G_S,4));
    I(32,k(D_S,4));
    R(48);
    I(50, k(G_S,4));
    I(56, k(D_S,5));
    R(60);

    printf("WRITING PATTERN 9 CHAN 4\n");
    PTRN_INDX(9);
    I(0,k(G_S,4));
    I(16,k(G_S,4));
    I(32,k(D_S,4));
    R(48);
    I(50, k(G_S,4));
    I(54, k(G_S,4));
    I(58, k(G_S,4));
    I(60, k(G_S,4));
    I(62, k(G_S,4));

    printf("WRITING PATTERN 10 CHAN 4\n");
    PTRN_INDX(10);
    I(0, k(C_S,5));
    R(4);

    printf("WRITING PATTERN 13 CHAN 4\n");
    PTRN_INDX(13);
    I(4, k(G_S,4));
    I(8, k(G_S,4));
    I(10, k(G_S,4));
    I(14, k(G_S,4));

    I(32 + 4, k(F_S,4));
    I(32 + 8, k(F_S,4));
    I(32 + 10, k(F_S,4));
    I(32 + 14, k(G_S,4));

    printf("WRITING PATTERN 14 CHAN 4\n");
    PTRN_INDX(14);
    I(0, k(A_S,4));
    R(12);
    I(16, k(G_S,4));
    I(32,k(A_S,4)); R(34);
    I(36,k(A_S,4)); R(38);
    I(40, k(G_S,4));
    I(42, k(G_S,4));
    I(46, k(G_S,4));
    R(52);

    CHAN_INDX(5);
    printf("WRITING PATTERN 0 CHAN 5\n");
    PTRN_INDX(0);
    INSTR_INDX(WOOD);
    VOLUME(0.5f);
    R(14);
    I(16, k(A,3));
    I(18, k(A,3));
    I(48, k(A,3));
    I(54, k(A,3));

    printf("WRITING PATTERN 1 CHAN 5\n");
    PTRN_INDX(1);
    I(16, k(A,3));
    I(18, k(A,3));

    printf("WRITING PATTERN 4 CHAN 5\n");
    PTRN_INDX(4);
    INSTR_INDX(MAIN);
    VOLUME(0.24f);
    //I(4, k(F,5), new uint_fast32_t* [fx_per_chan[5]]{new uint_fast32_t(0x137AFFFF), new uint_fast32_t(0x12AFF004)});
    I(0, k(A,4), 0, ui32(0x1B200000));
    I(4, k(F,5), {(0x137AFFFF), (0x12AFF004)});
    //I(8, k(F,5));
    I(12, k(C_S,5), ui32(0x1B000000));
    I(14, k(D_S,5), ui32(0x1B200000));
    I(22, k(G_S,4));
    R(30);

    I(32 + 4, k(C_S,5), ui32(0x1B000000));
    I(32 + 8, k(C,5));
    I(32 + 12, k(A_S,4));
    I(32 + 14, k(C,5), ui32(0x1B200000));
    I(32 + 22, k(F,4));
    R(32 + 30,ui32(0x1B000000));

    printf("WRITING PATTERN 5 CHAN 5\n");
    PTRN_INDX(5);
    I(4, k(A_S,4));
    I(8, k(G_S,4));
    I(12, k(F_S,4));
    I(14, k(G_S,4));
    I(22, k(C_S,5));
    R(30);

    I(32, k(C_S,5));
    //R(32 + 8);
    I(32 + 10, k(C,5));
    I(32 + 12, k(C_S,5));
    I(32 + 14, k(D_S,5));
    R(32 + 30);

    printf("WRITING PATTERN 6 CHAN 5\n");
    PTRN_INDX(6);
    I(4, k(G_S,4), ui32(0x1B200000));
    I(8, k(F,5));
    I(12, k(C_S,5),ui32(0x1B000000));
    I(14, k(D_S,5));
    I(22, k(G_S,4));
    R(30);

    I(32 + 4, k(C_S,5));
    I(32 + 8, k(C,5));
    I(32 + 12, k(A_S,4));
    I(32 + 14, k(C,5));
    I(32 + 22, k(F,4));
    R(32 + 30);

    printf("WRITING PATTERN 7 CHAN 5\n");
    PTRN_INDX(7);
    I(0, k(A_S, 4));
    I(6, k(C, 5));
    I(12, k(C_S, 5));
    R(13);
    I(14, k(C_S, 5));
    I(22, k(G_S, 4));

    I(32 + 0, k(C_S, 5));
    I(32 + 10, k(C, 5));
    I(32 + 12, k(C_S, 5));
    I(32 + 14, k(D_S, 5));
    I(61, uint_fast32_t(0x0A009000)); // JUMP TO frame 8

    printf("WRITING PATTERN 8 CHAN 5\n");
    PTRN_INDX(8);
    I(0, k(F,5));
    R(8);
    I(10,k(F_S,5));
    I(16,k(D_S,5));
    R(24);
    I(26,k(F,5));
    I(32,k(C_S,5));

    I(44,k(A_S,4));
    I(46,k(C,5));
    I(48,k(C_S,5));
    I(50,k(D_S,5));
    I(52,k(C_S,5));
    I(54,k(C,5));
    I(56,k(G_S,4));

    printf("WRITING PATTERN 9 CHAN 5\n");
    PTRN_INDX(9);
    I(0, k(F,5));
    R(8);
    I(10,k(F_S,5),ui32(0x1B200000));
    I(16,k(D_S,5));
    R(24);
    I(28, k(G_S,5));
    I(32, k(F_S,5),ui32(0x1B000000));
    R(40);

    I(44,k(F,5));
    I(46,k(D_S,5));
    I(48,k(C_S,5));
    I(50,k(C,5));
    I(52,k(C_S,5));
    I(54,k(D_S,5));
    I(56, k(G_S,5));

    printf("WRITING PATTERN 10 CHAN 5\n");
    PTRN_INDX(10);
    R(0);
    I(5, uint_fast32_t(0x0A00C004)); // JUMP TO frame B row 4

    printf("WRITING PATTERN 11 CHAN 5\n");
    PTRN_INDX(11);
    I(4, k(G_S,5));
    I(8, k(G_S,5));
    I(10, k(G_S,5));
    I(14, k(G_S,5));
    I(22, k(G_S,5));
    I(26, k(F_S,5));
    I(28, k(F,5));
    I(30, k(D_S,5));
    I(32, k(F,5));
    I(36, k(D_S,5));
    I(40, k(C_S,5));
    I(44, k(D_S,5));
    I(46, k(C,5));
    R(54);

    printf("WRITING PATTERN 12 CHAN 5\n");
    PTRN_INDX(12);
    I(4, k(A_S,4));
    I(8, k(C,5));
    I(10, k(C_S,5));
    I(14, k(C_S,5));

    I(16, k(G_S,4));
    I(20, k(G_S,4));
    I(22, k(C_S,5));
    I(26, k(G_S,4));
    I(28, k(C_S,5));

    I(30, k(F,5));
    I(32, k(F_S,5));
    I(36, k(F,5));
    I(40, k(D_S,5));
    I(44, k(C_S,5));
    I(46, k(D_S,5));
    R(54);

    printf("WRITING PATTERN 13 CHAN 5\n");
    PTRN_INDX(13);
    I(4,k(G_S,5));
    I(8,k(G_S,5));
    I(10,k(G_S,5));
    I(14,k(G_S,5));
    I(20, k(F_S,5));
    I(24, k(F,5));
    I(28, k(D_S,5));
    I(30, k(F,5));
    R(38);
    I(42, k(F,5),ui32(0x1B200000));
    I(44, k(F_S,5));
    I(46, k(G_S,5));
    I(48, k(A_S,5));
    I(52, k(G_S,5));
    I(54, k(F_S,5));
    R(56);
    I(58, k(F,5),ui32(0x1B000000));
    R(60);

    printf("WRITING PATTERN 14 CHAN 5\n");
    PTRN_INDX(14);
    I(0,k(A_S,4));
    I(6,k(C,5));
    I(12,k(C_S,5));
    I(16,k(G_S,4));
    R(18);
    I(20,k(G_S,4));
    I(22,k(C_S,5));
    I(28,k(D_S,5));
    I(32,k(F,5));
    R(34);
    I(36,k(D_S,5));
    R(38);
    I(40,k(C_S,5));
    I(42,k(C_S,5));
    I(44,k(C,5));
    I(46,k(C_S,5));
    I(51, uint_fast32_t(0x0A003004));

    printf("WRITING PATTERN 0 CHAN 6\n");
    CHAN_INDX(6);
    PTRN_INDX(0);
    INSTR_INDX(TRIANGLE);
    VOLUME(0.3f);
    I(0, k(A,2), uint_fast32_t(0x183FFFFF));
    I(6, k(A,2));
    I(12, k(A,2));

    I(18, k(A,2));
    I(24, k(A,2));
    I(28, k(A,2));

    I(32, k(A,2));
    I(38, k(A,2));
    I(44, k(A,2));

    I(50, k(A,2));
    I(56, k(A,2));
    I(60, k(A,2));

    PTRN_INDX(8);
    INSTR_INDX(WOOD);
    VOLUME(0.5f);
    I(8, k(A,3));
    I(12, k(A,3));

    I(20, k(A,3));
    I(24, k(A,3));

    I(36, k(A,3));
    I(40, k(A,3));
    I(44, k(A,3));


    CHAN_INDX(7);
    INSTR_INDX(CRASH);
    PTRN_INDX(0);
    printf("WRITING PATTERN 0 CHAN 7\n");
    VOLUME(0.55);
    I(0, k(C_S,3));
    VOLUME(0.35);
    I(12, k(A_S,2));
    I(20, k(A_S,2));
    I(28, k(A_S,2));
    VOLUME(0.55);
    I(32, k(C_S,3));
    VOLUME(0.35);
    I(44, k(A_S,2));
    I(52, k(A_S,2));
    I(60, k(A_S,2));
    VOLUME(0.55);
    I(62, k(C_S,3));
    VOLUME(0.35);

    PTRN_INDX(1);
    printf("WRITING PATTERN 1 CHAN 7\n");
    I(4, k(A_S, 2));
    I(12, k(A_S, 2));
    I(20, k(A_S, 2));
    I(28, k(A_S, 2));
    VOLUME(0.55);
    I(32, k(C_S,3));
    VOLUME(0.35);
    I(44, k(A_S,2));
    VOLUME(0.55);
    I(46, k(C_S, 3));
    INSTR_INDX(COWBELL);
    VOLUME(0.55);
    I(52, k(C_S,3));
    I(56, k(C_S,3));

    PTRN_INDX(2);
    printf("WRITING PATTERN 1 CHAN 7\n");
    INSTR_INDX(CRASH);
    I(0, k(C_S,3));
    INSTR_INDX(COWBELL);
    I(4, k(C_S,3));
    I(8, k(C_S,3));
    I(12, k(C_S,3));
    I(20, k(C_S,3));
    I(24, k(C_S,3));
    I(28, k(C_S,3));
    I(32, k(C_S,3));
    I(36, k(C_S,3));
    I(40, k(C_S,3));
    I(44, k(C_S,3));
    I(52, k(C_S,3));
    I(56, k(C_S,3));
    I(60, k(C_S,3));
    INSTR_INDX(CRASH);
    I(62, k(C_S,3));

    PTRN_INDX(3);
    INSTR_INDX(COWBELL);
    I(4, k(C_S,3));
    I(8, k(C_S,3));
    I(12, k(C_S,3));
    I(20, k(C_S,3));
    I(24, k(C_S,3));
    I(28, k(C_S,3));
    I(32, k(C_S,3));
    I(36, k(C_S,3));
    I(40, k(C_S,3));
    I(44, k(C_S,3));
    INSTR_INDX(CRASH);
    I(46, k(C_S,3));
    INSTR_INDX(COWBELL);
    I(52, k(C_S,3));
    I(56, k(C_S,3));

    printf("WRITING PATTERN 4 CHAN 7\n");
    PTRN_INDX(4);
    INSTR_INDX(CRASH);
    I(0, k(C_S,3));
    INSTR_INDX(HITHAT);
    VOLUME(0.3);
    I(4, k(A,2)); I(6, k(A,2)); I(8, k(A,2)); I(10, k(A,2)); I(12, k(A,2)); I(14, k(A,2));
    I(16, k(A,2)); I(18, k(A,2)); I(20, k(A,2)); I(22, k(A,2)); I(24, k(A,2)); I(26, k(A,2)); I(28, k(A,2)); I(30, k(A,2));
    I(32, k(A,2)); I(34, k(A,2)); I(36, k(A,2)); I(38, k(A,2)); I(40, k(A,2)); I(42, k(A,2)); I(44, k(A,2)); I(46, k(A,2));
    I(48, k(A,2)); I(50, k(A,2)); I(52, k(A,2)); I(54, k(A,2)); I(56, k(A,2)); I(58, k(A,2)); I(60, k(A,2)); I(62, k(A,2));

    printf("WRITING PATTERN 5 CHAN 7\n");
    PTRN_INDX(5);
    I(0, k(A,2)); I(2,k(A,2)); I(4, k(A,2)); I(6, k(A,2)); I(8, k(A,2)); I(10, k(A,2)); I(12, k(A,2)); I(14, k(A,2));
    I(16, k(A,2)); I(18, k(A,2)); I(20, k(A,2)); I(22, k(A,2)); I(24, k(A,2)); I(26, k(A,2)); I(28, k(A,2)); I(30, k(A,2));
    I(32, k(A,2)); I(34, k(A,2)); I(36, k(A,2)); I(38, k(A,2)); I(40, k(A,2)); I(42, k(A,2)); I(44, k(A,2)); I(46, k(A,2));
    I(48, k(A,2)); I(50, k(A,2)); I(52, k(A,2)); I(54, k(A,2)); I(56, k(A,2)); I(58, k(A,2)); I(60, k(A,2)); I(62, k(A,2));

    printf("WRITING PATTERN 7 CHAN 7\n");
    PTRN_INDX(7);
    I(0, k(A,2)); I(2,k(A,2)); I(4, k(A,2)); I(6, k(A,2)); I(8, k(A,2)); I(10, k(A,2)); I(12, k(A,2)); I(14, k(A,2));
    I(16, k(A,2)); I(18, k(A,2)); I(20, k(A,2)); I(22, k(A,2)); I(24, k(A,2)); I(26, k(A,2)); I(28, k(A,2)); I(30, k(A,2));
    I(32, k(A,2)); I(34, k(A,2)); I(36, k(A,2)); I(38, k(A,2)); I(40, k(A,2)); I(42, k(A,2)); I(44, k(A,2)); I(46, k(A,2));
    I(48, k(A,2)); I(50, k(A,2)); I(52, k(A,2)); I(54, k(A,2));
    INSTR_INDX(CRASH);
    VOLUME(0.35);
    I(56, k(A_S,2));
    I(58, k(A_S,2));
    I(60, k(A_S,2));
    VOLUME(0.55);
    I(62, k(C_S,3));

    printf("WRITING PATTERN 8 CHAN 7\n");
    PTRN_INDX(8);
    INSTR_INDX(CRASH);
    VOLUME(0.55);
    I(0, k(C_S,3));
    VOLUME(0.35);
    I(6, k(A_S,2));
    I(10, k(A_S,2));
    I(14, k(A_S,2));
    I(16, k(A_S,2));
    I(18, k(A_S,2));
    I(22, k(A_S,2));
    I(26, k(A_S,2));
    I(32, k(A_S,2));
    I(34, k(A_S,2));
    I(38, k(A_S,2));
    I(42, k(A_S,2));
    I(46, k(A_S,2));
    I(48, k(A_S,2));
    VOLUME(0.55);
    I(50, k(C_S,3));
    I(56, k(C_S,3));

    INSTR_INDX(HITHAT);
    VOLUME(0.5);
    I(26+2, k(D,4), uint_fast32_t(0x1C030301));
    I(28+2, k(D,4));
    I(58+2, k(D,4), uint_fast32_t(0x1C030301));
    I(60+2, k(D,4));

    printf("WRITING PATTERN 9 CHAN 7\n");
    PTRN_INDX(9);
    INSTR_INDX(HITHAT);
    I(26+2, k(D,4),  uint_fast32_t(0x1C030301));
    I(28+2, k(D,4));
    INSTR_INDX(CRASH);
    VOLUME(0.55);
    I(0, k(C_S,3));
    VOLUME(0.35);
    I(6, k(A_S,2));
    I(10, k(A_S,2));
    I(14, k(A_S,2));
    I(16, k(A_S,2));
    I(18, k(A_S,2));
    I(22, k(A_S,2));
    I(26, k(A_S,2));
    I(32, k(A_S,2));
    I(34, k(A_S,2));
    I(38, k(A_S,2));
    I(42, k(A_S,2));
    I(46, k(A_S,2));
    I(48, k(A_S,2));
    VOLUME(0.55);
    I(50, k(C_S,3));
    I(54, k(C_S,3));

    printf("WRITING PATTERN 10 CHAN 7\n");
    PTRN_INDX(10);
    I(0, k(C_S,3));

    printf("WRITING PATTERN 11 CHAN 7\n");
    PTRN_INDX(11);
    INSTR_INDX(CRASH);
    VOLUME(0.55);
    I(46, k(C_S,3));
    INSTR_INDX(COWBELL);
    I(4,k(C_S,3)); I(8,k(C_S,3)); I(12,k(C_S,3));
    I(16,k(C_S,3)); I(20,k(C_S,3)); I(24,k(C_S,3)); I(28,k(C_S,3));
    I(32,k(C_S,3)); I(36,k(C_S,3));I(40,k(C_S,3)); I(44,k(C_S,3));
    I(52,k(C_S,3)); I(56,k(C_S,3)); I(60 ,k(C_S,3));

    printf("WRITING PATTERN 12 CHAN 7\n");
    PTRN_INDX(12);
    INSTR_INDX(CRASH);
    VOLUME(0.55);
    I(46, k(C_S,3));
    I(62, k(A,3));
    INSTR_INDX(COWBELL);
    I(0,k(C_S,3)); I(4,k(C_S,3)); I(8,k(C_S,3)); I(12,k(C_S,3));
    I(16,k(C_S,3)); I(20,k(C_S,3)); I(24,k(C_S,3)); I(28,k(C_S,3));
    I(32,k(C_S,3)); I(36,k(C_S,3));I(40,k(C_S,3)); I(44,k(C_S,3));
    I(52,k(C_S,3)); I(56,k(C_S,3)); I(60 ,k(C_S,3));

    printf("WRITING PATTERN 13 CHAN 7\n");
    PTRN_INDX(13);
    INSTR_INDX(CRASH);
    VOLUME(0.55);
    I(0, k(C_S,3));
    I(30, k(C_S,3));
    INSTR_INDX(COWBELL);
    I(8,k(C_S,3)); I(12,k(C_S,3));
    I(16,k(C_S,3)); I(20,k(C_S,3)); I(24,k(C_S,3)); I(28,k(C_S,3));
    I(36,k(C_S,3));I(40,k(C_S,3)); I(44,k(C_S,3));
    I(48,k(C_S,3)); I(52,k(C_S,3)); I(56,k(C_S,3)); I(60 ,k(C_S,3));

    printf("WRITING PATTERN 14 CHAN 7\n");
    PTRN_INDX(14);
    INSTR_INDX(CRASH);
    VOLUME(0.33);
    I(16, k(C_S,3));
    VOLUME(0.33);
    I(32, k(A_S,2));
    I(36, k(A_S,2));
    VOLUME(0.55);
    I(46, k(C_S,3));
    INSTR_INDX(COWBELL);
    I(0,k(C_S,3)); I(4,k(C_S,3)); I(8,k(C_S,3)); I(12,k(C_S,3));


    printf("WRITING PATTERN 0 CHAN 8\n");
    CHAN_INDX(8);
    PTRN_INDX(0);
    INSTR_INDX(BASSGUITAR);
    VOLUME(1.f);
    I(0, k(C_S, 2), ui32(0x13820000)); //R(31);
    I(32, k(B, 1)); R(60);
    I(62, k(A_S, 1));

    printf("WRITING PATTERN 1 CHAN 8\n");
    PTRN_INDX(1);
    //R(31);
    I(32, k(B, 1)); //R(45);
    I(46, k(G_S, 1)); R(58);
    I(59, k(C_S, 2),0, ui32(0x1B100000));
    I(60, k(G_S, 1));

    printf("WRITING PATTERN 2 CHAN 8\n");
    PTRN_INDX(2);
    I(0, k(C_S, 2), ui32(0x1B000000)); //R(1);
    I(32, k(B,1)); R(49);
    I(48, k(B,1)); R(59);
    I(50, k(B,1)); R(51);
    I(52, k(B,1)); R(53);
    I(54, k(B,1)); R(59);
    I(60, k(B,1)); R(61);
    I(62, k(A_S,1));

    printf("WRITING PATTERN 1 CHAN 8\n");
    PTRN_INDX(3);
    //R(31);
    I(32, k(B, 1)); //R(45);
    I(46, k(G_S, 1)); R(58);
    I(60, k(G_S, 1));

    printf("WRITING PATTERN 4 CHAN 3\n");
    PTRN_INDX(4);
    I(0, k(C_S, 2), ui32(0x1F000507));
    I(2, k(C_S, 2));
    I(4, k(C_S, 2));
    I(6, k(C_S, 2));
    I(8, k(C_S, 2));
    I(10, k(C_S, 2));
    I(12, k(C_S, 2));

    I(14, k(C, 2), ui32(0x1F000F01));
    I(18, k(C, 2), ui32(0x1F00050F));
    I(20, k(C, 2));
    I(22, k(C, 2));
    I(24, k(C, 2));
    I(26, k(C, 2));
    I(28, k(C, 2));
    I(30, k(C, 2));
    I(31, k(C, 2));

    I(32+0, k(A_S, 1));
    I(32+2, k(A_S, 1));
    I(32+4, k(A_S, 1));
    I(32+6, k(A_S, 1));
    I(32+8, k(A_S, 1));
    I(32+10, k(A_S, 1));
    I(32+12, k(A_S, 1));

    I(32+14, k(G_S, 1), ui32(0x1F000F01));
    I(32+18, k(G_S, 1), ui32(0x1F00050F));
    I(32+20, k(G_S, 1));
    I(32+22, k(G_S, 1));
    I(32+24, k(G_S, 1));
    I(32+26, k(G_S, 1));
    I(32+28, k(G_S, 1));
    I(32+30, k(G_S, 1));
    I(32+31, k(G_S, 1));

    printf("WRITING PATTERN 5 CHAN 3\n");
    PTRN_INDX(5);
    I(0, k(F_S, 1));
    I(2, k(F_S, 1));
    I(4, k(F_S, 1));
    I(6, k(F_S, 1));
    I(8, k(F_S, 1));
    I(10, k(F_S, 1));
    I(12, k(F_S, 1));

    I(14, k(F,1), ui32(0x1F000F01));
    I(18, k(F,1), ui32(0x1F00050F));
    I(20, k(F,1));
    I(22, k(F,1));
    I(24, k(F,1));
    I(26, k(F,1));
    I(28, k(F,1));
    I(30, k(F,1));

    I(32 + 0, k(D_S, 1));
    I(32 + 2, k(D_S, 1));
    I(32 + 4, k(D_S, 1));
    I(32 + 6, k(D_S, 1));
    I(32 + 8, k(D_S, 1));
    I(32 + 10, k(D_S, 1));
    I(32 + 12, k(D_S, 1));

    I(32+14, k(G_S, 1), ui32(0x1F000F01));
    I(50, k(G_S, 1), ui32(0x1F000504));
    I(52, k(G_S, 1));
    I(54, k(G_S, 1));
    I(55, k(G_S, 1));
    I(56, k(G_S, 1), ui32(0x1F000F01));
    I(60, k(G_S, 1), ui32(0x1F000503));
    I(62, k(G_S, 1));
    I(63, k(G_S, 1));

    printf("WRITING PATTERN 8 CHAN 3\n");
    PTRN_INDX(8);
    I(0, k(A_S,1), ui32(0x1F000F01));
    I(4, k(A_S,1), ui32(0x1F000A01));
    I(6, k(A_S,1), ui32(0x1F000503));
    I(8, k(A_S,1));
    I(9, k(A_S,1));
    I(10, k(A_S,1), ui32(0x1F000A01));
    I(12, k(A_S,1), ui32(0x1F000502));
    I(14, k(A_S,1));

    I(16, k(G_S,1), ui32(0x1F000F01));
    I(20, k(G_S,1), ui32(0x1F000503));
    I(22, k(G_S,1));
    I(24, k(G_S,1));
    I(26, k(G_S,1), ui32(0x1F000F01));
    I(30, k(G_S,1), ui32(0x1F000501));

    I(32, k(F_S,1), ui32(0x1F000F01));
    I(36, k(F_S,1), ui32(0x1F000505));
    I(38, k(F_S,1));
    I(40, k(F_S,1));
    I(42, k(F_S,1));
    I(44, k(F_S,1));
    I(46, k(F_S,1), ui32(0x1F000F02));

    I(50, k(G_S,1));
    I(54, k(D_S,1), ui32(0x1F000501));
    I(56, k(G_S,1), ui32(0x1F000F01));
    I(60, k(D_S,1), ui32(0x1F000502));
    I(62, k(D_S,1));

    printf("WRITING PATTERN 9 CHAN 3\n");
    PTRN_INDX(9);
    I(0, k(A_S,1), ui32(0x1F000F01));
    I(4, k(A_S,1), ui32(0x1F000A01));
    I(6, k(A_S,1), ui32(0x1F000503));
    I(8, k(A_S,1));
    I(9, k(A_S,1));
    I(10, k(A_S,1), ui32(0x1F000A01));
    I(12, k(A_S,1), ui32(0x1F000502));
    I(14, k(A_S,1));

    I(16, k(G_S,1), ui32(0x1F000F01));
    I(20, k(G_S,1), ui32(0x1F000503));
    I(22, k(G_S,1));
    I(24, k(G_S,1));
    I(26, k(G_S,1), ui32(0x1F000F01));
    I(30, k(G_S,1), ui32(0x1F000501));

    I(32, k(F_S,1), ui32(0x1F000F01));
    I(36, k(F_S,1), ui32(0x1F000505));
    I(38, k(F_S,1));
    I(40, k(F_S,1));
    I(42, k(F_S,1));
    I(44, k(F_S,1));
    I(46, k(F_S,1), ui32(0x1F000F02));

    I(50, k(G_S,1), ui32(0x1F000A07));
    I(52, k(G_S,1));
    I(54, k(G_S,1));
    I(56, k(G_S,1));
    I(58, k(G_S,1));
    I(60, k(A_S,1));
    I(62, k(C,2));

    printf("WRITING PATTERN 10 CHAN 3\n");
    PTRN_INDX(10);
    I(0, k(C_S,2));

    printf("WRITING PATTERN 11 CHAN 3\n");
    PTRN_INDX(11);
    I(0, k(C_S,2));
    I(16, k(C,2));
    I(32, k(A_S,1));
    I(46, k(G_S,1));

    printf("WRITING PATTERN 12 CHAN 3\n");
    PTRN_INDX(12);
    I(0, k(F_S,1));
    I(16 + 0, k(F,1));
    I(32 + 0, k(D_S,1));
    I(46, k(G_S,1));
    I(62, k(C,2), ui32(0x1F000A01));

    printf("WRITING PATTERN 13 CHAN 3\n");
    PTRN_INDX(13);
    I(0, k(C_S,2));
    I(16 + 0, k(C,2));
    I(30, k(B,1));

    I(48, k(A_S,1), ui32(0x1F000A01));
    I(48 + 2,  k(A_S,1), ui32(0x1F000502));
    I(48 + 4,  k(A_S,1));
    I(48 + 6,  k(A_S,1), ui32(0x1F000F01));
    I(48 + 10,  k(A_S,1), ui32(0x1F000503));
    I(48 + 12,  k(A_S,1));
    I(48 + 14,  k(A_S,1));

    printf("WRITING PATTERN 14 CHAN 3\n");
    PTRN_INDX(14);
    I(0, k(F_S,1));
    I(12, k(F_S,1), ui32(0x1F000F01));

    I(16, k(F,1));
    I(32, k(D_S,1), ui32(0x1F000A04));
    I(36, k(D_S,1));
    I(40, k(G_S,1));
    I(42, k(G_S,1));
    I(46, k(C_S,2));

#define EPI Editor::enterPatternIndice


    EPI(0,0,15); EPI(0,1,0); EPI(0,2,1); EPI(0,3,2); EPI(0,4,3); EPI(0,5,4);
    EPI(0,6,4); EPI(0,7,4); EPI(0,8,5); EPI(0,9,8); EPI(0,10,9); EPI(0,11,10);
    EPI(0,12,11); EPI(0,13,12); EPI(0,14,12); EPI(0,15,14);

    EPI(1,0,15); EPI(1,1,0); EPI(1,2,1);EPI(1,3,0); EPI(1,4,1); EPI(1,5,4);
    EPI(1,6,5); EPI(1,7,4); EPI(1,8,5); EPI(1,9,8); EPI(1,10,9); EPI(1,11,10);
    EPI(1,12,4); EPI(1,13,5); EPI(1,14,13); EPI(1,15,14);

    EPI(2,0,15); EPI(2,1,0); EPI(2,2,1); EPI(2,3,0); EPI(2,4,1); EPI(2,5,4);
    EPI(2,6,5); EPI(2,7,6); EPI(2,8,7); EPI(2,9,8); EPI(2,10,9); EPI(2,11,10);
    EPI(2,12,11); EPI(2,13,12); EPI(2,14,13); EPI(2,15,14);


    EPI(3,0,15); EPI(3,1,0); EPI(3,2,1); EPI(3,3,2); EPI(3,4,3); EPI(3,5,4);
    EPI(3,6,5); EPI(3,7,4); EPI(3,8,5); EPI(3,9,8); EPI(3,10,9); EPI(3,11,10);
    EPI(3,12,11); EPI(3,13,12); EPI(3,14,13); EPI(3,15,14);

    EPI(4,0,15); EPI(4,1,0); EPI(4,2,1); EPI(4,3,0); EPI(4,4,1); EPI(4,5,4);
    EPI(4,6,5); EPI(4,7,4); EPI(4,8,5); EPI(4,9,8); EPI(4,10,9); EPI(4,11,10);
    EPI(4,12,4); EPI(4,13,5); EPI(4,14,13); EPI(4,15,14);


    EPI(5,0,15); EPI(5,1,0); EPI(5,2,1);  EPI(5,3,0); EPI(5,4,0); EPI(5,5,4);
    EPI(5,6,5); EPI(5,7,6); EPI(5,8,7); EPI(5,9,8); EPI(5,10,9); EPI(5,11,10);
    EPI(5,12,11); EPI(5,13,12); EPI(5,14,13); EPI(5,15,14);

    EPI(6,0,15); EPI(6,1,0); EPI(6,2,0); EPI(6,3,0); EPI(6,4,0); EPI(6,5,4);
    EPI(6,6,5); EPI(6,7,6); EPI(6,8,7); EPI(6,9,8); EPI(6,10,8); EPI(6,11,10);
    EPI(6,12,11); EPI(6,13,12); EPI(6,14,13); EPI(6,15,14);

    EPI(7,0,15); EPI(7,1,0); EPI(7,2,1); EPI(7,3,2); EPI(7,4,3); EPI(7,5,4);
    EPI(7,6,5); EPI(7,7,5); EPI(7,8,7); EPI(7,9,8); EPI(7,10,9); EPI(7,11,10);
    EPI(7,12,11); EPI(7,13,12); EPI(7,14,13); EPI(7,15,14);


    EPI(8,0,15); EPI(8,1,0); EPI(8,2,1); EPI(8,3,2); EPI(8,4,3); EPI(8,5,4);
    EPI(8,6,5); EPI(8,7,4); EPI(8,8,5); EPI(8,9,8); EPI(8,10,9); EPI(8,11,10);
    EPI(8,12,11); EPI(8,13,12); EPI(8,14,13); EPI(8,15,14);

    this->setPatterns(patterns);
    this->setPatternsIndices(pattern_indices);
}



