//
// Created by Abdulmajid, Olivier NASSER on 24/08/2020.
//
#include "code_tracker.hpp"

namespace  CodeTracker{

    Key::Key(uint_fast8_t n, uint_fast8_t o) {this->note = n; this->octave = o;}

    Key::Key(){this->note = Notes::CONTINUE; this->octave = Notes::CONTINUE;};

    ADSR::ADSR(float A, float D, float S, float R) { this->attack = A; this->decay = D; this->sustain = S; this->release = R;}


    namespace Notes {
        float pitch(float p){return pow(1.059460646483f, p) * 440.0f;}

        float key2freq(uint_fast8_t note , uint_fast8_t octave){
            //A4 == 440 HZ = pitch 0
            //-12 pitch == 3A == 220 HZ
            //+12
            return pitch(float(PITCHES_PER_OCTAVE
                                  *(octave - OCTAVE_PITCH_OFFSET)
                                  +(note - NOTE_PITCH_OFFSET)
                                  ));
        }

        float key2freq(Key key){
            return key2freq(key.note, key.octave);
        }
    }

    Instruction::Instruction(uint_fast8_t instrument, Key k, float vol) : key(k) {
        this->instrument_index = instrument; this->volume = vol; this->effects = nullptr;
    }

    Instruction::Instruction(uint_fast8_t instrument, uint_fast8_t note, uint_fast8_t octave, float vol) : key(Key(note,octave)) {
        this->instrument_index = instrument; this->volume = vol; this->effects = nullptr;
    }

    Instruction::Instruction(uint_fast8_t instrument, Key k, float vol, uint_fast32_t *effects) : key(k){
        this->instrument_index = instrument; this->volume = vol; this->effects = effects;
    }

    Instruction::Instruction(uint_fast8_t instrument, uint_fast8_t note, uint_fast8_t octave, float vol, uint_fast32_t *effects) : key(note,octave) {
        this->instrument_index = instrument; this->volume = vol; this->effects = effects;
    }

    Instruction::Instruction() {this->volume = Notes::CONTINUE; this->instrument_index = Notes::CONTINUE; this->key = Key(); this->effects = nullptr;}

    Instruction::~Instruction() {delete[] this->effects;}

    Pattern::Pattern(uint_fast8_t rows) {
        this->instructions = new Instruction* [rows];
        for(uint_fast8_t i = 0; i < rows; ++i){
            this->instructions[i] = new Instruction();
        }
        this->rows = rows;
    }

    Pattern::~Pattern() {
        for(uint_fast8_t i = 0; i < this->rows; ++i){
            delete this->instructions[i];
        }
        delete[] this->instructions;
    }


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


    Track::Track(float clk, float basetime, float speed, uint_fast8_t rows, uint_fast8_t frames, uint_fast8_t channels,
                 Instrument** instruments_bank, uint_fast8_t numb_of_instruments, Pattern** track_patterns, uint_fast8_t** pattern_indices) {
        this->clk = clk; this->basetime = basetime; this->speed = speed;
        this->rows = rows; this->frames = frames;
        this->channels = channels; this->instruments_bank = instruments_bank; this->instruments = numb_of_instruments;
        this->track_patterns = track_patterns; this->pattern_indices = pattern_indices;
        this->step = this->basetime * this->speed / this->clk;
        this->duration = float(this->frames * this->rows) * this-> step;
        printf("STEP : %f\n",this->step);
        printf("DURATION : %f\n", this->duration);
    }

    Track::~Track() {
        for(uint8_t i = 0; i < this->channels * this->frames; ++i){delete this->pattern_indices[i];}
        delete[] this->pattern_indices;
        for(uint8_t i = 0; i < this->channels * this->frames; ++i){delete this->track_patterns[i];}
        delete[] this->track_patterns;
        for(uint8_t i = 0; i < this->instruments; ++i){ delete this->instruments_bank[i];}
        delete[] this->instruments_bank;
    }



    uint_fast8_t Track::getNumberofChannels() {
        return this->channels;
    }
    float Track::getDuration() {
        return this->duration;
    }

    float Track::play_single_channel(double t, Channel *chan) {
        if(chan->getNumber() > this->channels){return 0.0f;}
        if(chan->isEnable()) {
            double time_in_track = fmod(t, double(this->duration));
            uint_fast8_t row_index = floor(time_in_track / this->step);
            uint_fast8_t pattern_index = floor(row_index / this->rows);
            row_index = row_index % this->rows;
            uint_fast8_t chan_number = chan->getNumber();
            pattern_index = *this->pattern_indices[chan_number * this->frames + pattern_index];
            Pattern* pat = this->track_patterns[chan_number * (this->frames) + pattern_index];
            Instruction* current_instruction = pat->instructions[row_index];
                if(current_instruction->instrument_index < this->instruments){
                    if(current_instruction != chan->getLastInstructionAddress()){
                        chan->setLastInstructionAddress(current_instruction);
                        this->instruments_bank[current_instruction->instrument_index]->get_oscillator()->setRelease(false);
                        chan->setRelease(false);
                        chan->setTime(t);
                        chan->setTrack(this);
                    }
                }else{
                    if(current_instruction->instrument_index == Notes::RELEASE && chan->getLastInstructionAddress()->instrument_index < this->instruments){
                        if(!chan->isReleased()){
                            chan->setRelease(true);
                            chan->setTimeRelease(t);
                            chan->setTrack(this);
                            this->instruments_bank[chan->getLastInstructionAddress()->instrument_index]->get_oscillator()->setRelease(true);
                        }
                        if(current_instruction->volume != Notes::CONTINUE &&  ( (0.f <= current_instruction->volume) || (current_instruction->volume <= MASTER_VOLUME) )){
                            chan->setVolumeInstructionState(current_instruction->volume);
                        }
                    }
                    if(current_instruction->instrument_index == Notes::CONTINUE && chan->getLastInstructionAddress()->instrument_index < this->instruments){
                        if(current_instruction->volume != Notes::CONTINUE &&  ( (0.f <= current_instruction->volume) || (current_instruction->volume <= MASTER_VOLUME) )){
                            chan->setVolumeInstructionState(current_instruction->volume);
                        }
                    }
                }
                if (chan->getLastInstructionAddress() != nullptr && chan->getTrack() != nullptr){
                    if(!chan->isReleased()){
                        return this->volume * chan->getVolume()
                               * this->instruments_bank[chan->getLastInstructionAddress()->instrument_index]->play(
                                chan->getLastInstructionAddress()->volume, chan->getLastInstructionAddress()->key, t - chan->getTime());
                    }else{
                        return this->volume * chan->getVolume()
                              * this->instruments_bank[chan->getLastInstructionAddress()->instrument_index]->play(
                                chan->getLastInstructionAddress()->volume, chan->getLastInstructionAddress()->key, t - chan->getTime(), t - chan->getTimeRelease());
                    }
                }

        }
        return 0.0f;
    }

    float Track::play(double t, Channel *chan) {
        double time_in_track = fmod(t, double(this->duration));

        uint_fast8_t row_index = floor(time_in_track / this->step);
        uint_fast8_t index = floor(row_index / this->rows);
        row_index =  row_index% this->rows;


        float s = 0.f;
        for(int_fast8_t i = this->getNumberofChannels()-1; i >= 0; --i){
            if(chan[i].isEnable()) {
                uint_fast8_t chan_number = chan[i].getNumber();
                uint_fast8_t pattern_index = *this->pattern_indices[chan_number * this->frames + index];
                Pattern* pat = this->track_patterns[chan_number * (this->frames) + pattern_index];
                Instruction* current_instruction = pat->instructions[row_index];
                if(current_instruction->instrument_index < this->instruments){
                    if(current_instruction != chan[i].getLastInstructionAddress()){
                        chan[i].setLastInstructionAddress(current_instruction);
                        chan[i].setRelease(false);
                        chan[i].setTime(t);
                        chan[i].setTrack(this);
                        chan[i].setInstructionState(current_instruction);
                        this->instruments_bank[chan[i].getInstructionState()->instrument_index]->get_oscillator()->setRelease(false);
                    }
                }else{
                    if(chan[i].getLastInstructionAddress() != nullptr){
                        if(current_instruction->instrument_index == Notes::RELEASE && chan[i].getLastInstructionAddress()->instrument_index < this->instruments){
                            if(!chan[i].isReleased()){
                                chan[i].setRelease(true);
                                chan[i].setTimeRelease(t);
                                chan[i].setTrack(this);
                                this->instruments_bank[chan[i].getInstructionState()->instrument_index]->get_oscillator()->setRelease(true);
                            }
                            if(current_instruction->volume != Notes::CONTINUE &&  ( (0.f <= current_instruction->volume) || (current_instruction->volume <= MASTER_VOLUME) )){
                                chan[i].setVolumeInstructionState(current_instruction->volume);
                            }
                        }
                        if(current_instruction->instrument_index == Notes::CONTINUE && chan[i].getLastInstructionAddress()->instrument_index < this->instruments){
                            if(current_instruction->volume != Notes::CONTINUE &&  ( (0.f <= current_instruction->volume) || (current_instruction->volume <= MASTER_VOLUME) )){
                                chan[i].setVolumeInstructionState(current_instruction->volume);
                            }
                        }
                    }
                }
                if (chan[i].getLastInstructionAddress() != nullptr && chan[i].getTrack() != nullptr){
                    if(!chan[i].isReleased()){
                        s += this->volume * chan[i].getVolume()
                               * this->instruments_bank[chan[i].getInstructionState()->instrument_index]->play(
                                chan[i].getInstructionState()->volume, chan[i].getInstructionState()->key, t - chan[i].getTime());
                    }else{
                        s += this->volume * chan[i].getVolume()
                               * this->instruments_bank[chan[i].getInstructionState()->instrument_index]->play(
                                chan[i].getInstructionState()->volume, chan[i].getInstructionState()->key, t - chan[i].getTime(), t - chan[i].getTimeRelease());
                    }
                }
            }
        }
        return s;
    }
}
