//
// Created by Abdulmajid, Olivier NASSER on 16/01/2021.
//

#include "examples.hpp"

namespace kirbys_dreamland_greengreens {
    C0deTracker::Track *init_track() {
        auto **instruments_bank = new C0deTracker::Instrument *[INSTRUMENTS];
        instruments_bank[TRIMAIN] = new C0deTracker::Instrument(
                new C0deTracker::PSG(C0deTracker::TRIANGLE, 1.f, 0.5f, C0deTracker::ADSR(100.0f, 0.f, 0.0f, 100.f)),
                1.f);


        using C0deTracker::Editor;
        using C0deTracker::Key;
        using namespace C0deTracker::Notes;

        Editor::loadTrackProperties(ROWS, FRAMES, CHANNELS, fx_per_chan); //Load track propreties in the editor
        auto **patterns = Editor::loadEmptyPatterns(); //generate empty patterns for song writing
        auto **pattern_indices = Editor::loadEmptyPatternsIndices(); //generate empty patterns indices for patterns indexing
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

        VOLM(0.7f);
        CHANL(TRIANGLE2);
        PATRN(0);
        INSTR(TRIMAIN);
        I(0x00, K(F_S, 4), UI32(0x1F000309));
        I(0x01, K(F_S, 4));
        I(0x03, K(F_S, 4));
        I(0x04, K(F_S, 4));
        I(0x06, K(F_S, 4));
        I(0x08, K(F_S, 4));
        I(0x0A, K(C_S, 6));
        I(0x0B, K(C_S, 6));
        I(0x0C, K(C_S, 6));
        I(0x0E, K(F_S, 3), UI32(0x1A820401));

        PATRN(1);
        I(0x00, K(B,2), UI32(0x1F000E02));

        PATRN(2);
        I(0x00, K(B,2), UI32(0x1F000E02));
        P(TRIANGLE2, 2,1);




        return new C0deTracker::Track(CLOCK, BASETIME, SPEED, ROWS, FRAMES, CHANNELS, instruments_bank, INSTRUMENTS,
                                      patterns, pattern_indices, fx_per_chan);

    }


}