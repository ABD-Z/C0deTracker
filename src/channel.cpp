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
    void Channel::disable() {this->enable_sound = false; this->last_instruct_address = nullptr;
        this->track = nullptr;}

    float Channel::getVolume() const{return this->volume.val;}
    void Channel::setVolume(float volume) {this->volume.val = volume;}

    float Channel::getPitch() const {return this->pitch.val;}
    void Channel::setPitch(float pitch) {this->pitch.val = pitch;}

    Instruction* Channel::getLastInstructionAddress() const {return this->last_instruct_address;}
    void Channel::setLastInstructionAddress(Instruction *lastInstructionAddress) {this->last_instruct_address = lastInstructionAddress;}

    double Channel::getTime() const{return this->time;}

void Channel::setTime(double time) {
        this->time = time;
        if (!this->portamento.isActive() || this->isReleased()) {
            for (uint_fast8_t i = 0; i < this->oscillators_count; ++i)
                this->oscillators[i].resetPhaseTimeOffset();
        }
    }

    double Channel::getTimeRelease() const {return this->time_release;}

    void Channel::setTimeRelease(double time) {this->time_release = time; this->setRelease(true);}

    bool Channel::isReleased() const {return this->released;}

    void Channel::setRelease(bool r) {
        this->released = r;
        for (uint_fast8_t i = 0; i < this->oscillators_count; ++i)
            this->oscillators[i].setRelease(r);
    }

    const Instruction *Channel::getInstructionState() const {return &this->instruct_state;}

    void Channel::setInstructionState(Instruction *instruc) {
        if (instruc == nullptr) return;
        this->instruct_state.volume = instruc->volume;
        this->instruct_state.instrument_index = instruc->instrument_index;
        this->instruct_state.key = instruc->key;
        this->instruct_state.effects = instruc->effects;
    }

    void Channel::setVolumeInstructionState(float a) {
        this->instruct_state.volume = a;
    }

    void Channel::update_fx(double t) {
        float rv = this->retrieg.getValue();

        bool relstate = this->release.isActive();
        bool delstate = this->delay.isActive();

        ChannelFXs::update_fx(t, this->track->getClock(), this->track->getSpeed());

        if (rv != this->retrieg.getValue())
            this->setTime(t);

        if (delstate) { // delay before update
            if (!this->delay.isActive()) { // finished from processing delay (delay state switched to off)
                this->setTime(t);
                this->setRelease(false);

                this->setInstructionState(delayed_instruct_address);
                this->setInstrumentParams(this->delayed_instrument);
                this->setLastInstructionAddress(delayed_instruct_address);

                if (this->delayed_fx_counter > 0) {
                    for (uint_fast8_t i = 0; i < delayed_fx_counter; ++i) {
                        this->decode_fx(this->delayed_fxs[i], t);
                    }
                    this->delayed_fx_counter = 0;
                }

                this->delayed_instruct_address = nullptr;
                this->delayed_instrument = nullptr;
                this->release.time_step = t;
                this->pitch.val = 0;
                this->pitch.time_step = t;
                this->transpose.val = 0;
                this->transpose.semitones_counter = 0;
                this->transpose.time_step = t;
                this->retrieg.time_step = time;
                this->retrieg.counter = 0;
            }
        }

        if (relstate) { // release before updates
            if (!this->release.isActive()) // finished from processing release (release state switched to off)
                this->setTimeRelease(t); // so time to set release time
        }
    }

    bool Channel::decode_fx(uint_fast32_t fx, double t) {
        if(this->delay.isActive()) {
            if (this->delayed_fx_counter < this->delayed_fxs_size) {
                this->delayed_fxs[this->delayed_fx_counter] = fx;
                ++this->delayed_fx_counter;
            }
            return true;
        }
        return ChannelFXs::decode_fx(fx, t);
    }

    float Channel::play_pitch(float a, float p, double t) {
        return (*this->algorithm)(this->oscillators, this->oscillators_count, a,p,t,-1,0);
    }

    float Channel::play_pitch(float a, float p, double t, double rt) {
        return (*this->algorithm)(this->oscillators, this->oscillators_count, a,p,t,rt,0);
    }

    void Channel::resetState() {
        this->reset_fxs();
        last_instruct_address = nullptr;
        track = nullptr;
        /**Channel state**/
         time = 0.0;
         enable_sound = true;
         speed = 1.0f;
         released = false;
         time_release = 0.0;
         instrument_index = Notes::KeysUtilities::CONTINUE;
         delayed_instruct_address = nullptr;
    }

    void Channel::setTrack(Track *track) {this->track = track;}
    Track *Channel::getTrack() const {return this->track;}

    void Channel::setInstrumentParams(Instrument_Data *instrument) {
        if (instrument == nullptr) return;
        for(uint_fast8_t i = 0; i < instrument->getOscillatorsCount(); ++i)
            this->oscillators[i].setOscillatorData(&instrument->oscillators_data[i]);

        this->algorithm = instrument->algo;
        this->oscillators_count = instrument->getOscillatorsCount();
    }

    void Channel::initFXs(Instruction *instruction, double time) {
        if(this->transpose.repeat > 0 && time > this->transpose.time_step){
            --this->transpose.repeat;
        }
        if(this->retrieg.repeat > 0 && time > this->retrieg.time_step){
            --this->retrieg.repeat;
        }
        if(this->delay.repeat > 0 && time > this->delay.time_step){
            --this->delay.repeat;
        }
        if(this->release.repeat > 0 && time > this->release.time_step/*&& !this->release.isActive()*/){
            --this->release.repeat;
        }

        if (this->portamento.isActive()) { // init portamento
            this->portamento.time_step = time;
            //empty note
            if (this->getInstructionState()->key.note == Notes::CONTINUE || this->getInstructionState()->key.octave == Notes::CONTINUE) {
                this->portamento.val = 0;
            } else {
                float diffpitch = this->portamento.getValue() +
                                  Notes::key2pitch(instruction->key) -
                                  Notes::key2pitch(this->getInstructionState()->key);

                this->portamento.sign = (diffpitch > 0) ? 1 : -1;
                this->portamento.val = abs(diffpitch);
                //check if diff (val) is positiv -> portamento = portamento.val
                //else if negativ -> portamento = - portamento.val
            }
        }

        this->pitch.val = 0;
        this->pitch.time_step = time;
        this->transpose.time_step = time;
        this->transpose.val = 0;
        this->transpose.semitones_counter = 0;
        this->retrieg.time_step = time;
        this->retrieg.counter = 0;

        this->delay.time_step = time;
        this->release.time_step = time;

        this->delay.counter = 0;
        this->release.counter = 0;
    }

    float Channel::calcAmplitude() {
        return this->getVolume() * this->getInstructionState()->volume * this->tremolo.getValue();
    }

    float Channel::calcPitch(double time) {
        return Notes::key2pitch(this->getInstructionState()->key)  + this->pitch.getValue()
                + (this->arpeggio.isActive() ? this->arpeggio.getValue() : 0)
                - this->portamento.getValue()
                + this->transpose.getValue()
                + (time - this->getTime() > 0 ? this->vibrato.getValue() : 0);
    }

    float Channel::getPanning() const {
        return this->panning.getValue();
    }
}