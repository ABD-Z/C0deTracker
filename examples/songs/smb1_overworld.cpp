//
// Created by Abdulmajid, Olivier NASSER on 08/01/2021.
//
#include "examples.hpp"


SuperMarioBros_OverworldTheme::SuperMarioBros_OverworldTheme() {
    this->setName(NAME);
    this->setSizeDimensions(ROWS,FRAMES,CHANNELS,fx_per_chan);
    this->setTimeDimensions(CLOCK, SPEED, BASETIME);
}

void SuperMarioBros_OverworldTheme::init() {
    //Track::init();

    auto *instruments_data_bank = new C0deTracker::Instrument_Data[INSTRUMENTS];
    instruments_data_bank[MAIN].setData(C0deTracker::SQUARE, C0deTracker::ADSR(100.f, 5.f, 0.f, 100.f), .128f, 0.f, .5f, 0.f);
    instruments_data_bank[BASS].setData(C0deTracker::TRIANGLE, C0deTracker::ADSR(100.0f, 0.f, 0.0f, 100.f), 1.f, 0, 1.f, .5f);
    instruments_data_bank[DRUMS].setData(C0deTracker::WHITENOISE, C0deTracker::ADSR(100.f, 0.0f, 0.0f, 100.f), .32f, 0.f, .00377f, 0.f);
    instruments_data_bank[SNARE].setData(C0deTracker::WHITENOISE, C0deTracker::ADSR(100.f, 0.0f, 0.0f, 100.f), .384f, 0.f, .225f, 0.f);
    this->setInstrumentsDataBank(instruments_data_bank, INSTRUMENTS);


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



    //square wave : O octave famitracker corresponds to O + 1 for C0deTracker
    CHANL(0);
    VOLM(0.7f);
    PATRN(0);
    INSTR(MAIN);
    I(0, K(F_S, 4), UI32(0x1F0107FF)); I(1, K(F_S, 4)); I(3, K(F_S, 4)); I(5, K(F_S, 4)); I(6, K(F_S, 4));
    I(8, K(B, 4)); I(0x0C, K(G, 4));

    PATRN(1);
    I(0, K(E,4)); I(3, K(C,4)); I(6, K(G,3));
    I(9, K(C,4)); I(0xB, K(D,4)); I(0xD, K(C_S,4)); I(0xE, K(C,4));
    I(0x10, K(C,4)); I(0x11, K(G,4), UI32(0x1F040701)); I(0x12, K(B,4), UI32(0x1F070701)); I(0x14, K(C,5), UI32(0x1F0107FF)); I(0x16, K(A,4)); I(0x17, K(B,4));
    I(0x19, K(A,4)); I(0x1B, K(E,4)); I(0x1C, K(F,4)); I(0x1D, K(D,4));
    I(0x20, K(E,4)); I(0x23, K(C,4)); I(0x26, K(G,3));
    I(0x29, K(C,4)); I(0x2B, K(D,4)); I(0x2D, K(C_S,4)); I(0x2E, K(C,4));
    I(0x30, K(C,4)); I(0x31, K(G,4), UI32(0x1F040701)); I(0x32, K(B,4), UI32(0x1F070701)); I(0x34, K(C,5), UI32(0x1F0107FF)); I(0x36, K(A,4)); I(0x37, K(B,4));
    I(0x39, K(A,4)); I(0x3B, K(E,4)); I(0x3C, K(F,4)); I(0x3D, K(D,4));

    PATRN(2);
    I(0x02, K(E,5)); I(0x03, K(D_S,5)); I(0x04, K(D,5)); I(0x05, K(B,4)); I(0x07, K(C,5));
    I(0x09, K(E,4)); I(0x0A, K(F,4)); I(0x0B, K(G,4)); I(0x0D, K(C,4)); I(0x0E, K(E,4)); I(0x0F, K(F,4));
    I(0x12, K(E,5)); I(0x13, K(D_S,5)); I(0x14, K(D,5)); I(0x15, K(B,4)); I(0x17, K(C,5));
    I(0x19, K(F,5)); I(0x1B, K(F,5)); I(0x1C, K(F,5));
    I(0x22, K(E,5)); I(0x23, K(D_S,5)); I(0x24, K(D,5)); I(0x25, K(B,4)); I(0x27, K(C,5));
    I(0x29, K(E,4)); I(0x2A, K(F,4)); I(0x2B, K(G,4)); I(0x2D, K(C,4)); I(0x2E, K(E,4)); I(0x2F, K(F,4));
    I(0x32, K(G_S,4)); I(0x35, K(F,4)); I(0x38, K(E,4));
    P(0,3,2);

    PATRN(3);
    I(0x00, K(G_S,4)); I(0x01, K(G_S,4)); I(0x03, K(G_S,4)); I(0x05, K(G_S,4)); I(0x06, K(A_S,4));
    I(0x08, K(G,4)); I(0x09, K(E,4)); I(0x0B, K(E,4)); I(0x0C, K(C,4));
    I(0x10, K(G_S,4)); I(0x11, K(G_S,4)); I(0x13, K(G_S,4)); I(0x15, K(G_S,4)); I(0x16, K(A_S,4)); I(0x17, K(G,4));
    I(0x20, K(G_S,4)); I(0x21, K(G_S,4)); I(0x23, K(G_S,4)); I(0x25, K(G_S,4)); I(0x26, K(A_S,4));
    I(0x28, K(G,4)); I(0x29, K(E,4)); I(0x2B, K(E,4)); I(0x2C, K(C,4));
    I(0x30, K(F_S, 4)); I(0x31, K(F_S, 4)); I(0x33, K(F_S, 4)); I(0x35, K(F_S, 4)); I(0x36, K(F_S, 4));
    I(0x38, K(B, 4));
    P(0,4,3);
    P(0,5,1);

    PATRN(4);
    I(0x00, K(C,5)); I(0x01, K(A,4)); I(0x03, K(E,4)); I(0x06, K(E,4));
    I(0x08, K(F,4)); I(0x09, K(C,5)); I(0x0B, K(C,5)); I(0x0C, K(F,4));
    I(0x10, K(G,4));
    I(0x11, K(F,5), UI32(0x1F040701)); I(0x12, K(F,5), UI32(0x1F070701));
    I(0x14, K(F,5), UI32(0x1F010701));
    I(0x15, K(E,5), UI32(0x1F040701)); I(0x16, K(D,5), UI32(0x1F070701));
    I(0x18, K(C,5), UI32(0x1F0107FF)); I(0x19, K(A,4)); I(0x1B, K(F,4)); I(0x1C, K(E,4));
    I(0x20, K(C,5)); I(0x21, K(A,4)); I(0x23, K(E,4)); I(0x26, K(E,4));
    I(0x28, K(F,4)); I(0x29, K(C,5)); I(0x2B, K(C,5)); I(0x2C, K(F,4));
    I(0x30, K(G,4)); I(0x31, K(D,5)); I(0x33, K(D,5)); I(0x34, K(D,5));
    I(0x35, K(C,5), UI32(0x1F040701)); I(0x36, K(B,4), UI32(0x1F070701));
    I(0x38, K(C,5), UI32(0x1F0107FF));

    P(0,6,4);
    P(0,7,4);
    P(0,8,3);
    P(0,9,4);

    CHANL(1);
    PATRN(0);
    I(0, K(E, 5), UI32(0x1F0107FF)); I(1, K(E, 5)); I(3, K(E, 5)); I(5, K(C, 5)); I(6, K(E, 5));
    I(8, K(G, 5));

    PATRN(1);
    I(0x00, K(C,5)); I(0x03, K(G,4)); I(0x06, K(E,4));
    I(0x09, K(A,4)); I(0x0B, K(B,4)); I(0x0D, K(A_S,4)); I(0x0E, K(A,4));
    I(0x10, K(G,4)); I(0x11, K(E,5), UI32(0x1F040701)); I(0x12, K(G,5), UI32(0x1F070701)); I(0x14, K(A,5), UI32(0x1F0107FF)); I(0x16, K(F,5)); I(0x17, K(G,5));
    I(0x19, K(E,5)); I(0x1B, K(C,5)); I(0x1C, K(D,5)); I(0x1D, K(B,4));
    I(0x20, K(C,5)); I(0x23, K(G,4)); I(0x26, K(E,4));
    I(0x29, K(A,4)); I(0x2B, K(B,4)); I(0x2D, K(A_S,4)); I(0x2E, K(A,4));
    I(0x30, K(G,4)); I(0x31, K(E,5), UI32(0x1F040701)); I(0x32, K(G,5), UI32(0x1F070701)); I(0x34, K(A,5), UI32(0x1F0107FF)); I(0x36, K(F,5)); I(0x37, K(G,5));
    I(0x39, K(E,5)); I(0x3B, K(C,5)); I(0x3C, K(D,5)); I(0x3D, K(B,4));

    PATRN(2);
    I(0x02, K(G,5)); I(0x03, K(F_S,5)); I(0x04, K(F,5)); I(0x05, K(D_S,5)); I(0x07, K(E,5));
    I(0x09, K(G_S,4)); I(0x0A, K(A,4)); I(0x0B, K(C,5)); I(0x0D, K(A,4)); I(0x0E, K(C,5)); I(0x0F, K(D,5));
    I(0x12, K(G,5)); I(0x13, K(F_S,5)); I(0x14, K(F,5)); I(0x15, K(D_S,5)); I(0x17, K(E,5));
    I(0x19, K(C,6)); I(0x1B, K(C,6)); I(0x1C, K(C,6));
    I(0x22, K(G,5)); I(0x23, K(F_S,5)); I(0x24, K(F,5)); I(0x25, K(D_S,5)); I(0x27, K(E,5));
    I(0x29, K(G_S,4)); I(0x2A, K(A,4)); I(0x2B, K(C,5)); I(0x2D, K(A,4)); I(0x2E, K(C,5)); I(0x2F, K(D,5));
    I(0x32, K(D_S,5)); I(0x35, K(D,5)); I(0x38, K(C,5));
    P(1,3,2);
    PATRN(3);
    I(0x00, K(C,5)); I(0x01, K(C,5)); I(0x03, K(C,5)); I(0x05, K(C,5)); I(0x06, K(D,5));
    I(0x08, K(E,5)); I(0x09, K(C,5)); I(0x0B, K(A,4)); I(0x0C, K(G,4));
    I(0x10, K(C,5)); I(0x11, K(C,5)); I(0x13, K(C,5)); I(0x15, K(C,5)); I(0x16, K(D,5)); I(0x17, K(E,5));

    I(0x20, K(C,5)); I(0x21, K(C,5)); I(0x23, K(C,5)); I(0x25, K(C,5)); I(0x26, K(D,5));
    I(0x28, K(E,5)); I(0x29, K(C,5)); I(0x2B, K(A,4)); I(0x2C, K(G,4));

    I(0x30, K(E, 5)); I(0x31, K(E, 5)); I(0x33, K(E, 5)); I(0x35, K(C, 5)); I(0x36, K(E, 5));
    I(0x38, K(G, 5)); I(0x3C, K(G,4));
    P(1,4,3);
    P(1,5,1);

    PATRN(4);
    I(0x00, K(E,5)); I(0x01, K(C,4)); I(0x03, K(G,4)); I(0x06, K(G_S,4));
    I(0x08, K(A,4)); I(0x09, K(F,5)); I(0x0B, K(F,5)); I(0x0C, K(A,4));
    I(0x10, K(B,4));
    I(0x11, K(A,5), UI32(0x1F040701)); I(0x12, K(A,5), UI32(0x1F070701));
    I(0x14, K(A,5), UI32(0x1F010701));
    I(0x15, K(G,5), UI32(0x1F040701)); I(0x16, K(F,5), UI32(0x1F070701));
    I(0x18, K(E,5), UI32(0x1F0107FF)); I(0x19, K(C,4)); I(0x1B, K(A,4)); I(0x1C, K(G,4));
    I(0x20, K(E,5)); I(0x21, K(C,5)); I(0x23, K(G,4)); I(0x26, K(G_S,4));
    I(0x28, K(A,4)); I(0x29, K(F,5)); I(0x2B, K(F,5)); I(0x2C, K(A,4));
    I(0x30, K(B,4)); I(0x31, K(F,5)); I(0x33, K(F,5)); I(0x34, K(F,5));
    I(0x35, K(E,5), UI32(0x1F040701)); I(0x36, K(D,5), UI32(0x1F070701));
    I(0x38, K(G,4), UI32(0x1F0107FF));
    I(0x39, K(E,4)); I(0x3B, K(E,4)); I(0x3C, K(C,4));

    P(1,6,4);
    P(1,7,4);
    P(1,8,3);
    P(1,9,4);

    CHANL(2);
    VOLM(1.0f);
    INSTR(BASS);
    PATRN(0);
    I(0, K(D, 3), UI32(0x1F0007FF)); I(1, K(D, 3)); I(3, K(D, 3)); I(5, K(D, 3)); I(6, K(D, 3));
    I(8, K(G, 4)); I(0x0C, K(G, 3)); I(0x0F, UI32(0x0A001000));

    PATRN(1);
    I(0x00, K(G,3)); I(0x03, K(E,3)); I(0x06, K(C,3));
    I(0x09, K(F,3)); I(0x0B, K(G,3)); I(0x0D, K(F_S,3)); I(0x0E, K(F,3));
    I(0x10, K(E,3)); I(0x11, K(C,4), UI32(0x1F030701)); I(0x12, K(E,4), UI32(0x1F060701)); I(0x14, K(F,4), UI32(0x1F0007FF)); I(0x16, K(D,4)); I(0x17, K(E,4));
    I(0x19, K(C,4)); I(0x1B, K(A,3)); I(0x1C, K(B,3)); I(0x1D, K(G,3));
    I(0x20, K(G,3)); I(0x23, K(E,3)); I(0x26, K(C,3));
    I(0x29, K(F,3)); I(0x2B, K(G,3)); I(0x2D, K(F_S,3)); I(0x2E, K(F,3));
    I(0x30, K(E,3)); I(0x31, K(C,4), UI32(0x1F030701)); I(0x32, K(E,4), UI32(0x1F060701)); I(0x34, K(F,4), UI32(0x1F0007FF)); I(0x36, K(D,4)); I(0x37, K(E,4));
    I(0x39, K(C,4)); I(0x3B, K(A,3)); I(0x3C, K(B,3)); I(0x3D, K(G,3));

    PATRN(2);
    I(0x00, K(C,3)); I(0x03, K(G,3)); I(0x06, K(C,4));
    I(0x08, K(F,3)); I(0x0B, K(C,4)); I(0x0C, K(C,4)); I(0x0E, K(F,4));
    I(0x10, K(C,3)); I(0x13, K(E,3)); I(0x16, K(G,3)); I(0x17, K(C,4));
    I(0x19, K(G,5)); I(0x1B, K(G,5)); I(0x1C, K(G,5)); I(0x1E, K(G,3));
    I(0x20, K(C,3)); I(0x23, K(G,3)); I(0x26, K(C,4));
    I(0x28, K(F,3)); I(0x2B, K(C,4)); I(0x2C, K(C,4)); I(0x2E, K(F,3));
    I(0x30, K(C,3)); I(0x32, K(G_S,3)); I(0x35, K(A_S, 3));
    I(0x38, K(C,4)); I(0x3B, K(G,3)); I(0x3C, K(G,3)); I(0x3E, K(C,3));

    P(2,3,2);

    PATRN(3);
    I(0x00, K(G_S,2)); I(0x03, K(D_S,3)); I(0x06, K(G_S,3));
    I(0x08, K(G,3)); I(0x0B, K(C,3)); I(0x0E, K(G,2));
    I(0x10, K(G_S,2)); I(0x13, K(D_S,3)); I(0x16, K(G_S,3));
    I(0x18, K(G,3)); I(0x1B, K(C,3)); I(0x1E, K(G,2));
    I(0x20, K(G_S,2)); I(0x23, K(D_S,3)); I(0x26, K(G_S,3));
    I(0x28, K(G,3)); I(0x2B, K(C,3)); I(0x2E, K(G,2));
    I(0x30, K(D, 3)); I(0x31, K(D, 3)); I(0x33, K(D, 3)); I(0x35, K(D, 3)); I(0x36, K(D, 3));
    I(0x38, K(G, 4)); I(0x3C, K(G, 3));
    P(2,4,3);
    P(2,5,1);

    PATRN(4);
    I(0x00, K(C,3)); I(0x03, K(F_S,3)); I(0x04, K(G,3)); I(0x06, K(C,4));
    I(0x08, K(F,3)); I(0x0A, K(F,3)); I(0x0C, K(C,4)); I(0x0D, K(C,4)); I(0x0E, K(F,3));
    I(0x10, K(D,3)); I(0x13, K(F,3)); I(0x14, K(G,3)); I(0x16, K(B,3));
    I(0x18, K(G,3)); I(0x1A, K(G,3)); I(0x1C, K(C,4)); I(0x1D, K(C,4)); I(0x1E, K(G,3));
    I(0x20, K(C,3)); I(0x23, K(F_S,3)); I(0x24, K(G,3)); I(0x26, K(C,4));
    I(0x28, K(F,3)); I(0x2A, K(F,3)); I(0x2C, K(C,4)); I(0x2D, K(C,4)); I(0x2E, K(F,3));
    I(0x30, K(G,3)); I(0x33, K(G,3)); I(0x34, K(G,3));
    I(0x35, K(A,3), UI32(0x1F030701)); I(0x36, K(B,3), UI32(0x1F060701));
    I(0x38, K(C, 4), UI32(0x1F0007FF));
    I(0x3A, K(G,3)); I(0x3C, K(C,3));

    P(2,6,4);
    P(2,7,4);
    P(2,8,3);
    P(2,9,4);


    CHANL(3);
    PATRN(0);
    VOLM(1.f);
    INSTR(DRUMS);
    I(0x00, K(C_S, 2), UI32(0x1F000501));
    I(0x02, K(C_S, 2), UI32(0x1F000104));
    I(0x03, K(C_S, 2)); I(0x05, K(C_S, 2)); I(0x06, K(C_S, 2));
    I(0x08, K(C_S, 2), UI32(0x1F000502));
    I(0x0B, K(C_S, 2));
    I(0x0D, K(C_S, 2), UI32(0x1F000103));
    I(0x0E, K(C_S, 2)); I(0x0F, K(C_S, 2));
    I(0x10, K(C_S, 2), UI32(0x1F000501));
    I(0x12, K(C_S, 2), UI32(0x1F000104));
    I(0x13, K(C_S, 2)); I(0x15, K(C_S, 2)); I(0x16, K(C_S, 2));
    I(0x18, K(C_S, 2), UI32(0x1F000502));
    I(0x1B, K(C_S, 2));
    I(0x1D, K(C_S, 2), UI32(0x1F000103));
    I(0x1E, K(C_S, 2)); I(0x1F, K(C_S, 2));
    I(0x20, K(C_S, 2), UI32(0x1F000501));
    I(0x22, K(C_S, 2), UI32(0x1F000104));
    I(0x23, K(C_S, 2)); I(0x25, K(C_S, 2)); I(0x26, K(C_S, 2));
    I(0x28, K(C_S, 2), UI32(0x1F000502));
    I(0x2B, K(C_S, 2));
    I(0x2D, K(C_S,2), UI32(0x1F000103));
    I(0x2E, K(C_S, 2)); I(0x2F, K(C_S, 2));
    I(0x30, K(C_S, 2), UI32(0x1F000501));
    I(0x32, K(C_S, 2), UI32(0x1F000104));
    I(0x33, K(C_S, 2)); I(0x35, K(C_S, 2)); I(0x36, K(C_S, 2));
    I(0x38, K(C_S, 2), UI32(0x1F000502));
    I(0x3B, K(C_S, 2));
    I(0x3D, K(C_S,2), UI32(0x1F000103));
    I(0x3E, K(C_S, 2)); I(0x3F, K(C_S, 2));

    P(3,4,0); P(3,8,0);

    PATRN(2);
    I(0x00, K(C_S,2), UI32(0x1F000102));
    I(0x03, K(C_S,2));
    I(0x04, K(C_S,2), UI32(0x1F000501));
    I(0x06, K(C_S,2), UI32(0x1F000103));
    I(0x08, K(C_S,2)); I(0x0B, K(C_S,2));
    I(0x0C, K(C_S,2), UI32(0x1F000501));
    I(0x0E, K(C_S,2), UI32(0x1F000101));
    I(0x10, K(C_S,2), UI32(0x1F000102));
    I(0x13, K(C_S,2));
    I(0x14, K(C_S,2), UI32(0x1F000501));
    I(0x16, K(C_S,2), UI32(0x1F000103));
    I(0x18, K(C_S,2)); I(0x1B, K(C_S,2));
    I(0x1C, K(C_S,2), UI32(0x1F000501));
    I(0x1E, K(C_S,2), UI32(0x1F000101));
    I(0x20, K(C_S,2), UI32(0x1F000102));
    I(0x23, K(C_S,2));
    I(0x24, K(C_S,2), UI32(0x1F000501));
    I(0x26, K(C_S,2), UI32(0x1F000103));
    I(0x28, K(C_S,2)); I(0x2B, K(C_S,2));
    I(0x2C, K(C_S,2), UI32(0x1F000501));
    I(0x2E, K(C_S,2), UI32(0x1F000101));
    I(0x30, K(C_S,2), UI32(0x1F000102));
    I(0x33, K(C_S,2));
    I(0x34, K(C_S,2), UI32(0x1F000501));
    I(0x36, K(C_S,2), UI32(0x1F000103));
    I(0x38, K(C_S,2)); I(0x3B, K(C_S,2));
    I(0x3C, K(C_S,2), UI32(0x1F000501));
    I(0x3E, K(C_S,2), UI32(0x1F000101));
    P(3,6,2); P(3,7,2); P(3,9,2);

    PATRN(1);
    I(0x00, SNARE, K(C_S,1), UI32(0x1F000103));
    I(0x02, K(C_S,2));
    I(0x03, K(C_S,2), UI32(0x1F030101));
    I(0x04, K(C_S,2), UI32(0x1F000501));
    I(0x06, K(C_S,2), UI32(0x1F000105));
    I(0x07, K(C_S,2), UI32(0x1F030101));
    I(0x08, SNARE, K(C_S,1), UI32(0x1F000103));
    I(0x0A, K(C_S,2));
    I(0x0B, K(C_S,2), UI32(0x1F030101));
    I(0x0C, K(C_S,2), UI32(0x1F000501));
    I(0x0E, K(C_S,2), UI32(0x1F000102));
    I(0x0F, K(C_S,2), UI32(0x1F030101));

    I(0x10, SNARE, K(C_S,1), UI32(0x1F000103));
    I(0x12, K(C_S,2));
    I(0x13, K(C_S,2), UI32(0x1F030101));
    I(0x14, K(C_S,2), UI32(0x1F000501));
    I(0x16, K(C_S,2), UI32(0x1F000105));
    I(0x17, K(C_S,2), UI32(0x1F030101));
    I(0x18, SNARE, K(C_S,1), UI32(0x1F000103));
    I(0x1A, K(C_S,2));
    I(0x1B, K(C_S,2), UI32(0x1F030101));
    I(0x1C, K(C_S,2), UI32(0x1F000501));
    I(0x1E, K(C_S,2), UI32(0x1F000102));
    I(0x1F, K(C_S,2), UI32(0x1F030101));

    I(0x20, SNARE, K(C_S,1), UI32(0x1F000103));
    I(0x22, K(C_S,2));
    I(0x23, K(C_S,2), UI32(0x1F030101));
    I(0x24, K(C_S,2), UI32(0x1F000501));
    I(0x26, K(C_S,2), UI32(0x1F000105));
    I(0x27, K(C_S,2), UI32(0x1F030101));
    I(0x28, SNARE, K(C_S,1), UI32(0x1F000103));
    I(0x2A, K(C_S,2));
    I(0x2B, K(C_S,2), UI32(0x1F030101));
    I(0x2C, K(C_S,2), UI32(0x1F000501));
    I(0x2E, K(C_S,2), UI32(0x1F000102));
    I(0x2F, K(C_S,2), UI32(0x1F030101));

    I(0x30, SNARE, K(C_S,1), UI32(0x1F000103));
    I(0x32, K(C_S,2));
    I(0x33, K(C_S,2), UI32(0x1F030101));
    I(0x34, K(C_S,2), UI32(0x1F000501));
    I(0x36, K(C_S,2), UI32(0x1F000105));
    I(0x37, K(C_S,2), UI32(0x1F030101));
    I(0x38, SNARE, K(C_S,1), UI32(0x1F000103));
    I(0x3A, K(C_S,2));
    I(0x3B, K(C_S,2), UI32(0x1F030101));
    I(0x3C, K(C_S,2), UI32(0x1F000501));
    I(0x3E, K(C_S,2), UI32(0x1F000102));
    I(0x3F, K(C_S,2), UI32(0x1F030101));

    P(3,1,1); P(3,2,1); P(3,3,1); P(3,5,1);

    CHANL(4);
    P(4,1,0); P(4,2,0); P(4,3,0); P(4,4,0); P(4,5,0); P(4,6,0); P(4,7,0); P(4,8,0); P(4,9,1);
    PATRN(1);
    I(0x3F, UI32(0x0A001000));

    this->setPatterns(patterns);
    this->setPatternsIndices(pattern_indices);
}

