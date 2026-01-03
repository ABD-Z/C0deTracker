//
// Created by Abdulmajid, Olivier NASSER on 13/09/2025.
//
#include "custom_sdl2_stream.hpp"

bool C0deTrackerStream::init(C0deTracker::Track *t) {
    this->time = 0;
    printf("SAMPLE RATE = %u Hz\nBUFFER LENGTH = %f second\n", t->getConfig()->getSampleRate(),
           t->getConfig()->getBufferDuration());
    this->track = t;

    this->openAudioDevice();

    if (!this->device) {
        printf("Failed to open SDL2 audio %s\n", SDL_GetError());
        return false;
    }

    this->smpls = new int16_t [this->track->getConfig()->getBufferSize()]{0};

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
    this->playing.store(true);

    if (!this->sampler_thread.joinable())
        this->sampler_thread = std::thread(&C0deTrackerStream::samplerLoop, this);
}

void C0deTrackerStream::stop() {
    if (this->device) {
        this->playing.store(false);
        if (this->sampler_thread.joinable())
                this->sampler_thread.join();

        SDL_ClearQueuedAudio(this->device);
        SDL_CloseAudioDevice(this->device);
        this->time = 0;
        this->device = 0;
    }
}

bool C0deTrackerStream::isPlaying() const {
    return this->playing.load();
}

void C0deTrackerStream::changeTrack(C0deTracker::Track *t) {
    std::lock_guard<std::mutex> lock(this->mutex);
    this->stop();
    this->track->resetState();
    this->time = 0;
    this->track = t;
}

void C0deTrackerStream::openAudioDevice() {
    SDL_AudioSpec want{}, have{};
    want.freq = this->track->getConfig()->getSampleRate();
    want.format = AUDIO_S16SYS;
    want.channels = this->track->getConfig()->getPanning();
    want.samples = this->track->getConfig()->getBufferSize() / this->track->getConfig()->getPanning();
    want.callback = nullptr;
    //want.userdata = this;

    this->device = SDL_OpenAudioDevice(nullptr, 0, &want, &have, 0);
}

bool C0deTrackerStream::ongetData(int16_t *samples, std::size_t sampleCount) {
    std::lock_guard<std::mutex> lock(this->mutex);

    for (size_t i = 0; i < sampleCount; i += this->track->getConfig()->getPanning()) {
        float* sound = this->track->play(this->time + (double(i)/this->track->getConfig()->getPanning()) / this->track->getConfig()->getSampleRate());

        if (this->track->getConfig()->isStereo()) {
            samples[i]     = static_cast<int16_t>(sound[0] * BITS_16 * 0.5);
            samples[i + 1] = static_cast<int16_t>(sound[1] * BITS_16 * 0.5);
        } else {
            samples[i] = static_cast<int16_t>((sound[0] + sound[1]) * 0.5 * BITS_16 * 0.5);
        }
    }

    this->time += this->track->getConfig()->getBufferDuration();
    return true;
}

void C0deTrackerStream::samplerLoop() {
    while (this->playing.load()) {
        Uint32 queued = SDL_GetQueuedAudioSize(device);

        if (queued < this->track->getConfig()->getBufferSize() * sizeof(int16_t)) {
            this->ongetData(this->smpls, this->track->getConfig()->getBufferSize());

            SDL_QueueAudio(device,
                           this->smpls,
                           this->track->getConfig()->getBufferSize() * sizeof(int16_t));
        } else {
            SDL_Delay(1);
        }
    }
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
    this->stop();
    delete this->smpls;
}