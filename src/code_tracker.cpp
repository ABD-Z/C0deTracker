//
// Created by Abdulmajid NASSER on 24/08/2020.
//
#include "code_tracker.hpp"

namespace  CodeTracker{

    Key::Key(uint8_t n, uint8_t o) {this->note = n; this->octave = o;}

    Key::Key(){this->note = CONTINUE; this->octave = CONTINUE;};

    ADSR::ADSR(float A, float D, float S, float R) { this->attack = A; this->decay = D; this->sustain = S; this->release = R;}


    namespace Notes {
        float pitch(float p){return pow(1.059460646483f, p) * 440.0f;}

        float key2freq(uint8_t note , uint8_t octave){
            //A4 == 440 HZ = pitch 0
            //-12 pitch == 3A == 220 HZ
            //+12
            return pitch(float(PITCHES_PER_OCTAVE
                                  *(octave - OCTAVE_PITCH_OFFSET)
                                  +(note - NOTE_PITCH_OFFSET)
                                  ));
        }

        float key2freq(Key key){
            return pitch(float(PITCHES_PER_OCTAVE
                               *(key.octave - OCTAVE_PITCH_OFFSET)
                               +(key.note - NOTE_PITCH_OFFSET)
                               ));
        }
    }

    Instruction::Instruction(uint8_t instrument, Key k, float vol) : key(k) {
        this->instrument_index = instrument; this->volume = vol; this->effects = nullptr;
    }

    Instruction::Instruction(uint8_t instrument, uint8_t note, uint8_t octave, float vol) : key(Key(note,octave)) {
        this->instrument_index = instrument; this->volume = vol; this->effects = nullptr;
    }

    Instruction::Instruction(uint8_t instrument, Key k, float vol, uint32_t *effects) : key(k){
        this->instrument_index = instrument; this->volume = vol; this->effects = effects;
    }

    Instruction::Instruction(uint8_t instrument, uint8_t note, uint8_t octave, float vol, uint32_t *effects) : key(note,octave) {
        this->instrument_index = instrument; this->volume = vol; this->effects = effects;
    }

    Instruction::Instruction() {this->volume = CONTINUE; this->instrument_index = CONTINUE; this->key = Key(); this->effects = nullptr;}

    Instruction::~Instruction() {delete[] this->effects;}

    Pattern::~Pattern() {
        for(uint8_t i = 0; i < this->rows; ++i){
            delete this->instructions[i];
        }
        delete[] this->instructions;
    }

    Pattern::Pattern(uint8_t rows) {
        this->instructions = new Instruction* [rows];
        for(uint8_t i = 0; i < rows; ++i){
            this->instructions[i] = new Instruction();
        }
        this->rows = rows;
    }


    Channel::Channel(uint8_t number) {this->number = number;}
    uint8_t Channel::getNumber() const {return number;}

    bool Channel::isEnable() const{return this->enable_sound;}
    void Channel::enable() {this->enable_sound = true;}
    void Channel::disable() {this->enable_sound = false; this->last_instruction = nullptr; this->track = nullptr;}

    float Channel::getVolume() const{return this->volume;}
    void Channel::setVolume(float volume) {this->volume = volume;}

    float Channel::getPitch() const {return this->pitch;}
    void Channel::setPitch(float pitch) {this->pitch = pitch;}

    float Channel::getSpeed() const {return this->speed;}
    void Channel::setSpeed(float speed) {this->speed = speed;}

    Instruction* Channel::getLastInstruction() const {return this->last_instruction;}
    void Channel::setLastInstruction(Instruction *lastInstruction) {this->last_instruction = lastInstruction;}

    void Channel::setTrack(Track *track) {this->track = track;} Track *Channel::getTrack() const {return this->track;}

    float Channel::getTime() const{return this->time;}

    void Channel::setTime(float time) {this->time = time;}

    uint8_t Channel::chancount = 0;

    Channel::Channel() {
        this->number = Channel::chancount++;
    }

    float Channel::getTimeRelease() const {
        return this->time_release;
    }

    void Channel::setTimeRelease(float time) {
        this->time_release = time;
    }

    bool Channel::isReleased() const {
        return this->released;
    }

    void Channel::setRelease(bool r) {
        this->released = r;
    }


    Track::~Track() {
        for(uint8_t i = 0; i < this->channels * this->frames; ++i){delete this->pattern_indices[i];}
        delete[] this->pattern_indices;
        for(uint8_t i = 0; i < this->channels * this->frames; ++i){delete this->track_patterns[i];}
        delete[] this->track_patterns;
        for(uint8_t i = 0; i < this->instruments; ++i){ delete this->instruments_bank[i];}
        delete[] this->instruments_bank;
    }

    Track::Track(float clk, float basetime, float speed, uint8_t rows, uint8_t frames, uint8_t channels,
                 Instrument** instruments_bank, uint8_t numb_of_instruments, Pattern** track_patterns, uint8_t** pattern_indices) {
        this->clk = clk; this->basetime = basetime; this->speed = speed;
        this->rows = rows; this->frames = frames;
        this->channels = channels; this->instruments_bank = instruments_bank; this->instruments = numb_of_instruments;
        this->track_patterns = track_patterns; this->pattern_indices = pattern_indices;
        this->step = this->basetime * this->speed / this->clk;
        this->duration = float(this->frames * this->rows) * this-> step;
        printf("STEP : %f\n",this->step);
        printf("DURATION : %f\n", this->duration);
    }

    float Track::play(float t, Channel *chan) {
        if(chan->getNumber() > this->channels){return 0.0f;}
        if(chan->isEnable()) {
            float time_in_track = fmod(t, this->duration);
            uint8_t row_index = floor(time_in_track / this->step);
            uint8_t pattern_index = floor(row_index / this->rows);
            row_index = row_index % this->rows;
            uint8_t chan_number = chan->getNumber();
            pattern_index = *this->pattern_indices[chan_number * this->frames + pattern_index];
            Pattern* pat = this->track_patterns[chan_number * (this->frames) + pattern_index];
            Instruction* current_instruction = pat->instructions[row_index];
                if(current_instruction->instrument_index < this->instruments){
                    if(current_instruction != chan->getLastInstruction()){
                        chan->setLastInstruction(current_instruction);
                        this->instruments_bank[current_instruction->instrument_index]->get_oscillator()->setRelease(false);
                        chan->setRelease(false);
                        chan->setTime(t);
                        chan->setTrack(this);
                    }
                    return this->volume * chan->getVolume()
                            * this->instruments_bank[current_instruction->instrument_index]->play(current_instruction->volume, current_instruction->key, t - chan->getTime());
                }else{
                    if(current_instruction->instrument_index == RELEASE && chan->getLastInstruction()->instrument_index < this->instruments){
                        if(!chan->isReleased()){
                            chan->setRelease(true);
                            chan->setTimeRelease(t);
                            chan->setTrack(this);
                            this->instruments_bank[chan->getLastInstruction()->instrument_index]->get_oscillator()->setRelease(true);
                        }
                        return this->volume * chan->getVolume()
                               * this->instruments_bank[chan->getLastInstruction()->instrument_index]->play(chan->getLastInstruction()->volume, chan->getLastInstruction()->key, t - chan->getTime(), t - chan->getTimeRelease());
                    }
                }
                if (chan->getLastInstruction() != nullptr && chan->getTrack() != nullptr){
                    if(!chan->isReleased()){
                        return this->volume * chan->getVolume()
                               * this->instruments_bank[chan->getLastInstruction()->instrument_index]->play(chan->getLastInstruction()->volume, chan->getLastInstruction()->key, t - chan->getTime());
                    }else{
                        return this->volume * chan->getVolume()
                              * this->instruments_bank[chan->getLastInstruction()->instrument_index]->play(chan->getLastInstruction()->volume, chan->getLastInstruction()->key, t - chan->getTime(), t - chan->getTimeRelease());
                    }
                }

        }
        return 0.0f;
    }


}
