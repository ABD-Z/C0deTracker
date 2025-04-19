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
    void Channel::setLastInstructionAddress(Instruction *lastInstructionAddress) { this->last_instruct_address = lastInstructionAddress;}

    double Channel::getTime() const{return this->time;}

void Channel::setTime(double time) {
        this->time = time;
        if (!this->portamento.isActive() || (this->portamento.isActive() && this->isReleased()))
            this->oscillator.resetPhaseTimeOffset();
    }

    double Channel::getTimeRelease() const {return this->time_release;}

    void Channel::setTimeRelease(double time) {this->time_release = time; this->setRelease(true);}

    bool Channel::isReleased() const {return this->released;}

    void Channel::setRelease(bool r) {this->released = r; this->oscillator.setRelease(r);}

    const Instruction *Channel::getInstructionState() const {return &this->instruct_state;}

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
        float rv = this->retrieg.getValue();
        uint_fast8_t reldel_state = this->delay_release.getValue();
        ChannelFXs::update_fx(t, this->track->getClock(), this->track->getSpeed());

        if (rv != this->retrieg.getValue())
            this->setTime(t);

        if (this->delay_release.getValue() == 1) //delay
            this->setTime(t);

        if (reldel_state == 2) { // release
            if (reldel_state != this->delay_release.getValue()) {
                this->setTimeRelease(t);
            }
        }
    }

    bool Channel::decode_fx(uint_fast32_t fx, double t) {
        return ChannelFXs::decode_fx(fx, t);
    }

    float Channel::play_pitch(float a, float p, double t) {
        float f = this->oscillator.pitch2freq(p, t);
        return this->oscillator.oscillate(a, f, t);
    }

    float Channel::play_pitch(float a, float p, double t, double rt) {
        float f = this->oscillator.pitch2freq(p, t);
        return this->oscillator.oscillate(a, f, t, rt);
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
    }

    void Channel::setTrack(Track *track) {this->track = track;}
    Track *Channel::getTrack() const {return this->track;}

    void Channel::setInstrumentParams(Instrument_Data *instrument) {
        this->oscillator.setOscillatorParams(instrument);
    }

    void Channel::initFXs(Instruction *instruction, double time) {
        if (this->portamento.isActive()) { //init portamento
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

        this->oscillator.setRelease(false);
        this->pitch.val = 0;
        this->pitch.time_step = time;
        this->transpose.time_step = time;
        this->transpose.semitones_counter = 0;
        this->retrieg.time_step = time;
        this->retrieg.counter = 0;

        this->delay_release.delay.time_step = time;
        this->delay_release.release.time_step = time;
        this->delay_release.delay.counter = 0;
        this->delay_release.release.counter = 0;

        this->transpose.val = 0;
        if(this->transpose.repeat > 0){
            --this->transpose.repeat;
        }
        if(this->retrieg.repeat > 0){
            --this->retrieg.repeat;
        }
        if(this->delay_release.delay.repeat){
            --this->delay_release.delay.repeat;
        }
        if(this->delay_release.release.repeat){
            --this->delay_release.release.repeat;
        }
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