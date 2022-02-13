//
// Created by Abdulmajid, Olivier NASSER on 13/02/2022.
//

#include "nokia3310_DUSHMAN_REMOVER.hpp"

Nokia3310_DUSHMAN_REMOVER_GameOver::Nokia3310_DUSHMAN_REMOVER_GameOver() {
    this->setName(NAME);
    this->setSizeDimensions(ROWS, FRAMES, CHANNELS, FX_per_CHAN);
    this->setTimeDimensions(CLOCK, SPEED, BASETIME);
}

void Nokia3310_DUSHMAN_REMOVER_GameOver::load_data() {
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

    //UI32(0x1F0006FF)
    CHANL(0);
    INSTR(0);
    VOLM(1.f);
    PATRN(0);
    I(0, K(G,6));//
    I(2, K(F,6));
    I(4, K(E,6));
    I(6, K(A,5));
    PATRN(1);
    I(0, K(G-2,6));//
    I(2, K(F-2,6));
    I(4, K(E-2,6));
    I(6, K(A-2,5));

    this->setPatterns(patterns);
    this->setPatternsIndices(pattern_indices);
}