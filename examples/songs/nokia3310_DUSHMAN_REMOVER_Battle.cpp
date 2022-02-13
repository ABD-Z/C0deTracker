//
// Created by Abdulmajid, Olivier NASSER on 13/02/2022.
//

#include "nokia3310_DUSHMAN_REMOVER.hpp"

Nokia3310_DUSHMAN_REMOVER_Battle::Nokia3310_DUSHMAN_REMOVER_Battle() {
    this->setName(NAME);
    this->setSizeDimensions(ROWS, FRAMES, CHANNELS, FX_per_CHAN);
    this->setTimeDimensions(CLOCK, SPEED, BASETIME);
}

void Nokia3310_DUSHMAN_REMOVER_Battle::load_data() {
    Track_Data::load_data();
    auto *instruments_data_bank = new C0deTracker::Instrument_Data[INSTRUMENTS];
    instruments_data_bank[0].setData(C0deTracker::NOKIA3310, C0deTracker::ADSR(100.f,0.f,1.0f,100.f), 1.f, 0.0f, .00f, 0.0f);
    this->setInstrumentsDataBank(instruments_data_bank, INSTRUMENTS);

    using C0deTracker::Editor;
    using C0deTracker::Key;
    using namespace C0deTracker::Notes;

    Editor::loadTrackProperties(ROWS, FRAMES, CHANNELS, FX_per_CHAN); //Load track propreties in the editor
    auto** patterns = Editor::loadEmptyPatterns(); //generate empty patterns for song writing
    auto* pattern_indices = Editor::loadEmptyPatternsIndices(); //generate empty patterns indices for patterns indexing
    Editor::storePatterns(patterns); // store patterns in editor
    Editor::storePatternsIndices(pattern_indices); // store pattern indices in editor

#define VOLM Editor::storeVolume
#define CHANL Editor::storeChannelIndex
#define PATRN Editor::storePatternIndex
#define INSTR Editor::storeInstrumentIndex
#define I Editor::enterInstruction
#define R Editor::release
#define P Editor::enterPatternIndice
#define K Key
#define UI32 uint_fast32_t

    UI32 stop4 = 0x1F000604;
    UI32 stop1 = 0x1F000601;
    //UI32(0x1F0006FF)
    CHANL(0);
    INSTR(0);
    VOLM(1.f);
    PATRN(0);
    I(0, K(D,5));
    I(4, stop4);
    I(6, K(D,5));
    I(8, K(D,5));
    I(10, K(D,5));

    PATRN(2);
    I(0, K(D+2,5));
    I(4, stop4);
    I(6, K(D+2,5));
    I(8, K(D+2,5));
    I(10, K(D+2,5));

    PATRN(4);
    I(0, K(C,5));
    I(4, stop4);
    I(6, K(C,5));
    I(8, K(C,5));
    I(10, K(C,5));

    PATRN(7);
    I(0, K(D,5));
    I(4, stop4);
    I(6, K(A,6));
    I(8, K(G,6));
    I(10, K(F,6));

    PATRN(15);
    I(0, K(D,5));
    I(4, stop1);
    I(6, K(F,5));
    R(8);
    I(9, K(G,5));
    R(11);

    //*************
    PATRN(16);
    I(0, K(D,5));
    I(4, stop4);
    I(6, K(A,5));
    I(8, K(G,5));
    I(10, K(F,5));

    PATRN(18);
    I(0, K(E,5));
    I(4, stop4);
    I(6, K(G,5));
    I(8, K(F,5));
    I(10, K(D,5));

    PATRN(20);
    I(0, K(C,5));
    I(4, stop4);
    I(6, K(C,5));
    I(8, K(E,5));
    I(10, K(D,5));

    PATRN(21);
    I(0, K(C,5));
    I(4, stop4);
    I(6, K(C,5));
    I(8, K(E,5));
    I(10, K(C,5));


    PATRN(24);
    I(0, K(D,5));
    I(4, stop4);
    I(6, K(A,5));
    I(8, K(G,5));
    I(10, K(E,5));

    PATRN(25);
    I(0, K(D,5));
    I(4, stop4);
    I(6, K(A,5));
    I(8, K(G,5));
    I(10, K(A,5));

    PATRN(27);
    I(0, K(E,5));
    I(4, stop4);
    I(6, K(G,5));
    I(8, K(F,5));
    I(10, K(A,5));

    PATRN(29);
    I(0, K(C,5));
    I(4, stop4);
    I(6, K(D,5));
    I(8, K(C,5));
    I(10, K(E,5));

    P(0,1,0); P(0,3,2); P(0,5,4); P(0,6,0);

    P(0,8,0); P(0,9,0);
    P(0,10,2); P(0,11,2);
    P(0,12,4); P(0,13,4);
    P(0,14,0);

    P(0,17,16);
    P(0,19,18);
    P(0,22,0); P(0,23,7);

    P(0,26,18); P(0,28,20);
    P(0,30,0); P(0,31,15);

    this->setPatterns(patterns);
    this->setPatternsIndices(pattern_indices);
}