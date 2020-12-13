//
// Created by Abdulmajid, Olivier NASSER on 24/11/2020.
//
#include "code_tracker.hpp"

namespace CodeTracker {

    float Editor::volume = 0;
    uint_fast8_t Editor::chan_index = 0;
    uint_fast8_t Editor::pattern_index = 0;
    uint_fast8_t Editor::instrument_index = 0;
    uint_fast8_t Editor::frames = 0;
    Pattern **Editor::pattern = nullptr;

    void Editor::prepare(CodeTracker::Pattern **p, uint_fast8_t frames, uint_fast8_t chanindx, uint_fast8_t patternindx,
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

    void Editor::enterInstruction(uint_fast8_t instruction_index, CodeTracker::Key key) {
        Editor::enterInstruction(instruction_index, Editor::instrument_index, key, Editor::volume);
    }

    void Editor::enterInstruction(uint_fast8_t instruction_index, uint_fast8_t instrument_index, CodeTracker::Key key) {
        Editor::enterInstruction(instruction_index, instrument_index, key, Editor::volume);
    }

    void Editor::enterInstruction(uint_fast8_t instruction_index, CodeTracker::Key key, float volume) {
        Editor::enterInstruction(instruction_index, Editor::instrument_index, key, volume);
    }

    void Editor::enterInstruction(uint_fast8_t instruction_index, uint_fast8_t instrument_index,
                                  CodeTracker::Key key, float volume) {
        if(instruction_index < Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->rows){
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->instrument_index = instrument_index;
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->volume = volume;
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->key = key;
        }
    }


    void Editor::enterInstruction(uint_fast8_t instruction_index, CodeTracker::Key key, uint_fast32_t **effects) {
        Editor::enterInstruction(instruction_index, Editor::instrument_index, key, Editor::volume, effects);
    }

    void Editor::enterInstruction(uint_fast8_t instruction_index, uint_fast8_t instrument_index, CodeTracker::Key key,
                                  uint_fast32_t **effects) {
        Editor::enterInstruction(instruction_index, instrument_index, key, Editor::volume, effects);
    }

    void Editor::enterInstruction(uint_fast8_t instruction_index, CodeTracker::Key key, float volume,
                                  uint_fast32_t **effects) {
        Editor::enterInstruction(instruction_index, Editor::instrument_index, key, volume, effects);

    }

    void Editor::enterInstruction(uint_fast8_t instruction_index, uint_fast8_t instrument_index,
                                  CodeTracker::Key key, float volume, uint_fast32_t **effects) {
        if(instruction_index < Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->rows){
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->instrument_index = instrument_index;
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->volume = volume;
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->key = key;
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->effects = effects;
        }
    }

    void Editor::release(uint_fast8_t instruction_index) {
        if(instruction_index < Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->rows){
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->instrument_index = CodeTracker::Notes::RELEASE;
        }
    }

    void Editor::release(uint_fast8_t instruction_index, uint_fast32_t **effects) {
        if(instruction_index < Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->rows){
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->instrument_index = CodeTracker::Notes::RELEASE;
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->effects = effects;

        }

    }

    void Editor::enterInstruction(uint_fast8_t instruction_index, uint_fast32_t **effects) {
        if(instruction_index < Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->rows){
            Editor::pattern[Editor::chan_index * Editor::frames + Editor::pattern_index]->instructions[instruction_index]->effects = effects;
        }
    }


}