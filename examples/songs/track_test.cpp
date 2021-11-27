//
// Created by Abdulmajid, Olivier NASSER on 14/11/2021.
//

#include "examples.hpp"

Track_Test::Track_Test() {
    this->setName(NAME);
    this->setSizeDimensions(ROWS, FRAMES, CHANNELS, FX_per_CHAN);
    this->setTimeDimensions(CLOCK, SPEED, BASETIME);
}


void Track_Test::load_data() {
    Track_Data::load_data();

    if(!IS_GLOBAL_INSTRUMENTS_BANK_INITIALISED)
        initGlobalInstruments();

    this->setGlobalInstrumentsDataBank(GLOBAL_INSTRUMENTS_BANK, GLOBAL_NUMBER_OF_INSTRUMENTS);

    using namespace C0deTracker::Notes; using namespace C0deTracker;
#define VOLM Editor::storeVolume
#define CHANL Editor::storeChannelIndex
#define PATRN Editor::storePatternIndex
#define INSTR Editor::storeInstrumentIndex
#define I Editor::enterInstruction
#define R Editor::release
#define P Editor::enterPatternIndice
#define K Key
#define UI32 uint_fast32_t

    Editor::loadTrackProperties(ROWS, FRAMES, CHANNELS, FX_per_CHAN); //Load track propreties in the editor
    auto** patterns = Editor::loadEmptyPatterns(); //generate empty patterns for song writing
    auto* pattern_indices = Editor::loadEmptyPatternsIndices(); //generate empty patterns indices for patterns indexing

    Editor::storePatterns(patterns); // store patterns in editor
    Editor::storePatternsIndices(pattern_indices); // store pattern indices in editor

    VOLM(0.75);

    VOLM(1.0);
    CHANL(CHAN0);
    INSTR(KICK);
    PATRN(0);
    I(0, K(C_S, 2));
    I(8, SNARE, K(D_S,4), 0.6f, UI32(0x1F000501));

    this->setPatterns(patterns);
    this->setPatternsIndices(pattern_indices);

}

