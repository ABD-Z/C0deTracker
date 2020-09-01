//
// Created by Administrateur on 30/08/2020.
//

#include "example.hpp"
namespace ssf2_credit_theme{

    CodeTracker::Instrument** gen_instrubank(){
        printf("BANK OF %d INITIALIZING\n", INSTRUMENTS);
        //*******************************************INSTRUMENTS BANK*************************************************//
        CodeTracker::Instrument** instrubank;
        instrubank = new CodeTracker::Instrument*[INSTRUMENTS];
        instrubank[KICK] = new CodeTracker::Instrument(new CodeTracker::PSG(CodeTracker::WHITENOISE, 0.1f, CodeTracker::ADSR(1000000.f, 80.75f, 0.0f, 0.f)));
        instrubank[SNARE] = new CodeTracker::Instrument(new CodeTracker::PSG(CodeTracker::WHITENOISE, 0.00001f, CodeTracker::ADSR(100000000.f, 4.44f, 0.0f, 0.f)));
        instrubank[STRING] = new CodeTracker::Instrument(new CodeTracker::PSG(CodeTracker::SAW, 1.0f, CodeTracker::ADSR(10.f, 0.88, 0.33, 0.0f)));
        instrubank[BASS] = new CodeTracker::Instrument(new CodeTracker::PSG(CodeTracker::TRIANGLE, 0.78f, CodeTracker::ADSR(100.0f, 2.5f, 0.3f, 0.0f)));
        instrubank[MAIN2] = new CodeTracker::Instrument(new CodeTracker::PSG(CodeTracker::SQUARE, .125f, 0.f, CodeTracker::ADSR(10.0f, 1.f, .075f, 10.f)));
        return instrubank;
    }

    void INPUT(CodeTracker::Pattern** p, uint8_t pattern_index, uint8_t instruction_index, uint8_t instrument_index, float volume, CodeTracker::Key key){
        //printf("WRITING INSTRUCTION\n");
        p[pattern_index]->instructions[instruction_index]->instrument_index = instrument_index;
        p[pattern_index]->instructions[instruction_index]->volume = volume;
        p[pattern_index]->instructions[instruction_index]->key = key;
    }

    CodeTracker::Pattern** gen_patterns(){
        printf("PATTERNS OF %d INITIALIZING\n", CHANNELS * FRAMES);
        auto** patterns = new CodeTracker::Pattern*[CHANNELS * FRAMES];
        for(uint8_t i = 0; i < CHANNELS * FRAMES; ++i){
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
        INPUT(patterns, 0 * FRAMES + 1, 52, SNARE, 0.5f, Key(C,0));
        INPUT(patterns, 0 * FRAMES + 1, 56, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 1, 58, SNARE, 0.5f, Key(C,0));
        INPUT(patterns, 0 * FRAMES + 1, 60, SNARE, 0.5f, Key(C,0));

        printf("WRITING PATTERN 2 CHAN 0\n");
        INPUT(patterns, 0 * FRAMES + 2,  0, KICK, .5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 2, 4, SNARE, .5f, Key(C,0));
        INPUT(patterns, 0 * FRAMES + 2,  8, KICK, .5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 2, 12, SNARE, .5f, Key(C,0));

        INPUT(patterns, 0 * FRAMES + 2,  16, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 2, 20, SNARE, 0.5f, Key(C,0));
        INPUT(patterns, 0 * FRAMES + 2,  24, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 2,  26, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 2, 28, SNARE, 0.5f, Key(C,0));

        INPUT(patterns, 0 * FRAMES + 2,  32, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 2, 36, SNARE, 0.5f, Key(C,0));
        INPUT(patterns, 0 * FRAMES + 2,  40, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 2, 44, SNARE, 0.5f, Key(C,0));

        INPUT(patterns, 0 * FRAMES + 2,  48, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 2, 52, SNARE, 0.5f, Key(C,0));
        INPUT(patterns, 0 * FRAMES + 2,  56, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 2,  58, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 2, 60, SNARE, 0.5f, Key(C,0));
        INPUT(patterns, 0 * FRAMES + 2, 62, KICK, 0.5f, Key(A,1));

        printf("WRITING PATTERN 3 CHAN 0\n");
        INPUT(patterns, 0 * FRAMES + 3,  2, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 3, 4, SNARE, 0.5f, Key(C,0));
        INPUT(patterns, 0 * FRAMES + 3,  8, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 3, 12, SNARE, 0.5f, Key(C,0));

        INPUT(patterns, 0 * FRAMES + 3,  16, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 3, 20, SNARE, 0.5f, Key(C,0));
        INPUT(patterns, 0 * FRAMES + 3,  24, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 3,  26, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 3, 28, SNARE, 0.5f, Key(C,0));

        INPUT(patterns, 0 * FRAMES + 3,  32, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 3, 36, SNARE, 0.5f, Key(C,0));
        INPUT(patterns, 0 * FRAMES + 3,  40, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 3, 44, SNARE, 0.5f, Key(C,0));
        INPUT(patterns, 0 * FRAMES + 3,  46, KICK, 0.5f, Key(A,1));

        INPUT(patterns, 0 * FRAMES + 3, 50, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 3, 52, SNARE, 0.5f, Key(C,0));
        INPUT(patterns, 0 * FRAMES + 3, 56, KICK, 0.5f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 3, 58, SNARE, 0.5f, Key(C,0));
        INPUT(patterns, 0 * FRAMES + 3, 60, SNARE, 0.5f, Key(C,0));

        printf("WRITING PATTERN 0 CHAN 1\n");
        INPUT(patterns, 1 * FRAMES + 0, 4, MAIN2, 0.16f, Key(F,5));
        INPUT(patterns, 1 * FRAMES + 0, 8, MAIN2, 0.16f, Key(D_S,5));
        INPUT(patterns, 1 * FRAMES + 0, 10, MAIN2, 0.16f, Key(F,5));
        INPUT(patterns, 1 * FRAMES + 0, 14, MAIN2, 0.16f, Key(F_S,5));

        INPUT(patterns, 1 * FRAMES + 0, 18, MAIN2, 0.16f, Key(F_S,5));
        INPUT(patterns, 1 * FRAMES + 0, 20, MAIN2, 0.16f, Key(F,5));
        INPUT(patterns, 1 * FRAMES + 0, 24, MAIN2, 0.16f, Key(D_S,5));
        INPUT(patterns, 1 * FRAMES + 0, 28, MAIN2, 0.16f, Key(F,5));

        INPUT(patterns, 1 * FRAMES + 0, 32 +4, MAIN2, 0.16f, Key(F,5));
        INPUT(patterns, 1 * FRAMES + 0, 32 + 8, MAIN2, 0.16f, Key(D_S,5));
        INPUT(patterns, 1 * FRAMES + 0, 32 + 10, MAIN2, 0.16f, Key(F,5));
        INPUT(patterns, 1 * FRAMES + 0, 32 + 14, MAIN2, 0.16f, Key(F_S,5));

        INPUT(patterns, 1 * FRAMES + 0, 32 + 18, MAIN2, 0.16f, Key(F_S,5));
        INPUT(patterns, 1 * FRAMES + 0, 32 + 20, MAIN2, 0.16f, Key(F,5));
        INPUT(patterns, 1 * FRAMES + 0, 32 + 24, MAIN2, 0.16f, Key(D_S,5));
        INPUT(patterns, 1 * FRAMES + 0, 32 + 28, MAIN2, 0.16f, Key(F,5));

        printf("WRITING PATTERN 1 CHAN 1\n");
        INPUT(patterns, 1 * FRAMES + 1, 4, MAIN2, 0.16f, Key(F,5));
        INPUT(patterns, 1 * FRAMES + 1, 8, MAIN2, 0.16f, Key(D_S,5));
        INPUT(patterns, 1 * FRAMES + 1, 10, MAIN2, 0.16f, Key(F,5));
        INPUT(patterns, 1 * FRAMES + 1, 14, MAIN2, 0.16f, Key(F_S,5));

        INPUT(patterns, 1 * FRAMES + 1, 18, MAIN2, 0.16f, Key(F_S,5));
        INPUT(patterns, 1 * FRAMES + 1, 20, MAIN2, 0.16f, Key(F,5));
        INPUT(patterns, 1 * FRAMES + 1, 24, MAIN2, 0.16f, Key(D_S,5));
        INPUT(patterns, 1 * FRAMES + 1, 28, MAIN2, 0.16f, Key(F,5));

        INPUT(patterns, 1 * FRAMES + 1, 32 + 0, MAIN2, 0.16f, Key(F_S,5));
        INPUT(patterns, 1 * FRAMES + 1, 32 + 6, MAIN2, 0.16f, Key(F_S,5));

        INPUT(patterns, 1 * FRAMES + 1, 32 + 14, MAIN2, 0.16f, Key(G_S,5));

        printf("WRITING PATTERN 0 CHAN 2\n");
        INPUT(patterns, 2 * FRAMES + 0, 0, STRING, 0.15f, Key(G_S,4));
        INPUT(patterns, 2 * FRAMES + 0, 32, STRING, 0.15f, Key(G_S,4));
        INPUT(patterns, 2 * FRAMES + 0, 62, STRING, 0.15f, Key(G_S,4));

        printf("WRITING PATTERN 1 CHAN 2\n");
        INPUT(patterns, 2 * FRAMES + 1, 32, STRING, 0.15f, Key(C_S,5));
        INPUT(patterns, 2 * FRAMES + 1, 46, STRING, 0.15f, Key(C,5));

        printf("WRITING PATTERN 0 CHAN 3\n");
        INPUT(patterns, 3 * FRAMES + 0, 0, BASS, 1.f, Key(C_S,2));
        INPUT(patterns, 3 * FRAMES + 0, 32, BASS, 1.f, Key(B,1));
        INPUT(patterns, 3 * FRAMES + 0, 62, BASS, 1.f, Key(A_S,1));

        printf("WRITING PATTERN 1 CHAN 3\n");
        INPUT(patterns, 3 * FRAMES + 1, 32, BASS, 1.f, Key(B,1));
        INPUT(patterns, 3 * FRAMES + 1, 46, BASS, 1.f, Key(G_S,1));

        printf("WRITING PATTERN 2 CHAN 3\n");
        INPUT(patterns, 3 * FRAMES + 2, 0, BASS, 1.f, Key(C_S,2));
        INPUT(patterns, 3 * FRAMES + 2, 2, BASS, 1.f, Key(C_S,2));
        INPUT(patterns, 3 * FRAMES + 2, 4, BASS, 1.f, Key(C_S,2));
        INPUT(patterns, 3 * FRAMES + 2, 6, BASS, 1.f, Key(C_S,2));
        INPUT(patterns, 3 * FRAMES + 2, 8, BASS, 1.f, Key(C_S,2));
        INPUT(patterns, 3 * FRAMES + 2, 10, BASS, 1.f, Key(C_S,2));
        INPUT(patterns, 3 * FRAMES + 2, 12, BASS, 1.f, Key(C_S,2));
        INPUT(patterns, 3 * FRAMES + 2, 14, BASS, 1.f, Key(C_S,2));

        INPUT(patterns, 3 * FRAMES + 2, 16, BASS, 1.f, Key(C_S,2));
        INPUT(patterns, 3 * FRAMES + 2, 18, BASS, 1.f, Key(C_S,2));
        INPUT(patterns, 3 * FRAMES + 2, 20, BASS, 1.f, Key(C_S,2));
        INPUT(patterns, 3 * FRAMES + 2, 22, BASS, 1.f, Key(C_S,2));
        INPUT(patterns, 3 * FRAMES + 2, 24, BASS, 1.f, Key(C_S,2));
        INPUT(patterns, 3 * FRAMES + 2, 26, BASS, 1.f, Key(C_S,2));
        INPUT(patterns, 3 * FRAMES + 2, 28, BASS, 1.f, Key(C_S,2));
        INPUT(patterns, 3 * FRAMES + 2, 30, BASS, 1.f, Key(C_S,2));

        INPUT(patterns, 3 * FRAMES + 2, 32, BASS, 1.f, Key(B,1));
        INPUT(patterns, 3 * FRAMES + 2, 34, BASS, 1.f, Key(B,1));
        INPUT(patterns, 3 * FRAMES + 2, 36, BASS, 1.f, Key(B,1));
        INPUT(patterns, 3 * FRAMES + 2, 38, BASS, 1.f, Key(B,1));
        INPUT(patterns, 3 * FRAMES + 2, 40, BASS, 1.f, Key(B,1));
        INPUT(patterns, 3 * FRAMES + 2, 42, BASS, 1.f, Key(B,1));
        INPUT(patterns, 3 * FRAMES + 2, 44, BASS, 1.f, Key(B,1));
        INPUT(patterns, 3 * FRAMES + 2, 46, BASS, 1.f, Key(B,1));

        INPUT(patterns, 3 * FRAMES + 2, 48, BASS, 1.f, Key(B,1));
        INPUT(patterns, 3 * FRAMES + 2, 50, BASS, 1.f, Key(B,1));
        INPUT(patterns, 3 * FRAMES + 2, 52, BASS, 1.f, Key(B,1));
        INPUT(patterns, 3 * FRAMES + 2, 54, BASS, 1.f, Key(B,1));
        INPUT(patterns, 3 * FRAMES + 2, 56, BASS, 1.f, Key(B,1));
        INPUT(patterns, 3 * FRAMES + 2, 58, BASS, 1.f, Key(F_S,1));
        INPUT(patterns, 3 * FRAMES + 2, 60, BASS, 1.f, Key(B,1));
        INPUT(patterns, 3 * FRAMES + 2, 62, BASS, 1.f, Key(A_S,1));

        printf("WRITING PATTERN 3 CHAN 3\n");
        INPUT(patterns, 3 * FRAMES + 3, 2, BASS, 1.f, Key(A_S,1));
        INPUT(patterns, 3 * FRAMES + 3, 4, BASS, 1.f, Key(A_S,1));
        INPUT(patterns, 3 * FRAMES + 3, 6, BASS, 1.f, Key(A_S,1));
        INPUT(patterns, 3 * FRAMES + 3, 8, BASS, 1.f, Key(A_S,1));
        INPUT(patterns, 3 * FRAMES + 3, 10, BASS, 1.f, Key(A_S,1));
        INPUT(patterns, 3 * FRAMES + 3, 12, BASS, 1.f, Key(A_S,1));
        INPUT(patterns, 3 * FRAMES + 3, 14, BASS, 1.f, Key(A_S,1));

        INPUT(patterns, 3 * FRAMES + 3, 16, BASS, 1.f, Key(A_S,1));
        INPUT(patterns, 3 * FRAMES + 3, 18, BASS, 1.f, Key(A_S,1));
        INPUT(patterns, 3 * FRAMES + 3, 20, BASS, 1.f, Key(A_S,1));
        INPUT(patterns, 3 * FRAMES + 3, 22, BASS, 1.f, Key(A_S,1));
        INPUT(patterns, 3 * FRAMES + 3, 24, BASS, 1.f, Key(A_S,1));
        INPUT(patterns, 3 * FRAMES + 3, 26, BASS, 1.f, Key(A_S,1));
        INPUT(patterns, 3 * FRAMES + 3, 28, BASS, 1.f, Key(A_S,1));
        INPUT(patterns, 3 * FRAMES + 3, 30, BASS, 1.f, Key(A_S,1));

        INPUT(patterns, 3 * FRAMES + 3, 32, BASS, 1.f, Key(B,1));
        INPUT(patterns, 3 * FRAMES + 3, 34, BASS, 1.f, Key(B,1));
        INPUT(patterns, 3 * FRAMES + 3, 36, BASS, 1.f, Key(B,1));
        INPUT(patterns, 3 * FRAMES + 3, 38, BASS, 1.f, Key(B,1));
        INPUT(patterns, 3 * FRAMES + 3, 40, BASS, 1.f, Key(B,1));
        INPUT(patterns, 3 * FRAMES + 3, 42, BASS, 1.f, Key(A_S,1));
        INPUT(patterns, 3 * FRAMES + 3, 44, BASS, 1.f, Key(A,1));
        INPUT(patterns, 3 * FRAMES + 3, 46, BASS, 1.f, Key(G_S,1));

        INPUT(patterns, 3 * FRAMES + 3, 50, BASS, 1.f, Key(G_S,1));
        INPUT(patterns, 3 * FRAMES + 3, 52, BASS, 1.f, Key(G_S,1));
        INPUT(patterns, 3 * FRAMES + 3, 54, BASS, 1.f, Key(G_S,1));
        INPUT(patterns, 3 * FRAMES + 3, 56, BASS, 1.f, Key(G_S,1));
        INPUT(patterns, 3 * FRAMES + 3, 58, BASS, 1.f, Key(G_S,1));
        INPUT(patterns, 3 * FRAMES + 3, 60, BASS, 1.f, Key(G_S,1));
        INPUT(patterns, 3 * FRAMES + 3, 62, BASS, 1.f, Key(G_S,1));

        return patterns;
    }

    uint8_t**  gen_track_patterns_indices(){
        printf("PATTERN INDICES TAB OF LENGTH %d INITIALIZING\n", CHANNELS*FRAMES);
        auto** patterns_indices = new uint8_t*[CHANNELS * FRAMES];
        for(uint8_t i = 0; i < CHANNELS; ++i){
            for(uint8_t j = 0; j < FRAMES; ++j){
                patterns_indices[i * FRAMES + j] = new uint8_t(j);
            }
        }
        //printf("END OF PATTERN INDICES INIT\n");
        *patterns_indices[1 * FRAMES + 2] = 0;
        *patterns_indices[1 * FRAMES + 3] = 1;

        *patterns_indices[2 * FRAMES + 2] = 0;
        *patterns_indices[2 * FRAMES + 3] = 1;




        return patterns_indices;
    }


    CodeTracker::Track* init_track(){
        printf("INITIALIZING TRACK\n");
        //*******************************************INSTRUMENTS BANK*************************************************//
        CodeTracker::Instrument** instrubank = gen_instrubank();
        CodeTracker::Pattern** patterns = gen_patterns();
        uint8_t** indices = gen_track_patterns_indices();

        return new CodeTracker::Track(CLOCK, BASETIME, SPEED, ROWS, FRAMES, CHANNELS, instrubank, INSTRUMENTS, patterns, indices);
    }

    float play(CodeTracker::Track* track, float t, CodeTracker::Channel* chan){
        return track->play(t, chan);
    }

    void destroy_track(CodeTracker::Track* track){
        printf("DESTROYING TRACK\n");
       // delete[] instrument_bank;
        //blank.~Pattern();
    }

}