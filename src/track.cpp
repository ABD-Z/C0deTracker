//
// Created by Abdulmajid, Olivier NASSER on 21/10/2020.
//

#include "../include/c0de_tracker.hpp"

/**
 * @file track.cpp
 * @brief Track class code
 * @see code_tracker.hpp
 * @author Abdulmajid, Olivier NASSER
 * @version 0.1
 * @date 21/10/2020
 */

namespace C0deTracker {
    Track::Track(float clk, float basetime, float speed, uint_fast8_t rows, uint_fast8_t frames, uint_fast8_t channels,
                 Instrument **instruments_bank, uint_fast8_t numb_of_instruments, Pattern **track_patterns,
                 uint_fast8_t *pattern_indices,
                 const uint_fast8_t *effects_per_chan) {
        this->clk = clk;
        this->basetime = basetime;
        this->speed = speed;
        this->rows = rows;
        this->frames = frames;
        this->channels = channels;
        this->instruments_bank = instruments_bank;
        this->instruments = numb_of_instruments;
        this->track_patterns = track_patterns;
        this->pattern_indices = pattern_indices;
        this->step = this->basetime * this->speed / this->clk;
        this->duration = float(this->frames * this->rows) * this->step;
        this->fx_per_chan = effects_per_chan;
    }

    Track::~Track() {
        //for (uint8_t i = 0; i < this->channels * this->frames; ++i) { delete this->pattern_indices[i]; }
        delete[] this->pattern_indices;
        for (uint8_t i = 0; i < this->channels * this->frames; ++i) {delete this->track_patterns[i];}
        delete[] this->track_patterns;
        for (uint8_t i = 0; i < this->instruments; ++i) { delete this->instruments_bank[i]; }
        delete[] this->instruments_bank;
        delete[] this->chans;
        //delete this->name;
    }


    uint_fast8_t Track::getNumberofChannels() const {
        return this->channels;
    }

    float Track::getDuration() const {
        return this->duration;
    }

    void Track::update_fx(double t) {
        if(this->volume_slide_down != 0){
            this->volume -= (this->volume_slide_down / this->speed) * (t - this->volume_slide_time);
            if (this->volume <= 0) {
                this->volume = 0.f;
                this->volume_slide_down = 0.f;
            }
        }
        if(this->volume_slide_up != 0){
            this->volume += (this->volume_slide_up / this->speed) * (t - this->volume_slide_time);
            if (this->volume >= MASTER_VOLUME) {
                this->volume = MASTER_VOLUME;
                this->volume_slide_up = 0.f;
            }
        }
        if(this->pitch_slide_down != 0)
            this->pitch -= (this->pitch_slide_down / this->speed) * (t - this->pitch_slide_time);

        if(this->pitch_slide_up != 0)
            this->pitch += (this->pitch_slide_up / this->speed) * (t - this->pitch_slide_time);

        if(this->panning_slide_right != 0){
            this->panning += (this->panning_slide_right / this->speed) * (t - this->panning_slide_time);
            if (this->panning >= MASTER_VOLUME) {
                this->panning = MASTER_VOLUME;
                this->panning_slide_right = 0.f;
            }
        }
        if(this->panning_slide_left != 0){
            this->panning -= (this->panning_slide_left / this->speed) * (t - this->panning_slide_time);
            if (this->panning <= 0) {
                this->panning = 0;
                this->panning_slide_left = 0.f;
            }
        }
        if (this->tremolo_speed == 0.f || this->tremolo_depth == 0.f) {
            this->tremolo_val = 1.0f;
        } else {
            this->tremolo_val = 0.5f * this->tremolo_depth * sin(TWOPI * this->tremolo_speed * (t - this->tremolo_time))
                    + (1 - 0.5f * this->tremolo_depth);
        }
        if (this->vibrato_speed == 0.f || this->vibrato_depth == 0.f) {
            this->vibrato_val = 0.0f;
        } else {
            this->vibrato_val = this->vibrato_depth * sin(TWOPI * this->vibrato_speed * (t - this->vibrato_time));
        }
    }

    bool Track::decode_fx(uint_fast32_t fx, double t) {
        uint_fast8_t fx_code = fx >> 4 * 6;
        uint_fast32_t fx_val = fx & 0x00FFFFFF;
        switch (fx_code) {
            case 0x00://pitch slide up
                this->pitch_slide_up = float(fx_val) / float(0x00FFFFFF);
                this->pitch_slide_down = 0.f;
                this->pitch_slide_time = t;

                return true;
            case 0x01://pitch slide down
                this->pitch_slide_down = float(fx_val) / float(0x00FFFFFF);
                this->pitch_slide_up = 0.f;
                this->pitch_slide_time = t;
                return true;
            case 0x02://vibrato
                this->vibrato_speed = float((fx_val >> 4 * 3)) / float(0x100);
                this->vibrato_depth = float(fx_val & 0xFFF) / float(0x800);
                this->vibrato_time = t;
                return true;
            case 0x03://set pitch
                this->pitch = (float(fx_val) - float(0x800000)) / float(0x800000);
                return true;
            case 0x04://set volume
                this->volume = float(fx_val) / float(0x00FFFFFF);
                return true;
            case 0x05://volume slide up
                this->volume_slide_up = float(fx_val) / float(0x00FFFFFF);
                this->volume_slide_down = 0.f;
                this->volume_slide_time = t;
                return true;
            case 0x06://volume slide down
                this->volume_slide_down = float(fx_val) / float(0x00FFFFFF);
                this->volume_slide_up = 0.f;
                this->volume_slide_time = t;
                return true;
            case 0x07://tremolo
                this->tremolo_speed = float(fx_val >> 4 * 3) / float(0x100);
                this->tremolo_depth = float(fx_val & 0xFFF) / float(0xFFF);
                this->tremolo_time = t;
                return true;
            case 0x08://set global track panning
                this->panning = float(fx_val) / float(0xFFFFFF);
                return true;
            case 0x09://change speed of the track
                this->speed = float(fx_val >> 4 * 3) + float(fx_val & 0xFFF) / float(0xFFF);;
                this->step = this->basetime * this->speed / this->clk;
                this->duration = float(this->frames * this->rows) * this->step;
                return true;
            case 0x0A:// jumpt to frame row
                this->branch = true;
                this->frametojump = fx_val >> 4 * 3;
                this->rowtojump = fx_val & 0xFFF;
                if ((this->frametojump == this->frame_counter && this->rowtojump == this->row_counter) ||
                    (this->frametojump >= this->frames) || (this->rowtojump >= this->rows)) {
                    this->branch = false;
                }
                return true;
            case 0x0B://stop song
                this->stop = true;
                return true;
            case 0x0D://slide right panning
                this->panning_slide_right = float(fx_val) / float(0xFFFFFF);
                this->panning_slide_left = 0.0f;
                this->panning_slide_time = t;
                return true;
            case 0x0E://slide left panning
                this->panning_slide_left = float(fx_val) / float(0xFFFFFF);
                this->panning_slide_right = 0.0f;
                this->panning_slide_time = t;
                return true;
            default:
                return false;
        }
    }

    float *Track::play(double t) {
        static float res[2];

        res[0] = 0.f; res[1] = 0.f;
        this->update_fx(t);

        if (t - this->time_advance >= this->step) {
            if (this->stop) {
                res[0] = 0;
                res[1] = 0;
                return res;
            }
            this->time_advance += this->step;
            ++this->row_counter;
            this->readFx = true;
            if (this->branch) {
                this->row_counter = this->rowtojump;
                this->frame_counter = this->frametojump;
                this->branch = false;
            }
        }

        if (this->row_counter >= this->rows) {
            this->row_counter = 0;
            ++this->frame_counter;
        }
        if (this->frame_counter >= this->frames) {
            this->frame_counter = 0;
        }

        float s = 0.f;//generated signal
        float a = 0.f;//amplitude
        float p = 0.f;//pitch

        for (int_fast8_t i = this->channels - 1; i >= 0; --i) {
            if (this->chans[i].isEnable()) {
                if(this->chans[i].getTrack() != nullptr){
                    this->chans[i].update_fx(t);
                }
                uint_fast8_t chan_number = i;
                uint_fast8_t pattern_index = this->pattern_indices[chan_number * this->frames + this->frame_counter];
                Pattern *pat = this->track_patterns[chan_number * (this->frames) + pattern_index];
                Instruction *current_instruction = &pat->instructions[this->row_counter];

                if (current_instruction->instrument_index < this->instruments) {
                    if (this->readFx) {
                        this->chans[i].setLastInstructionAddress(current_instruction);
                        this->chans[i].setRelease(false);
                        this->chans[i].setTime(t);
                        this->chans[i].setTrack(this);
                        if(this->chans[i].getInstructionState()->key.note == Notes::CONTINUE || this->chans[i].getInstructionState()->key.octave == Notes::CONTINUE){
                            if(this->chans[i].getInstructionState()->instrument_index != current_instruction->instrument_index){
                                //delete chan[i].instrument;
                                //chan[i].instrument = this->instruments_bank[current_instruction->instrument_index]->clone();
                                this->chans[i].oscillator.setOscillatorParams(&this->instruments_data_bank[current_instruction->instrument_index]);
                            }
                            this->chans[i].setInstructionState(current_instruction);
                        }else{
                            if(!this->chans[i].portamento){
                                if(this->chans[i].getInstructionState()->instrument_index != current_instruction->instrument_index){
                                    //delete chan[i].instrument;
                                    //chan[i].instrument = this->instruments_bank[current_instruction->instrument_index]->clone();
                                    this->chans[i].oscillator.setOscillatorParams(&this->instruments_data_bank[current_instruction->instrument_index]);
                                }
                                this->chans[i].setInstructionState(current_instruction);
                            }else{
                                this->chans[i].portamento_time_step = t;
                                if(this->chans[i].instruct_state.key.octave == Notes::CONTINUE){
                                    this->chans[i].porta_pitch_dif = 0;
                                }else{
                                    this->chans[i].porta_pitch_dif += Notes::key2pitch(current_instruction->key) - (Notes::key2pitch(this->chans[i].instruct_state.key) /*- chan[i].porta_pitch_dif*/);
                                }

                                if(this->chans[i].getInstructionState()->instrument_index != current_instruction->instrument_index){
                                    //delete chan[i].instrument;
                                    //chan[i].instrument = this->instruments_bank[current_instruction->instrument_index]->clone();
                                    this->chans[i].oscillator.setOscillatorParams(&this->instruments_data_bank[current_instruction->instrument_index]);
                                }
                                this->chans[i].setInstructionState(current_instruction);
                            }
                        }
                        //chan[i].instrument->get_oscillator()->setRelease(false);
                        this->chans[i].oscillator.setRelease(false);
                        this->chans[i].pitch_slide_val = 0;
                        this->chans[i].pitch_slide_time = t;
                        this->chans[i].transpose_time_step = t;
                        this->chans[i].transpose_semitone_counter = 0;
                        this->chans[i].retrieg_time_step = t;
                        this->chans[i].retrieg_counter = 0;
                        this->chans[i].delrel_time_step = t;
                        this->chans[i].release_counter = 0;
                        this->chans[i].delay_counter = 0;
                        if(this->chans[i].n_time_to_transpose > 0){
                            --this->chans[i].n_time_to_transpose;
                        }
                        if(this->chans[i].n_time_to_retrieg > 0){
                            --this->chans[i].n_time_to_retrieg;
                        }
                        if(this->chans[i].n_time_to_delrel){
                            --this->chans[i].n_time_to_delrel;
                        }
                    }
                } else {
                    if (this->chans[i].getLastInstructionAddress() != nullptr) {
                        if (current_instruction->instrument_index == Notes::RELEASE &&
                                this->chans[i].getInstructionState()->instrument_index < this->instruments) {
                            if (!this->chans[i].isReleased()) {
                                this->chans[i].setRelease(true);
                                this->chans[i].setTimeRelease(t);
                                this->chans[i].setTrack(this);
                                //chan[i].instrument->get_oscillator()->setRelease(true);
                                this->chans[i].oscillator.setRelease(true);
                            }
                            if (current_instruction->volume != Notes::CONTINUE &&
                                ((0.f <= current_instruction->volume) &&
                                 (current_instruction->volume <= MASTER_VOLUME))) {
                                this->chans[i].setVolumeInstructionState(current_instruction->volume);
                            }
                        }
                        if (current_instruction->instrument_index == Notes::CONTINUE &&
                                this->chans[i].getInstructionState()->instrument_index < this->instruments) {
                            if (current_instruction->volume != Notes::CONTINUE &&
                                ((0.f <= current_instruction->volume) &&
                                 (current_instruction->volume <= MASTER_VOLUME))) {
                                this->chans[i].setVolumeInstructionState(current_instruction->volume);
                            }
                        }
                    }
                }

                if (current_instruction->effects != nullptr && this->readFx) {
                    for (int_fast8_t fx_indx = this->fx_per_chan[chan_number] - 1; fx_indx >= 0; --fx_indx) {
                        if (current_instruction->effects[fx_indx] != nullptr) {
                            if (!this->decode_fx(*current_instruction->effects[fx_indx], t)) {
                                this->chans[i].decode_fx(*current_instruction->effects[fx_indx], t);
                            }
                        }
                    }
                }
                //check if channel is released because of release effect
                if(this->chans[i].isReleased()){
                    //chan[i].instrument->get_oscillator()->setRelease(true);
                    this->chans[i].oscillator.setRelease(true);
                }

                uint_fast8_t arpeggio = 0;
                if(this->chans[i].arpeggio){
                    arpeggio = this->chans[i].arpeggio_val[this->chans[i].arpeggio_index];
                }

                a =  this->chans[i].getVolume() * this->chans[i].tremolo_val * this->chans[i].getInstructionState()->volume;
                p = Notes::key2pitch(this->chans[i].getInstructionState()->key) + this->pitch + this->vibrato_val + this->chans[i].pitch
                        + this->chans[i].pitch_slide_val + this->chans[i].vibrato_val + arpeggio - this->chans[i].porta_pitch_dif
                        + this->chans[i].oscillator.getPitch();

                if (this->chans[i].getLastInstructionAddress() != nullptr && this->chans[i].getTrack() != nullptr) {
                    if (!this->chans[i].isReleased()) {
                        //s = chan[i].instrument->play_pitch(a, p, t - chan[i].getTime());
                        s = this->chans[i].play_pitch(a, p, t - this->chans[i].getTime());//new
                    } else {
                        //s = chan[i].instrument->play_pitch(a, p, t - chan[i].getTime(), t - chan[i].getTimeRelease());
                        s = this->chans[i].play_pitch(a, p, t - this->chans[i].getTime(), t - this->chans[i].getTimeRelease());//new
                    }
                    res[0] += s * (1 - this->chans[i].panning);
                    res[1] += s * this->chans[i].panning;
                }
            }
        }


        res[0] *= this->volume * this->tremolo_val;
        res[1] *=  this->volume * this->tremolo_val;

        res[0] *= 4*(1 - this->panning);//left
        res[1] *= 4*this->panning;//right

        this->readFx = false;
        return res;
    }

    float Track::getPanning() const {
        return this->panning;
    }

    float Track::getClock() const {
        return this->clk;
    }

    float Track::getSpeed() const {
        return this->speed;
    }

    void Track::setSizeDimensions(const uint_fast8_t rows, const uint_fast8_t frames, const uint_fast8_t channels, const uint_fast8_t *fx_per_chan) {
        this->rows = rows; this->frames = frames; this->channels = channels; this->fx_per_chan = fx_per_chan;
        this->chans = new C0deTracker::Channel[this->channels];
    }

    uint_fast8_t Track::getNumberofRows() const {
        return this->rows;
    }

    uint_fast8_t Track::getNumberofFrames() const {
        return this->frames;
    }

    const uint_fast8_t *Track::getNumberofFXperChannel() {
        return this->fx_per_chan;
    }

    void Track::setTimeDimensions(const float clk, const float basetime, const float speed) {
        this->clk = clk; this->basetime = basetime; this->speed = speed;
        this->step = this->basetime * this->speed / this->clk;
        this->duration = float(this->frames * this->rows) * this->step;
    }

    float Track::getBasetime() const {
        return this->basetime;
    }

    void Track::setInstrumentsBank(const Instrument*const*instruments_bank, uint_fast8_t n_instr) {
        this->instruments_bank = const_cast<Instrument **>(instruments_bank); this->instruments = n_instr;
    }

    void Track::setPatterns(const Pattern *const *patterns) {
        this->track_patterns = const_cast<Pattern **>(patterns);
    }

    void Track::setPatternsIndices(const uint_fast8_t *patterns_indices) {
        this->pattern_indices = const_cast<uint_fast8_t *>(patterns_indices);
    }

    void Track::init() {}

    void Track::setInstrumentsDataBank(const Instrument_Data* instruments_data_bank, uint_fast8_t n_instr) {
        this->instruments_data_bank = const_cast<Instrument_Data*>(instruments_data_bank);
        this->instruments = n_instr;
    }

    void Track::setName(const char *name) {
        //delete[] this->name;
        this->name = const_cast<char *>(name);
    }

    char* Track::getName() const {
        return this->name;
    }

    void Track::resetState() {
        volume = 1.0f; pitch = 0.0f;
         row_counter = 0; frame_counter = 0;
         time_advance = 0.0;

        readFx = true;
         volume_slide_up = 0.f;
         volume_slide_down = 0.f;
         volume_slide_time = 0.0;

         pitch_slide_up = 0.f;
         pitch_slide_down = 0.f;
         pitch_slide_time = 0.0;

         tremolo_speed = 0.0f;
         tremolo_depth = 0.0f;
         tremolo_val = 1.0f;
         tremolo_time = 0.0;

         vibrato_speed = 0.0f;
         vibrato_depth = 0.0f;
         vibrato_val = 0.0f;
         vibrato_time = 0.0;
         panning = 0.5f;
         branch = false;
         frametojump = 0;
         rowtojump = 0;

         stop = false;

         panning_slide_right = 0.f;
         panning_slide_left = 0.f;
         panning_slide_time = 0.0;

         for(int16_t i = this->channels-1; i >= 0 ; --i){
             this->chans[i].resetState();
         }
    }

}