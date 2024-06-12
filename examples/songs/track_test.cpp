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

    UI32 tremolo = 0x17400400; //OK
    UI32 vibrato = 0x12F00100; //OK
    UI32 arpeggio = 0x19100200; //MEH : Arpeggio is well implemented, but phasing must be applied when changing frequency/note
    //volume track ; volume channel ; volume instruction ; volume osc
    //volume chan * volume instruc * volum osc * volume track
    UI32 volslidown = 0x160A0950; // OK on chan
    UI32 volslidup = 0x150A0F00; // OK on chan : must be set chan volume low to the slide up (via effect and not pattern)
    UI32 volset = 0x1400F0F0; //OK

    UI32 pitchset = 0x13100000; // OK but phase shift should be applied to avoid pop for tri wave
    UI32 pitchset2 = 0x13ABCDEF;
    UI32 pitchslidup  = 0x10020AA3;//OK
    UI32 pitchslidupstop  = 0x10000000;//OK
    UI32 pitchslidown = 0x11AAAAA3;//OK not OK when going from slide up to slidedown
    //SHOULD ADD MIN/MAX FREQ
    UI32 panleft = 0x18000000;//OK
    UI32 panright = 0x18FFFFFF;//OK
    UI32 panslideRL = 0x1D0A0000;//OK
    UI32 panslideLR = 0x1E0A0000;//OK
    UI32 delrel = 0x1F000A01;//OK
    UI32 retirieg = 0x1C020504;//OK dont retrieg if release just make it longer, doesnt restart, ignore retrieg partially
    //retrieg 1 is 2, 2 3 etc...
    //Portamento ; Delayed Transpose
    UI32 portamento = 0x1B100000;// OK, BUT PHASE SHIFT TO DO WHEN CHANGING FREQUENCY
    UI32 deltranspos = 0x1A8A0A01;// OK BUT PHASE SHIFT!!!!!!!!!


    VOLM(0.8);
    CHANL(CHAN0);
    PATRN(0);
    INSTR(KICK);
    //I(0, K(C_S, 2),retirieg);
    //I(4, SNARE, K(D_S,4), 0.6f, UI32(0x1F050501));
    INSTR(SQUARE_WAVE);
    //I(0, K(A,2), pitchslidup);//, pitchslidup);
    //I(8, K(B,2), pitchslidup);
    //I(16, pitchslidupstop);
    //I(4, K(B,4)); I(8, K(B,4));
    //I(4, K(B,4), {volset, volslidup});
    //I(0, K(B,4), {panright, panslideLR});
    I(0, K(B,4), vibrato);
    //I(12, K(G,7));
    //I(6, K(C,4));
    //I(4, pitchslidown);
    //I(15, pitchslidup);
    //I(20, pitchslidown);
    //I(15, panslideLR);
    //PATRN(1);
    //I(10, panslideLR);
    //P(0,1,0);


    this->setPatterns(patterns);
    this->setPatternsIndices(pattern_indices);

}

