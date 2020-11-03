//
// Created by Abdulmajid, Olivier NASSER on 21/10/2020.
//

#include "code_tracker.hpp"

namespace CodeTracker {
    Track::Track(float clk, float basetime, float speed, uint_fast8_t rows, uint_fast8_t frames, uint_fast8_t channels,
                 Instrument **instruments_bank, uint_fast8_t numb_of_instruments, Pattern **track_patterns,
                 uint_fast8_t **pattern_indices,
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
        printf("STEP : %f\n", this->step);
        printf("DURATION : %f\n", this->duration);
    }

    Track::~Track() {
        for (uint8_t i = 0; i < this->channels * this->frames; ++i) { delete this->pattern_indices[i]; }
        delete[] this->pattern_indices;
        for (uint8_t i = 0; i < this->channels * this->frames; ++i) { delete this->track_patterns[i]; }
        delete[] this->track_patterns;
        for (uint8_t i = 0; i < this->instruments; ++i) { delete this->instruments_bank[i]; }
        delete[] this->instruments_bank;
    }


    uint_fast8_t Track::getNumberofChannels() {
        return this->channels;
    }

    float Track::getDuration() {
        return this->duration;
    }

    float Track::play_single_channel(double t, Channel *chan) {
        if (chan->getNumber() > this->channels) { return 0.0f; }
        if (chan->isEnable()) {
            double time_in_track = fmod(t, double(this->duration));
            uint_fast8_t row_index = floor(time_in_track / this->step);
            uint_fast8_t pattern_index = floor(row_index / this->rows);
            row_index = row_index % this->rows;
            uint_fast8_t chan_number = chan->getNumber();
            pattern_index = *this->pattern_indices[chan_number * this->frames + pattern_index];
            Pattern *pat = this->track_patterns[chan_number * (this->frames) + pattern_index];
            Instruction *current_instruction = pat->instructions[row_index];
            if (current_instruction->instrument_index < this->instruments) {
                if (current_instruction != chan->getLastInstructionAddress()) {
                    chan->setLastInstructionAddress(current_instruction);
                    this->instruments_bank[current_instruction->instrument_index]->get_oscillator()->setRelease(false);
                    chan->setRelease(false);
                    chan->setTime(t);
                    chan->setTrack(this);
                }
            } else {
                if (current_instruction->instrument_index == Notes::RELEASE &&
                    chan->getLastInstructionAddress()->instrument_index < this->instruments) {
                    if (!chan->isReleased()) {
                        chan->setRelease(true);
                        chan->setTimeRelease(t);
                        chan->setTrack(this);
                        this->instruments_bank[chan->getLastInstructionAddress()->instrument_index]->get_oscillator()->setRelease(
                                true);
                    }
                    if (current_instruction->volume != Notes::CONTINUE &&
                        ((0.f <= current_instruction->volume) || (current_instruction->volume <= MASTER_VOLUME))) {
                        chan->setVolumeInstructionState(current_instruction->volume);
                    }
                }
                if (current_instruction->instrument_index == Notes::CONTINUE &&
                    chan->getLastInstructionAddress()->instrument_index < this->instruments) {
                    if (current_instruction->volume != Notes::CONTINUE &&
                        ((0.f <= current_instruction->volume) || (current_instruction->volume <= MASTER_VOLUME))) {
                        chan->setVolumeInstructionState(current_instruction->volume);
                    }
                }
            }
            if (chan->getLastInstructionAddress() != nullptr && chan->getTrack() != nullptr) {
                if (!chan->isReleased()) {
                    return this->volume * chan->getVolume()
                           * this->instruments_bank[chan->getLastInstructionAddress()->instrument_index]->play(
                            chan->getLastInstructionAddress()->volume, chan->getLastInstructionAddress()->key,
                            t - chan->getTime());
                } else {
                    return this->volume * chan->getVolume()
                           * this->instruments_bank[chan->getLastInstructionAddress()->instrument_index]->play(
                            chan->getLastInstructionAddress()->volume, chan->getLastInstructionAddress()->key,
                            t - chan->getTime(), t - chan->getTimeRelease());
                }
            }

        }
        return 0.0f;
    }


    void Track::update_fx(double t) {
        this->volume -= (this->volume_slide_down / this->speed) * (t - this->volume_slide_time);
        if (this->volume <= 0) {
            this->volume = 0.f;
            this->volume_slide_down = 0.f;
        }
        this->volume += (this->volume_slide_up / this->speed) * (t - this->volume_slide_time);
        if (this->volume >= MASTER_VOLUME) {
            this->volume = MASTER_VOLUME;
            this->volume_slide_up = 0.f;
        }

        this->pitch -= (this->pitch_slide_down / this->speed) * (t - this->pitch_slide_time);

        this->pitch += (this->pitch_slide_up / this->speed) * (t - this->pitch_slide_time);

        this->panning += (this->panning_slide_right / this->speed) * (t - this->panning_slide_time);
        if (this->panning >= MASTER_VOLUME) {
            this->panning = MASTER_VOLUME;
            this->panning_slide_right = 0.f;
        }
        this->panning -= (this->panning_slide_left / this->speed) * (t - this->panning_slide_time);
        if (this->panning <= 0) {
            this->panning = 0;
            this->panning_slide_left = 0.f;
        }

        if (this->tremolo_speed == 0.f || this->tremolo_depth == 0.f) {
            this->tremolo_val = 1.0f;
        } else {
            this->tremolo_val =
                    0.5f * this->tremolo_depth * sin(TWOPI * this->tremolo_speed * (t - this->tremolo_time)) +
                    (1 - 0.5f * this->tremolo_depth);
        }
        if (this->vibrato_speed == 0.f || this->vibrato_depth == 0.f) {
            this->vibrato_val = 0.0f;
        } else {
            this->vibrato_val = this->vibrato_depth * sin(TWOPI * this->vibrato_speed * (t - this->vibrato_time));
        }
        //printf("volume %f", this->volume);
    }

    bool Track::decode_fx(uint_fast32_t fx, double t) {
        uint_fast8_t fx_code = fx >> 4 * 6;
        uint_fast32_t fx_val = fx & 0x00FFFFFF;
        printf("pitch %f\n", this->pitch);
        printf("%.3f FX CODE : %x ; FX VAL : %x\n", t, fx_code, fx_val);
        switch (fx_code) {
            case 0x00://pitch slide up
                this->pitch_slide_up = float(fx_val) / float(0x00FFFFFF);
                this->pitch_slide_down = 0.f;
                this->pitch_slide_time = t;
                printf("pitch slide up %f\n", this->pitch_slide_up);
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
                printf("pitch %f\n", this->pitch);
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
                this->tremolo_time = t; //printf("tremolo speed %f\n", this->tremolo_speed);
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
                printf("unknown effect %x\n", fx_code);
                return false;
        }
    }

    float Track::play(double t, Channel *chan) {
        t += this->time_offset;
        this->update_fx(t);
        double time_in_track = fmod(t, double(this->duration));
        uint_fast8_t row_index = floor(time_in_track / this->step);
        uint_fast8_t index = floor(row_index / this->rows);
        row_index = row_index % this->rows;

        float s = 0.f;
        for (int_fast8_t i = this->getNumberofChannels() - 1; i >= 0; --i) {
            if (chan[i].isEnable()) {
                uint_fast8_t chan_number = chan[i].getNumber();
                uint_fast8_t pattern_index = *this->pattern_indices[chan_number * this->frames + index];
                Pattern *pat = this->track_patterns[chan_number * (this->frames) + pattern_index];
                Instruction *current_instruction = pat->instructions[row_index];
                if (current_instruction->effects != nullptr) {
                    for (int_fast8_t fx_indx = this->fx_per_chan[chan_number] - 1; fx_indx >= 0; --fx_indx) {
                        if (current_instruction->effects[fx_indx] != nullptr) {
                            //printf("CHAN %d EFFECT %d : %x\n", chan_number, fx_indx,
                            //*current_instruction->effects[fx_indx]);
                            this->decode_fx(*current_instruction->effects[fx_indx], t);
                        }
                    }
                }
                if (current_instruction->instrument_index < this->instruments) {
                    if (current_instruction != chan[i].getLastInstructionAddress()) {
                        chan[i].setLastInstructionAddress(current_instruction);
                        chan[i].setRelease(false);
                        chan[i].setTime(t);
                        chan[i].setTrack(this);
                        chan[i].setInstructionState(current_instruction);
                        this->instruments_bank[chan[i].getInstructionState()->instrument_index]->get_oscillator()->setRelease(
                                false);
                    }
                } else {
                    if (chan[i].getLastInstructionAddress() != nullptr) {
                        if (current_instruction->instrument_index == Notes::RELEASE &&
                            chan[i].getLastInstructionAddress()->instrument_index < this->instruments) {
                            if (!chan[i].isReleased()) {
                                chan[i].setRelease(true);
                                chan[i].setTimeRelease(t);
                                chan[i].setTrack(this);
                                this->instruments_bank[chan[i].getInstructionState()->instrument_index]->get_oscillator()->setRelease(
                                        true);
                            }
                            if (current_instruction->volume != Notes::CONTINUE &&
                                ((0.f <= current_instruction->volume) ||
                                 (current_instruction->volume <= MASTER_VOLUME))) {
                                chan[i].setVolumeInstructionState(current_instruction->volume);
                            }
                        }
                        if (current_instruction->instrument_index == Notes::CONTINUE &&
                            chan[i].getLastInstructionAddress()->instrument_index < this->instruments) {
                            if (current_instruction->volume != Notes::CONTINUE &&
                                ((0.f <= current_instruction->volume) ||
                                 (current_instruction->volume <= MASTER_VOLUME))) {
                                chan[i].setVolumeInstructionState(current_instruction->volume);
                            }
                        }
                    }
                }

                if (chan[i].getLastInstructionAddress() != nullptr && chan[i].getTrack() != nullptr) {
                    if (!chan[i].isReleased()) {
                        s += chan[i].getVolume()
                             * this->instruments_bank[chan[i].getInstructionState()->instrument_index]->play(
                                chan[i].getInstructionState()->volume,
                                (chan[i].getInstructionState()->key.note + this->pitch) + this->vibrato_val,
                                chan[i].getInstructionState()->key.octave,
                                t - chan[i].getTime());
                    } else {
                        s += chan[i].getVolume()
                             * this->instruments_bank[chan[i].getInstructionState()->instrument_index]->play(
                                chan[i].getInstructionState()->volume,
                                (chan[i].getInstructionState()->key.note + this->pitch) + this->vibrato_val,
                                chan[i].getInstructionState()->key.octave,
                                t - chan[i].getTime(), t - chan[i].getTimeRelease());
                    }
                }
            }
        }
        return this->volume * this->tremolo_val * s;
    }

    float *Track::play_(double t, Channel *chan) {
        //t += this->time_offset;
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

        float s = 0.f;
        float a = 0.f;
        float f = 0.f;
        for (int_fast8_t i = this->getNumberofChannels() - 1; i >= 0; --i) {
        //for (int_fast8_t i = 2; i >= 2; --i) {
            if (chan[i].isEnable()) {
                if(chan[i].getTrack() != nullptr){
                    chan[i].update_fx(t);
                }
                uint_fast8_t chan_number = chan[i].getNumber();
                uint_fast8_t pattern_index = *this->pattern_indices[chan_number * this->frames + this->frame_counter];
                Pattern *pat = this->track_patterns[chan_number * (this->frames) + pattern_index];
                Instruction *current_instruction = pat->instructions[this->row_counter];


                if (current_instruction->instrument_index < this->instruments) {
                    if (current_instruction != chan[i].getLastInstructionAddress()) {
                        chan[i].setLastInstructionAddress(current_instruction);
                        chan[i].setRelease(false);
                        chan[i].setTime(t);
                        chan[i].setTrack(this);
                        chan[i].setInstructionState(current_instruction);
                        this->instruments_bank[chan[i].getInstructionState()->instrument_index]->get_oscillator()->setRelease(
                                false);
                        chan[i].pitch_slide_val = 0;
                        chan[i].pitch_slide_time = t;
                        chan[i].note_sliding = false;
                        chan[i].note_slide_val = 0;
                        chan[i].transpose_time_step = t;
                        chan[i].transpose_semitone_counter = 0;
                        if(chan[i].n_time_to_transpose > 0){
                            --chan[i].n_time_to_transpose;
                        }
                        if(chan[i].n_time_to_retrieg > 0){
                            --chan[i].n_time_to_retrieg;
                        }
                        chan[i].retrieg_time_step = t;
                        chan[i].retrieg_counter = 0;

                    }
                } else {
                    if (chan[i].getLastInstructionAddress() != nullptr) {
                        if (current_instruction->instrument_index == Notes::RELEASE &&
                            chan[i].getInstructionState()->instrument_index < this->instruments) {
                            if (!chan[i].isReleased()) {
                                chan[i].setRelease(true);
                                chan[i].setTimeRelease(t);
                                chan[i].setTrack(this);
                                this->instruments_bank[chan[i].getInstructionState()->instrument_index]->get_oscillator()->setRelease(
                                        true);
                            }
                            if (current_instruction->volume != Notes::CONTINUE &&
                                ((0.f <= current_instruction->volume) &&
                                 (current_instruction->volume <= MASTER_VOLUME))) {
                                chan[i].setVolumeInstructionState(current_instruction->volume);
                            }
                        }
                        if (current_instruction->instrument_index == Notes::CONTINUE &&
                            chan[i].getInstructionState()->instrument_index < this->instruments) {
                            if (current_instruction->volume != Notes::CONTINUE &&
                                ((0.f <= current_instruction->volume) &&
                                 (current_instruction->volume <= MASTER_VOLUME))) {
                                chan[i].setVolumeInstructionState(current_instruction->volume);
                            }
                        }
                    }
                }

                if (current_instruction->effects != nullptr && this->readFx) {
                    for (int_fast8_t fx_indx = this->fx_per_chan[chan_number] - 1; fx_indx >= 0; --fx_indx) {
                        if (current_instruction->effects[fx_indx] != nullptr) {
                            if (!this->decode_fx(*current_instruction->effects[fx_indx], t)) {
                                chan[i].decode_fx(*current_instruction->effects[fx_indx], t);
                            }
                        }
                    }
                }

                uint_fast8_t arpeggio = 0;
                if(chan[i].arpeggio){
                    arpeggio = chan[i].arpeggio_val[chan[i].arpeggio_index];
                }

                a =  chan[i].getVolume() * chan[i].tremolo_val * chan[i].getInstructionState()->volume;
                f = this->pitch + this->vibrato_val + chan[i].pitch + chan[i].pitch_slide_val + chan[i].vibrato_val + arpeggio;
                /*if(this->readFx){
                    printf("chan %d volume %f = chanvol %f * chantremolo %f * instruction %f\n", i, a, chan[i].getVolume(), chan[i].tremolo_val, chan[i].getInstructionState()->volume );
                }*/
                //printf("chan %d volume %f = chanvol %f * chantremolo %f * instruction %f\n", i, a, chan[i].getVolume(), chan[i].tremolo_val, chan[i].getInstructionState()->volume );

                if (chan[i].getLastInstructionAddress() != nullptr && chan[i].getTrack() != nullptr) {
                    if (!chan[i].isReleased()) {
                        s = this->instruments_bank[chan[i].getInstructionState()->instrument_index]->play(
                                a,
                                chan[i].getInstructionState()->key.note + f,
                                chan[i].getInstructionState()->key.octave,
                                t - chan[i].getTime());
                    } else {
                        s = this->instruments_bank[chan[i].getInstructionState()->instrument_index]->play(
                                a,
                                chan[i].getInstructionState()->key.note + f,
                                chan[i].getInstructionState()->key.octave,
                                t - chan[i].getTime(), t - chan[i].getTimeRelease());
                    }
                    res[0] += s * (1 - chan[i].panning);
                    res[1] += s * chan[i].panning;
                }
            }
        }


        res[0] *= this->volume * this->tremolo_val;
        res[1] *=  this->volume * this->tremolo_val;

        res[0] *= 4*(1 - this->panning);//left
        res[1] *= 4*this->panning;//right

        this->readFx = false;
        this->time = t;
        return res;
    }

    float Track::getPanning() {
        return this->panning;
    }

    float Track::getClock() {
        return this->clk;
    }

    float Track::getSpeed() {
        return this->speed;
    }

}