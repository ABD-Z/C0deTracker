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
        instrubank[STRING] = new CodeTracker::Instrument(new CodeTracker::PSG(CodeTracker::SAW, 1.0f, CodeTracker::ADSR(10.f, 3.66, 0.33, 0.0f)));
        instrubank[BASS] = new CodeTracker::Instrument(new CodeTracker::PSG(CodeTracker::TRIANGLE, 0.78f, CodeTracker::ADSR(100.0f, 2.5f, 0.15f, 0.0f)));
        instrubank[MAIN2] = new CodeTracker::Instrument(new CodeTracker::PSG(CodeTracker::SQUARE, 0.2f, CodeTracker::ADSR(25.0f, 2.f, 0.5f, 10.f)));
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
        INPUT(patterns, 0 * FRAMES + 0,  0, KICK, 1.f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 0, 24, KICK, 1.f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 0, 32, KICK, 1.f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 0, 40, KICK, 1.f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 0, 56, KICK, 1.f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 0, 62, KICK, 1.f, Key(A,1));

        printf("WRITING PATTERN 1 CHAN 0\n");
        INPUT(patterns, 0 * FRAMES + 1, 8, KICK, 1.f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 1, 24, KICK, 1.f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 1, 32, KICK, 1.f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 1, 40, KICK, 1.f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 1, 46, KICK, 1.f, Key(A,1));

        INPUT(patterns, 0 * FRAMES + 1, 50, KICK, 1.f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 1, 52, SNARE, 1.f, Key(C,0));
        INPUT(patterns, 0 * FRAMES + 1, 56, KICK, 1.f, Key(A,1));
        INPUT(patterns, 0 * FRAMES + 1, 58, SNARE, 1.f, Key(C,0));
        INPUT(patterns, 0 * FRAMES + 1, 60, SNARE, 1.f, Key(C,0));


        printf("WRITING PATTERN 0 CHAN 1\n");
        INPUT(patterns, 1 * FRAMES + 0, 4, MAIN2, 0.15f, Key(F,5));
        INPUT(patterns, 1 * FRAMES + 0, 8, MAIN2, 0.15f, Key(D_S,5));
        INPUT(patterns, 1 * FRAMES + 0, 10, MAIN2, 0.15f, Key(F,5));
        INPUT(patterns, 1 * FRAMES + 0, 14, MAIN2, 0.15f, Key(F_S,5));

        INPUT(patterns, 1 * FRAMES + 0, 18, MAIN2, 0.15f, Key(F_S,5));
        INPUT(patterns, 1 * FRAMES + 0, 20, MAIN2, 0.15f, Key(F,5));
        INPUT(patterns, 1 * FRAMES + 0, 24, MAIN2, 0.15f, Key(D_S,5));
        INPUT(patterns, 1 * FRAMES + 0, 28, MAIN2, 0.15f, Key(F,5));

        INPUT(patterns, 1 * FRAMES + 0, 32 +4, MAIN2, 0.15f, Key(F,5));
        INPUT(patterns, 1 * FRAMES + 0, 32 + 8, MAIN2, 0.15f, Key(D_S,5));
        INPUT(patterns, 1 * FRAMES + 0, 32 + 10, MAIN2, 0.15f, Key(F,5));
        INPUT(patterns, 1 * FRAMES + 0, 32 + 14, MAIN2, 0.15f, Key(F_S,5));

        INPUT(patterns, 1 * FRAMES + 0, 32 + 18, MAIN2, 0.15f, Key(F_S,5));
        INPUT(patterns, 1 * FRAMES + 0, 32 + 20, MAIN2, 0.15f, Key(F,5));
        INPUT(patterns, 1 * FRAMES + 0, 32 + 24, MAIN2, 0.15f, Key(D_S,5));
        INPUT(patterns, 1 * FRAMES + 0, 32 + 28, MAIN2, 0.15f, Key(F,5));

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
        *patterns_indices[0 * FRAMES + 0] = 0;
        *patterns_indices[0 * FRAMES + 1] = 1;

        *patterns_indices[1 * FRAMES + 0] = 0;
        *patterns_indices[1 * FRAMES + 1] = 0;
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