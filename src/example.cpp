//
// Created by Abdulmajid, Olivier NASSER on 30/08/2020.
//

#include "example.hpp"
namespace ssf2_credit_theme{

    CodeTracker::Instrument** gen_instrubank(){
        printf("BANK OF %d INSTRUMENTS INITIALIZING\n", INSTRUMENTS);
        //*******************************************INSTRUMENTS BANK*************************************************//
        CodeTracker::Instrument** instrubank;
        instrubank = new CodeTracker::Instrument*[INSTRUMENTS];
        instrubank[KICK] = new CodeTracker::Instrument(new CodeTracker::PSG(CodeTracker::WHITENOISE, 0.1f, CodeTracker::ADSR(10000.f, 50.75f, 0.0f, 0.f)), 1.f);
        instrubank[SNARE] = new CodeTracker::Instrument(new CodeTracker::PSG(CodeTracker::WHITENOISE, .0025f, CodeTracker::ADSR(10000.f, 4.44f, 0.0f, 0.f)),0.78f);
        instrubank[STRING] = new CodeTracker::Instrument(new CodeTracker::PSG(CodeTracker::SAW, .08f, CodeTracker::ADSR(10.f, 0.88, 0.5, 0.0f)),.78f);
        instrubank[BASS] = new CodeTracker::Instrument(new CodeTracker::PSG(CodeTracker::TRIANGLE, 0.78f, 0.5f, CodeTracker::ADSR(666.0f, 0.3f, 0.2f, 17.75f)),1.f);
        instrubank[MAIN2] = new CodeTracker::Instrument(new CodeTracker::PSG(CodeTracker::SQUARE, .125f, 0.f, CodeTracker::ADSR(10.0f, 1.f, .075f, 10.f)),0.5f);
        return instrubank;
    }

    void INPUT(CodeTracker::Pattern** p, uint_fast8_t pattern_index, uint_fast8_t instruction_index, uint_fast8_t instrument_index, float volume, CodeTracker::Key key){
        p[pattern_index]->instructions[instruction_index]->instrument_index = instrument_index;
        p[pattern_index]->instructions[instruction_index]->volume = volume;
        p[pattern_index]->instructions[instruction_index]->key = key;
    }

    void RELES(CodeTracker::Pattern **p, uint_fast8_t pattern_index, uint_fast8_t instruction_index) {
        p[pattern_index]->instructions[instruction_index]->instrument_index = CodeTracker::Notes::RELEASE;
    }

    void INVOL(CodeTracker::Pattern** p, uint_fast8_t pattern_index, uint_fast8_t instruction_index, float volume){
        p[pattern_index]->instructions[instruction_index]->volume = volume;
    }

    void INPUT(CodeTracker::Pattern** p, uint_fast8_t chan_index, uint_fast8_t pattern_index, uint_fast8_t instruction_index, uint_fast8_t instrument_index, float volume, CodeTracker::Key key){
        p[chan_index * FRAMES + pattern_index]->instructions[instruction_index]->instrument_index = instrument_index;
        p[chan_index * FRAMES + pattern_index]->instructions[instruction_index]->volume = volume;
        p[chan_index * FRAMES + pattern_index]->instructions[instruction_index]->key = key;
    }

    void INPUT(CodeTracker::Pattern** p, uint_fast8_t chan_index, uint_fast8_t pattern_index, uint_fast8_t instruction_index, uint_fast8_t instrument_index){
        p[chan_index * FRAMES + pattern_index]->instructions[instruction_index]->instrument_index = instrument_index;
    }

    CodeTracker::Pattern** gen_patterns(){
        printf("PATTERNS OF %d INITIALIZING\n", CHANNELS * FRAMES);
        auto** patterns = new CodeTracker::Pattern*[CHANNELS * FRAMES];
        for(uint_fast8_t i = 0; i < CHANNELS * FRAMES; ++i){
            patterns[i] = new CodeTracker::Pattern(ROWS);
        }

        using namespace CodeTracker::Notes; using namespace CodeTracker;

        printf("WRITING PATTERN 0 CHAN 0\n");
        INPUT(patterns, 0 * FRAMES + 0,  0, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 0, 24, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 0, 32, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 0, 40, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 0, 56, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 0, 62, KICK, 0.5f, Key(A,1));

        printf("WRITING PATTERN 1 CHAN 0\n");
        INPUT(patterns, 0 * FRAMES + 1, 8, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 1, 24, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 1, 32, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 1, 40, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 1, 46, KICK, 0.5f, Key(A,1));

        INPUT(patterns, 0 * FRAMES + 1, 50, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 1, 52, SNARE, 0.5f, Key(G_S,2));
        INPUT(patterns, 0 * FRAMES + 1, 56, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 1, 58, SNARE, 0.5f, Key(G_S,2));
        INPUT(patterns, 0 * FRAMES + 1, 60, SNARE, 0.5f, Key(G_S,3));

        printf("WRITING PATTERN 2 CHAN 0\n");
        INPUT(patterns, 0 * FRAMES + 2,  0, KICK, .5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 2, 4, SNARE, .5f, Key(G_S,2));
        INPUT(patterns, 0 * FRAMES + 2,  8, KICK, .5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 2, 12, SNARE, .5f, Key(G_S,2));

        INPUT(patterns, 0 * FRAMES + 2,  16, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 2, 20, SNARE, 0.5f, Key(G_S,2));
        INPUT(patterns, 0 * FRAMES + 2,  24, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 2,  26, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 2, 28, SNARE, 0.5f, Key(G_S,2));

        INPUT(patterns, 0 * FRAMES + 2,  32, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 2, 36, SNARE, 0.5f, Key(G_S,2));
        INPUT(patterns, 0 * FRAMES + 2,  40, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 2, 44, SNARE, 0.5f, Key(G_S,2));

        INPUT(patterns, 0 * FRAMES + 2,  48, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 2, 52, SNARE, 0.5f, Key(G_S,2));
        INPUT(patterns, 0 * FRAMES + 2,  56, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 2,  58, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 2, 60, SNARE, 0.5f, Key(G_S,2));
        INPUT(patterns, 0 * FRAMES + 2, 62, KICK, 0.5f, Key(A,1));

        printf("WRITING PATTERN 3 CHAN 0\n");
        INPUT(patterns, 0 * FRAMES + 3,  2, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 3, 4, SNARE, 0.5f, Key(G_S,2));
        INPUT(patterns, 0 * FRAMES + 3,  8, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 3, 12, SNARE, 0.5f, Key(G_S,2));

        INPUT(patterns, 0 * FRAMES + 3,  16, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 3, 20, SNARE, 0.5f, Key(G_S,2));
        INPUT(patterns, 0 * FRAMES + 3,  24, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 3,  26, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 3, 28, SNARE, 0.5f, Key(G_S,2));

        INPUT(patterns, 0 * FRAMES + 3,  32, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 3, 36, SNARE, 0.5f, Key(G_S,2));
        INPUT(patterns, 0 * FRAMES + 3,  40, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 3, 44, SNARE, 0.5f, Key(G_S,2));
        INPUT(patterns, 0 * FRAMES + 3,  46, KICK, 0.5f, Key(A,1));

        INPUT(patterns, 0 * FRAMES + 3, 50, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 3, 52, SNARE, 0.5f, Key(G_S,2));
        INPUT(patterns, 0 * FRAMES + 3, 56, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 3, 58, SNARE, 0.5f, Key(G_S,2));
        INPUT(patterns, 0 * FRAMES + 3, 60, SNARE, 0.5f, Key(G_S,3));

        printf("WRITING PATTERN 0 CHAN 1\n");
        INPUT(patterns, 1 * FRAMES + 0, 4, MAIN2, 0.16f, Key(F,5));
        RELES(patterns, 1 * FRAMES + 0, 6);
        INPUT(patterns, 1 * FRAMES + 0, 8, MAIN2, 0.16f, Key(D_S,5));
        INPUT(patterns, 1 * FRAMES + 0, 10, MAIN2, 0.16f, Key(F,5));
        RELES(patterns, 1 * FRAMES + 0, 12);
        INPUT(patterns, 1 * FRAMES + 0, 14, MAIN2, 0.16f, Key(F_S,5));
        RELES(patterns, 1 * FRAMES + 0, 16);

        INPUT(patterns, 1 * FRAMES + 0, 18, MAIN2, 0.16f, Key(F_S,5));
        INPUT(patterns, 1 * FRAMES + 0, 20, MAIN2, 0.16f, Key(F,5));
        RELES(patterns, 1 * FRAMES + 0, 22);
        INPUT(patterns, 1 * FRAMES + 0, 24, MAIN2, 0.16f, Key(D_S,5));
        INPUT(patterns, 1 * FRAMES + 0, 28, MAIN2, 0.16f, Key(F,5));
        RELES(patterns, 1 * FRAMES + 0, 30);

        INPUT(patterns, 1 * FRAMES + 0, 32 + 4, MAIN2, 0.16f, Key(F,5));
        RELES(patterns, 1 * FRAMES + 0, 32 + 6);
        INPUT(patterns, 1 * FRAMES + 0, 32 + 8, MAIN2, 0.16f, Key(D_S,5));
        INPUT(patterns, 1 * FRAMES + 0, 32 + 10, MAIN2, 0.16f, Key(F,5));
        RELES(patterns, 1 * FRAMES + 0, 32 + 12);
        INPUT(patterns, 1 * FRAMES + 0, 32 + 14, MAIN2, 0.16f, Key(F_S,5));
        RELES(patterns, 1 * FRAMES + 0, 32 + 16);

        INPUT(patterns, 1 * FRAMES + 0, 32 + 18, MAIN2, 0.16f, Key(F_S,5));
        INPUT(patterns, 1 * FRAMES + 0, 32 + 20, MAIN2, 0.16f, Key(F,5));
        RELES(patterns, 1 * FRAMES + 0, 32 + 22);
        INPUT(patterns, 1 * FRAMES + 0, 32 + 24, MAIN2, 0.16f, Key(D_S,5));
        INPUT(patterns, 1 * FRAMES + 0, 32 + 28, MAIN2, 0.16f, Key(F,5));
        RELES(patterns, 1 * FRAMES + 0, 32 + 30);

        printf("WRITING PATTERN 1 CHAN 1\n");
        INPUT(patterns, 1 * FRAMES + 1, 4, MAIN2, 0.16f, Key(F,5));
        RELES(patterns, 1 * FRAMES + 1, 6);
        INPUT(patterns, 1 * FRAMES + 1, 8, MAIN2, 0.16f, Key(D_S,5));
        INPUT(patterns, 1 * FRAMES + 1, 10, MAIN2, 0.16f, Key(F,5));
        RELES(patterns, 1 * FRAMES + 1, 12);
        INPUT(patterns, 1 * FRAMES + 1, 14, MAIN2, 0.16f, Key(F_S,5));
        RELES(patterns, 1 * FRAMES + 1, 16);

        INPUT(patterns, 1 * FRAMES + 1, 18, MAIN2, 0.16f, Key(F_S,5));
        INPUT(patterns, 1 * FRAMES + 1, 20, MAIN2, 0.16f, Key(F,5));
        RELES(patterns, 1 * FRAMES + 1, 22);
        INPUT(patterns, 1 * FRAMES + 1, 24, MAIN2, 0.16f, Key(D_S,5));
        INPUT(patterns, 1 * FRAMES + 1, 28, MAIN2, 0.16f, Key(F,5));
        RELES(patterns, 1 * FRAMES + 1, 30);

        INPUT(patterns, 1 * FRAMES + 1, 32 + 0, MAIN2, 0.16f, Key(F_S,5));
        INPUT(patterns, 1 * FRAMES + 1, 32 + 6, MAIN2, 0.16f, Key(F_S,5));
        RELES(patterns, 1 * FRAMES + 1, 32 + 12);

        INPUT(patterns, 1 * FRAMES + 1, 32 + 14, MAIN2, 0.16f, Key(G_S,5));
        RELES(patterns, 1 * FRAMES + 1, 32 + 14 + 12);

        printf("WRITING PATTERN 0 CHAN 2\n");
        INPUT(patterns, 2 * FRAMES + 0, 0, STRING, 0.15f, Key(G_S,4));
        INPUT(patterns, 2 * FRAMES + 0, 32, STRING, 0.15f, Key(G_S,4));
        INPUT(patterns, 2 * FRAMES + 0, 62, STRING, 0.15f, Key(G_S,4));

        printf("WRITING PATTERN 1 CHAN 2\n");
        INPUT(patterns, 2 * FRAMES + 1, 32, STRING, 0.15f, Key(C_S,5));
        INPUT(patterns, 2 * FRAMES + 1, 46, STRING, 0.15f, Key(C,5));

        printf("WRITING PATTERN 0 CHAN 3\n");
        INPUT(patterns, 3 * FRAMES + 0, 0, BASS, 1.f, Key(C_S,2));
        RELES(patterns, 3 * FRAMES + 0, 31);
        INPUT(patterns, 3 * FRAMES + 0, 32, BASS, 1.f, Key(B,1));
        RELES(patterns, 3 * FRAMES + 0, 61);
        INPUT(patterns, 3 * FRAMES + 0, 62, BASS, 1.f, Key(A_S,1));

        printf("WRITING PATTERN 1 CHAN 3\n");
        RELES(patterns, 3 * FRAMES + 1, 31);
        INPUT(patterns, 3 * FRAMES + 1, 32, BASS, 1.f, Key(B,1));
        RELES(patterns, 3 * FRAMES + 1, 45);
        INPUT(patterns, 3 * FRAMES + 1, 46, BASS, 1.f, Key(G_S,1));
        RELES(patterns, 3 * FRAMES + 1, 63);

        printf("WRITING PATTERN 2 CHAN 3\n");
        INPUT(patterns, 3 * FRAMES + 2, 0, BASS, 1.f, Key(C_S,2));
        RELES(patterns, 3 * FRAMES + 2, 1);
        INPUT(patterns, 3 * FRAMES + 2, 2, BASS, 1.f, Key(C_S,2));
        RELES(patterns, 3 * FRAMES + 2, 3);
        INPUT(patterns, 3 * FRAMES + 2, 4, BASS, 1.f, Key(C_S,2));
        RELES(patterns, 3 * FRAMES + 2, 5);
        INPUT(patterns, 3 * FRAMES + 2, 6, BASS, 1.f, Key(C_S,2));
        RELES(patterns, 3 * FRAMES + 2, 7);
        INPUT(patterns, 3 * FRAMES + 2, 8, BASS, 1.f, Key(C_S,2));
        RELES(patterns, 3 * FRAMES + 2, 9);
        INPUT(patterns, 3 * FRAMES + 2, 10, BASS, 1.f, Key(C_S,2));
        RELES(patterns, 3 * FRAMES + 2, 11);
        INPUT(patterns, 3 * FRAMES + 2, 12, BASS, 1.f, Key(C_S,2));
        RELES(patterns, 3 * FRAMES + 2, 13);
        INPUT(patterns, 3 * FRAMES + 2, 14, BASS, 1.f, Key(C_S,2));
        RELES(patterns, 3 * FRAMES + 2, 15);

        INPUT(patterns, 3 * FRAMES + 2, 16, BASS, 1.f, Key(C_S,2));
        RELES(patterns, 3 * FRAMES + 2, 17);
        INPUT(patterns, 3 * FRAMES + 2, 18, BASS, 1.f, Key(C_S,2));
        RELES(patterns, 3 * FRAMES + 2, 19);
        INPUT(patterns, 3 * FRAMES + 2, 20, BASS, 1.f, Key(C_S,2));
        RELES(patterns, 3 * FRAMES + 2, 21);
        INPUT(patterns, 3 * FRAMES + 2, 22, BASS, 1.f, Key(C_S,2));
        RELES(patterns, 3 * FRAMES + 2, 23);
        INPUT(patterns, 3 * FRAMES + 2, 24, BASS, 1.f, Key(C_S,2));
        RELES(patterns, 3 * FRAMES + 2, 25);
        INPUT(patterns, 3 * FRAMES + 2, 26, BASS, 1.f, Key(C_S,2));
        RELES(patterns, 3 * FRAMES + 2, 27);
        INPUT(patterns, 3 * FRAMES + 2, 28, BASS, 1.f, Key(C_S,2));
        RELES(patterns, 3 * FRAMES + 2, 29);
        INPUT(patterns, 3 * FRAMES + 2, 30, BASS, 1.f, Key(C_S,2));
        RELES(patterns, 3 * FRAMES + 2, 31);

        INPUT(patterns, 3 * FRAMES + 2, 32, BASS, 1.f, Key(B,1));
        RELES(patterns, 3 * FRAMES + 2, 33);
        INPUT(patterns, 3 * FRAMES + 2, 34, BASS, 1.f, Key(B,1));
        RELES(patterns, 3 * FRAMES + 2, 35);
        INPUT(patterns, 3 * FRAMES + 2, 36, BASS, 1.f, Key(B,1));
        RELES(patterns, 3 * FRAMES + 2, 37);
        INPUT(patterns, 3 * FRAMES + 2, 38, BASS, 1.f, Key(B,1));
        RELES(patterns, 3 * FRAMES + 2, 39);
        INPUT(patterns, 3 * FRAMES + 2, 40, BASS, 1.f, Key(B,1));
        RELES(patterns, 3 * FRAMES + 2, 41);
        INPUT(patterns, 3 * FRAMES + 2, 42, BASS, 1.f, Key(B,1));
        RELES(patterns, 3 * FRAMES + 2, 43);
        INPUT(patterns, 3 * FRAMES + 2, 44, BASS, 1.f, Key(B,1));
        RELES(patterns, 3 * FRAMES + 2, 45);
        INPUT(patterns, 3 * FRAMES + 2, 46, BASS, 1.f, Key(B,1));
        RELES(patterns, 3 * FRAMES + 2, 47);

        INPUT(patterns, 3 * FRAMES + 2, 48, BASS, 1.f, Key(B,1));
        RELES(patterns, 3 * FRAMES + 2, 49);
        INPUT(patterns, 3 * FRAMES + 2, 50, BASS, 1.f, Key(B,1));
        RELES(patterns, 3 * FRAMES + 2, 51);
        INPUT(patterns, 3 * FRAMES + 2, 52, BASS, 1.f, Key(B,1));
        RELES(patterns, 3 * FRAMES + 2, 53);
        INPUT(patterns, 3 * FRAMES + 2, 54, BASS, 1.f, Key(B,1));
        RELES(patterns, 3 * FRAMES + 2, 55);
        INPUT(patterns, 3 * FRAMES + 2, 56, BASS, 1.f, Key(B,1));
        RELES(patterns, 3 * FRAMES + 2, 57);
        INPUT(patterns, 3 * FRAMES + 2, 58, BASS, 1.f, Key(F_S,1));
        RELES(patterns, 3 * FRAMES + 2, 59);
        INPUT(patterns, 3 * FRAMES + 2, 60, BASS, 1.f, Key(B,1));
        RELES(patterns, 3 * FRAMES + 2, 61);
        INPUT(patterns, 3 * FRAMES + 2, 62, BASS, 1.f, Key(A_S,1));


        printf("WRITING PATTERN 3 CHAN 3\n");
        RELES(patterns, 3 * FRAMES + 3, 1);
        INPUT(patterns, 3 * FRAMES + 3, 2, BASS, 1.f, Key(A_S,1));
        RELES(patterns, 3 * FRAMES + 3, 3);
        INPUT(patterns, 3 * FRAMES + 3, 4, BASS, 1.f, Key(A_S,1));
        RELES(patterns, 3 * FRAMES + 3, 5);
        INPUT(patterns, 3 * FRAMES + 3, 6, BASS, 1.f, Key(A_S,1));
        RELES(patterns, 3 * FRAMES + 3, 7);
        INPUT(patterns, 3 * FRAMES + 3, 8, BASS, 1.f, Key(A_S,1));
        RELES(patterns, 3 * FRAMES + 3, 9);
        INPUT(patterns, 3 * FRAMES + 3, 10, BASS, 1.f, Key(A_S,1));
        RELES(patterns, 3 * FRAMES + 3, 11);
        INPUT(patterns, 3 * FRAMES + 3, 12, BASS, 1.f, Key(A_S,1));
        RELES(patterns, 3 * FRAMES + 3, 13);
        INPUT(patterns, 3 * FRAMES + 3, 14, BASS, 1.f, Key(A_S,1));
        RELES(patterns, 3 * FRAMES + 3, 15);

        INPUT(patterns, 3 * FRAMES + 3, 16, BASS, 1.f, Key(A_S,1));
        RELES(patterns, 3 * FRAMES + 3, 17);
        INPUT(patterns, 3 * FRAMES + 3, 18, BASS, 1.f, Key(A_S,1));
        RELES(patterns, 3 * FRAMES + 3, 19);
        INPUT(patterns, 3 * FRAMES + 3, 20, BASS, 1.f, Key(A_S,1));
        RELES(patterns, 3 * FRAMES + 3, 21);
        INPUT(patterns, 3 * FRAMES + 3, 22, BASS, 1.f, Key(A_S,1));
        RELES(patterns, 3 * FRAMES + 3, 23);
        INPUT(patterns, 3 * FRAMES + 3, 24, BASS, 1.f, Key(A_S,1));
        RELES(patterns, 3 * FRAMES + 3, 25);
        INPUT(patterns, 3 * FRAMES + 3, 26, BASS, 1.f, Key(A_S,1));
        RELES(patterns, 3 * FRAMES + 3, 27);
        INPUT(patterns, 3 * FRAMES + 3, 28, BASS, 1.f, Key(A_S,1));
        RELES(patterns, 3 * FRAMES + 3, 29);
        INPUT(patterns, 3 * FRAMES + 3, 30, BASS, 1.f, Key(A_S,1));
        RELES(patterns, 3 * FRAMES + 3, 31);

        INPUT(patterns, 3 * FRAMES + 3, 32, BASS, 1.f, Key(B,1));
        RELES(patterns, 3 * FRAMES + 3, 33);
        INPUT(patterns, 3 * FRAMES + 3, 34, BASS, 1.f, Key(B,1));
        RELES(patterns, 3 * FRAMES + 3, 35);
        INPUT(patterns, 3 * FRAMES + 3, 36, BASS, 1.f, Key(B,1));
        RELES(patterns, 3 * FRAMES + 3, 37);
        INPUT(patterns, 3 * FRAMES + 3, 38, BASS, 1.f, Key(B,1));
        RELES(patterns, 3 * FRAMES + 3, 39);
        INPUT(patterns, 3 * FRAMES + 3, 40, BASS, 1.f, Key(B,1));
        RELES(patterns, 3 * FRAMES + 3, 41);
        INPUT(patterns, 3 * FRAMES + 3, 42, BASS, 1.f, Key(A_S,1));
        RELES(patterns, 3 * FRAMES + 3, 43);
        INPUT(patterns, 3 * FRAMES + 3, 44, BASS, 1.f, Key(A,1));
        RELES(patterns, 3 * FRAMES + 3, 45);
        INPUT(patterns, 3 * FRAMES + 3, 46, BASS, 1.f, Key(G_S,1));
        RELES(patterns, 3 * FRAMES + 3, 49);

        INPUT(patterns, 3 * FRAMES + 3, 50, BASS, 1.f, Key(G_S,1));
        RELES(patterns, 3 * FRAMES + 3, 51);
        INPUT(patterns, 3 * FRAMES + 3, 52, BASS, 1.f, Key(G_S,1));
        RELES(patterns, 3 * FRAMES + 3, 53);
        INPUT(patterns, 3 * FRAMES + 3, 54, BASS, 1.f, Key(G_S,1));
        RELES(patterns, 3 * FRAMES + 3, 55);
        INPUT(patterns, 3 * FRAMES + 3, 56, BASS, 1.f, Key(G_S,1));
        RELES(patterns, 3 * FRAMES + 3, 57);
        INPUT(patterns, 3 * FRAMES + 3, 58, BASS, 1.f, Key(G_S,1));
        RELES(patterns, 3 * FRAMES + 3, 59);
        INPUT(patterns, 3 * FRAMES + 3, 60, BASS, 1.f, Key(G_S,1));
        RELES(patterns, 3 * FRAMES + 3, 61);
        INPUT(patterns, 3 * FRAMES + 3, 62, BASS, 1.f, Key(G_S,1));
        RELES(patterns, 3 * FRAMES + 3, 63);

        printf("WRITING PATTERN 0 CHAN 4\n");
        INPUT(patterns, 4 * FRAMES + 0, 4, MAIN2, 0.1f, Key(G_S,5));
        RELES(patterns, 4 * FRAMES + 0, 6);
        INPUT(patterns, 4 * FRAMES + 0, 8, MAIN2, 0.1f, Key(G_S,5));
        INPUT(patterns, 4 * FRAMES + 0, 10, MAIN2, 0.1f, Key(G_S,5));
        RELES(patterns, 4 * FRAMES + 0, 12);
        INPUT(patterns, 4 * FRAMES + 0, 14, MAIN2, 0.1f, Key(G_S,5));
        RELES(patterns, 4 * FRAMES + 0, 16);

        INPUT(patterns, 4 * FRAMES + 0, 18, MAIN2, 0.1f, Key(G_S,5));
        INPUT(patterns, 4 * FRAMES + 0, 20, MAIN2, 0.1f, Key(G_S,5));
        RELES(patterns, 4 * FRAMES + 0, 22);
        INPUT(patterns, 4 * FRAMES + 0, 24, MAIN2, 0.1f, Key(G_S,5));
        INPUT(patterns, 4 * FRAMES + 0, 28, MAIN2, 0.1f, Key(G_S,5));
        RELES(patterns, 4 * FRAMES + 0, 30);

        INPUT(patterns, 4 * FRAMES + 0, 32 + 4, MAIN2, 0.1f, Key(G_S,5));
        RELES(patterns, 4 * FRAMES + 0, 32 + 6);
        INPUT(patterns, 4 * FRAMES + 0, 32 + 8, MAIN2, 0.1f, Key(G_S,5));
        INPUT(patterns, 4 * FRAMES + 0, 32 + 10, MAIN2, 0.1f, Key(G_S,5));
        RELES(patterns, 4 * FRAMES + 0, 32 + 12);
        INPUT(patterns, 4 * FRAMES + 0, 32 + 14, MAIN2, 0.1f, Key(G_S,5));
        RELES(patterns, 4 * FRAMES + 0, 32 + 16);

        INPUT(patterns, 4 * FRAMES + 0, 32 + 18, MAIN2, 0.1f, Key(G_S,5));
        INPUT(patterns, 4 * FRAMES + 0, 32 + 20, MAIN2, 0.1f, Key(G_S,5));
        RELES(patterns, 4 * FRAMES + 0, 32 + 22);
        INPUT(patterns, 4 * FRAMES + 0, 32 + 24, MAIN2, 0.1f, Key(G_S,5));
        INPUT(patterns, 4 * FRAMES + 0, 32 + 28, MAIN2, 0.1f, Key(G_S,5));
        RELES(patterns, 4 * FRAMES + 0, 32 + 30);

        printf("WRITING PATTERN 1 CHAN 4\n");
        INPUT(patterns, 4 * FRAMES + 1, 4, MAIN2, 0.1f, Key(G_S,5));
        RELES(patterns, 4 * FRAMES + 1, 6);
        INPUT(patterns, 4 * FRAMES + 1, 8, MAIN2, 0.1f, Key(G_S,5));
        INPUT(patterns, 4 * FRAMES + 1, 10, MAIN2, 0.1f, Key(G_S,5));
        RELES(patterns, 4 * FRAMES + 1, 12);
        INPUT(patterns, 4 * FRAMES + 1, 14, MAIN2, 0.1f, Key(G_S,5));
        RELES(patterns, 4 * FRAMES + 1, 16);

        INPUT(patterns, 4 * FRAMES + 1, 18, MAIN2, 0.1f, Key(G_S,5));
        INPUT(patterns, 4 * FRAMES + 1, 20, MAIN2, 0.1f, Key(G_S,5));
        RELES(patterns, 4 * FRAMES + 1, 22);
        INPUT(patterns, 4 * FRAMES + 1, 24, MAIN2, 0.1f, Key(G_S,5));
        INPUT(patterns, 4 * FRAMES + 1, 28, MAIN2, 0.1f, Key(G_S,5));
        RELES(patterns, 4 * FRAMES + 1, 30);

        INPUT(patterns, 4 * FRAMES + 1, 32 + 0, MAIN2, 0.1f, Key(G_S,5));
        INPUT(patterns, 4 * FRAMES + 1, 32 + 6, MAIN2, 0.1f, Key(G_S,5));
        RELES(patterns, 4 * FRAMES + 1, 32 + 12);

        INPUT(patterns, 4 * FRAMES + 1, 32 + 14, MAIN2, 0.1f, Key(C,6));
        RELES(patterns, 4 * FRAMES + 1, 32 + 14 + 12);

        return patterns;
    }

    uint_fast8_t**  gen_track_patterns_indices(){
        printf("PATTERN INDICES TAB OF LENGTH %d INITIALIZING\n", CHANNELS*FRAMES);
        auto** patterns_indices = new uint8_t*[CHANNELS * FRAMES];
        for(uint_fast8_t i = 0; i < CHANNELS; ++i){
            for(uint_fast8_t j = 0; j < FRAMES; ++j){
                patterns_indices[i * FRAMES + j] = new uint8_t(j);
            }
        }
        //printf("END OF PATTERN INDICES INIT\n");
        *patterns_indices[1 * FRAMES + 2] = 0;
        *patterns_indices[1 * FRAMES + 3] = 1;

        *patterns_indices[2 * FRAMES + 2] = 0;
        *patterns_indices[2 * FRAMES + 3] = 1;

        *patterns_indices[4 * FRAMES + 2] = 0;
        *patterns_indices[4 * FRAMES + 3] = 1;


        return patterns_indices;
    }


    CodeTracker::Track* init_track(){
        printf("INITIALIZING TRACK\n");
        //*******************************************INSTRUMENTS BANK*************************************************//
        CodeTracker::Instrument** instrubank = gen_instrubank();
        CodeTracker::Pattern** patterns = gen_patterns();
        uint_fast8_t** indices = gen_track_patterns_indices();

        return new CodeTracker::Track(CLOCK, BASETIME, SPEED, ROWS, FRAMES, CHANNELS, instrubank, INSTRUMENTS, patterns, indices);
    }




}