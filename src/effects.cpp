//
// Created by Abdulmajid, Olivier NASSER on 28/07/2024.
//

#include "c0de_tracker.hpp"
#define FX(f) fx_code == this->fx_codes[f]

namespace C0deTracker {
    float AbstractFX::getValue() {
        return this->val;
    }


    SlideFX::SlideFX(const float min, const float max, const float init_val) : MIN(min), MAX(max), INIT_VAL(init_val){this->val = init_val;}

    void SlideFX::process(const double t, const float clock, const float speed) {
        if (t - this->time_step >= 1./clock) {
            this->time_step += 1./clock;
            this->val += this->slide / speed;
            if (this->val <= this->MIN) {
                this->val = this->MIN;
            } else {
                if (this->val >= this->MAX) {
                    this->val = this->MAX;
                }
            }
        }
    }

    void SlideFX::reset() {
        this->val = this->INIT_VAL;
        this->slide = 0;
    }

    bool SlideFX::isActive() {
        return this->slide != 0;
    }


    SpeedDepthFX::SpeedDepthFX(const float min) : MIN(min) {this->val = min;}

    void SpeedDepthFX::process(const double t, const float clock, const float speed) {
        this->val = this->depth * sin(TWOPI * this->speed / speed * (t - this->start_time))
                + this->MIN * (1 - this->depth);
    }

    void SpeedDepthFX::reset() {
        this->val = this->MIN;
        this->speed = 0; this->depth = 0;
    }

    bool SpeedDepthFX::isActive() {
        return this->speed != 0 && this->depth != 0;
    }


    TransposeFX::TransposeFX(const float min, const float max, const float init_val) : SlideFX(min, max, init_val) {}

    void TransposeFX::process(const double t, const float clock, const float speed) {
        float v = this->val;
        SlideFX::process(t, clock/float(this->delay), 1);
        if (v != this->val)
            ++this->semitones_counter;
    }

    bool TransposeFX::isActive() {
        return this->semitones > 0 && this->repeat > 0 && this->semitones_counter < this->semitones;
    }


    PortamentoFX::PortamentoFX(const float min, const float max, const float init_val) : SlideFX(min, max, init_val) {}

    void PortamentoFX::reset() {
        this->sign = 0;
        SlideFX::reset();
    }

    float PortamentoFX::getValue() {
        return this->val * this->sign;
    }


    ArpeggioFX::ArpeggioFX(const float min, const float max, const float init_val) : SlideFX(min, max, init_val) {}

    void ArpeggioFX::process(const double t, const float clock, const float speed) {
        SlideFX::process(t, clock, speed);
        this->val = uint_fast8_t(this->val) % ArpeggioFX::SIZE;
    }

    float ArpeggioFX::getValue() {
        return this->tab[uint_fast8_t(this->val)];
    }


    void CountableRepeatableFX::process(const double t, const float clock, const float speed) {

        if(t - this->time_step >= double(this->delay) / clock){
            this->time_step += double(this->delay) / clock;
            ++this->counter;
        }
    }

    void CountableRepeatableFX::reset() {
        this->repeat = 0; this->counter = 0; this->delay = 0; this->number = 0;
    }

    bool CountableRepeatableFX::isActive() {
        return this->repeat > 0 && this->counter < this->number;
    }

    void RetriegFX::process(const double t, const float clock, const float speed) {
        uint_fast8_t c = this->counter;
        CountableRepeatableFX::process(t, clock, speed);
        if (this->counter > c)
            this->val = t;
    }
    bool RetriegFX::isActive() {
        return this->repeat > 0  && this->counter < this->number;
    }

    void DelayReleaseFX::process(const double t, const float clock, const float speed) {
        if (this->delay.isActive())
            this->delay.process(t, clock, speed);
        else if (this->release.isActive()) {
            this->release.process(t, clock, speed);
        }
    }

    void DelayReleaseFX::reset() {
        this->delay.reset(); this->release.reset();
    }

    bool DelayReleaseFX::isActive() {
        return this->delay.isActive() || this->release.isActive();
    }

    float DelayReleaseFX::getValue() {
        if (this->delay.isActive())
            return 1;
        if (this->release.isActive())
            return 2;
        else
            return 0;
    }

    GlobalFXs::GlobalFXs() {
        this->effects_table.push_back(&this->panning);
        this->effects_table.push_back(&this->volume);
        this->effects_table.push_back(&this->pitch);
        this->effects_table.push_back(&this->vibrato);
        this->effects_table.push_back(&this->tremolo);
    }

    bool GlobalFXs::decode_fx(const uint_fast32_t fx, const double t) {
        uint_fast8_t fx_code = fx >> 4 * 6;
        uint_fast32_t fx_val = fx & 0x00FFFFFF;
        if (FX(PITCH_SLIDE_UP)) {
            this->pitch.time_step = t;
            this->pitch.slide = float(fx_val) / float(0x001FFFFF);
            return true;
        }
        if (FX(PITCH_SLIDE_DOWN)) {
            this->pitch.time_step = t;
            this->pitch.slide = - float(fx_val) / float(0x00FFFFFF);
            return true;
        }
        if (FX(VIBRATO)) {
            this->vibrato.speed = float(fx_val >> 4 * 3) / float(0x00A);
            this->vibrato.depth = float(fx_val & 0xFFF) / float(0x00A);
            this->vibrato.start_time = t;
            if (this->vibrato.speed == 0 || this->vibrato.depth == 0) {
                this->vibrato.reset();
            }
            return true;
        }
        if (FX(SET_PITCH)) {
            this->pitch.val = (float(fx_val) - float(0x800000)) / float(0x800000);
            return true;
        }
        if (FX(SET_VOLUME)) {
            this->volume.val = float(fx_val) / float(0x00FFFFFF);
            return true;
        }
        if (FX(VOLUME_SLIDE_UP)) {
            this->volume.slide = float(fx_val) / float(0x00FFFFFF);
            this->volume.time_step = t;
            return true;
        }
        if (FX(VOLUME_SLIDE_DOWN)) {
            this->volume.slide = - float(fx_val) / float(0x00FFFFFF);
            this->volume.time_step = t;
            return true;
        }
        if (FX(TREMOLO)) {
            this->tremolo.speed = float(fx_val >> 4 * 3) / float(0x100);
            this->tremolo.depth = (float(fx_val & 0xFFF) / float(0xFFF)) * 0.5f;
            this->tremolo.start_time = t;
            if (this->tremolo.speed == 0 || this->tremolo.depth == 0) {
                this->tremolo.reset();
            }
            return true;
        }
        if (FX(SET_PANNING)) {
            this->panning.val = float(fx_val) / float(0xFFFFFF);
            return true;
        }
        if (FX(PANNING_SLIDE_RIGHT)) {
            this->panning.slide = float(fx_val) / float(0xFFFFFF);
            this->panning.time_step = t;
            return true;
        }
        if (FX(PANNING_SLIDE_LEFT)) {
            this->panning.slide = - float(fx_val) / float(0xFFFFFF);
            this->panning.time_step = t;
            return true;
        }
        return false;
    }

    void GlobalFXs::update_fx(const double t, const float clock, const float speed) {
        for (AbstractFX* fx : this->effects_table) {
            if(fx->isActive())
                fx->process(t, clock, speed);
        }
    }

    void GlobalFXs::reset_fxs() {
        for (AbstractFX* fx : this->effects_table) {
            fx->reset();
        }
    }


     ChannelFXs::ChannelFXs() : GlobalFXs(){
        for(uint_fast8_t & fx_code : this->fx_codes) {
            fx_code += 0x10;
        }
        this->fx_codes.push_back(0x1A); // Transpose
        this->effects_table.push_back(&this->transpose);

        this->fx_codes.push_back(0x1B); // Portamento
        this->effects_table.push_back(&this->portamento);

        this->fx_codes.push_back(0x19); // Arpeggio
        this->effects_table.push_back(&this->arpeggio);

        this->fx_codes.push_back(0x1C); // Retrieg
        this->effects_table.push_back(&this->retrieg);

        this->fx_codes.push_back(0x1F); // Delay Release
        this->effects_table.push_back(&this->delay_release);

    }

    bool ChannelFXs::decode_fx(const uint_fast32_t fx, const double t) {
        uint_fast8_t fx_code = fx >> 4 * 6;
        uint_fast32_t fx_val = fx & 0x00FFFFFF;

        if (FX(TRANSPOSE)) {
            this->transpose.semitones = (fx_val & 0xFF00) >> 4 * 2;
            this->transpose.repeat = (fx_val & 0xFF);
            this->transpose.time_step = t;
            this->transpose.semitones_counter = 0;
            uint_fast8_t td = (fx_val >> 4 * 4);
            if (td > 0x7F) { // transpose up
                this->transpose.slide = 1;
                this->transpose.delay = td - 0x80;
            } else { // transpose down
                this->transpose.slide = -1;
                this->transpose.delay = td;
            }
            return true;
        }
        if (FX(PORTAMENTO)) {
            this->portamento.slide = - float(fx_val)/float(0x800000);
            this->portamento.time_step = t;
            if (this->portamento.slide == 0)
                this->portamento.val = 0;
            return true;
        }
        if (FX(ARPEGGIO)) {
            this->arpeggio.time_step = t;
            this->arpeggio.tab[0] = fx_val >> 4 * 5;
            this->arpeggio.tab[1] = (fx_val >> 4 * 4) & 0xF;
            this->arpeggio.tab[2] = (fx_val >> 4 * 3) & 0xF;
            this->arpeggio.tab[3] = (fx_val >> 4 * 2) & 0xF;
            this->arpeggio.tab[4] = (fx_val >> 4 * 1) & 0xF;
            this->arpeggio.tab[5] = fx_val & 0xF;
            if ( this->arpeggio.tab[0] == 0 && this->arpeggio.tab[1] == 0
              && this->arpeggio.tab[2] == 0 && this->arpeggio.tab[3] == 0
              && this->arpeggio.tab[4] == 0 && this->arpeggio.tab[5] == 0){
                this->arpeggio.slide = 0;
            } else {
                this->arpeggio.slide = 1;
            }
            return true;
        }
        if (FX(RETRIEG)) {
            this->retrieg.delay = (fx_val >> 4 * 4);
            this->retrieg.number = (fx_val & 0xFF00) >> 4 * 2;
            this->retrieg.repeat = (fx_val & 0xFF);
            this->retrieg.time_step = t;
            return true;
        }
        if (FX(DELAY_RELEASE)) {
            this->delay_release.delay.delay = (fx_val >> 4 * 4);
            this->delay_release.delay.time_step = t;
            if(this->delay_release.delay.delay > 0) {
                this->delay_release.delay.number = 1;
                this->delay_release.delay.repeat = (fx_val & 0xFF);
            } else {
                this->delay_release.delay.number = 0;
                this->delay_release.delay.repeat = 0;
            }

            this->delay_release.release.delay = (fx_val & 0xFF00) >> 4 * 2;
            this->delay_release.release.time_step = t;

            if (this->delay_release.release.delay > 0) {
                this->delay_release.release.number = 1;
                this->delay_release.release.repeat = (fx_val & 0xFF);
            } else {
                this->delay_release.release.number = 0;
                this->delay_release.release.repeat = 0;
            }
        }
        return GlobalFXs::decode_fx(fx, t);
    }
}