//
// Created by Abdulmajid, Olivier NASSER on 21/11/2021.
//
#include "c0de_tracker.hpp"

namespace C0deTracker {
    void Track::setTrack_Data(Track_Data *td) {
        this->track_data = td;
        this->chans = new C0deTracker::Channel[td->channels];
        this->clk = td->clk; this->speed = td->speed; this->step = td->step; this->duration = td->duration;

        for (uint_fast8_t i = 0; i < td->channels; ++i) {
            this->chans[i].initDelayedFXsBuffer(td->fx_per_chan[i]);
        }
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

    AudioConfig *Track::getConfig() {
        return &this->config;
    }

    Track::Track(const AudioConfig cfg) : config(cfg){}

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

        for (int_fast8_t i = this->track_data->channels - 1; i >= 0; --i) {
            if (this->chans[i].isEnable()) {
                this->chans[i].setTrack(this);
                uint_fast8_t pattern_index = this->track_data->pattern_indices[i * this->track_data->frames + this->frame_counter];
                Pattern *pat = this->track_data->patterns[i * (this->track_data->frames) + pattern_index];
                Instruction *current_instruction = &pat->instructions[this->row_counter];

                this->decodeAllFXsFromChannel(i, current_instruction, t);

                if (this->readFx && this->isInstrumentValid(current_instruction->instrument_index)
                    && !this->chans[i].delay.isActive()) {
                    this->chans[i].initFXs(current_instruction, t);
                }

                if(this->isInstrumentValid(current_instruction->instrument_index)) {
                    if (this->readFx) {
                        if (this->chans[i].delay.isActive() != true) {

                            this->chans[i].setLastInstructionAddress(current_instruction);

                            this->chans[i].setTime(t);
                            this->chans[i].setRelease(false);

                            this->chans[i].setTrack(this);

                            if (this->isNewInstrumentFromChannel(i, current_instruction)) {
                                this->chans[i].setInstrumentParams(&this->track_data->instruments_data_bank[current_instruction->instrument_index]);
                            }

                            this->chans[i].setInstructionState(current_instruction);
                        } else {
                            this->chans[i].delayed_instruct_address = current_instruction;
                            this->chans[i].delayed_instrument = &this->track_data->instruments_data_bank[current_instruction->instrument_index];
                        }
                    }
                } else {
                    if (this->chans[i].getLastInstructionAddress() != nullptr
                        && this->isInstrumentValid(this->chans[i].getInstructionState()->instrument_index)) {
                        if (this->isNoteReleased(current_instruction)) {
                            if (!this->chans[i].isReleased()) {
                                this->chans[i].setTimeRelease(t);
                                this->chans[i].setTrack(this);
                            }
                        }

                        if (this->isVolumeValid(current_instruction->volume)) {
                            this->chans[i].setVolumeInstructionState(current_instruction->volume);
                        }
                    }
                }

                if(this->chans[i].getTrack() != nullptr){
                    this->chans[i].update_fx(t);
                }

                this->calcStereoSampleFromChannel(i, t, res);
            }
        }

        this->calcTracksStereoSample(res);

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

    void Track::calcStereoSampleFromChannel(uint_fast8_t index, double time, float* output) {
        if (this->chans[index].getLastInstructionAddress() != nullptr && this->chans[index].getTrack() != nullptr) { // if last instruction is not empty (null) and has a track
            float s;
            float amplitude = this->chans[index].calcAmplitude();
            float pitch = this->chans[index].calcPitch(time)
                          + this->pitch.getValue()
                          + (time - this->chans[index].getTime() > 0 ? this->vibrato.getValue() : 0);
            float panning = this->chans[index].getPanning();
            if (!this->chans[index].isReleased())
                s = this->chans[index].play_pitch(amplitude, pitch, time - this->chans[index].getTime());// unreleased sample
            else
                s = this->chans[index].play_pitch(amplitude, pitch, time - this->chans[index].getTime(), time - this->chans[index].getTimeRelease());// released sample

            output[0] += s * (1 - panning);
            output[1] += s * panning;
        }
    }

    void Track::decodeAllFXsFromChannel(int_fast8_t index, Instruction *current_instruction, double time) {
        if (current_instruction->effects != nullptr && this->readFx) { // read and decode FX only when time is to read em (readFx to true) and ofc not null
            for (int_fast8_t fx_indx = 0; fx_indx < this->track_data->fx_per_chan[index]; ++fx_indx) {
                if (current_instruction->effects[fx_indx] == nullptr) // break instant at first empty FX (it means no more FXx)
                    break;
                if (!this->decode_fx(*current_instruction->effects[fx_indx], time)) {
                    this->chans[index].decode_fx(*current_instruction->effects[fx_indx], time);
                }

            }
        }
    }

    bool Track::isVolumeValid(float volume) {
        return (volume != Notes::CONTINUE && ((0.f <= volume) && (volume <= MAX_VOLUME)));
    }

    bool Track::isNoteReleased(Instruction *instruction) {
        return instruction->instrument_index == Notes::RELEASE;
    }

    void Track::calcTracksStereoSample(float *output) {
        output[0] *= this->volume.val * this->tremolo.val;
        output[1] *=  this->volume.val * this->tremolo.val;

        output[0] *= 2*(1 - this->panning.val); //left
        output[1] *= 2*this->panning.val; //right
    }

    bool Track::isInstrumentValid(uint_fast8_t instru_index) {
        return instru_index < this->track_data->instruments;
    }

    bool Track::isNewInstrumentFromChannel(int_fast8_t chan_index, Instruction *instru) {
        return this->chans[chan_index].getInstructionState()->instrument_index != instru->instrument_index;
    }
}
