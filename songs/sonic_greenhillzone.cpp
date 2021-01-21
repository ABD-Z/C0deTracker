//
// Created by Abdulmajid, Olivier NASSER on 21/01/2021.
//

#include "examples.hpp"

namespace sonic_green_hill_zone{
    C0deTracker::Track *init_track() {
        auto **instruments_bank = new C0deTracker::Instrument *[INSTRUMENTS];
        instruments_bank[HITHAT] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::WHITENOISE, 0.00377f, C0deTracker::ADSR(100.f, 10.f, 0.0f, 0.f)), .56f);

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

        VOLM(0.75f);
        CHANL(0);
        PATRN(0);
        I(0x00, K(A,2));
        I(0x08, K(A,2));
        I(0x10, K(A,2));
        I(0x18, K(A,2));
        I(0x1C, K(A,2));





        return new C0deTracker::Track(CLOCK, BASETIME, SPEED, ROWS, FRAMES, CHANNELS, instruments_bank, INSTRUMENTS,
                                      patterns, pattern_indices, fx_per_chan);
    }
}
