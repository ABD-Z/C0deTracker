//
// Created by Abdulmajid, Olivier NASSER on 20/09/2020.
//
#include "custom_sdl2_stream.hpp"

bool C0deTrackerStream::init(C0deTracker::Track *t) {
    this->time = 0;
    printf("SAMPLE RATE = %u Hz\nBUFFER LENGTH = %f second\n", t->getConfig()->getSampleRate(),
           t->getConfig()->getBufferDuration());
    this->track = t;
    // Initialize the stream -- important!

    this->openAudioDevice();

    if (!this->device) {
        printf("Failed to open SDL2 audio %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void C0deTrackerStream::play() {
    if(!this->device) {
        this->openAudioDevice();
        if (!this->device) {
            printf("Failed to open SDL2 audio %s\n", SDL_GetError());
            return;
        }
    }

    SDL_PauseAudioDevice(device, 0);// unpause → start feeding audio
    this->playing = true;
}

void C0deTrackerStream::stop() {
    if (this->device) {
        SDL_CloseAudioDevice(this->device);
        this->time = 0;
        this->device = 0;
        this->playing = false;
    }
}

bool C0deTrackerStream::isPlaying() const {
    return this->playing;
}

void C0deTrackerStream::audioCallback(void *userdata, Uint8 *stream, int len) {
    auto *self = reinterpret_cast<C0deTrackerStream*>(userdata);
    std::lock_guard<std::mutex> lock(self->mutex);

    int16_t *buffer = reinterpret_cast<int16_t*>(stream);
    unsigned int samples = len / sizeof(int16_t);

    for(size_t i = 0; i < samples; i += self->track->getConfig()->getPanning()){

        float* sound = self->track->play(self->time + (double(i) / self->track->getConfig()->getPanning()) / self->track->getConfig()->getSampleRate());
        if(self->track->getConfig()->isStereo()) {
            buffer[i] = static_cast<int16_t>(sound[0] * BITS_16*0.5);
            buffer[i+1] = static_cast<int16_t>(sound[1] * BITS_16*0.5);
        } else {
            buffer[i] = static_cast<int16_t>((sound[0] + sound[1])/2 * BITS_16*0.5);
        }
    }

    self->time += self->track->getConfig()->getBufferDuration();
}

void C0deTrackerStream::changeTrack(C0deTracker::Track *t) {
    std::lock_guard<std::mutex> lock(this->mutex);
    this->track->resetState();
    this->time = 0;
    this->track = t;
}

bool C0deTrackerStream::saveWave(const std::string& filename, float loopcount) {
    if (!this->track) return false;

    unsigned int number_of_samples = loopcount * this->track->getConfig()->getSampleRate() * this->track->getDuration() * this->track->getConfig()->getPanning();

    std::vector<int16_t> samples;
    samples.reserve(number_of_samples);

    for (uint_fast64_t i = 0; i < number_of_samples; i += track->getConfig()->getPanning()) {
        float* sound = this->track->play((double(i)/this->track->getConfig()->getPanning() )/ this->track->getConfig()->getSampleRate());

        if(this->track->getConfig()->isStereo()) {
            samples.push_back(static_cast<int16_t>(sound[0] * BITS_16*0.5));
            samples.push_back(static_cast<int16_t>(sound[1] * BITS_16*0.5));
        } else {
            samples.push_back(static_cast<int16_t>((sound[0] + sound[1])/2 * BITS_16*0.5));
        }
    }

    // Open file
    std::ofstream out(filename, std::ios::binary);
    if (!out) {
        std::cerr << "Failed to open file for writing: " << filename.c_str() << "\n";
        return false;
    }

    uint32_t sampleRate = track->getConfig()->getSampleRate();
    uint16_t channels = track->getConfig()->getPanning();
    uint32_t dataSize = samples.size() * sizeof(int16_t);

    // --- WAV header ---
    out.write("RIFF", 4);
    uint32_t chunkSize = 36 + dataSize;
    out.write(reinterpret_cast<const char*>(&chunkSize), 4);
    out.write("WAVE", 4);

    out.write("fmt ", 4);
    uint32_t subchunk1Size = 16;
    uint16_t audioFormat = 1;
    uint16_t bitsPerSample = 16;
    uint32_t byteRate = track->getConfig()->getSampleRate() * track->getConfig()->getPanning() * bitsPerSample / 8;
    uint16_t blockAlign = track->getConfig()->getPanning() * bitsPerSample / 8;

    out.write(reinterpret_cast<const char*>(&subchunk1Size), 4);
    out.write(reinterpret_cast<const char*>(&audioFormat), 2);
    out.write(reinterpret_cast<const char*>(&channels), 2);
    out.write(reinterpret_cast<const char*>(&sampleRate), 4);
    out.write(reinterpret_cast<const char*>(&byteRate), 4);
    out.write(reinterpret_cast<const char*>(&blockAlign), 2);
    out.write(reinterpret_cast<const char*>(&bitsPerSample), 2);

    out.write("data", 4);
    out.write(reinterpret_cast<const char*>(&dataSize), 4);

    // Samples
    out.write(reinterpret_cast<const char*>(samples.data()), dataSize);

    return true;
}

C0deTrackerStream::~C0deTrackerStream() {
    if (this->device) {
        SDL_CloseAudioDevice(device);
        this->device = 0;
    }
}

void C0deTrackerStream::openAudioDevice() {
    SDL_AudioSpec want{}, have{};
    want.freq = this->track->getConfig()->getSampleRate();
    want.format = AUDIO_S16SYS;
    want.channels = this->track->getConfig()->getPanning();
    want.samples = this->track->getConfig()->getBufferSize() / this->track->getConfig()->getPanning();
    want.callback = C0deTrackerStream::audioCallback;
    want.userdata = this;

    this->device = SDL_OpenAudioDevice(nullptr, 0, &want, &have, 0);
}

