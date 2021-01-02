//
// Created by Administrateur on 02/01/2021.
//
#include "examples.hpp"

namespace fzero_intro{
    C0deTracker::Track* init_track(){
        auto** instruments_bank = new C0deTracker::Instrument*[INSTRUMENTS];
        instruments_bank[TRUMPET] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::TRIANGLE, .08f, 0.5f, C0deTracker::ADSR(69.f,3.33f,0.0f,4.f)), 0.2f);
        instruments_bank[SNARE] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::WHITENOISE, 0.002f, C0deTracker::ADSR(100000.f, 16.66f, 0.0f, 1.f)), 0.44f);
        instruments_bank[BASS] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::TRIANGLE, .6f, 0.f, C0deTracker::ADSR(100.0f, 6.f, 0.0f, 5.33f)), 1.f);
        instruments_bank[BRASS] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::TRIANGLE, .12f, 0.0f, C0deTracker::ADSR(33.f,3.33f,0.4f,2.f)), 0.4f);
        instruments_bank[MAIN] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::SINUS,.025f, 0.5f, C0deTracker::ADSR(6.64f,0.f,0.0f,4.f)), 0.33f);

        using C0deTracker::Editor;
        using C0deTracker::Key;
        using namespace C0deTracker::Notes;

        Editor::loadTrackProperties(ROWS, FRAMES, CHANNELS, fx_per_chan); //Load track propreties in the editor
        auto** patterns = Editor::loadEmptyPatterns(); //generate empty patterns for song writing
        auto** pattern_indices = Editor::loadEmptyPatternsIndices(); //generate empty patterns indices for patterns indexing
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
        INSTR(TRUMPET);
        VOLM(0.5f);
        PATRN(0);
        I(0, K(D_S,5));
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
        I(16, K(D_S,5));
        I(17, K(D_S,5));
        P(0,1,0); P(0,2,0); P(0,3,0); P(0,4,0); P(0,5,0); P(0,6,0); P(0,7,0);

        CHANL(1);
        INSTR(TRUMPET);
        VOLM(0.5f);
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
        I(16, K(D_S,4));
        I(17, K(D_S,4));
        P(1,1,0); P(1,2,0); P(1,3,0); P(1,4,0); P(1,5,0); P(1,6,0); P(1,7,0);

        CHANL(2);
        INSTR(SNARE);
        VOLM(0.6f);
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
        I(16, K(D_S,2));
        I(17, K(D_S,2));
        P(2,1,0); P(2,2,0); P(2,3,0); P(2,4,0); P(2,5,0); P(2,6,0); P(2,7,0);

        CHANL(3);
        INSTR(BASS);
        VOLM(1.f);
        PATRN(0);
        I(0, K(D_S,3));
        I(2, K(D_S,2));
        I(4, K(A_S,2));
        I(6, K(D_S,3));

        I(0+8, K(D_S,3));
        I(2+8, K(D_S,2));
        I(4+8, K(A_S,2));
        I(6+8, K(D_S,3));
        P(3,1,0); P(3,2,0); P(3,3,0); P(3,4,0); P(3,5,0); P(3,6,0); P(3,7,0);

        CHANL(4);
        INSTR(BRASS);
        VOLM(0.6f);
        PATRN(0);
        I(0, K(G,4), UI32(0x13800000));
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

        P(4, 3, 1);

        P(4,4,0); P(4,5,1); P(4,6,2); P(4,7,3);

        CHANL(5);
        INSTR(BRASS);
        VOLM(0.6f);
        PATRN(0);
        I(0, K(A_S,3), UI32(0x13800000));
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

        P(5, 3, 1);

        P(5,4,0); P(5,5,1); P(5,6,2); P(5,7,3);

        CHANL(6);
        INSTR(MAIN);
        VOLM(1.f);
        PATRN(4);
        I(0, K(G,4));
        I(2, K(G_S,4));
        I(4, K(A_S,4));
        I(6, K(D_S, 5));
        I(10, K(F, 5));
        I(12, K(G,5));
        PATRN(5);
        I(10, K(G_S,5));
        I(12, K(A_S,5));
        I(14, K(F,5));
        PATRN(6);
        R(11);
        I(12, K(D_S,5));
        I(14, K(G,5));
        PATRN(7);
        R(15);



        return new C0deTracker::Track(CLOCK, BASETIME, SPEED, ROWS, FRAMES, CHANNELS, instruments_bank, INSTRUMENTS, patterns, pattern_indices, fx_per_chan);
    }
}