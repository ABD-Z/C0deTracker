//
// Created by Abdulmajid, Olivier NASSER on 11/11/2021.
//
#include "c0de_tracker.hpp"

namespace C0deTracker {
#define I(C, F) ((C) * this->frames + (F))

    Track_Data::Track_Data(const char *name, const float clk, const float basetime, const float speed,
                           const uint_fast8_t rows, const uint_fast8_t frames, const uint_fast8_t channels,
                           const uint_fast8_t *fx_per_chan) : name(name), clk(clk), basetime(basetime), speed(speed),
                                                              rows(rows), frames(frames), channels(channels), fx_per_chan(fx_per_chan){
        assert(clk > 0 && "Clock must be greater than zero.");
        assert(basetime > 0 && "Basetime must be greater than zero.");
        assert(speed > 0 && "Speed must be greater than zero.");

        this->step = this->basetime * this->speed / this->clk;
        this->duration = float(this->frames * this->rows) * this->step;
    }

    Track_Data::Track_Data(const char *name, const float clk, const float basetime, const float speed,
                           const uint_fast8_t rows, const uint_fast8_t frames, const uint_fast8_t channels,
                           const uint_fast8_t *fx_per_chan, const uint_fast8_t instruments)
                           : Track_Data(name, clk, basetime, speed, rows, frames, channels, fx_per_chan) {
        assert(instruments > 0 && "Instruments number must be greater than zero."
                                  "Remove instruments argument if you want to use a global instruments bank.");

        this->instruments = instruments;
    }

    Track_Data::~Track_Data() {
        this->free_data();
    }

    void Track_Data::setInstrumentData(uint_fast8_t instrument_index, uint_fast8_t wavetype, ADSR amp_envelope, float volume, float pitch, float duty_cycle, float phase) {
        assert(this->is_data_loaded() && "Data must be loaded first");
        assert(this->instruments > 0 && "Track must have instruments");
        assert(instrument_index < this->instruments && "Instrument index must be lesser than total available instruments");

        this->instruments_data_bank[instrument_index].setData(wavetype, amp_envelope, volume, pitch, duty_cycle, phase);
    }


    void Track_Data::setGlobalInstrumentsDataBank(const Instrument_Data* global_instruments_data_bank, uint_fast8_t n_instr) {
        this->instruments_data_bank = const_cast<Instrument_Data*>(global_instruments_data_bank);
        this->instruments = n_instr;
        this->use_global_inst = true;
    }

    const char *Track_Data::getName() {
        return this->name;
    }

    void Track_Data::free_data() {
        if(this->data_loaded){
            delete[] this->pattern_indices;
            for (uint_fast32_t i = 0; i < this->channels * this->frames; ++i) {delete this->patterns[i];}
            if(!this->use_global_inst) {delete[] this->instruments_data_bank;}
            delete[] this->patterns;
            this->data_loaded = false;
        }
    }

    void Track_Data::load_data() {
        assert(this->channels > 0 && "Number of channels must be greater than zero.");
        assert(this->frames > 0 && "Number of frames must be greater than zero.");

        this->loadEmptyPatterns();
        this->loadDefaultPatternsIndices();
        // if instruments = 0, no eror, using global instru bank
        if (this->instruments > 0) {
            this->loadEmptyInstrumentDataBank();
        }
        this->data_loaded = true;
    }

    bool Track_Data::is_data_loaded() const {
        return this->data_loaded;
    }

    void Track_Data::selectChannel(uint_fast8_t channel_index) {
        assert(channel_index < this->channels && "Selected channel must be lesser than available channels.");

        this->selected_channel = channel_index;
    }

    void Track_Data::selectPattern(uint_fast8_t pattern_index) {
        assert(pattern_index < this->frames && "Selected pattern must be lesser than available total frames.");

        this->selected_pattern = pattern_index;
    }

    void Track_Data::selectInstrument(uint_fast8_t instrument_index) {
        assert(instrument_index < this->instruments && "Selected instrument must be lesser than available instruments number.");

        this->selected_instrument = instrument_index;
    }

    void Track_Data::selectVolume(float volume) {
        assert(volume >= 0 && "Volume must be positive.");

        this->selected_volume = volume;
    }

    void Track_Data::enterInstruction(uint_fast8_t instruction_index, C0deTracker::Key key) {
        this->enterInstruction(instruction_index, this->selected_instrument, key, this->selected_volume);
    }

    void Track_Data::enterInstruction(uint_fast8_t instruction_index, uint_fast8_t instrument_index, C0deTracker::Key key) {
        this->enterInstruction(instruction_index, instrument_index, key, this->selected_volume);
    }

    void Track_Data::enterInstruction(uint_fast8_t instruction_index, C0deTracker::Key key, float volume) {
        this->enterInstruction(instruction_index, this->selected_instrument, key, volume);
    }

    void Track_Data::enterInstruction(uint_fast8_t instruction_index, uint_fast8_t instrument_index,
                                      C0deTracker::Key key, float volume) {
        assert(instruction_index < this->rows && "Instruction index must be lesser than total available rows in a pattern's frame.");
        assert(instrument_index < this->instruments && "Selected instrument must be lesser than available instruments number.");
        assert(volume >= 0 && "Volume must be positive.");

        this->patterns[I(this->selected_channel, this->selected_pattern)]->instructions[instruction_index].instrument_index = instrument_index;
        this->patterns[I(this->selected_channel, this->selected_pattern)]->instructions[instruction_index].volume = volume;
        this->patterns[I(this->selected_channel, this->selected_pattern)]->instructions[instruction_index].key = key;
    }

    void Track_Data::enterInstruction(uint_fast8_t instruction_index, C0deTracker::Key key, uint_fast32_t **effects) {
        this->enterInstruction(instruction_index, this->selected_instrument, key, this->selected_volume, effects);
    }

    void Track_Data::enterInstruction(uint_fast8_t instruction_index, C0deTracker::Key key,
                                      std::vector<uint_fast32_t> effects) {
        this->enterInstruction(instruction_index, this->selected_instrument, key, this->selected_volume, std::move(effects));
    }

    void Track_Data::enterInstruction(uint_fast8_t instruction_index, C0deTracker::Key key, uint_fast32_t effect) {
        this->enterInstruction(instruction_index, this->selected_instrument, key, this->selected_volume, effect);
    }

    void Track_Data::enterInstruction(uint_fast8_t instruction_index, uint_fast8_t instrument_index, C0deTracker::Key key,
                                 uint_fast32_t **effects) {
        this->enterInstruction(instruction_index, instrument_index, key, this->selected_volume, effects);
    }

    void Track_Data::enterInstruction(uint_fast8_t instruction_index, uint_fast8_t instrument_index, C0deTracker::Key key,
                                 std::vector<uint_fast32_t> effects) {
        this->enterInstruction(instruction_index, instrument_index, key, this->selected_volume, std::move(effects));
    }

    void Track_Data::enterInstruction(uint_fast8_t instruction_index, uint_fast8_t instrument_index, C0deTracker::Key key,
                                 uint_fast32_t effect) {
        this->enterInstruction(instruction_index, instrument_index, key, this->selected_volume, effect);
    }

    void Track_Data::enterInstruction(uint_fast8_t instruction_index, C0deTracker::Key key, float volume,
                                      uint_fast32_t **effects) {
        this->enterInstruction(instruction_index, this->selected_instrument, key, volume, effects);
    }

    void Track_Data::enterInstruction(uint_fast8_t instruction_index, C0deTracker::Key key, float volume,
                                      std::vector<uint_fast32_t> effects) {
        this->enterInstruction(instruction_index, this->selected_instrument, key, volume, std::move(effects));
    }

    void Track_Data::enterInstruction(uint_fast8_t instruction_index, C0deTracker::Key key, float volume,
                                      uint_fast32_t effect) {
        this->enterInstruction(instruction_index, this->selected_instrument, key, volume, effect);
    }

    void Track_Data::enterInstruction(uint_fast8_t instruction_index, uint_fast8_t instrument_index,
                                      C0deTracker::Key key, float volume, uint_fast32_t **effects) {
        this->enterInstruction(instruction_index, instrument_index, key, volume);
        this->patterns[I(this->selected_channel, this->selected_pattern)]->instructions[instruction_index].effects = effects;
    }

    void Track_Data::enterInstruction(uint_fast8_t instruction_index, uint_fast8_t instrument_index,
                                      C0deTracker::Key key, float volume, std::vector<uint_fast32_t> effects) {
        this->enterInstruction(instruction_index, instrument_index, key, volume);

        //fill fx
        uint_fast8_t size = this->patterns[I(this->selected_channel, this->selected_pattern)]->n_fx;
        this->patterns[I(this->selected_channel, this->selected_pattern)]->instructions[instruction_index].effects = new uint_fast32_t*[size]{};

        if(effects.size() < size){
            size =  effects.size();
        }

        for(int fi = 0; fi < size; ++fi){
            this->patterns[I(this->selected_channel, this->selected_pattern)]->instructions[instruction_index].effects[fi] = new uint_fast32_t(effects[fi]);
        }
    }

    void Track_Data::enterInstruction(uint_fast8_t instruction_index, uint_fast8_t instrument_index,
                                      C0deTracker::Key key, float volume, uint_fast32_t effect) {
        this->enterInstruction(instruction_index, instrument_index, key, volume);
        uint_fast8_t size = this->patterns[I(this->selected_channel, this->selected_pattern)]->n_fx;
        this->patterns[I(this->selected_channel, this->selected_pattern)]->instructions[instruction_index].effects =
                new uint_fast32_t*[size]{new uint_fast32_t(effect)};
    }

    void Track_Data::enterInstruction(uint_fast8_t instruction_index, float volume) {
        assert(instruction_index < this->rows && "Instruction index must be lesser than total available rows in a pattern's frame.");
        assert(volume >= 0 && "Volume must be positive.");

        this->patterns[I(this->selected_channel, this->selected_pattern)]->instructions[instruction_index].volume = volume;
    }

    void Track_Data::enterInstruction(uint_fast8_t instruction_index, uint_fast32_t **effects) {
        assert(instruction_index < this->rows && "Instruction index must be lesser than total available rows in a pattern's frame.");

        this->patterns[I(this->selected_channel, this->selected_pattern)]->instructions[instruction_index].effects = effects;
    }

    void Track_Data::enterInstruction(uint_fast8_t instruction_index, float volume, uint_fast32_t **effects) {
        this->enterInstruction(instruction_index, effects);
        this->enterInstruction(instruction_index, volume);
    }

    void Track_Data::enterInstruction(uint_fast8_t instruction_index, std::vector<uint_fast32_t> effects) {
        assert(instruction_index < this->rows && "Instruction index must be lesser than total available rows in a pattern's frame.");

        //fill fx
        uint_fast8_t size = this->patterns[I(this->selected_channel, this->selected_pattern)]->n_fx;
        this->patterns[I(this->selected_channel, this->selected_pattern)]->instructions[instruction_index].effects = new uint_fast32_t*[size]{};

        if(effects.size() < size){
            size =  effects.size();
        }

        for(int fi = 0; fi < size; ++fi) {
            this->patterns[I(this->selected_channel, this->selected_pattern)]->instructions[instruction_index].effects[fi] = new uint_fast32_t(effects[fi]);
        }
    }

    void Track_Data::enterInstruction(uint_fast8_t instruction_index, float volume, std::vector<uint_fast32_t> effects) {
        this->enterInstruction(instruction_index, effects);

        assert(volume >= 0 && "Volume must be positive.");

        this->patterns[I(this->selected_channel, this->selected_pattern)]->instructions[instruction_index].volume = volume;
    }

    void Track_Data::enterInstruction(uint_fast8_t instruction_index, uint_fast32_t effect) {
        assert(instruction_index < this->rows && "Instruction index must be lesser than total available rows in a pattern's frame.");

        uint_fast8_t size = this->patterns[I(this->selected_channel, this->selected_pattern)]->n_fx;
        this->patterns[I(this->selected_channel, this->selected_pattern)]->instructions[instruction_index].effects = new uint_fast32_t*[size]{new uint_fast32_t(effect)};

    }

    void Track_Data::enterInstruction(uint_fast8_t instruction_index, float volume, uint_fast32_t effect) {
        this->enterInstruction(instruction_index, effect);

        assert(volume >= 0 && "Volume must be positive.");

        this->patterns[I(this->selected_channel, this->selected_pattern)]->instructions[instruction_index].volume = volume;
    }

    void Track_Data::enterRelease(uint_fast8_t instruction_index) {
        assert(instruction_index < this->rows && "Instruction index must be lesser than total available rows in a pattern's frame.");

        this->patterns[I(this->selected_channel, this->selected_pattern)]->instructions[instruction_index].instrument_index = C0deTracker::Notes::RELEASE;
    }

    void Track_Data::enterRelease(uint_fast8_t instruction_index, float volume) {
        this->enterRelease(instruction_index);

        assert(volume >= 0 && "Volume must be positive.");

        this->patterns[I(this->selected_channel, this->selected_pattern)]->instructions[instruction_index].volume = volume;
    }

    void Track_Data::enterRelease(uint_fast8_t instruction_index, uint_fast32_t **effects) {
        this->enterRelease(instruction_index);
        this->patterns[I(this->selected_channel, this->selected_pattern)]->instructions[instruction_index].effects = effects;
    }

    void Track_Data::enterRelease(uint_fast8_t instruction_index, float volume, uint_fast32_t **effects) {
        this->enterRelease(instruction_index, volume);
        this->patterns[I(this->selected_channel, this->selected_pattern)]->instructions[instruction_index].effects = effects;
    }

    void Track_Data::enterRelease(uint_fast8_t instruction_index, std::vector<uint_fast32_t> effects) {

        this->enterRelease(instruction_index);

        // fill fx
        uint_fast8_t size = this->patterns[I(this->selected_channel, this->selected_pattern)]->n_fx;
        this->patterns[I(this->selected_channel, this->selected_pattern)]->instructions[instruction_index].effects = new uint_fast32_t*[size]{};
        if(effects.size() < size){
            size =  effects.size();
        }
        for(int fi = 0; fi < size; ++fi){
            this->patterns[I(this->selected_channel, this->selected_pattern)]->instructions[instruction_index].effects[fi] = new uint_fast32_t(effects[fi]);
        }
    }

    void Track_Data::enterRelease(uint_fast8_t instruction_index, float volume, std::vector<uint_fast32_t> effects) {
        this->enterRelease(instruction_index, std::move(effects));

        assert(volume >= 0 && "Volume must be positive.");

        this->patterns[I(this->selected_channel, this->selected_pattern)]->instructions[instruction_index].volume = volume;

    }

    void Track_Data::enterRelease(uint_fast8_t instruction_index, uint_fast32_t effect) {
        this->enterRelease(instruction_index);
        uint_fast8_t size = this->patterns[I(this->selected_channel, this->selected_pattern)]->n_fx;
        this->patterns[I(this->selected_channel, this->selected_pattern)]->instructions[instruction_index].effects = new uint_fast32_t*[size]{new uint_fast32_t(effect)};
    }

    void Track_Data::enterRelease(uint_fast8_t instruction_index, float volume, uint_fast32_t effect) {
        this->enterRelease(instruction_index, effect);

        assert(volume >= 0 && "Volume must be positive.");

        this->patterns[I(this->selected_channel, this->selected_pattern)]->instructions[instruction_index].volume = volume;
    }

    void Track_Data::enterPatternIndex(uint_fast8_t channel, uint_fast8_t frame, uint_fast8_t pattern_index) {
        assert(channel < this->channels && "Selected channel must be lesser than available channels.");
        assert(frame < this->frames && "Selected frame must be lesser than available total frames.");
        assert(pattern_index < this->frames && "Selected pattern index must be lesser than available total frames.");
        this->pattern_indices[I(channel, frame)] = pattern_index;
    }

    void Track_Data::loadEmptyPatterns() {
        this->patterns = new C0deTracker::Pattern*[this->channels * this->frames];
        for(uint_fast16_t i = 0; i < this->channels * this->frames; ++i){
            this->patterns[i] = new C0deTracker::Pattern(this->rows, this->fx_per_chan[i / this->frames]);
        }
    }

    void Track_Data::loadDefaultPatternsIndices() {
        this->pattern_indices = new uint8_t[this->channels * this->frames];
        for(uint_fast8_t i = 0; i < this->channels; ++i){
            for(uint_fast8_t j = 0; j < this->frames; ++j){
                this->pattern_indices[i * this->frames + j] = j;
            }
        }
    }

    void Track_Data::loadEmptyInstrumentDataBank() {
        this->instruments_data_bank = new C0deTracker::Instrument_Data[this->instruments];
    }
}

