//
// Created by Abdulmajid, Olivier NASSER on 21/10/2020.
//

/**
 * @file channel.cpp
 * @brief Channel class code
 * @see code_tracker.hpp
 * @author Abdulmajid, Olivier NASSER
 * @version 0.1
 * @date 21/10/2020
 */

#include "../include/c0de_tracker.hpp"

namespace C0deTracker {
    bool Channel::isEnable() const{return this->enable_sound;}
    void Channel::enable() {this->enable_sound = true;}
    void Channel::disable() {this->enable_sound = false; this->last_instruct_address = nullptr; this->track = nullptr;}

    float Channel::getVolume() const{return this->volume;}
    void Channel::setVolume(float volume) {this->volume = volume;}

    float Channel::getPitch() const {return this->pitch;}
    void Channel::setPitch(float pitch) {this->pitch = pitch;}

    Instruction* Channel::getLastInstructionAddress() const {return this->last_instruct_address;}
    void Channel::setLastInstructionAddress(Instruction *lastInstructionAddress) { this->last_instruct_address = lastInstructionAddress;}

    void Channel::setTrack(Track *track) {this->track = track;} Track *Channel::getTrack() const {return this->track;}

    double Channel::getTime() const{return this->time;}

    void Channel::setTime(double time) { this->time = time;}


    Channel::Channel()=default;

    Channel::~Channel()= default;

    double Channel::getTimeRelease() const {
        return this->time_release;
    }

    void Channel::setTimeRelease(double time) {
        this->time_release = time;
    }

    bool Channel::isReleased() const {
        return this->released;
    }

    void Channel::setRelease(bool r) {
        this->released = r;
    }

    const Instruction *Channel::getInstructionState() const {
        return &this->instruct_state;
    }

    void Channel::setInstructionState(Instruction *instruc) {
        this->instruct_state.volume = instruc->volume;
        this->instruct_state.instrument_index = instruc->instrument_index;
        this->instruct_state.key = instruc->key;
        this->instruct_state.effects = instruc->effects;
    }

    void Channel::setVolumeInstructionState(float a) {
        this->instruct_state.volume = a;
    }

    void Channel::update_fx(double t) {
        if(this->volume_slide_down != 0){
            this->volume -= (this->volume_slide_down / this->track->getSpeed()) * (t - this->volume_slide_time);
            if (this->volume <= 0) {
                this->volume = 0.f;
                this->volume_slide_down = 0.f;
            }
        }

        if(this->volume_slide_up != 0){
            this->volume += (this->volume_slide_up / this->track->getSpeed()) * (t - this->volume_slide_time);
            if (this->volume >= MASTER_VOLUME) {
                this->volume = MASTER_VOLUME;
                this->volume_slide_up = 0.f;
            }
        }

        if(this->pitch_slide_down != 0)
            this->pitch_slide_val -= (this->pitch_slide_down / this->track->getSpeed()) * (t - this->pitch_slide_time);

        if(this->pitch_slide_up != 0)
            this->pitch_slide_val += (this->pitch_slide_up   / this->track->getSpeed()) * (t - this->pitch_slide_time);

        if(this->panning_slide_right != 0){
            this->panning += (this->panning_slide_right / this->track->getSpeed()) * (t - this->panning_slide_time);
            if (this->panning >= MASTER_VOLUME) {
                this->panning = MASTER_VOLUME;
                this->panning_slide_right = 0.f;
            }
        }

        if(this->panning_slide_left != 0){
            this->panning -= (this->panning_slide_left / this->track->getSpeed()) * (t - this->panning_slide_time);
            if (this->panning <= 0) {
                this->panning = 0;
                this->panning_slide_left = 0.f;
            }
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
        if(this->arpeggio){
            if (t - this->arpeggio_step >= 1./this->track->getClock()){
                this->arpeggio_step += 1./this->track->getClock();
                ++this->arpeggio_index;
                if(this->arpeggio_index > 5){
                    this->arpeggio_index = 0;
                }
            }
        }

        if(this->transpose_semitones > 0 && this->n_time_to_transpose > 0){
            if(this->transpose_delay > 0x7F){//transpose up to this->transpose_semitones
                if(t - (this->transpose_time_step) >=  double((this->transpose_delay - 0x7F)) / this->track->getClock() && this->transpose_semitone_counter < this->transpose_semitones) {
                    this->transpose_time_step +=  double((this->transpose_delay - 0x7F)) / this->track->getClock();
                    ++this->transpose_semitone_counter;
                    ++this->instruct_state.key.note;

                }
            }else{//transpose down
                if(t - (this->transpose_time_step) >= double((this->transpose_delay) ) / this->track->getClock() && this->transpose_semitone_counter < this->transpose_semitones ){
                    this->transpose_time_step += double((this->transpose_delay)) / this->track->getClock();
                    ++this->transpose_semitone_counter;
                    --this->instruct_state.key.note;
                }
            }
        }

        if(this->retrieg_number > 0 && this->n_time_to_retrieg > 0){
            if(t - this->retrieg_time_step >= double(this->retrieg_delay) / this->track->getClock() && this->retrieg_counter < this->retrieg_number){
                this->retrieg_time_step += double(this->retrieg_delay) / this->track->getClock();
                this->setTime(t);
                ++this->retrieg_counter;
            }
        }

        if(this->delay_counter <= this->delay && this->delay > 0 && this->n_time_to_delrel > 0){
            this->setTime(t);
            if(t - this->delrel_time_step >= 1. / this->track->getClock()){
                ++this->delay_counter;
                this->delrel_time_step += 1. / this->track->getClock();
            }
        }else{
            if(this->release > 0 && !this->isReleased()){
                if(this->release_counter <= this->release && this->n_time_to_delrel > 0){
                    if(t - this->delrel_time_step >= 1. / this->track->getClock()){
                        ++this->release_counter;
                        this->delrel_time_step += 1. / this->track->getClock();
                        if(this->release_counter >= this->release){
                            this->setRelease(true);
                            this->setTimeRelease(t);
                        }
                    }
                }
            }
        }
        if(this->portamento) {
            if (this->porta_pitch_dif < 0) {
                if (t - this->portamento_time_step >= 1. / this->track->getClock()) {
                    this->portamento_time_step += 1. / this->track->getClock();
                    this->porta_pitch_dif += (this->portamento_speed * this->track->getSpeed());
                    if (this->porta_pitch_dif > 0) {
                        this->porta_pitch_dif = 0;
                    }
                }
            } else {
                if (this->porta_pitch_dif > 0) {
                    if (t - this->portamento_time_step >= 1. / this->track->getClock()) {
                        this->portamento_time_step += 1. / this->track->getClock();
                        this->porta_pitch_dif -= (this->portamento_speed * this->track->getSpeed());
                        if (this->porta_pitch_dif < 0) {
                            this->porta_pitch_dif = 0;
                        }
                    }
                }
            }
        }
    }

    bool Channel::decode_fx(uint_fast32_t fx, double t) {
        uint_fast8_t fx_code = fx >> 4 * 6;
        uint_fast32_t fx_val = fx & 0x00FFFFFF;
        switch (fx_code) {
            case 0x10://pitch slide up
                this->pitch_slide_up = float(fx_val) / float(0x00FFFFFF);
                this->pitch_slide_down = 0.f;
                this->pitch_slide_time = t;
                return true;
            case 0x11://pitch slide down
                this->pitch_slide_down = float(fx_val) / float(0x00FFFFFF);
                this->pitch_slide_up = 0.f;
                this->pitch_slide_time = t;
                return true;
            case 0x12://vibrato
                this->vibrato_speed = float((fx_val >> 4 * 3)) / float(0x100);
                this->vibrato_depth = float(fx_val & 0xFFF) / float(0x800);
                this->vibrato_time = t;
                return true;
            case 0x13://set pitch
                this->pitch = (float(fx_val) - float(0x800000)) / float(0x800000);
                return true;
            case 0x14://set volume
                this->volume = float(fx_val) / float(0x00FFFFFF);
                return true;
            case 0x15://volume slide up
                this->volume_slide_up = float(fx_val) / float(0x00FFFFFF);
                this->volume_slide_down = 0.f;
                this->volume_slide_time = t;
                return true;
            case 0x16://volume slide down
                this->volume_slide_down = float(fx_val) / float(0x00FFFFFF);
                this->volume_slide_up = 0.f;
                this->volume_slide_time = t;
                return true;
            case 0x17://tremolo
                this->tremolo_speed = float(fx_val >> 4 * 3) / float(0x100);
                this->tremolo_depth = float(fx_val & 0xFFF) / float(0xFFF);
                this->tremolo_time = t;
                return true;
            case 0x18://set  panning
                this->panning = float(fx_val) / float(0xFFFFFF);
                return true;
            case 0x19://arpeggio
                this->arpeggio = true;
                this->arpeggio_step = t;
                this->arpeggio_val[0] = float(fx_val >> 4 * 5);
                this->arpeggio_val[1] = float( (fx_val >> 4 * 4) & 0xF);
                this->arpeggio_val[2] = float( (fx_val >> 4 * 3) & 0xF);
                this->arpeggio_val[3] = float( (fx_val >> 4 * 2) & 0xF);
                this->arpeggio_val[4] = float( (fx_val >> 4 * 1) & 0xF);
                this->arpeggio_val[5] = float(fx_val & 0xF);
                if(this->arpeggio_val[0] == 0 && this->arpeggio_val[1] == 0 && this->arpeggio_val[2] == 0 && this->arpeggio_val[3] == 0 && this->arpeggio_val[4] == 0 && this->arpeggio_val[5] == 0){
                    this->arpeggio = false;
                }
                return true;
            case 0x1A://transpose
                this->transpose_delay = (fx_val >> 4 * 4);
                this->transpose_semitones = (fx_val & 0xFF00) >> 4 * 2;
                this->n_time_to_transpose = (fx_val & 0xFF);
                this->transpose_time_step = t;
                return true;
            case 0x1B://portamento
                this->portamento = fx_val != 0;
                this->portamento_speed = float(fx_val)/float(0x800000);
                this->portamento_time_step = t;
                if(this->portamento_speed == 0){
                    this->porta_pitch_dif = 0;
                }
                return true;
            case 0x1C://retrieg
                this->retrieg_delay = (fx_val >> 4 * 4);
                this->retrieg_number = (fx_val & 0xFF00) >> 4 * 2;
                this->n_time_to_retrieg = (fx_val & 0xFF);
                this->retrieg_time_step = t;
                return true;
            case 0x1D://slide right panning
                this->panning_slide_right = float(fx_val) / float(0xFFFFFF);
                this->panning_slide_left = 0.0f;
                this->panning_slide_time = t;
                return true;
            case 0x1E://slide left panning
                this->panning_slide_left = float(fx_val) / float(0xFFFFFF);
                this->panning_slide_right = 0.0f;
                this->panning_slide_time = t;
                return true;
            case 0x1F:
                this->delay = (fx_val >> 4 * 4);
                this->release = (fx_val & 0xFF00) >> 4 * 2;
                this->n_time_to_delrel = (fx_val & 0xFF);
                this->delrel_time_step = t;
                return true;
            default:
                return false;
        }
    }

    float Channel::play_pitch(float a, float p, double t) {
        return this->oscillator.oscillate(a, this->oscillator.pitch2freq(p), t, this->oscillator.getDutycycle(), this->oscillator.getPhase());
    }

    float Channel::play_pitch(float a, float p, double t, double rt) {
        return this->oscillator.oscillate(a, this->oscillator.pitch2freq(p), t, rt, this->oscillator.getDutycycle(), this->oscillator.getPhase());;
    }

    void Channel::resetState() {
        last_instruct_address = nullptr;
        track = nullptr;
        /**Channel state**/
         time = 0.0;
         enable_sound = true;
         volume = 1.0f; pitch = 0.0f; speed = 1.0f;
         released = false;
         time_release = 0.0;
         instrument_index = Notes::KeysUtilities::CONTINUE;

         volume_slide_up = 0.f;
         volume_slide_down = 0.f;
         volume_slide_time = 0.0;

         pitch_slide_up = 0.f;
         pitch_slide_down = 0.f;
         pitch_slide_time = 0.0;
         pitch_slide_val =0.0;

         portamento = false;
         portamento_speed = 0.f;
         porta_pitch_dif = 0.0f;
         portamento_time_step = 0;

         tremolo_speed = 0.0f;
         tremolo_depth = 0.0f;
         tremolo_val = 1.0f;
         tremolo_time = 0.0;

         vibrato_speed = 0.0f;
         vibrato_depth = 0.0f;
         vibrato_val = 0.0f;
         vibrato_time = 0.0;

         panning = 0.5f;

         panning_slide_right = 0.f;
         panning_slide_left = 0.f;
         panning_slide_time = 0.0;

         arpeggio = false;
         arpeggio_step = 0.0;
          arpeggio_index = 0;

         transpose_delay = 0;
         n_time_to_transpose = 0;
         transpose_semitones = 0;
         transpose_semitone_counter = 0;
         transpose_time_step = 0;

         retrieg_delay = 0;
         retrieg_number = 0;
         n_time_to_retrieg = 0;
         retrieg_time_step = 0;
         retrieg_counter = 0;

         delay = 0;
         release = 0;
         n_time_to_delrel = 0;
         delrel_time_step = 0;
         delay_counter = 0;
         release_counter = 0;
    }


}