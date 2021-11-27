//
// Created by Abdulmajid, Olivier NASSER on 11/11/2021.
//
#include "c0de_tracker.hpp"

namespace C0deTracker {
    Track_Data::~Track_Data() {
        this->free_data();
    }

    void Track_Data::setName(const char *name) { this->name = const_cast<char *>(name); }

    void Track_Data::setSizeDimensions(const uint_fast8_t rows, const uint_fast8_t frames, const uint_fast8_t channels, const uint_fast8_t *fx_per_chan) {
        this->rows = rows; this->frames = frames; this->channels = channels; this->fx_per_chan = fx_per_chan;
    }

    void Track_Data::setTimeDimensions(const float clk, const float basetime, const float speed){
        this->clk = clk; this->basetime = basetime; this->speed = speed;
        this->step = this->basetime * this->speed / this->clk;
        this->duration = float(this->frames * this->rows) * this->step;
    }

    void Track_Data::setInstrumentsDataBank(const Instrument_Data* instruments_data_bank, uint_fast8_t n_instr){
        this->instruments_data_bank = const_cast<Instrument_Data*>(instruments_data_bank);
        this->instruments = n_instr;
    }

    void Track_Data::setPatterns(const Pattern* const* patterns){this->track_patterns = const_cast<Pattern **>(patterns);}

    void Track_Data::setPatternsIndices(const uint_fast8_t* patterns_indices){this->pattern_indices = const_cast<uint_fast8_t *>(patterns_indices);}

    void Track_Data::useGlobalInstruments(){this->use_global_inst = true;}

    void Track_Data::setGlobalInstrumentsDataBank(const Instrument_Data* global_instruments_data_bank, uint_fast8_t n_instr) {
        this->instruments_data_bank = const_cast<Instrument_Data*>(global_instruments_data_bank);
        this->instruments = n_instr;
        this->useGlobalInstruments();
    }

    const char *Track_Data::getName() {
        return this->name;
    }

    void Track_Data::free_data() {
        if(this->data_loaded){
            delete[] this->pattern_indices;
            for (uint_fast32_t i = 0; i < this->channels * this->frames; ++i) {delete this->track_patterns[i];}
            if(!this->use_global_inst){delete this->instruments_data_bank;}
            delete[] this->track_patterns;
            this->data_loaded = false;
        }
    }

    void Track_Data::load_data() {
        this->data_loaded = true;
    }

    bool Track_Data::is_data_loaded() {
        return this->data_loaded;
    }

}

