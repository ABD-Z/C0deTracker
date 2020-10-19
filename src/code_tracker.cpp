//
// Created by Abdulmajid, Olivier NASSER on 24/08/2020.
//
#include "code_tracker.hpp"

namespace  CodeTracker{

    Key::Key(float n, float o) { this->note = n; this->octave = o;}

    Key::Key(){this->note = Notes::CONTINUE; this->octave = Notes::CONTINUE;};

    ADSR::ADSR(float A, float D, float S, float R) { this->attack = A; this->decay = D; this->sustain = S; this->release = R;}


    namespace Notes {
        float pitch(float p){return pow(1.059460646483f, p) * 440.0f;}

        float key2freq(float note , float octave){
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
                 Instrument** instruments_bank, uint_fast8_t numb_of_instruments, Pattern** track_patterns, uint_fast8_t** pattern_indices,
                 const uint_fast8_t* effects_per_chan) {
        this->clk = clk; this->basetime = basetime; this->speed = speed;
        this->rows = rows; this->frames = frames;
        this->channels = channels; this->instruments_bank = instruments_bank; this->instruments = numb_of_instruments;
        this->track_patterns = track_patterns; this->pattern_indices = pattern_indices;
        this->step = this->basetime * this->speed / this->clk;
        this->duration = float(this->frames * this->rows) * this-> step;
        this->fx_per_chan = effects_per_chan;
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


    void Track::update_fx(double t) {
        this->volume -= (this->volume_slide_down/this->speed) *(t-this->volume_slide_time);
        if(this->volume <= 0){this->volume = 0.f; this->volume_slide_down = 0.f;}
        this->volume += (this->volume_slide_up/this->speed) *(t-this->volume_slide_time);
        if(this->volume >= MASTER_VOLUME){this->volume = MASTER_VOLUME; this->volume_slide_up = 0.f;}


        this->pitch -= (this->pitch_slide_down/this->speed) * (t-this->pitch_slide_time);
        this->pitch += (this->pitch_slide_up/this->speed) * (t-this->pitch_slide_time);




        if(this->tremolo_speed == 0.f || this->tremolo_depth == 0.f){
            this->tremolo_val = 1.0f;
        }else{
            this->tremolo_val = 0.5f * this->tremolo_depth * sin(TWOPI * this->tremolo_speed *(t - this->tremolo_time)) + (1 - 0.5f * this->tremolo_depth);
        }
        if(this->vibrato_speed == 0.f || this->vibrato_depth == 0.f){
            this->vibrato_val = 0.0f;
        }else{
            this->vibrato_val = this->vibrato_depth * sin(TWOPI * this->vibrato_speed *(t - this->vibrato_time));
        }
        //printf("volume %f", this->volume);
    }

    bool Track::decode_fx(uint_fast32_t fx, double t) {
        uint_fast8_t fx_code =  fx >> 4*6;
        uint_fast32_t fx_val = fx & 0x00FFFFFF;
        printf("pitch %f\n", this->pitch);
        printf("%.3f FX CODE : %x ; FX VAL : %x\n",t, fx_code, fx_val);
        switch(fx_code){
            case 0x00://pitch slide up
                this->pitch_slide_up = float(fx_val) / float(0x00FFFFFF); this->pitch_slide_down = 0.f; this->pitch_slide_time = t;
                break;
            case 0x01://pitch slide down
                this->pitch_slide_down = float(fx_val) / float(0x00FFFFFF); this->pitch_slide_up = 0.f; this->pitch_slide_time = t;
                break;
            case 0x02://vibrato
                this->vibrato_speed = float((fx_val >> 4*3))/float(0x100); this->vibrato_depth = float(fx_val & 0xFFF)/float(0x800); this->vibrato_time = t; printf("vibrato speed %.2f  depth %.2f\n", this->vibrato_speed, this->vibrato_depth);
                break;
            case 0x03://set pitch
                this->pitch = (float(fx_val) - float(0x800000))/float(0x800000); printf("pitch %f\n", this->pitch);
                break;
            case 0x04://set volume
                this->volume = float(fx_val) / float(0x00FFFFFF);
                break;
            case 0x05://volume slide up
                this->volume_slide_up = float(fx_val) / float(0x00FFFFFF); this->volume_slide_down = 0.f; this->volume_slide_time = t;
                break;
            case 0x06://volume slide down
                this->volume_slide_down = float(fx_val) / float(0x00FFFFFF); this->volume_slide_up = 0.f; this->volume_slide_time = t;
                break;
            case 0x07://tremolo
                this->tremolo_speed =  float(fx_val >> 4*3)/float(0x800); this->tremolo_depth = float(fx_val & 0xFFF)/float(0xFFF); this->tremolo_time = t; //printf("tremolo speed %f\n", this->tremolo_speed);
                break;
            case 0x08://set global track panning
                this->panning = float(fx_val)/float(0xFFFFFF);
                break;
            case 0x09:
                this->speed = float(fx_val >> 4 * 3) + float(fx_val & 0xFFF) / float(0xFFF);;
                this->step = this->basetime * this->speed / this->clk;
                this->duration = float(this->frames * this->rows) * this->step;
                break;
            case 0x0A:
                this->branch = true;
                this->frametojump = fx_val >> 4*3;
                this->rowtojump = fx_val & 0xFFF;
                if( (this->frametojump == this->frame_counter && this->rowtojump == this->row_counter) || (this->frametojump >= this->frames) || (this->rowtojump >= this->rows)){
                    this->branch = false;
                }
                break;
            default:
                printf("unknown effect\n");
                break;
        }
        return false;
    }

    float Track::play(double t, Channel *chan) {
        t += this->time_offset;
        this->update_fx(t);
        double time_in_track = fmod(t, double(this->duration));
        uint_fast8_t row_index = floor(time_in_track / this->step);
        uint_fast8_t index = floor(row_index / this->rows);
        row_index =  row_index % this->rows;

        float s = 0.f;
        for(int_fast8_t i = this->getNumberofChannels()-1; i >= 0; --i){

            if(chan[i].isEnable()) {
                uint_fast8_t chan_number = chan[i].getNumber();
                uint_fast8_t pattern_index = *this->pattern_indices[chan_number * this->frames + index];
                Pattern* pat = this->track_patterns[chan_number * (this->frames) + pattern_index];
                Instruction* current_instruction = pat->instructions[row_index];
                if(current_instruction->effects != nullptr){
                    for(int_fast8_t fx_indx = this->fx_per_chan[chan_number] - 1; fx_indx >= 0; --fx_indx) {
                        if (current_instruction->effects[fx_indx] != nullptr) {
                            //printf("CHAN %d EFFECT %d : %x\n", chan_number, fx_indx,
                            //*current_instruction->effects[fx_indx]);
                            this->decode_fx(*current_instruction->effects[fx_indx], t);
                        }
                    }
                }
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
                        s +=  chan[i].getVolume()
                               * this->instruments_bank[chan[i].getInstructionState()->instrument_index]->play(
                                chan[i].getInstructionState()->volume,
                                (chan[i].getInstructionState()->key.note + this->pitch) + this->vibrato_val, chan[i].getInstructionState()->key.octave,
                                t - chan[i].getTime());
                    }else{
                        s +=   chan[i].getVolume()
                               * this->instruments_bank[chan[i].getInstructionState()->instrument_index]->play(
                                chan[i].getInstructionState()->volume,
                                (chan[i].getInstructionState()->key.note + this->pitch) + this->vibrato_val, chan[i].getInstructionState()->key.octave,
                                t - chan[i].getTime(), t - chan[i].getTimeRelease());
                    }
                }
            }
        }
        return this->volume * this->tremolo_val * s;
    }

    float* Track::play_(double t, Channel *chan) {
        //t += this->time_offset;
        this->update_fx(t);


        if(t- this->time_advance >= this->step){
            this->time_advance += this->step;
            ++this->row_counter;
            this->readFx = true;
            if(this->branch){
                this->row_counter = this->rowtojump;
                this->frame_counter = this->frametojump;
                this->branch = false;
            }
           // printf("row ++ \n");
        }

        if(this->row_counter >= this->rows){
            this->row_counter = 0;
            ++this->frame_counter;
            //printf("frame ++ \n");
        }
        if(this->frame_counter >= this->frames){
            this->frame_counter = 0;
            //printf("frame counter 0 \n");
        }

        float s = 0.f;
        for(int_fast8_t i = this->getNumberofChannels()-1; i >= 0; --i){
            if(chan[i].isEnable()) {
                uint_fast8_t chan_number = chan[i].getNumber();
                uint_fast8_t pattern_index = *this->pattern_indices[chan_number * this->frames + this->frame_counter];
                Pattern* pat = this->track_patterns[chan_number * (this->frames) + pattern_index];
                Instruction* current_instruction = pat->instructions[this->row_counter];

                if(current_instruction->effects != nullptr && this->readFx){
                    for(int_fast8_t fx_indx = this->fx_per_chan[chan_number] - 1; fx_indx >= 0; --fx_indx) {
                        if (current_instruction->effects[fx_indx] != nullptr) {
                            this->decode_fx(*current_instruction->effects[fx_indx], t);
                        }
                    }
                }

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
                        s +=  chan[i].getVolume()
                              * this->instruments_bank[chan[i].getInstructionState()->instrument_index]->play(
                                chan[i].getInstructionState()->volume,
                                (chan[i].getInstructionState()->key.note + this->pitch) + this->vibrato_val, chan[i].getInstructionState()->key.octave,
                                t - chan[i].getTime());
                    }else{
                        s +=   chan[i].getVolume()
                               * this->instruments_bank[chan[i].getInstructionState()->instrument_index]->play(
                                chan[i].getInstructionState()->volume,
                                (chan[i].getInstructionState()->key.note + this->pitch) + this->vibrato_val, chan[i].getInstructionState()->key.octave,
                                t - chan[i].getTime(), t - chan[i].getTimeRelease());
                    }
                }
            }
        }
        static float res[2];
        res[0] = this->volume * this->tremolo_val * s;
        res[1] = res[0];

        res[0] *= (1 - this->panning);//left
        res[1] *= this->panning;//right
        this->readFx = false;
        return res;
    }

    float Track::getPanning() {
        return this->panning;
    }


}
