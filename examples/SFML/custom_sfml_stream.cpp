//
// Created by Abdulmajid, Olivier NASSER on 20/09/2020.
//
#include "custom_sfml_stream.hpp"

bool C0deTrackerStream::init(C0deTracker::Track *t) {
    this->time = 0;
    printf("SAMPLE RATE = %u Hz\nBUFFER LENGTH = %f second\n", t->getConfig()->getSampleRate(),
           t->getConfig()->getBufferDuration());
    this->track = t;
    // Initialize the stream -- important!
    this->smpls = new sf::Int16 [this->track->getConfig()->getBufferSize()]{0};
    sf::SoundStream::initialize(this->track->getConfig()->getPanning(), t->getConfig()->getSampleRate());
    return true;
}

bool C0deTrackerStream::onGetData(sf::SoundStream::Chunk &data) {
    sf::Lock lock(this->mutex);
    // Fill the chunk with audio data from the stream source
    // (note: must not be empty if you want to continue playing)
    //std::chrono::time_point t1 = std::chrono::system_clock::now();
    for(size_t i = 0; i < this->track->getConfig()->getBufferSize(); i += this->track->getConfig()->getPanning()){
        float* sound = this->track->play(this->time + (double(i)/this->track->getConfig()->getPanning()) / this->track->getConfig()->getSampleRate());

        if(this->track->getConfig()->isStereo()) {
            this->smpls[i] = sound[0] * BITS_16*0.5;
            this->smpls[i+1] = sound[1] * BITS_16*0.5;
        } else {
            this->smpls[i] = (sound[0] + sound[1])/2 * BITS_16*0.5;
        }
    }
    data.samples = this->smpls;
    data.sampleCount = this->track->getConfig()->getBufferSize();
    this->time += this->track->getConfig()->getBufferDuration();

    // Return true to continue playing
    return true;
}

void C0deTrackerStream::onSeek(sf::Time timeOffset) {
    sf::Lock lock(this->mutex);
    this->time = timeOffset.asSeconds();
    // Change the current position in the stream source
}

void C0deTrackerStream::changeTrack(C0deTracker::Track *t) {
    sf::Lock lock(this->mutex);
    this->track->resetState();
    this->stop();
    this->time = 0;
    this->track = t;
}

bool C0deTrackerStream::saveWave(const std::string& filename, float loopcount) {
    if (!this->track) return false;

    sf::SoundBuffer buffer;
    std::vector<sf::Int16> samples;

    unsigned int number_of_samples = loopcount * this->track->getConfig()->getSampleRate() * this->track->getDuration() * this->track->getConfig()->getPanning();
    samples.reserve(number_of_samples);

    for (uint_fast64_t i = 0; i < number_of_samples; i += this->track->getConfig()->getPanning()) {
        float* sound = this->track->play((double(i)/this->track->getConfig()->getPanning()) / this->track->getConfig()->getSampleRate());


        if(this->track->getConfig()->isStereo()) {
            samples.push_back(sound[0] * BITS_16*0.5);
            samples.push_back(sound[1] * BITS_16*0.5);
        } else {
            samples.push_back((sound[0] + sound[1])/2 * BITS_16*0.5);
        }
    }

    buffer.loadFromSamples(&samples[0], samples.size(), this->track->getConfig()->getPanning(), this->track->getConfig()->getSampleRate());
    buffer.saveToFile(filename);

    return true;


}

C0deTrackerStream::~C0deTrackerStream() {
    delete this->smpls;
}


