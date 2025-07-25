//
// Created by Abdulmajid, Olivier NASSER on 27/08/2020.
//

#include "../include/c0de_tracker.hpp"

/**
 * @file instrument.cpp
 * @brief Instrument class code
 * @see code_tracker.hpp
 * @author Abdulmajid, Olivier NASSER
 * @version 0.1
 * @date 27/08/2020
 */

namespace C0deTracker{

    Instrument_Data::Instrument_Data() {
        this->oscillators_data = new Oscillator_Data[1];
        ++this->oscillators_count;
    }

    Instrument_Data::Instrument_Data(uint_fast8_t wavetype, ADSR amp_envelope) {
        this->setData(wavetype, amp_envelope);
    }

    Instrument_Data::Instrument_Data(uint_fast8_t wavetype, ADSR amp_envelope, float volume) {
        this->setData(wavetype, amp_envelope, volume);
    }

    Instrument_Data::Instrument_Data(uint_fast8_t wavetype, ADSR amp_envelope, float volume, float pitch) {
        this->setData(wavetype, amp_envelope, volume, pitch);
    }

    Instrument_Data::Instrument_Data(uint_fast8_t wavetype, ADSR amp_envelope, float volume, float pitch, float duty_cycle) {
        this->setData(wavetype, amp_envelope, volume, pitch, duty_cycle);
    }

    Instrument_Data::Instrument_Data(uint_fast8_t wavetype, ADSR amp_envelope, float volume, float pitch,float duty_cycle, float phase) {
        this->setData(wavetype, amp_envelope, volume, pitch, duty_cycle, phase);
    }

    Instrument_Data::Instrument_Data(uint_fast8_t wavetype, ADSR amp_envelope, float volume, float pitch, float duty_cycle, float phase, float feedback_level) {
        this->setData(wavetype, amp_envelope, volume, pitch, duty_cycle, phase, feedback_level);
    }

    Instrument_Data::Instrument_Data(uint_fast8_t wavetype, ADSR amp_envelope, float volume, float pitch, float duty_cycle, float phase, float feedback_level, float mul_freq) {
        this->setData(wavetype, amp_envelope, volume, pitch, duty_cycle, phase, feedback_level, mul_freq);
    }

    void Instrument_Data::setData(uint_fast8_t wavetype, ADSR amp_envelope) {
        this->oscillators_data[0].setData(wavetype, amp_envelope);
    }

    void Instrument_Data::setData(uint_fast8_t wavetype, ADSR amp_envelope, float volume) {
        this->oscillators_data[0].setData(wavetype, amp_envelope, volume);
    }

    void Instrument_Data::setData(uint_fast8_t wavetype, ADSR amp_envelope, float volume, float pitch) {
        this->oscillators_data[0].setData(wavetype, amp_envelope, volume, pitch);
    }

    void Instrument_Data::setData(uint_fast8_t wavetype, ADSR amp_envelope, float volume, float pitch, float duty_cycle) {
        this->oscillators_data[0].setData(wavetype, amp_envelope, volume, pitch, duty_cycle);
    }

    void Instrument_Data::setData(uint_fast8_t wavetype, ADSR amp_envelope, float volume, float pitch, float duty_cycle, float phase) {
        this->oscillators_data[0].setData(wavetype, amp_envelope, volume, pitch, duty_cycle, phase);
    }

    void Instrument_Data::setData(uint_fast8_t wavetype, ADSR amp_envelope, float volume, float pitch, float duty_cycle, float phase, float feedback_level) {
        this->oscillators_data[0].setData(wavetype, amp_envelope, volume, pitch, duty_cycle, phase, feedback_level);
    }

    void Instrument_Data::setData(uint_fast8_t wavetype, ADSR amp_envelope, float volume, float pitch, float duty_cycle, float phase, float feedback_level, float mul_freq) {
        this->oscillators_data[0].setData(wavetype, amp_envelope, volume, pitch, duty_cycle, phase, feedback_level, mul_freq);
    }

    Instrument_Data::~Instrument_Data() {
        delete[] this->oscillators_data;
        delete this->algo;
    }

    uint_fast8_t Instrument_Data::getOscillatorsCount() {
        return this->oscillators_count;
    }

    void Instrument_Data::setData(std::vector<Oscillator_Data> oscillators) {
        assert(oscillators.size() <= MAX_OSCILLATORS && "Oscillators count must be under MAX_OSCILLATORS (0xF)");
        delete[] this->oscillators_data;

        this->oscillators_data = new Oscillator_Data[oscillators.size()];
        this->oscillators_count = oscillators.size();

        for (uint_fast8_t i = 0; i < oscillators.size(); ++i) {
            this->oscillators_data[i] = oscillators[i];
        }
    }

}