//
// Created by Abdulmajid, Olivier NASSER on 21/11/2021.
//
#include "c0de_tracker.hpp"

namespace C0deTracker {
    void Track::setTrack_Data(Track_Data *td) {
        this->track_data = td;
        this->chans = new C0deTracker::Channel[td->channels];
        this->clk = td->clk; this->speed = td->speed; this->step = td->step; this->duration = td->duration;
    }

    Track::Track(Track_Data* td){
        this->setTrack_Data(td);
    }

    void Track::changeTrack(Track_Data* td) {
        this->resetState();
        delete[] this->chans;
        this->setTrack_Data(td);
    }

    Track::~Track() {
        delete[] this->chans;
    }

    void Track::resetState() {
        this->reset_fxs();
        row_counter = 0; frame_counter = 0;
        time_advance = 0.0;
        readFx = true;
        branch = false;
        frametojump = 0;
        rowtojump = 0;
        stop = false;
        /*for(int16_t i = this->track_data->channels-1; i >= 0 ; --i){
            this->chans[i].resetState();
        }*/
    }

    float *Track::play(double t) {
        static float res[2];

        res[0] = 0.f; res[1] = 0.f;
        this->update_fx(t, this->getClock(), this->getSpeed());

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

        if (this->row_counter >= this->track_data->rows) {
            this->row_counter = 0;
            ++this->frame_counter;
        }
        if (this->frame_counter >= this->track_data->frames) {
            this->frame_counter = 0;
        }

        float s = 0.f;//generated signal
        float a = 0.f;//amplitude
        float p = 0.f;//pitch

        for (int_fast8_t i = this->track_data->channels - 1; i >= 0; --i) {
            if (this->chans[i].isEnable()) {
                if(this->chans[i].getTrack() != nullptr){
                    this->chans[i].update_fx(t);
                }
                uint_fast8_t chan_number = i;
                uint_fast8_t pattern_index = this->track_data->pattern_indices[chan_number * this->track_data->frames + this->frame_counter];
                Pattern *pat = this->track_data->track_patterns[chan_number * (this->track_data->frames) + pattern_index];
                Instruction *current_instruction = &pat->instructions[this->row_counter];


                if (current_instruction->instrument_index < this->track_data->instruments) {
                    if (this->readFx) {
                        this->chans[i].setLastInstructionAddress(current_instruction);
                        this->chans[i].setTime(t);
                        this->chans[i].setRelease(false);

                        this->chans[i].setTrack(this);
                        if(this->chans[i].getInstructionState()->key.note == Notes::CONTINUE || this->chans[i].getInstructionState()->key.octave == Notes::CONTINUE){
                            if(this->chans[i].getInstructionState()->instrument_index != current_instruction->instrument_index){
                                //delete chan[i].instrument;
                                //chan[i].instrument = this->instruments_bank[current_instruction->instrument_index]->clone();
                                this->chans[i].oscillator.setOscillatorParams(&this->track_data->instruments_data_bank[current_instruction->instrument_index]);
                            }
                            this->chans[i].setInstructionState(current_instruction);
                        }else{
                            if(!this->chans[i].portamento.isActive()){
                                if(this->chans[i].getInstructionState()->instrument_index != current_instruction->instrument_index){
                                    //delete chan[i].instrument;
                                    //chan[i].instrument = this->instruments_bank[current_instruction->instrument_index]->clone();
                                    this->chans[i].oscillator.setOscillatorParams(&this->track_data->instruments_data_bank[current_instruction->instrument_index]);
                                }
                                this->chans[i].setInstructionState(current_instruction);
                            }else{
                                this->chans[i].portamento.time_step = t;
                                if(this->chans[i].instruct_state.key.octave == Notes::CONTINUE){
                                    this->chans[i].portamento.val = 0;
                                }else{
                                    float diffpitch = this->chans[i].portamento.getValue() +
                                            Notes::key2pitch(current_instruction->key) - Notes::key2pitch(this->chans[i].instruct_state.key);

                                    if (diffpitch > 0)
                                        this->chans[i].portamento.sign = 1;
                                    if (diffpitch < 0)
                                        this->chans[i].portamento.sign = -1;

                                    this->chans[i].portamento.val = abs(diffpitch);
                                    //check if diff (val) is positiv -> portamento_bool.speed = abs(portamento_bool.speed)
                                    //else if negativ ->portamento_bool.speed = - abs(portamento_bool.speed)
                                }

                                if(this->chans[i].getInstructionState()->instrument_index != current_instruction->instrument_index){
                                    //delete chan[i].instrument;
                                    //chan[i].instrument = this->instruments_bank[current_instruction->instrument_index]->clone();
                                    this->chans[i].oscillator.setOscillatorParams(&this->track_data->instruments_data_bank[current_instruction->instrument_index]);
                                }
                                this->chans[i].setInstructionState(current_instruction);
                            }
                        }
                        //chan[i].instrument->get_oscillator()->setRelease(false);
                        this->chans[i].oscillator.setRelease(false);
                        this->chans[i].pitch.val = 0;
                        this->chans[i].pitch.time_step = t;
                        this->chans[i].transpose.time_step = t;
                        this->chans[i].transpose.semitones_counter = 0;
                        this->chans[i].retrieg.time_step = t;
                        this->chans[i].retrieg.counter = 0;
                        /*this->chans[i].delrel_time_step = t;
                        this->chans[i].release_counter = 0;
                        this->chans[i].delay_counter = 0;*/

                        this->chans[i].delay_release.delay.time_step = t;
                        this->chans[i].delay_release.release.time_step = t;
                        this->chans[i].delay_release.delay.counter = 0;
                        this->chans[i].delay_release.release.counter = 0;

                        this->chans[i].transpose.val = 0;
                        if(this->chans[i].transpose.repeat > 0){
                            --this->chans[i].transpose.repeat;
                        }
                        if(this->chans[i].retrieg.repeat > 0){
                            --this->chans[i].retrieg.repeat;
                        }
                        if(this->chans[i].delay_release.delay.repeat){
                            --this->chans[i].delay_release.delay.repeat;
                        }
                        if(this->chans[i].delay_release.release.repeat){
                            --this->chans[i].delay_release.release.repeat;
                        }
                    }
                } else {
                    if (this->chans[i].getLastInstructionAddress() != nullptr) {
                        if (current_instruction->instrument_index == Notes::RELEASE &&
                            this->chans[i].getInstructionState()->instrument_index < this->track_data->instruments) {
                            if (!this->chans[i].isReleased()) {
                                this->chans[i].setRelease(true);
                                this->chans[i].setTimeRelease(t);
                                this->chans[i].setTrack(this);
                                this->chans[i].oscillator.setRelease(true);
                            }
                            if (current_instruction->volume != Notes::CONTINUE &&
                                ((0.f <= current_instruction->volume) &&
                                 (current_instruction->volume <= MAX_VOLUME))) {
                                this->chans[i].setVolumeInstructionState(current_instruction->volume);
                            }
                        }
                        if (current_instruction->instrument_index == Notes::CONTINUE &&
                            this->chans[i].getInstructionState()->instrument_index < this->track_data->instruments) {
                            if (current_instruction->volume != Notes::CONTINUE &&
                                ((0.f <= current_instruction->volume) &&
                                 (current_instruction->volume <= MAX_VOLUME))) {
                                this->chans[i].setVolumeInstructionState(current_instruction->volume);
                            }
                        }
                    }
                }

                if (current_instruction->effects != nullptr && this->readFx) {
                    for (int_fast8_t fx_indx = 0; fx_indx < this->track_data->fx_per_chan[chan_number]; ++fx_indx) {
                        if (current_instruction->effects[fx_indx] == nullptr)
                            break;
                        if (!this->decode_fx(*current_instruction->effects[fx_indx], t))
                            this->chans[i].decode_fx(*current_instruction->effects[fx_indx], t);
                    }
                }
                //check if channel is released because of release effect
                if(this->chans[i].isReleased()){
                    this->chans[i].oscillator.setRelease(true);
                }

                uint_fast8_t arpeggio = 0;
                if(this->chans[i].arpeggio.isActive()){
                    arpeggio = this->chans[i].arpeggio.getValue();
                }

                a =  this->chans[i].getVolume() * this->chans[i].tremolo.getValue() * this->chans[i].getInstructionState()->volume;
                p = + this->pitch.getValue() + Notes::key2pitch(this->chans[i].getInstructionState()->key)  + this->chans[i].pitch.getValue()
                        + arpeggio - this->chans[i].portamento.getValue()
                        + this->chans[i].oscillator.getPitch()
                        + this->chans[i].transpose.getValue();

                if(t-this->chans[i].getTime() > 0)
                    p += (this->vibrato.getValue() + this->chans[i].vibrato.getValue());///(t-this->chans[i].getTime());


                if (this->chans[i].getLastInstructionAddress() != nullptr && this->chans[i].getTrack() != nullptr) {
                    if (!this->chans[i].isReleased()) {
                        //s = chan[i].instrument->play_pitch(a, p, t - chan[i].getTime());
                        s = this->chans[i].play_pitch(a, p, t - this->chans[i].getTime());//new
                    } else {
                        //s = chan[i].instrument->play_pitch(a, p, t - chan[i].getTime(), t - chan[i].getTimeRelease());
                        s = this->chans[i].play_pitch(a, p, t - this->chans[i].getTime(), t - this->chans[i].getTimeRelease());//new
                    }
                    res[0] += s * (1 - this->chans[i].panning.getValue());
                    res[1] += s * this->chans[i].panning.getValue();
                }
            }
        }

        res[0] *= this->volume.val * this->tremolo.val;
        res[1] *=  this->volume.val * this->tremolo.val;

        res[0] *= 4*(1 - this->panning.val);//left
        res[1] *= 4*this->panning.val;//right


        this->readFx = false;
        return res;
    }

    bool Track::decode_fx(uint_fast32_t fx, double t) {
        uint_fast8_t fx_code = fx >> 4 * 6;
        uint_fast32_t fx_val = fx & 0x00FFFFFF;
        switch (fx_code) {
            case 0x09://change speed of the track
                this->speed = float(fx_val >> 4 * 3) + float(fx_val & 0xFFF) / float(0xFFF);;
                this->step = this->track_data->basetime * this->speed / this->track_data->clk;
                this->duration = float(this->track_data->frames * this->track_data->rows) * this->step;
                return true;
            case 0x0A:// jumpt to frame row
                this->branch = true;
                this->frametojump = fx_val >> 4 * 3;
                this->rowtojump = fx_val & 0xFFF;
                if ((this->frametojump == this->frame_counter && this->rowtojump == this->row_counter) ||
                    (this->frametojump >= this->track_data->frames) || (this->rowtojump >= this->track_data->rows)) {
                    this->branch = false;
                }
                return true;
            case 0x0B://stop song
                this->stop = true;
                return true;
            default:
                return GlobalFXs::decode_fx(fx, t);
        }
    }

    float Track::getClock() const {
        return this->clk;
    }

    float Track::getSpeed() const {
        return this->speed;
    }

    float Track::getDuration() const {
        return this->duration;
    }
}
