//
// Created by Abdulmajid, Olivier NASSER on 23/12/2020.
//

#include "tutorial.hpp"

namespace my_song{
    C0deTracker::Track* init_track(){
        auto** instruments_bank = new C0deTracker::Instrument*[INSTRUMENTS];
        instruments_bank[MAIN] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::SQUARE, 0.5f, C0deTracker::ADSR(5.5f,5.5f,0.2f,1.f)), 0.1f);
        instruments_bank[BASS] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::TRIANGLE, 0.8f, 0.5f, C0deTracker::ADSR(400.0f, 10.f, 0.0f, 10.f)), 1.f);
        instruments_bank[KICK] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::WHITENOISE, 0.1f, C0deTracker::ADSR(10000.f, 50.75f, 0.0f, 0.f)), 0.64f);
        instruments_bank[SNARE] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::WHITENOISE, 0.0025f, C0deTracker::ADSR(100000.f, 9.66f, 0.0f, 1.f)), .8f);

        using C0deTracker::Editor;
        using C0deTracker::Key;
        using namespace C0deTracker::Notes;

        Editor::loadTrackProperties(ROWS, FRAMES, CHANNELS, fx_per_chan); //Load track propreties in the editor
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

        CHANL(0);
        PATRN(0);
        INSTR(MAIN);
        VOLM(0.5f);

        I(0, K(C,5));
        R(2);
        I(4, K(D,5));
        R(6);
        I(8, K(E,5));
        R(10);
        I(12, K(F,5));
        R(14);
        I(16, K(G,5));
        R(18);
        I(20, K(A,5));
        R(22);
        I(24, K(B,5));
        R(26);

        P(0,1,0); //frames 1 points to pattern 0

        PATRN(2);//dont forget to select the correct pattern
        I(2, K(B,5));
        R(4);
        I(6, K(G,5));
        R(8);
        I(10, K(C,5));
        R(18);

        P(0,3,2);//frames 3 points to pattern 2

        CHANL(1);
        PATRN(0);
        INSTR(BASS);
        VOLM(1.f);
        I(0, K(C, 2));
        I(4, K(C, 2));
        I(8, K(C, 2));
        I(12, K(A, 2));
        I(16, K(F, 2));
        I(20, K(F, 2));
        I(24, K(F, 2));

        PATRN(1);
        I(0, K(C, 2));
        I(2, K(C, 2));
        I(4, K(C, 2));
        I(6, K(C, 2));
        I(8, K(C, 2));
        I(10, K(C, 2));
        I(12, K(A, 2));
        I(14, K(A, 2));
        I(16, K(F, 2));
        I(18, K(F, 2));
        I(20, K(F, 2));
        I(22, K(F, 2));
        I(24, K(F, 2));
        I(26, K(F, 2));

        PATRN(2);
        I(0, K(F,2));
        I(4, K(B,2));
        I(8, K(F,2));
        I(10, K(C,2));
        I(14, K(G,1));
        I(16, K(G,1));
        I(18, K(G,1));

        P(1,3,2);//repeating the pattern

        CHANL(2);
        PATRN(0);
        INSTR(KICK);
        VOLM(.3f);
        I(0, K(A,1));
        I(4, K(A,1));
        I(8, K(A,1));
        I(10, K(A,1));
        I(12, SNARE, K(A,2));
        I(14, K(A,1));
        I(16, K(A,1));
        I(20, SNARE, K(A,2));
        I(22, K(A,1));
        I(26, K(A,1));

        PATRN(1);
        I(0, SNARE, K(A,2));
        I(4, K(A,1));
        I(8, SNARE, K(A,2));
        I(12, K(A,1));
        I(13, K(A,1));
        I(16, SNARE, K(A,2));
        I(20, K(A,1));
        I(22, K(A,1));
        I(24, SNARE, K(A,2));
        I(26, SNARE, K(A,2));
        I(27, SNARE, K(A,2));

        PATRN(2);
        I(2, K(A,1));
        I(4, K(A,1));
        I(8, K(A,1));
        I(12, K(A,1));
        I(14, K(A,1));
        I(17, SNARE, K(A,2));
        I(18, SNARE, K(A,2));

        P(2,3,2);//repeating the pattern

        return new C0deTracker::Track(CLOCK, BASETIME, SPEED, ROWS, FRAMES, CHANNELS, instruments_bank, INSTRUMENTS, patterns, pattern_indices, fx_per_chan);
    }
}