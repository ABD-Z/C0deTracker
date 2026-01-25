//
// Created by Abdulmajid, Olivier NASSER on 06/01/2026.
//
#include "custom_fmod_stream.hpp"

#define ERRCHECK(result) if ((result) != FMOD_OK) { printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result)); exit(-1);}

bool C0deTrackerStream::init(C0deTracker::Track *t) {
    this->time = 0;
    printf("SAMPLE RATE = %u Hz\nBUFFER LENGTH = %f second\n", t->getConfig()->getSampleRate(),
           t->getConfig()->getBufferDuration());
    this->track = t;

    FMOD_RESULT r;
    r = FMOD::System_Create(&this->system);
    ERRCHECK(r);

    r = this->system->setSoftwareFormat(
            this->track->getConfig()->getSampleRate(),
            (this->track->getConfig()->isStereo()) ? FMOD_SPEAKERMODE_STEREO : FMOD_SPEAKERMODE_MONO,
            0);
    ERRCHECK(r);

    r = this->system->setDSPBufferSize(this->track->getConfig()->getBufferSize()/this->track->getConfig()->getPanning(),
                                       4);
    ERRCHECK(r);

    r = this->system->init(1, FMOD_INIT_NORMAL, nullptr);
    ERRCHECK(r);

    //create desc of dsp
    FMOD_DSP_DESCRIPTION desc{};
    desc.numinputbuffers = 0;
    desc.numoutputbuffers = 1;
    desc.read = &C0deTrackerStream::DSPRead;
    //desc.setposition = onSeek;
    desc.userdata = this;
    std::snprintf(desc.name, sizeof(desc.name), "RealTimeC0deTrackerDSP");
    r = this->system->createDSP(&desc, &dsp);
    ERRCHECK(r);

    r = this->dsp->setChannelFormat(FMOD_CHANNELMASK_STEREO, this->track->getConfig()->isStereo() ? 2 : 1, FMOD_SPEAKERMODE_STEREO);
    ERRCHECK(r);

    r = this->system->playDSP(this->dsp, nullptr, true, &this->channel);
    ERRCHECK(r);

    r = this->dsp->setActive(false);
    ERRCHECK(r);

    return true;
}

void C0deTrackerStream::play() {
    FMOD_RESULT r;
    r = this->dsp->setActive(true);
    ERRCHECK(r);

    r = this->channel->setPaused(false);
    ERRCHECK(r);

    this->playing.store(true);
}

void C0deTrackerStream::stop() {
    FMOD_RESULT r;
    std::lock_guard<std::mutex> lock(this->mutex);
    this->time = 0;
    r = this->dsp->setActive(false);
    ERRCHECK(r);

    r = this->channel->setPaused(true);
    ERRCHECK(r);

    this->playing.store(false);
}

bool C0deTrackerStream::isPlaying() const {
    return this->playing.load();
}

void C0deTrackerStream::changeTrack(C0deTracker::Track *t) {
    this->stop();
    this->track->resetState();
    this->time = 0;
    this->track = t;
}

bool C0deTrackerStream::ongetData(float *samples, unsigned int sampleCount) {
    std::lock_guard<std::mutex> lock(this->mutex);

    for (size_t i = 0; i < sampleCount; i+=1) {
        float* sound = this->track->play(this->time + double(i) / this->track->getConfig()->getSampleRate());

        if (this->track->getConfig()->isStereo()) {
            samples[i * 2 + 0] = (sound[0] * 0.5);
            samples[i * 2 + 1] = (sound[1] * 0.5);
        } else {
            samples[i] = ((sound[0] + sound[1]) * 0.5 * 0.5);
        }
    }

    this->time += this->track->getConfig()->getBufferDuration();
    return true;
}

C0deTrackerStream::~C0deTrackerStream() {
    FMOD_RESULT r;
    this->stop();
    r = this->dsp->release();
    ERRCHECK(r);
    r = this->system->release();
    ERRCHECK(r);
}

FMOD_RESULT F_CALL C0deTrackerStream::DSPRead(
        FMOD_DSP_STATE* dsp_state, float* inbuffer, float* outbuffer,
unsigned int length, int inchannels, int* outchannels
) {
    void* ptr = nullptr;
    FMOD_RESULT  r = FMOD_DSP_GETUSERDATA(dsp_state, &ptr);
    ERRCHECK(r);
    auto* self = static_cast<C0deTrackerStream*>(ptr);
    self->ongetData(outbuffer, length);
    return FMOD_OK;
}

bool C0deTrackerStream::saveWave(C0deTracker::Track* tracker, C0deTracker::Track_Data* data, const std::string& filename, float loopcount) {
    if(!data->is_data_loaded())
        data->load_data();

    tracker->changeTrack(data);

    FMOD_RESULT r;

    FMOD::System* s = nullptr;
    r = FMOD::System_Create(&s); ERRCHECK(r);

    r = s->setSoftwareFormat(tracker->getConfig()->getSampleRate(),
            (tracker->getConfig()->isStereo()) ? FMOD_SPEAKERMODE_STEREO : FMOD_SPEAKERMODE_MONO,
            2);
    ERRCHECK(r);

    r = s->setOutput(FMOD_OUTPUTTYPE_WAVWRITER_NRT); // playing is redirected to write wave file
    ERRCHECK(r);

    s->init(1, FMOD_INIT_NORMAL, (void *) filename.c_str());
    ERRCHECK(r);

    FMOD::Sound *sound;
    FMOD_CREATESOUNDEXINFO exinfo;

    memset(&exinfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
    exinfo.cbsize           = sizeof(FMOD_CREATESOUNDEXINFO);
    exinfo.numchannels      = tracker->getConfig()->getPanning();
    exinfo.defaultfrequency = tracker->getConfig()->getSampleRate();
    exinfo.length           = exinfo.defaultfrequency * exinfo.numchannels * sizeof(signed short)
                              * tracker->getDuration() * loopcount;   // Length of sound - PCM data in bytes.
    exinfo.format           = FMOD_SOUND_FORMAT_PCM16;          // Data format of sound

    r = s->createSound(nullptr, FMOD_OPENUSER | FMOD_LOOP_OFF, &exinfo, &sound);
    ERRCHECK(r);

    void* ptr1 = nullptr; void* ptr2 = nullptr;
    unsigned int len1 = 0; unsigned int len2 = 0;

    r = sound->lock(0, exinfo.length, &ptr1, &ptr2, &len1, &len2);
    ERRCHECK(r);

    auto* out = static_cast<int16_t*>(ptr1);
    for (size_t i = 0; i < (len1 / sizeof (int16_t)) ; i+=exinfo.numchannels) {
        float *sample = tracker->play((double(i) / exinfo.numchannels) / tracker->getConfig()->getSampleRate());

        if (tracker->getConfig()->isStereo()) {
            out[i + 0] = sample[0] * BITS_16 * 0.5;
            out[i + 1] = sample[1] * BITS_16 * 0.5;
        } else {
            out[i] =  ((sample[0] + sample[1]) * 0.5 * BITS_16 * 0.5);
        }
    }

    r = sound->unlock(ptr1, ptr2, len1, len2);
    ERRCHECK(r);

    FMOD::Channel* c = nullptr;
    r = s->playSound(sound, nullptr, false, &c); // playing sound -> writing it in wav file
    ERRCHECK(r);

    // rendering audio
    bool playing = true;
    while (playing) {
        ERRCHECK(s->update());
        ERRCHECK(c->isPlaying(&playing));
    }

    r = sound->release();
    ERRCHECK(r);
    r = s->release();
    ERRCHECK(r);
    data->free_data();

    return true;
}