//
// Created by Abdulmajid, Olivier NASSER on 01/01/2021.
//
#include "examples.hpp"

namespace frere_jacques{
    C0deTracker::Track* init_track(){
        auto** instruments_bank = new C0deTracker::Instrument*[INSTRUMENTS];
        instruments_bank[MAIN] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::TRIANGLE,1.f, 0.5f, C0deTracker::ADSR(4.66f,2.f,0.5f,4.f)), 0.6f);
        instruments_bank[BASS] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::SINUS, .5f, 0.f, C0deTracker::ADSR(1000.0f, 2.f, 0.2f, 5.33f)), 1.f);

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

        I(0,K(D,4));
        R(3);
        I(4,K(E,4));
        R(7);
        I(8,K(F_S,4));
        R(11);
        I(12,K(D,4));
        R(15);
        P(0,1,0);//frames 1 points to pattern 0

        PATRN(2);
        I(0,K(D,4));
        R(3);
        I(4,K(E,4));
        R(7);
        I(8,K(F_S,4));
        R(15);
        P(0,3,2);//frames 3 points to pattern 2

        PATRN(4);
        I(0,K(A,4));
        R(1);
        I(2,K(B,4));
        R(3);
        I(4,K(A,4));
        R(5);
        I(6,K(G,4));
        R(7);
        I(8,K(F_S,4));
        R(11);
        I(12,K(D,4));
        R(15);

        P(0, 5, 4); //frames 5 points to pattern 4

        PATRN(6);
        I(0, K(D, 4));
        R(3);
        I(4, K(A,3));
        R(7);
        I(8, K(D, 4));
        R(15);
        //P(0, 7, 6);

        PATRN(7);
        I(0, K(D, 4));
        R(3);
        I(4, K(A,3));
        R(7);
        I(8, K(D, 4));
        PATRN(8);
        R(0);


        CHANL(1);
        VOLM(0.33);
        PATRN(2);
        I(0, K(F_S,4));
        R(3);
        I(4, K(G,4));
        R(7);
        I(8, K(A,4));
        R(15);
        P(1, 3, 2); //frames 3 points to pattern 2

        PATRN(4);
        I(0, K(D,4));
        R(3);
        I(4, K(C_S,4));
        R(7);
        I(8, K(D,4));
        R(11);
        P(1, 5, 4); //frames 5 points to pattern 4

        CHANL(2);
        VOLM(1.f);
        INSTR(BASS);
        PATRN(0);
        I(0, K(F_S,2));
        R(3);
        I(4, K(G,2));
        R(7);
        I(8, K(A,2));
        R(11);
        I(12, K(F_S,2));
        R(15);
        P(2, 1, 0);

        PATRN(2);
        I(0, K(D,2));
        R(3);
        I(4, K(E,2));
        R(7);
        I(8, K(F_S,2));
        R(15);
        P(2, 3, 2);

        PATRN(4);
        I(0, K(F_S, 2));
        R(3);
        I(4, K(G, 2));
        R(7);
        I(8, K(A, 2));
        R(15);
        P(2, 5,4);

        PATRN(6);
        I(0, K(E, 2));
        R(3);
        I(4, K(F_S,2));
        R(7);
        I(8, K(E, 2));
        R(15);
        P(2, 7, 6);
        PATRN(8);
        R(0);

        return new C0deTracker::Track(CLOCK, BASETIME, SPEED, ROWS, FRAMES, CHANNELS, instruments_bank, INSTRUMENTS, patterns, pattern_indices, fx_per_chan);
    }
}
