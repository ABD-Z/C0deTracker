//
// Created by Abdulmajid, Olivier NASSER on 24/08/2020.
//
#include "code_tracker.hpp"

namespace  CodeTracker{

    Key::Key(float n, float o) { this->note = n; this->octave = o;}

    Key::Key(){this->note = Notes::CONTINUE; this->octave = Notes::CONTINUE;};

    ADSR::ADSR(float A, float D, float S, float R) { this->attack = A; this->decay = D; this->sustain = S; this->release = R;}


    namespace Notes {
        float pitch(float p){return pow(1.059460646483f, p) * 440.0f;}

        float key2freq(float note , float octave){
            //A4 == 440 HZ = pitch 0
            //-12 pitch == 3A == 220 HZ
            //+12
            return pitch(float(PITCHES_PER_OCTAVE
                                  *(octave - OCTAVE_PITCH_OFFSET)
                                  +(note - NOTE_PITCH_OFFSET)
                                  ));
        }

        float key2freq(Key key){
            return key2freq(key.note, key.octave);
        }
    }

    Instruction::Instruction(uint_fast8_t instrument, Key k, float vol) : key(k) {
        this->instrument_index = instrument; this->volume = vol; this->effects = nullptr;
    }

    Instruction::Instruction(uint_fast8_t instrument, float note, float octave, float vol) : key(Key(note, octave)) {
        this->instrument_index = instrument; this->volume = vol; this->effects = nullptr;
    }

    Instruction::Instruction(uint_fast8_t instrument, Key k, float vol, uint_fast32_t**effects) : key(k){
        this->instrument_index = instrument; this->volume = vol; this->effects = effects;
    }

    Instruction::Instruction(uint_fast8_t instrument, float note, float octave, float vol, uint_fast32_t**effects) : key(note, octave) {
        this->instrument_index = instrument; this->volume = vol; this->effects = effects;
    }

    Instruction::Instruction() {this->volume = Notes::CONTINUE; this->instrument_index = Notes::CONTINUE; this->key = Key(); this->effects = nullptr;}

    Instruction::~Instruction() {delete[] this->effects;}

    Pattern::Pattern(uint_fast8_t rows) {
        this->instructions = new Instruction* [rows];
        for(uint_fast8_t i = 0; i < rows; ++i){
            this->instructions[i] = new Instruction();
        }
        this->rows = rows;
    }

    Pattern::~Pattern() {
        for(uint_fast8_t i = 0; i < this->rows; ++i){
            delete this->instructions[i];
        }
        delete[] this->instructions;
    }
}
