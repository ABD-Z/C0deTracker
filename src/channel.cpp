//
// Created by Abdulmajid, Olivier NASSER on 21/10/2020.
//

#include "code_tracker.hpp"

namespace CodeTracker {
    Channel::Channel(uint_fast8_t number) {this->number = number;}
    uint_fast8_t Channel::getNumber() const {return number;}

    bool Channel::isEnable() const{return this->enable_sound;}
    void Channel::enable() {this->enable_sound = true;}
    void Channel::disable() {this->enable_sound = false; this->last_instruct_address = nullptr; this->track = nullptr;}

    float Channel::getVolume() const{return this->volume;}
    void Channel::setVolume(float volume) {this->volume = volume;}

    float Channel::getPitch() const {return this->pitch;}
    void Channel::setPitch(float pitch) {this->pitch = pitch;}

    float Channel::getSpeed() const {return this->speed;}
    void Channel::setSpeed(float speed) {this->speed = speed;}

    Instruction* Channel::getLastInstructionAddress() const {return this->last_instruct_address;}
    void Channel::setLastInstructionAddress(Instruction *lastInstructionAddress) { this->last_instruct_address = lastInstructionAddress;}

    void Channel::setTrack(Track *track) {this->track = track;} Track *Channel::getTrack() const {return this->track;}

    double Channel::getTime() const{return this->time;}

    void Channel::setTime(double time) { this->time = time;}

    uint_fast8_t Channel::chancount = 0;

    Channel::Channel() {
        this->number = Channel::chancount++;
    }

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

    bool Channel::decode_fx(uint_fast32_t fx, double t) {
        uint_fast8_t fx_code = fx >> 4 * 6;
        uint_fast32_t fx_val = fx & 0x00FFFFFF;
        printf("pitch %f\n", this->pitch);
        printf("%.3f FX CODE : %x ; FX VAL : %x\n", t, fx_code, fx_val);
        switch (fx_code) {
            case 0x10://pitch slide up
                this->pitch_slide_up = float(fx_val) / float(0x00FFFFFF);
                this->pitch_slide_down = 0.f;
                this->pitch_slide_time = t;
                printf("pitch slide up %f\n", this->pitch_slide_up);
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
                printf("pitch %f\n", this->pitch);
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
                this->tremolo_speed = float(fx_val >> 4 * 3) / float(0x800);
                this->tremolo_depth = float(fx_val & 0xFFF) / float(0xFFF);
                this->tremolo_time = t; //printf("tremolo speed %f\n", this->tremolo_speed);
                return true;
            case 0x18://set  panning
                this->panning = float(fx_val) / float(0xFFFFFF);
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
            default:
                printf("unknown effect\n");
                return false;
        }
    }
}