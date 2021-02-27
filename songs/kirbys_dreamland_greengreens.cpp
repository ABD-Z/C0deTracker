//
// Created by Abdulmajid, Olivier NASSER on 16/01/2021.
//

#include "examples.hpp"

namespace kirbys_dreamland_greengreens {
    C0deTracker::Track *init_track() {
        auto **instruments_bank = new C0deTracker::Instrument *[INSTRUMENTS];
        instruments_bank[TRIMAIN] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::TRIANGLE, 1.f, 0.5f, C0deTracker::ADSR(100.0f, 0.f, 0.0f, 100.f)),1.f);
        instruments_bank[SQ50] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::SQUARE, .5f, 0.f, C0deTracker::ADSR(100.0f, 0.f, 0.0f, 100.f)),.3f);
        instruments_bank[SQ25] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::SQUARE, .25f, 0.f, C0deTracker::ADSR(100.0f, 0.f, 0.0f, 100.f)),.3f);
        instruments_bank[SQ125_LONG] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::SQUARE, .125f, 0.f, C0deTracker::ADSR(10.f, 0.f, 0.0f, 100.f)),.3f);
        instruments_bank[SQ125_SHORT] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::SQUARE, .125f, 0.f, C0deTracker::ADSR(80.f, 3.f, 0.0f, 100.f)),.3f);
        instruments_bank[SQ50_0A] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::SQUARE, .5f, 0.f, C0deTracker::ADSR(65.0f, 5.f, 0.3f, 100.f)),.3f);
        instruments_bank[SQ50_0B] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::SQUARE, .5f, 0.f, C0deTracker::ADSR(65.0f, 3.f, 0.2222f, 100.f)),.3f);
        instruments_bank[SQ50_0C] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::SQUARE, .5f, 0.f, C0deTracker::ADSR(65.0f, 5.f, 0.2222f, 100.f)),.3f);
        instruments_bank[SQ50_0D] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::SQUARE, .5f, 0.f, C0deTracker::ADSR(65.0f, 6.f, 0.2222f, 100.f)),.3f);
        instruments_bank[SQ50_0E] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::SQUARE, .5f, 0.f, C0deTracker::ADSR(1.767f, 4.4f, 0.1111f, 100.f)),.3f);
        instruments_bank[SQ50_0F] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::SQUARE, .5f, 0.f, C0deTracker::ADSR(65.f, 2.840909f, 0.f, 100.f)),.3f);
        instruments_bank[SQ50_10] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::SQUARE, .5f, 0.f, C0deTracker::ADSR(65.f, 100.f, 0.3f, 100.f)),.3f);
        instruments_bank[DRUM1] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::WHITENOISE, 0.00377f, C0deTracker::ADSR(100.f, 10.0f, 0.0f, 100.f)), .6f);
        instruments_bank[DRUM2] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::WHITENOISE, 0.00377f, C0deTracker::ADSR(100.f, 20.0f, 0.0f, 100.f)), .5f);
        instruments_bank[DRUM3] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::WHITENOISE, 0.00377f, C0deTracker::ADSR(100.f, 20.0f, 0.0f, 100.f)), .4f);
        instruments_bank[DRUM4] = new C0deTracker::Instrument(new C0deTracker::PSG(C0deTracker::WHITENOISE, 0.00377f, C0deTracker::ADSR(100.f, 20.0f, 0.0f, 100.f)), .3f);

        using C0deTracker::Editor;
        using C0deTracker::Key;
        using namespace C0deTracker::Notes;

        Editor::loadTrackProperties(ROWS, FRAMES, CHANNELS, fx_per_chan); //Load track propreties in the editor
        auto **patterns = Editor::loadEmptyPatterns(); //generate empty patterns for song writing
        auto *pattern_indices = Editor::loadEmptyPatternsIndices(); //generate empty patterns indices for patterns indexing
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


        CHANL(DPCM);
        PATRN(23);
        I(0xF, UI32(0x0A005000));
        VOLM(0.5f);
        CHANL(NOISE3);
        P(NOISE3, 1, 0); P(NOISE3, 2, 0); P(NOISE3, 3, 0);
        INSTR(DRUM1);
        PATRN(1);
        I(0x2, K(D_S,4));
        I(0x4, K(D_S,4));
        I(0x6, K(D_S,4));
        I(0x8, K(D_S,4));
        P(NOISE3, 4, 1);
        PATRN(2);
        INSTR(DRUM2);
        I(0x0, DRUM1, K(B, 2));
        I(0x2, K(C, 4));
        I(0x3, K(C, 4));
        I(0x4, DRUM1, K(B, 2));
        I(0x6, K(C, 4));
        I(0x7, K(C, 4));
        I(0x8, DRUM1, K(B, 2));
        I(0xA, K(C, 4));
        I(0xB, K(C, 4));
        I(0xC, DRUM3, K(B, 2));
        INSTR(DRUM4);
        I(0xD, K(C,4));
        I(0xE, K(B,4));
        I(0xF, K(C,4));
        P(NOISE3, 5, 2);
        P(NOISE3, 6, 2);
        P(NOISE3, 7, 2);
        P(NOISE3, 8, 2);
        P(NOISE3, 9, 2);
        P(NOISE3, 10, 2);
        P(NOISE3, 11, 2);
        P(NOISE3, 12, 2);
        PATRN(3);
        I(0x0, K(C,4));
        I(0x2, K(B,4));
        I(0x3, K(B,4));
        I(0x4, K(C,4));
        I(0x6, K(B,4));
        I(0x7, K(B,4));
        I(0x8, K(B,4));
        I(0xA, K(B,4));
        P(NOISE3, 13, 3);
        P(NOISE3, 14, 2);
        P(NOISE3, 15, 2);
        P(NOISE3, 16, 2);
        P(NOISE3, 17, 2);
        P(NOISE3, 18, 2);
        P(NOISE3, 19, 2);
        P(NOISE3, 20, 2);
        P(NOISE3, 21, 2);
        P(NOISE3, 22, 2);
        P(NOISE3, 23, 3);

        VOLM(0.3f);
        CHANL(PULSE1);
        INSTR(SQ50);
        PATRN(0);
        I(0x0, K(F_S,2), UI32(0x1F000303)); I(0x1, K(F_S,2));
        I(0x3, K(F_S,2)); I(0x4, K(F_S,2), UI32(0x1F000403));
        I(0x6, K(F_S,2)); I(0x8, K(F_S,2));
        I(0xA, K(F_S,5),  UI32(0x1F000203)); I(0xB, K(F_S,5)); I(0xC, K(F_S,5));
        I(0xE, K(F_S,2), UI32(0x1A820401));
        PATRN(1);
        R(0x0);
        I(0x2, K(D_S,4), UI32(0x1F000407));
        I(0x4, K(D_S,4));
        I(0x6, K(D_S,4));
        I(0x8, K(D_S,4));
        I(0xA, K(D_S,4));
        I(0xC, K(D_S,4));
        I(0xE, K(D_S,4));
        P(PULSE1, 2, 1);
        PATRN(2);
        R(0x0);
        I(0x2, K(E,4), UI32(0x1F000407));
        I(0x4, K(E,4));
        I(0x6, K(E,4));
        I(0x8, K(E,4));
        I(0xA, K(E,4));
        I(0xC, K(E,4));
        I(0xE, K(E,4));
        P(PULSE1, 3, 2);
        PATRN(3);
        INSTR(SQ25);
        I(0x2, K(E,5), UI32(0x1F000404));
        I(0x4, K(E,5));
        I(0x6, K(F_S,5));
        I(0x8, K(F_S,5));
        P(PULSE1, 4, 3);

        PATRN(4);
        VOLM(0.22);
        INSTR(SQ50);
        I(0x0, K(F_S,3)); I(0x2, K(D_S,4), UI32(0x1F000407));
        I(0x4, K(D_S,4)); I(0x6, K(D_S,4)); I(0x8, K(D_S,4)); I(0xA, K(D_S,4));
        I(0xC, K(D_S,4)); I(0xE, K(D_S,4));
        P(PULSE1, 5, 4);
        P(PULSE1, 6, 4);
        PATRN(5);
        I(0x0, K(G_S,3)); I(0x2, K(B,3), UI32(0x1F000403));
        I(0x4, K(B,3)); I(0x6, K(B,3));
        I(0x8, K(F_S,3)); I(0xA, K(A_S,3), UI32(0x1F000403));
        I(0xC, K(A_S,3)); I(0xE, K(A_S,3));
        P(PULSE1, 7, 5);
        P(PULSE1, 8, 4);
        P(PULSE1, 9, 4);
        P(PULSE1, 10, 4);
        PATRN(6);
        I(0x0, K(G_S,3)); I(0x2, K(B,3), UI32(0x1F000403));
        I(0x4, K(B,3)); I(0x6, K(B,3));
        I(0x8, K(G,3)); I(0xA, K(D_S,4), UI32(0x1F000403));
        I(0xC, K(D_S,4)); I(0xE, K(D_S,4));
        P(PULSE1, 11, 6);
        PATRN(7);
        I(0x0, K(B,3), UI32(0x1F000310));
        I(0x1, K(D_S,4)); I(0x2, K(B,3));
        I(0x3, K(D_S,4)); I(0x4, K(B,3));
        I(0x5, K(D_S,4)); I(0x6, K(B,3));
        I(0x7, K(D_S,4)); I(0x8, K(B,3));
        I(0x9, K(D_S,4)); I(0xA, K(B,3));
        I(0xB, K(D_S,4)); I(0xC, K(B,3));
        I(0xD, K(D_S,4)); I(0xE, K(B,3));
        I(0xF, K(D_S,4));
        P(PULSE1, 12, 7);
        PATRN(8);
        I(0x0, K(E,4), UI32(0x1F000701));
        I(0x3, K(E,4), UI32(0x1F000403));
        I(0x8, K(F_S,4));
        I(0xA, K(F_S,4));
        P(PULSE1, 13,8);
        PATRN(9);
        R(0x0);
        I(0x2, K(D_S,4), UI32(0x1F000407));
        I(0x4, K(D_S,4));
        I(0x6, K(D_S,4));
        I(0x8, K(D_S,4));
        I(0xA, K(D_S,4));
        I(0xC, K(D_S,4));
        I(0xE, K(D_S,4));
        P(PULSE1, 14,9);
        P(PULSE1, 15,9);

        PATRN(10);
        VOLM(0.445);
        INSTR(SQ125_LONG);
        I(0x0, K(G,4)); I(0x4, K(G,4));
        I(0x7, K(G,4)); I(0x8, K(C_S,5));
        I(0xC, K(B,4)); I(0xF, K(C_S,5));
        P(PULSE1, 16, 10);
        PATRN(11);
        I(0x0, K(D,5)); I(0x4, K(C_S,5));
        I(0x7, K(D,5)); I(0x8, K(G,4));
        I(0xC, K(G,4)); I(0xF, K(A,4));
        P(PULSE1, 17, 11);
        P(PULSE1, 18, 10);
        PATRN(12);
        I(0x0, K(D,5));
        INSTR(SQ125_SHORT);
        I(0x8, K(F_S,5));
        I(0xC, SQ50_0A, K(G,5));
        I(0xF, SQ50_10, K(A,5));
        P(PULSE1, 19, 12);
        PATRN(13);
        I(0x0, SQ50_0B, K(G,5));
        I(0x4, SQ50_0C, K(G,5));
        I(0x7, SQ50_0D, K(G,5));
        I(0x8, SQ50_0B, K(C_S,6));
        I(0xC, SQ50_0C, K(B, 5));
        I(0xF, SQ50_0D, K(C_S,6));
        P(PULSE1, 20, 13);
        PATRN(14);
        I(0x0, SQ50_0B, K(D,6));
        I(0x4, SQ50_0C, K(C_S,6));
        I(0x7, SQ50_0D, K(D,6));
        I(0x8, SQ50_0B, K(G,5));
        I(0xC, SQ50_0C, K(G,5));
        I(0xF, SQ50_0D, K(A,5));
        P(PULSE1, 21, 14);
        P(PULSE1, 22, 13);
        PATRN(15);
        I(0x0, SQ50_0E, K(A_S,5));
        I(0x8, SQ50_0F, K(A_S,5));
        P(PULSE1, 23, 15);


        CHANL(PULSE0);
        VOLM(0.3f);
        INSTR(SQ50);
        PATRN(0);
        I(0xA, K(E,5),  UI32(0x1F000303)); I(0xB, K(E,5)); I(0xC, K(E,5));
        PATRN(1);
        R(0x0);
        I(0x2, K(F_S,3), UI32(0x1F000407));
        I(0x4, K(F_S,3));
        I(0x6, K(F_S,3));
        I(0x8, K(F_S,3));
        I(0xA, K(F_S,3));
        I(0xC, K(F_S,3));
        I(0xE, K(F_S,3));
        P(PULSE0, 2, 1);
        PATRN(2);
        R(0x0);
        I(0x2, K(G_S,3), UI32(0x1F000407));
        I(0x4, K(G_S,3));
        I(0x6, K(G_S,3));
        I(0x8, K(G_S,3));
        I(0xA, K(G_S,3));
        I(0xC, K(G_S,3));
        I(0xE, K(G_S,3));
        P(PULSE0, 3, 2);
        PATRN(3);
        INSTR(SQ25);
        I(0x2, K(G_S,4), UI32(0x1F000404));
        I(0x4, K(G_S,4));
        I(0x6, K(G_S,4));
        I(0x8, K(A_S,4));
        P(PULSE0, 4, 3);

        PATRN(4);
        VOLM(0.35);
        INSTR(SQ50);
        I(0x0, K(B,2)); I(0x2, K(F_S,3), UI32(0x1F000407));
        I(0x4, K(F_S,3)); I(0x6, K(F_S,3)); I(0x8, K(F_S,3)); I(0xA, K(F_S,3));
        I(0xC, K(F_S,3)); I(0xE, K(F_S,3));
        P(PULSE0, 5, 4);
        P(PULSE0, 6, 4);

        PATRN(5);
        I(0x0, K(C_S,3)); I(0x2, K(G_S,3), UI32(0x1F000403));
        I(0x4, K(G_S,3)); I(0x6, K(G_S,3));
        I(0x8, K(C_S,3)); I(0xA, K(F_S,3), UI32(0x1F000403));
        I(0xC, K(F_S,3)); I(0xE, K(F_S,3));
        P(PULSE0, 7, 5);
        P(PULSE0, 8, 4);
        P(PULSE0, 9, 4);
        P(PULSE0, 10, 4);
        PATRN(6);
        I(0x0, K(C_S,3)); I(0x2, K(G_S,3), UI32(0x1F000403));
        I(0x4, K(G_S,3)); I(0x6, K(G_S,3));
        I(0x8, K(D_S,3)); I(0xA, K(A_S,3), UI32(0x1F000403));
        I(0xC, K(A_S,3)); I(0xE, K(A_S,3));
        P(PULSE0, 11, 6);
        PATRN(7);
        I(0x0, K(G_S,3));
        I(0x2, K(G_S,4), UI32(0x1F000403));
        I(0x4, K(G_S,4)); I(0x6, K(G_S,4));
        I(0x8, K(F_S,3));
        I(0xA, K(F_S,4), UI32(0x1F000403));
        I(0xC, K(F_S,4)); I(0xE, K(F_S,4));
        P(PULSE0, 12, 7);

        PATRN(8);
        I(0x0, K(G_S,3), UI32(0x1F000701));
        I(0x3, K(G_S,3), UI32(0x1F000403));
        I(0x8, K(A_S,3));
        I(0xA, K(A_S,3));
        P(PULSE0, 13,8);

        PATRN(9);
        R(0x0);
        I(0x2, K(F_S,3), UI32(0x1F000407));
        I(0x4, K(F_S,3));
        I(0x6, K(F_S,3));
        I(0x8, K(F_S,3));
        I(0xA, K(F_S,3));
        I(0xC, K(F_S,3));
        I(0xE, K(F_S,3));
        P(PULSE0, 14,9);
        P(PULSE0, 15,9);

        PATRN(10);
        VOLM(0.445);
        INSTR(SQ125_LONG);
        I(0x0, K(D,5)); I(0x4, K(C_S,5));
        I(0x7, K(D,5)); I(0x8, K(E,5));
        I(0xC, K(D,5)); I(0xF, K(E,5));
        P(PULSE0, 16, 10);
        PATRN(11);
        I(0x0, K(F_S,5)); I(0x4, K(E,5));
        I(0x7, K(F_S,5)); I(0x8, K(B,4));
        I(0xC, K(B,4)); I(0xF, K(C_S,4));
        P(PULSE0, 17, 11);
        P(PULSE0, 18, 10);
        PATRN(12);
        I(0x0, K(F_S,5));
        INSTR(SQ125_SHORT);
        I(0x8, K(B,5));
        I(0xC, SQ50_0A, K(B,4));
        I(0xF, SQ50_10, K(C_S,6));
        P(PULSE0, 19, 12);
        PATRN(13);
        I(0x0, SQ50_0B, K(D,6));
        I(0x4, SQ50_0C, K(C_S,6));
        I(0x7, SQ50_0D, K(D,6));
        I(0x8, SQ50_0B, K(E,6));
        I(0xC, SQ50_0C, K(D,6));
        I(0xF, SQ50_0D, K(E,6));
        P(PULSE0, 20, 13);
        PATRN(14);
        I(0x0, SQ50_0B, K(F_S,6));
        I(0x4, SQ50_0C, K(E,6));
        I(0x7, SQ50_0D, K(F_S,6));
        I(0x8, SQ50_0B, K(B,5));
        I(0xC, SQ50_0C, K(B,5));
        I(0xF, SQ50_0D, K(C_S,6));
        P(PULSE0, 21, 14);
        P(PULSE0, 22, 13);
        PATRN(15);
        I(0x0, SQ50_0E, K(C_S,6));
        I(0x8, SQ50_0F, K(F_S,6));
        P(PULSE0, 23, 15);

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
        P(TRIANGLE2, 2,1);

        PATRN(2);
        I(0x00, K(C_S,3), UI32(0x1F000E01));
        P(TRIANGLE2, 3,2);

        PATRN(3);
        I(0x02, K(F_S,4),  UI32(0x1F000304));
        I(0x04, K(F_S,4)); I(0x06, K(F_S,4)); I(0x08, K(F_S,4));
        I(0x0C, K(F_S,5), UI32(0x1F000701));
        I(0x0F, K(F_S,5), UI32(0x1F000301));
        P(TRIANGLE2, 4, 3);

        PATRN(4);
        I(0x00, K(B,5), UI32(0x1F003701)); I(0x0C, K(B,5), UI32(0x1F000D01));
        I(0x0F, K(D_S,6), UI32(0x1F000301));
        P(TRIANGLE2, 5, 4);

        PATRN(5);
        I(0x00, K(F_S,6), UI32(0x1F000801));
        I(0x02, K(B,6), UI32(0x1F000403));
        I(0x04, K(A_S,6)); I(0x06, K(G_S,6));
        I(0x08, K(F_S, 6), UI32(0x1F001201));
        I(0x0C, K(D_S,6), UI32(0x1F000D01));
        I(0x0F, K(F_S,6),UI32(0x1F000301));
        P(TRIANGLE2, 6, 5);

        PATRN(6);
        I(0x00, K(E,6), UI32(0x1F001101));
        I(0x04, K(C_S,6), UI32(0x1F000D01));
        I(0x07, K(D_S,6), UI32(0x1F000301));
        I(0x08, K(C_S,6), UI32(0x1F001101));
        I(0x0C, K(D_S,6), UI32(0x1F000D01));
        I(0x0F, K(C_S,6), UI32(0x1F000301));
        P(TRIANGLE2, 7, 6);

        PATRN(7);
        I(0x00, K(B,5), UI32(0x1F003401));
        I(0x0C, K(F_S, 5), UI32(0x1F000701));
        I(0x0F, K(F_S,5), UI32(0x1F000301));
        P(TRIANGLE2, 8, 7);

        P(TRIANGLE2, 9, 4); P(TRIANGLE2, 10, 5);
        P(TRIANGLE2, 11, 6);

        PATRN(8);
        I(0x00, K(B,5), UI32(0x1F003401));
        P(TRIANGLE2, 12, 8);

        PATRN(9);
        I(0x00, K(B,5), UI32(0x1F000C01));
        I(0x03, K(B,5), UI32(0x1F000302));
        I(0x04, K(C_S,6));
        I(0x06, K(D_S,6), UI32(0x1F001001));
        I(0x0A, K(B,5), UI32(0x1F000301));
        I(0x0C, K(C_S,6), UI32(0x1F000702));
        I(0x0E, K(B,5));
        P(TRIANGLE2, 13, 9);
        P(TRIANGLE2, 14, 1);
        P(TRIANGLE2, 15, 1);

        PATRN(10);
        I(0x00, K(E,3), UI32(0x1F000377));
        I(0x01, K(B,3)); I(0x02, K(G,4)); I(0x03, K(E,4));
        I(0x04, K(G,4)); I(0x05, K(E,4)); I(0x06, K(G,4)); I(0x07, K(E,4));
        I(0x08, K(A,3)); I(0x09, K(E,4)); I(0x0A, K(A,4)); I(0x0B, K(E,4));
        I(0x0C, K(A,4)); I(0x0D, K(E,4)); I(0x0E, K(A,4)); I(0x0F, K(E,4));
        P(TRIANGLE2, 16, 10);

        PATRN(11);
        I(0x00, K(D,3));
        I(0x01, K(A,3)); I(0x02, K(F_S,4)); I(0x03, K(D,4));
        I(0x04, K(F_S,4)); I(0x05, K(D,4)); I(0x06, K(F_S,4)); I(0x07, K(D,4));
        I(0x08, K(G,3)); I(0x09, K(D,4)); I(0x0A, K(G,4)); I(0x0B, K(D,4));
        I(0x0C, K(G,4)); I(0x0D, K(D,4)); I(0x0E, K(G,4)); I(0x0F, K(D,4));
        P(TRIANGLE2, 17, 11);

        P(TRIANGLE2, 18, 10); P(TRIANGLE2, 19, 11); P(TRIANGLE2, 20, 10); P(TRIANGLE2, 21, 11);
        P(TRIANGLE2, 22, 10);

        PATRN(12);
        I(0x0, K(F_S,3)); I(0x2, K(F_S,3)); I(0x3, K(C_S,4)); I(0x4, K(F_S,3));
        I(0x6, K(F_S,3)); I(0x7, K(C_S,4)); I(0x8, K(F_S,4));
        I(0xC, K(F_S,5), UI32(0x1F000701));
        I(0xF, K(F_S,5), UI32(0x1F000301));
        P(TRIANGLE2, 23, 12);


        return new C0deTracker::Track(CLOCK, BASETIME, SPEED, ROWS, FRAMES, CHANNELS, instruments_bank, INSTRUMENTS,
                                      patterns, pattern_indices, fx_per_chan);

    }


}