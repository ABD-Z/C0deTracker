//
// Created by Abdulmajid, Olivier NASSER on 24/11/2020.
//
#include <iostream>
#include <utility>

#include "../include/c0de_tracker.hpp"

/**
 * @file editor.cpp
 * @brief Editor class code used to ease the coding of a song
 * @see code_tracker.hpp
 * @author Abdulmajid, Olivier NASSER
 * @version 0.1
 * @date 24/11/2020
 */

namespace C0deTracker {

    float Editor::volume = 0;
    uint_fast8_t Editor::chan_index = 0;
    uint_fast8_t Editor::pattern_index = 0;
    uint_fast8_t Editor::instrument_index = 0;
    uint_fast8_t Editor::frames = 0;
    Pattern **Editor::pattern = nullptr;
    uint_fast8_t  ** Editor::pattern_indices = nullptr;

    void Editor::prepare(C0deTracker::Pattern **p, uint_fast8_t frames, uint_fast8_t chanindx, uint_fast8_t patternindx,
                         uint_fast8_t instrumentnindx, float volume) {
        Editor::frames = frames;
        Editor::pattern = p;
        Editor::pattern_index = patternindx;
        Editor::instrument_index = instrumentnindx;
        Editor::volume = volume;
    }

    void Editor::prepare(uint_fast8_t chanindx, uint_fast8_t patternindx, float volume) {
        Editor::pattern_index = patternindx;
        Editor::volume = volume;

    }

    void Editor::prepare(uint_fast8_t chanindx, uint_fast8_t patternindx, uint_fast8_t instrumentnindx, float volume) {
        Editor::pattern_index = patternindx;
        Editor::instrument_index = instrumentnindx;
        Editor::volume = volume;
    }

    void Editor::storePattern(Pattern **p) {
        Editor::pattern = p;
    }

    void Editor::storePatternIndices(uint_fast8_t **pi) {
        Editor::pattern_indices = pi;
    }

    void Editor::storeChannelIndex(uint_fast8_t chanindx) {
        Editor::chan_index = chanindx;
    }

    void Editor::storePatternIndex(uint_fast8_t patternindx) {
        if(patternindx < Editor::frames)
            Editor::pattern_index = patternindx;
    }

    void Editor::storeInstrumentIndex(uint_fast8_t instrumentnindx) {
        Editor::instrument_index = instrumentnindx;
    }

    void Editor::storeVolume(float volume) {
        Editor::volume = volume;
    }

    void Editor::enterInstruction(uint_fast8_t instruction_index, C0deTracker::Key key) {
        Editor::enterInstruction(instruction_index, Editor::instrument_index, key, Editor::volume);
    }

    void Editor::enterInstruction(uint_fast8_t instruction_index, uint_fast8_t instrument_index, C0deTracker::Key key) {
        Editor::enterInstruction(instruction_index, instrument_index, key, Editor::volume);
    }

    void Editor::enterInstruction(uint_fast8_t instruction_index, C0deTracker::Key key, float volume) {
        Editor::enterInstruction(instruction_index, Editor::instrument_index, key, volume);
    }

    void Editor::enterInstruction(uint_fast8_t instruction_index, uint_fast8_t instrument_index,
                                  C0deTracker::Key key, float volume) {
        if(instruction_index < Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->rows){
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->instrument_index = instrument_index;
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->volume = volume;
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->key = key;
        }
    }


    void Editor::enterInstruction(uint_fast8_t instruction_index, C0deTracker::Key key, uint_fast32_t **effects) {
        Editor::enterInstruction(instruction_index, Editor::instrument_index, key, Editor::volume, effects);
    }

    void Editor::enterInstruction(uint_fast8_t instruction_index, C0deTracker::Key key, std::vector<uint_fast32_t> effects) {
        Editor::enterInstruction(instruction_index, Editor::instrument_index, key, Editor::volume, std::move(effects));
    }

    void Editor::enterInstruction(uint_fast8_t instruction_index, C0deTracker::Key key, uint_fast32_t effect) {
        Editor::enterInstruction(instruction_index, Editor::instrument_index, key, Editor::volume, effect);
    }

    void Editor::enterInstruction(uint_fast8_t instruction_index, uint_fast8_t instrument_index, C0deTracker::Key key,
                                  uint_fast32_t **effects) {
        Editor::enterInstruction(instruction_index, instrument_index, key, Editor::volume, effects);
    }

    void Editor::enterInstruction(uint_fast8_t instruction_index, uint_fast8_t instrument_index, C0deTracker::Key key,
                                  std::vector<uint_fast32_t> effects) {
        Editor::enterInstruction(instruction_index, instrument_index, key, Editor::volume, std::move(effects));
    }

    void Editor::enterInstruction(uint_fast8_t instruction_index, uint_fast8_t instrument_index, C0deTracker::Key key,
                                  uint_fast32_t effect) {
        Editor::enterInstruction(instruction_index, instrument_index, key, Editor::volume, effect);
    }

    void Editor::enterInstruction(uint_fast8_t instruction_index, C0deTracker::Key key, float volume,
                                  uint_fast32_t **effects) {
        Editor::enterInstruction(instruction_index, Editor::instrument_index, key, volume, effects);

    }

    void Editor::enterInstruction(uint_fast8_t instruction_index, C0deTracker::Key key, float volume,
                                  std::vector<uint_fast32_t> effects) {
        Editor::enterInstruction(instruction_index, Editor::instrument_index, key, volume, std::move(effects));

    }

    void Editor::enterInstruction(uint_fast8_t instruction_index, C0deTracker::Key key, float volume, uint_fast32_t effect) {
        Editor::enterInstruction(instruction_index, Editor::instrument_index, key, volume, effect);
    }

    void Editor::enterInstruction(uint_fast8_t instruction_index, uint_fast8_t instrument_index,
                                  C0deTracker::Key key, float volume, uint_fast32_t **effects) {
        if(instruction_index < Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->rows){
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->instrument_index = instrument_index;
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->volume = volume;
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->key = key;
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->effects = effects;
            for(int i = 0; i < Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->n_fx; ++i){
                printf("Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->n_fx %d\n", Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->n_fx);
                printf("i %d\n", i);
                if(Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->effects[i] ==
                   nullptr){break;}
                std::cout << std::hex <<  *Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->effects[i] << std::endl;
            }
        }
    }

    void Editor::enterInstruction(uint_fast8_t instruction_index, uint_fast8_t instrument_index, C0deTracker::Key key,
                                  float volume, std::vector<uint_fast32_t> effects) {
        if(instruction_index < Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->rows){
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->instrument_index = instrument_index;
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->volume = volume;
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->key = key;
            uint_fast8_t size = Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->n_fx;
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->effects =
                    new uint_fast32_t*[size];
            if(effects.size() < size){
                size =  effects.size();
            }
            for(int i = 0; i < size; ++i){
                Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->effects[i] = new uint_fast32_t(effects[i]);
            }

            for(int i = 0; i < Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->n_fx; ++i){
                printf("Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->n_fx %d\n", Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->n_fx);
                printf("i %d\n", i);
                if(Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->effects[i] ==
                   nullptr){break;}
                std::cout << std::hex <<  *Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->effects[i] << std::endl;
            }
        }
    }

    void Editor::enterInstruction(uint_fast8_t instruction_index, uint_fast8_t instrument_index, C0deTracker::Key key,
                                  float volume, uint_fast32_t effect) {
        if(instruction_index < Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->rows){
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->instrument_index = instrument_index;
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->volume = volume;
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->key = key;
            uint_fast8_t size = Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->n_fx;
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->effects =
                        new uint_fast32_t*[size]{new uint_fast32_t(effect)};


            for(int i = 0; i < Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->n_fx; ++i){
                printf("Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->n_fx %d\n", Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->n_fx);
                printf("i %d\n", i);
                if(Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->effects[i] ==
                        nullptr){break;}
                std::cout << std::hex <<  *Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->effects[i] << std::endl;
            }
        }
    }

    void Editor::enterInstruction(uint_fast8_t instruction_index, float volume) {
        if(instruction_index < Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->rows) {
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->volume = volume;
        }
    }

    void Editor::enterInstruction(uint_fast8_t instruction_index, uint_fast32_t **effects) {
        if(instruction_index < Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->rows){
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->effects = effects;
        }
    }

    void Editor::enterInstruction(uint_fast8_t instruction_index, float volume, uint_fast32_t **effects) {
        if(instruction_index < Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->rows){
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->volume = volume;
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->effects = effects;
        }
    }

    void Editor::enterInstruction(uint_fast8_t instruction_index, std::vector<uint_fast32_t> effects) {
        if(instruction_index < Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->rows){
            uint_fast8_t size = Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->n_fx;
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->effects =
                    new uint_fast32_t*[size];
            if(effects.size() < size){
                size =  effects.size();
            }
            for(int i = 0; i < size; ++i){
                Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->effects[i] = new uint_fast32_t(effects[i]);
            }
        }
    }

    void Editor::enterInstruction(uint_fast8_t instruction_index, float volume, std::vector<uint_fast32_t> effects) {
        if(instruction_index < Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->rows){
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->volume = volume;
            Editor::enterInstruction(instruction_index, std::move(effects));
        }
    }

    void Editor::enterInstruction(uint_fast8_t instruction_index, uint_fast32_t effect) {
        if(instruction_index < Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->rows){
            uint_fast8_t size = Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->n_fx;
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->effects =
                    new uint_fast32_t*[size]{new uint_fast32_t(effect)};
        }
    }

    void Editor::enterInstruction(uint_fast8_t instruction_index, float volume, uint_fast32_t effect) {
        if(instruction_index < Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->rows){
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->volume = volume;
            Editor::enterInstruction(instruction_index, effect);
        }
    }

    void Editor::release(uint_fast8_t instruction_index) {
        if(instruction_index < Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->rows){
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->instrument_index = C0deTracker::Notes::RELEASE;
        }
    }

    void Editor::release(uint_fast8_t instruction_index, float volume) {
        if(instruction_index < Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->rows){
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->instrument_index = C0deTracker::Notes::RELEASE;
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->volume = volume;
        }
    }

    void Editor::release(uint_fast8_t instruction_index, uint_fast32_t **effects) {
        if(instruction_index < Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->rows){
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->instrument_index = C0deTracker::Notes::RELEASE;
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->effects = effects;
        }
    }

    void Editor::release(uint_fast8_t instruction_index, float volume, uint_fast32_t **effects) {
        if(instruction_index < Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->rows){
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->instrument_index = C0deTracker::Notes::RELEASE;
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->effects = effects;
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->volume = volume;
        }
    }

    void Editor::release(uint_fast8_t instruction_index, std::vector<uint_fast32_t> effects) {
        if(instruction_index < Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->rows){
            uint_fast8_t size = Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->n_fx;
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->instrument_index = C0deTracker::Notes::RELEASE;
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->effects =
                    new uint_fast32_t*[size];
            if(effects.size() < size){
                size =  effects.size();
            }
            for(int i = 0; i < size; ++i){
                Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->effects[i] = new uint_fast32_t(effects[i]);
            }
        }
    }

    void Editor::release(uint_fast8_t instruction_index, float volume, std::vector<uint_fast32_t> effects) {
        if(instruction_index < Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->rows){
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->volume = volume;
            Editor::release(instruction_index, std::move(effects));
        }
    }

    void Editor::release(uint_fast8_t instruction_index, uint_fast32_t effect) {
        if(instruction_index < Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->rows){
            uint_fast8_t size = Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->n_fx;
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->instrument_index = C0deTracker::Notes::RELEASE;
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->effects =
                        new uint_fast32_t*[size]{new uint_fast32_t(effect)};
        }
    }

    void Editor::release(uint_fast8_t instruction_index, float volume, uint_fast32_t effect) {
        if(instruction_index < Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->rows) {
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->volume = volume;
            Editor::release(instruction_index, effect);
        }
    }

    void Editor::enterPatternIndice(uint_fast8_t channel, uint_fast8_t frame, uint_fast8_t pattern_indice) {
        *Editor::pattern_indices[channel * Editor::frames + frame] = pattern_indice;
    }

}