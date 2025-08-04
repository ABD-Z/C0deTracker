//
// Created by Abdulmajid, Olivier NASSER on 24/08/2020.
//
#include "../include/c0de_tracker.hpp"

/**
 * @file code_tracker.cpp
 * @brief This file contains basic stuff for C0deTracker
 * @see Key , ADSR , Notes , Instruction , Pattern
 * @author Abdulmajid, Olivier NASSER
 * @version 0.1
 * @date 24/08/2020
 */

namespace  C0deTracker{

    AudioConfig::AudioConfig(uint_fast16_t sampleRate) : sampleRate(sampleRate) {
        this->bufferSize = AudioConfig::calcBufferSize(sampleRate, bufferDuration, this->getPanning());
    }

    AudioConfig::AudioConfig(uint_fast16_t sampleRate, float bufferLength) : sampleRate(sampleRate), bufferDuration(bufferLength) {
        this->bufferSize = AudioConfig::calcBufferSize(sampleRate, bufferDuration, this->getPanning());
    }

    AudioConfig::AudioConfig(uint_fast16_t sampleRate, float bufferLength, bool stereo) : sampleRate(sampleRate), bufferDuration(bufferLength), stereo(stereo) {
        this->bufferSize = AudioConfig::calcBufferSize(sampleRate, bufferDuration, this->getPanning());
    }

    AudioConfig::AudioConfig(float bufferLength) : bufferDuration(bufferLength) {
        this->bufferSize = AudioConfig::calcBufferSize(sampleRate, bufferDuration, this->getPanning());
    }

    AudioConfig::AudioConfig(float bufferLength, bool stereo) : bufferDuration(bufferLength), stereo(stereo) {
        this->bufferSize = AudioConfig::calcBufferSize(sampleRate, bufferDuration, this->getPanning());
    }

    AudioConfig::AudioConfig(bool stereo) : stereo(stereo) {
        this->bufferSize = AudioConfig::calcBufferSize(sampleRate, bufferDuration, this->getPanning());
    }

    AudioConfig::AudioConfig(uint_fast16_t sampleRate, bool stereo) : sampleRate(sampleRate), stereo(stereo) {
        this->bufferSize = AudioConfig::calcBufferSize(sampleRate, bufferDuration, this->getPanning());
    }

    uint_fast16_t AudioConfig::getSampleRate() const {
        return this->sampleRate;
    }

    float AudioConfig::getBufferDuration() const {
        return this->bufferDuration;
    }

    bool AudioConfig::isStereo() const {
        return this->stereo;
    }

    uint_fast8_t AudioConfig::getPanning() const {
        return 1 + this->stereo;
    }

    uint_fast32_t AudioConfig::getBufferSize() const {
        return this->bufferSize;
    }

    inline uint_fast32_t AudioConfig::calcBufferSize(uint_fast16_t sr, float bd, uint_fast8_t panning) {
        return static_cast<uint_fast32_t>(sr * bd * panning);
    }

    Key::Key(float n, float o) { this->note = n; this->octave = o;}

    Key::Key(){this->note = Notes::CONTINUE; this->octave = Notes::CONTINUE;}

    ADRComponent::ADRComponent(float speed, Easing::CallbackType easFunction) : speed(speed), easing(easFunction) {}

    ADRComponent::ADRComponent(float speed) : speed(speed) {}

    ADSR::ADSR(float A, float D, float S, float R) : A(A), D(D), S(S), R(R) {}

    ADSR::ADSR(ADRComponent A, ADRComponent D, float S, ADRComponent R) : A(A), D(D), S(S), R(R) {}

    namespace Notes {
        float pitch2freq(float p){return pow(2, p/12.f) * 440.0f;}

        float key2pitch(Key k){
            return key2pitch(k.note, k.octave);
        }

        float key2pitch(float note, float octave){
            return float(PITCHES_PER_OCTAVE
                         * (octave - OCTAVE_PITCH_OFFSET)
                         + (note - NOTE_PITCH_OFFSET));
        }

        float key2freq(float note , float octave){
            //A4 == 440 HZ = pitch2freq 0
            //-12 pitch2freq == 3A == 220 HZ
            //+12
            return pitch2freq(key2pitch(note, octave));
        }

        float key2freq(Key key){
            return key2freq(key.note, key.octave);
        }
    }

    Instruction::Instruction(uint_fast8_t instrument, Key k, float vol) : key(k) {
        this->instrument_index = instrument; this->volume = vol; this->effects = nullptr;
    }

    Instruction::Instruction(uint_fast8_t instrument, float note, float octave, float vol) : key(Key(note, octave)) {
        this->instrument_index = instrument; this->volume = vol; this->effects = nullptr;
    }

    Instruction::Instruction(uint_fast8_t instrument, Key k, float vol, uint_fast32_t**effects) : key(k){
        this->instrument_index = instrument; this->volume = vol; this->effects = effects;
    }

    Instruction::Instruction(uint_fast8_t instrument, float note, float octave, float vol, uint_fast32_t**effects) : key(note, octave) {
        this->instrument_index = instrument; this->volume = vol; this->effects = effects;
    }

    Instruction::Instruction() {this->volume = Notes::CONTINUE; this->instrument_index = Notes::CONTINUE; this->key = Key(); this->effects = nullptr;}


    Pattern::Pattern(uint_fast8_t rows, uint_fast8_t number_of_fx) {
        this->instructions = new Instruction[rows];
        /*for(uint_fast8_t i = 0; i < rows; ++i){
            this->instructions[i] = Instruction();
        }*/
        this->rows = rows;
        this->n_fx = number_of_fx;
    }

    Pattern::~Pattern() {
        for(uint_fast8_t i = 0; i < this->rows; ++i){
            if(this->instructions[i].effects != nullptr){
                for(uint_fast8_t j = 0; j < this->n_fx; ++j){
                    if(this->instructions[i].effects[j] == nullptr){
                        break;
                    }else{
                        delete this->instructions[i].effects[j];
                    }
                }
                delete[] this->instructions[i].effects;
            }
            //delete this->instructions[i];
        }
        delete[] this->instructions;
    }

    Oscillator_Data::Oscillator_Data(uint_fast8_t wavetype, ADSR amp_envelope) {this->setData(wavetype, amp_envelope);}

    Oscillator_Data::Oscillator_Data(uint_fast8_t wavetype, ADSR amp_envelope, float volume) {this->setData(wavetype, amp_envelope, volume);}

    Oscillator_Data::Oscillator_Data(uint_fast8_t wavetype, ADSR amp_envelope, float volume, float pitch) {this->setData(wavetype, amp_envelope, volume, pitch);}

    Oscillator_Data::Oscillator_Data(uint_fast8_t wavetype, ADSR amp_envelope, float volume, float pitch, float duty_cycle)
        {this->setData(wavetype, amp_envelope, volume, pitch, duty_cycle);}

    Oscillator_Data::Oscillator_Data(uint_fast8_t wavetype, ADSR amp_envelope, float volume, float pitch, float duty_cycle, float phase)
        {this->setData(wavetype, amp_envelope, volume, pitch, duty_cycle, phase);}

    Oscillator_Data::Oscillator_Data(uint_fast8_t wavetype, ADSR amp_envelope, float volume, float pitch, float duty_cycle, float phase, float feedback_level)
        {this->setData(wavetype, amp_envelope, volume, pitch, duty_cycle, phase, feedback_level);}

    Oscillator_Data::Oscillator_Data(uint_fast8_t wavetype, ADSR amp_envelope, float volume, float pitch, float duty_cycle, float phase, float feedback_level, float mul_freq)
        {this->setData(wavetype, amp_envelope, volume, pitch, duty_cycle, phase, feedback_level, mul_freq);}

    void Oscillator_Data::setData(uint_fast8_t wavetype, ADSR amp_envelope) { this->wavetype = wavetype; this->amp_envelope = amp_envelope;}

    void Oscillator_Data::setData(uint_fast8_t wavetype, ADSR amp_envelope, float volume) {this->setData(wavetype, amp_envelope); this->volume = volume;}

    void Oscillator_Data::setData(uint_fast8_t wavetype, ADSR amp_envelope, float volume, float pitch) {this->setData(wavetype, amp_envelope, volume); this->pitch = pitch;}

    void Oscillator_Data::setData(uint_fast8_t wavetype, ADSR amp_envelope, float volume, float pitch, float duty_cycle)
        {this->setData(wavetype, amp_envelope, volume, pitch); this->duty_cycle = duty_cycle;}

    void Oscillator_Data::setData(uint_fast8_t wavetype, ADSR amp_envelope, float volume, float pitch, float duty_cycle, float phase)
        {this->setData(wavetype, amp_envelope, volume, pitch, duty_cycle); this->phase = phase;}

    void Oscillator_Data::setData(uint_fast8_t wavetype, ADSR amp_envelope, float volume, float pitch, float duty_cycle, float phase, float feedback_level)
        {this->setData(wavetype, amp_envelope, volume, pitch, duty_cycle, phase); this->feedback_level = feedback_level;}

    void Oscillator_Data::setData(uint_fast8_t wavetype, ADSR amp_envelope, float volume, float pitch, float duty_cycle, float phase, float feedback_level, float mul_freq)
        {this->setData(wavetype, amp_envelope, volume, pitch, duty_cycle, phase, feedback_level); this->mul_freq = mul_freq;}

}
