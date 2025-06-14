//
// Created by Abdulmajid, Olivier NASSER on 20/09/2020.
//
#include "custom_sfml_stream.hpp"

#define BITS_16 0xFFFF

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
    float* sound;
    // Fill the chunk with audio data from the stream source
    // (note: must not be empty if you want to continue playing)
    //std::chrono::time_point t1 = std::chrono::system_clock::now();
    for(size_t i = 0; i < this->track->getConfig()->getBufferSize(); i += this->track->getConfig()->getPanning()){

        if(this->track->getConfig()->isStereo()) {
            sound = track->play(this->time + (double(i) * 0.5) / this->track->getConfig()->getSampleRate());
            this->smpls[i] = sound[0] * BITS_16*0.5;
            this->smpls[i+1] = sound[1] * BITS_16*0.5;
        } else {
            sound = track->play(this->time + double(i) / this->track->getConfig()->getSampleRate());
            this->smpls[i] = (sound[0] + sound[1])/2 * BITS_16*0.5;
        }
    }
    data.samples = this->smpls;
    data.sampleCount = this->track->getConfig()->getBufferSize();
    this->time += this->track->getConfig()->getBufferDuration();
    //std::chrono::time_point t2 = std::chrono::system_clock::now();

    //double deltaT = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    //std::cout << "CALC buffer time = " << deltaT << " ms" << std::endl;

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

C0deTrackerStream::~C0deTrackerStream() {
    delete this->smpls;
}


