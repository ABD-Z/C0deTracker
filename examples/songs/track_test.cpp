//
// Created by Abdulmajid, Olivier NASSER on 14/11/2021.
//

#include "examples.hpp"

float saw_pow_n(float n, float a, float f, double t, float dc, float FMfeed) {
    double frac_ft = f * (t + FMfeed) - floor(f * (t + FMfeed));
    double s = (std::pow(frac_ft, n) - dc < 0) ? std::pow(frac_ft, n)/dc : 0.f;
    return a * (2 * s - 1);
}

float quadra_saw(float a, float f, double t, float dc, float FMfeed) {
    return saw_pow_n(2, a, f, t, dc, FMfeed);
}

float quarter_pow_saw(float a, float f, double t, float dc, float FMfeed) {
    return saw_pow_n(0.25, a, f, t, dc, FMfeed);
}

float cuvette(float a, float f, double t, float dc, float FMfeed) {
    return a * ( 2*std::pow(C0deTracker::Osc::saw(1.f, f, t, dc, FMfeed), 2)-1);
}

float boobs(float a, float f, double t, float dc, float FMfeed) {
    return a * (  2 * std::pow(C0deTracker::Osc::triangle(1.f, f, t, dc, FMfeed), 4) -1);
}

float mountains(float a, float f, double t, float dc, float FMfeed) {
    return a * ( std::pow(C0deTracker::Osc::triangle(1.f, f, t, dc, FMfeed), 3));
}

float xylo(float a, float f, double t, float dc, float FMfeed) {
    float op1 = C0deTracker::Osc::sinus(1.f, f * 13, t, dc, FMfeed);
    float op2 = C0deTracker::Osc::sinus(0.5f , f * 33, t, dc, op1);
    float op3 = C0deTracker::Osc::sinus(1, f, t, dc, op2);
    return a*op3;
}

float slap_bass(float a, float f, double t, float dc, float FMfeed) {
    float op1 = C0deTracker::Osc::sinus(1.1f, f *.5f, t, dc, FMfeed);

    for (int i = 0; i < 5; ++i) {
        op1 = C0deTracker::Osc::sinus(1.1f, f * 0.5f, t, dc, op1);
    }

    float op2 = C0deTracker::Osc::sinus(3.4f, f * 0.5f, t, dc, op1);
    float op3 = C0deTracker::Osc::sinus(3.7f, f * 0.5f, t, dc, op2);

    float op4 = C0deTracker::Osc::sinus(a, f * 0.5f, t, dc, op3 + op1);

    return op4;
}

Track_Test::Track_Test() : Track_Data(
        NAME, CLOCK, BASETIME, SPEED, ROWS, FRAMES, CHANNELS, FX_per_CHAN
        ) {}


void Track_Test::load_data() {
    Track_Data::load_data();

    C0deTracker::Osc::registerCustomWaveFunc(
            QUADRA_SAW, quadra_saw);
    C0deTracker::Osc::registerCustomWaveFunc(
            QUARTER_SAW, quarter_pow_saw);
    C0deTracker::Osc::registerCustomWaveFunc(
            CUVETTE, cuvette);
    C0deTracker::Osc::registerCustomWaveFunc(
            BOOBS, boobs);
    C0deTracker::Osc::registerCustomWaveFunc(
            MOUNTAINS, mountains);

    C0deTracker::Osc::registerCustomWaveFunc(
            XYLOPHONE, xylo);

    C0deTracker::Osc::registerCustomWaveFunc(
            SLAP_BASS, slap_bass);

    C0deTracker::Osc::registerCustomWaveFunc(
            NOKIA3310,
            [](float a, float f, double t, float dc, float FMfeed) -> float {
                double p = 0.1;
                double mod = f*t + p + FMfeed - floor(f*t + p + FMfeed);

                double sin = sinf(TWOPI*10*f*t + FMfeed);

                if(mod < p){
                    double div_sin1 = 10*f* ( f * t +10*p  - floor(f * t + 10*p));
                    return a * 600*sin/div_sin1;
                }else{
                    double div_sin2 = 10*f* ( f * t + p  - floor(f * t + p));
                    return a * 600*sin/div_sin2;
                }
            });

    C0deTracker::Osc::registerCustomWaveFunc(
            MATH,
            [](double x) -> float {
                return std::pow(x, 10) * std::pow(10,x) * std::cos(x);
            },
            -7.8, 0.2
            );

    if(!IS_GLOBAL_INSTRUMENTS_BANK_INITIALISED)
        initGlobalInstruments();

    GLOBAL_INSTRUMENTS_BANK[SQUARE_WAVE].setData(MATH, C0deTracker::ADSR(1000, 5, 0.f, 5), 1.0f, 0.0, 1.f, 0.f);
    //GLOBAL_INSTRUMENTS_BANK[SQUARE_WAVE].feedback_level = .15f;

    this->setGlobalInstrumentsDataBank(GLOBAL_INSTRUMENTS_BANK, GLOBAL_NUMBER_OF_INSTRUMENTS);

    using namespace C0deTracker::Notes;
    using namespace C0deTracker;

#define VOLM selectVolume
#define CHANL selectChannel
#define PATRN selectPattern
#define INSTR selectInstrument
#define I enterInstruction
#define R enterRelease
#define P enterPatternIndex
#define K Key
#define UI32 uint_fast32_t

    VOLM(.75);

    UI32 tremolo = 0x17400800; //OK
    UI32 vibrato = 0x12000100; //OK
    vibrato = 0x12F449A8;
    vibrato = 0x12FFFFFF;
    //vibrato = 0x127FF7FF;
    //vibrato = 0x123FF3FF;
    vibrato = 0x12BFF05F;
    vibrato = 0x120A025F;
    vibrato = 0x122A025F;
    vibrato = 0x12420800; //stylé en ton bas
    vibrato = 0x12420600; //stylé en ton bas
    vibrato = 0x124204A0; //stylé en ton bas
    vibrato = 0x123204A0; //stylé en ton bas
    vibrato = 0x123AF4FF; // très stylé en ton bas
    vibrato = 0x123AF5AF; // très stylé en ton bas
    //vibrato = 0x1230F5AF; // très stylé en ton bas

    //vibrato = 0x124440A8;
    UI32 arpeggio = 0x19A01F56; //MEH : Arpeggio is well implemented, but phasing must be applied when changing frequency/note
    //volume track ; volume channel ; volume instruction ; volume osc
    //volume chan * volume instruc * volum osc * volume track
    UI32 volslidown = 0x160A0950; // OK on chan
    UI32 volslidup = 0x15001115; // OK on chan : must be set chan volume low to the slide up (via effect and not pattern)
    UI32 volset = 0x14000000; //OK

    UI32 pitchset = 0x13100000; // OK but phase shift should be applied to avoid pop for tri wave
    UI32 pitchset2 = 0x13ABCDEF;
    UI32 pitchslidup  = 0x100FFFFF;//OK
    UI32 pitchslidupstop  = 0x10000000;//OK
    UI32 pitchslidown = 0x11FFFFFF;//OK not OK when going from slide up to slidedown
    //SHOULD ADD MIN/MAX FREQ
    UI32 panleft = 0x18000000;//OK
    UI32 panright = 0x18FFFFFF;//OK
    UI32 panslideRL = 0x1D0A0000;//OK
    UI32 panslideLR = 0x1E0A0000;//OK
    UI32 delrel = 0x1F000A01;//OK
    UI32 retirieg = 0x1C020504;//OK dont retrieg if release just make it longer, doesnt restart, ignore retrieg partially
    //retrieg 1 is 2, 2 3 etc...
    //Portamento ; Delayed Transpose
    UI32 portamento = 0x1B4FFFFF;// OK, BUT PHASE SHIFT TO DO WHEN CHANGING FREQUENCY
    UI32 noportamento = 0x1B000000;// OK, BUT PHASE SHIFT TO DO WHEN CHANGING FREQUENCY
    UI32 deltransposup = 0x1A832004;// OK BUT PHASE SHIFT!!!!!!!!!
    UI32 deltransposdown = 0x1A032001;
    UI32 release = 0x1F000501;
    UI32 delay = 0x1F01020F;
    UI32 del_rel = 0x1F051001;

    UI32 global_pitchslideup = 0x00FFFFFF;
    UI32 global_pitchslidedown = 0x01FFFFFF;
    UI32 global_volume_slidedown = 0x060FFFFF;
    UI32 global_volume_slideup = 0x050FFFFF;
    UI32 global_volume_0 = 0x04000000;
    UI32 global_panning_slideleft = 0x0EFFFFFF;
    UI32 global_panning_slideright = 0x0DFFFFFF;
    UI32 global_panningleft = 0x08000000;
    UI32 global_panningright = 0x08FFFFFF;
    UI32 global_vibrato = 0x02FFFFFF;
    UI32 global_tremolo = 0x07FFFFFF;


    VOLM(1);
    CHANL(CHAN0);
    PATRN(0);
    INSTR(KICK);
    /*I(0, K(C_S, 1));
    I(4, SNARE, K(D_S,4), 0.6f, UI32(0x1F050501));
    I(8, K(C_S, 2));
    I(12, K(C_S, 1));
    I(13, K(C_S, 1));
    I(15, SNARE, K(D_S,4), 0.6f, UI32(0x1F050501));
    I(20, K(C_S, 2));
    //I(22, K(C_S, 1));
    I(24, K(C_S, 1));
    I(26, SNARE, K(D_S,4), 0.6f, UI32(0x1F050501));*/
    //I(25, SNARE, K(D_S,4), 0.6f, UI32(0x1F050501));
    INSTR(SQUARE_WAVE);
    //I(0, K(A,4), delay);
    //I(0, K(A,4), vibrato);
    /*I(4, K(B,2));
    I(8, K(C,2));
    I(10, K(D,2));
    I(12, K(E,3));
    I(14, K(F,3));

    I(16, K(A,3));
    I(18, K(B,3));
    I(20, K(C,3));
    I(22, K(D,3));
    I(24, K(E,4));
    I(26, K(F,4));*/
    //I(4, K(C,0));
    //I(10, K(A,0));
    //I(16, K(C,1));
vibrato = 0x12018008;
    /*I(0, K(G,5), UI32(0x137C0000));
    I(4, vibrato);*/
    //INSTR(WHITENOISETEST);
    /*I(0, K(A,5));



    I(0, K(A,5), portamento);//, pitchslidup);
    //R(5);
    I(8, K(A,6));
    //R(15);
    I(16, K(A,5));
    I(24, K(A,4));*/
    UI32 FX_bass_global_del0_rel7 = 0x1F0008FF;
    UI32 FX_bass_del3_rel7 = 0x1F030802;
    UI32 FX_bass_del6_rel7 = 0x1F060804;

    INSTR(SQUARE_WAVE);
    //I(0, K(C,5), UI32(0x1F0F00FF));//, pitchslidup);
    /*I(0x00, K(G,3), {FX_bass_global_del0_rel7, 0x11000000});
    I(0x03, K(E,3));I(0x06, K(C,3));
    I(0x09, K(F,3));I(0x0B, K(G,3));
    I(0x0D, K(F_S,3)); I(0x0E, K(F,3));
    I(0x10, K(E,3)); I(0x11, K(C,4), FX_bass_del3_rel7);
    I(0x12, K(E,4), FX_bass_del6_rel7); I(0x14, K(F,4), FX_bass_global_del0_rel7);
    I(0x16, K(D,4)); I(0x17, K(E,4));*/

    uint_fast8_t  oct = 4;
    I(0, K(Do, oct));
    R(2);
    I(3, K(Re, oct));
    R(5);
    I(6, K(Mi, oct));
    R(8);
    I(9, K(Fa, oct));
    R(11);
    I(12, K(Sol, oct));
    R(14);
    I(15, K(La, oct));
    R(17);
    I(18, K(Si, oct));
    R(20);
    I(21, K(Do, oct+1));

    /*I(0x20, K(G,3), {0x1F020802, 0x1C000000});

    I(0x25, K(G,3));
    R(0x30);
    I(0x32, K(G,4));*/


    UI32 releaseTOM = UI32(0x1F051000);
    UI32 panrightTOM = 0x18A00000;
    UI32 centered_pan = 0x187FFFFF;
    UI32 cancel_slidedown = 0x11000000;
    UI32 full_slidedown = 0x11FFFFFF;


    auto tom1effects = {releaseTOM + 1, full_slidedown, panrightTOM};
    auto tom2effects = {releaseTOM + 2, full_slidedown, panrightTOM};
    auto cancelTOMeffects = {centered_pan, cancel_slidedown};
    INSTR(TOM);
    I(0x20, Key(A, 1), tom2effects);
    I(0x21, Key(A, 1));
    I(0x23, cancelTOMeffects);
    INSTR(CRASH);
    I(0x25, K(C_S,3));



    /*I(0x0, K(E,4), {UI32(0x1F001803),0x1BFFF000});
    I(0x10, K(E,5));
    I(0x20, K(E,6));

    I(0x25, K(E,4), {UI32(0x1F000703), 0x1B000000});
    I(0x27, K(E,5));
    I(0x30, K(E,6));*/



    /*I(0, K(C,4), UI32(0x1F040A01));
    I(1, K(D,4), UI32(0x1F040A01));
    I(2, K(E,4), UI32(0x1F040A01));
    I(3, K(F,4), UI32(0x1F040A01));
    I(4, K(G,4), UI32(0x1F040A01));
    I(5, K(A,4), UI32(0x1F040A01));
    I(6, K(B,4), UI32(0x1F040A01));*/

    //I(0, K(G,3), UI32(0x1F010401));

    //I(1, K(G,4), UI32(0x1F0100F01));


    /*PATRN(1);
    I(0, K(A,3));//, pitchslidup);

    PATRN(2);
    INSTR(GAME_OVER_FX0);
    I(0, K(C_S, 4), UI32(0x10FFFFFF));
    I(30, {0x11000000, 0x12000000, 0});

    PATRN(3);
    INSTR(WOOD);
    I(0, K(A,3), UI32(0x1C0A0701));

    PATRN(4);
    INSTR(SNARE);
    I(16, K(G_S, 2), UI32(0x1F000501));*/
   /* I(4, K(A,5));
    I(8, K(A,5));
    I(12, K(A,5));

    I(16, K(A,5));
    I(18, K(F,5), UI32(0x18000000));
    I(20, K(D,5), UI32(0x187FFFFF));*/

    //I(0, K(A,4), arpeggio);//, tremolo);
    //I(15, UI32(0x17000000));
    //I(20, K(B,2));
    //I(8, K(B,5), arpeggio);
    //R(24);
    //I(10, K(C,5));
    //I(28, K(A,3));
    //I(16, pitchslidupstop);
    //I(4, K(B,4)); I(8, K(B,7)); I(16, K(B,5));
    //I(4, K(B,4), {volset, volslidup});
    //I(1, K(B,4), {panright, panslideLR});
    //I(0, K(A,4));
    //I(2, K(A,4));
    //I(4, K(B,1));

    //I(0, K(C_S,4), global_pitchslideup);
    //I(0, K(B,8), global_pitchslidedown);
    //I(0, K(A, 4), global_volume_slidedown);
    //I(0, K(A, 4), {global_volume_0, global_volume_slideup});
    //I(0, K(A, 4), {global_panningleft, global_panning_slideright});
    //I(0, K(A, 4), {global_panningright, global_panning_slideleft});
    //I(0, K(A, 4), global_vibrato);
    //I(0, K(A, 4), global_tremolo);

    /*I(7, release);
    I(8, K(F,2));

    I(15, release);
    I(16, K(C,3));

    I(23, release);
    I(24, K(F,3));

    I(31, release);*/
    //I(15, K(B,3));
    //I(20, K(B,4));
    //I(12, K(G,7));
    //I(6, K(C,4));
    //I(4, pitchslidown);
    //I(15, pitchslidup);
    //I(20, pitchslidown);
    //I(15, panslideLR);
    //PATRN(1);
    //I(10, panslideLR);
    //P(0,1,0);
}