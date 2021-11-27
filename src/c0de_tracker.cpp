//
// Created by Abdulmajid, Olivier NASSER on 24/08/2020.
//
#include "../include/c0de_tracker.hpp"

/**
 * @file code_tracker.cpp
 * @brief This file contains basic stuff for C0deTracker
 * @see Key , ADSR , Notes , Instruction , Pattern
 * @author Abdulmajid, Olivier NASSER
 * @version 0.1
 * @date 24/08/2020
 */

namespace  C0deTracker{

    Key::Key(float n, float o) { this->note = n; this->octave = o;}

    Key::Key(){this->note = Notes::CONTINUE; this->octave = Notes::CONTINUE;}

    ADSR::ADSR(float A, float D, float S, float R) { this->attack = A; this->decay = D; this->sustain = S; this->release = R;}


    namespace Notes {
        float pitch2freq(float p){return pow(1.059460646483f, p) * 440.0f;}

        float key2pitch(Key k){
            return key2pitch(k.note, k.octave);
        }
        float key2pitch(float note, float octave){
            return float(PITCHES_PER_OCTAVE
                         * (octave - OCTAVE_PITCH_OFFSET)
                         + (note - NOTE_PITCH_OFFSET));
        }

        float key2freq(float note , float octave){
            //A4 == 440 HZ = pitch2freq 0
            //-12 pitch2freq == 3A == 220 HZ
            //+12
            return pitch2freq(key2pitch(note, octave));
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


    Pattern::Pattern(uint_fast8_t rows, uint_fast8_t number_of_fx) {
        this->instructions = new Instruction[rows];
        /*for(uint_fast8_t i = 0; i < rows; ++i){
            this->instructions[i] = Instruction();
        }*/
        this->rows = rows;
        this->n_fx = number_of_fx;
    }

    Pattern::~Pattern() {
        for(uint_fast8_t i = 0; i < this->rows; ++i){
            if(this->instructions[i].effects != nullptr){
                for(uint_fast8_t j = 0; j < this->n_fx; ++j){
                    if(this->instructions[i].effects[j] == nullptr){
                        break;
                    }else{
                        delete this->instructions[i].effects[j];
                    }
                }
                delete[] this->instructions[i].effects;
            }
            //delete this->instructions[i];
        }
        delete[] this->instructions;
    }
}
