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

    Instrument_Data::Instrument_Data(uint_fast8_t wavetype, ADSR amp_envelope, float volume, float pitch,float duty_cycle, float phase) {
        this->wavetype = wavetype;
        this->amp_envelope = amp_envelope;
        this->volume = volume; this->pitch = pitch; this->duty_cycle = duty_cycle; this->phase = phase;
    }

    void Instrument_Data::setData(uint_fast8_t wavetype, ADSR amp_envelope, float volume, float pitch, float duty_cycle, float phase) {
        this->wavetype = wavetype; this->amp_envelope = amp_envelope; this->volume = volume; this->pitch = pitch;
        this->duty_cycle = duty_cycle; this->phase = phase;

    }
}

