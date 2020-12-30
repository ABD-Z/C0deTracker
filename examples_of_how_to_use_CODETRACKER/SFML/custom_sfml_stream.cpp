//
// Created by Abdulmajid, Olivier NASSER on 20/09/2020.
//
#include "custom_sfml_stream.hpp"

bool C0deTrackerStream::init(C0deTracker::Track *t, C0deTracker::Channel *c, uint_fast8_t  size_of_c) {
    printf("SAMPLE RATE = %f Hz\nBUFFER LENGTH = %f second\n", SAMPLE_RATE, BUFFER_LENGTH_S);
    this->track = t; this->chans = c; this->size_of_chans = size_of_c;
    // Initialize the stream -- important!
    sf::SoundStream::initialize(PANNING, SAMPLE_RATE);
    return true;
}

bool C0deTrackerStream::onGetData(sf::SoundStream::Chunk &data) {
    sf::Lock lock(this->mutex);
    float* sound;
    // Fill the chunk with audio data from the stream source
    // (note: must not be empty if you want to continue playing)
    std::chrono::time_point t1 = std::chrono::system_clock::now();
    for(int i = 0; i < SAMPLE_RATE * BUFFER_LENGTH_S * PANNING; ++++i){
        sound = track->play(this->time + (double(i) / 2) / SAMPLE_RATE, this->chans, this->size_of_chans);
        this->smpls[i] = sound[0] * BITS_16*0.5;
        this->smpls[i+1] = sound[1] * BITS_16*0.5;
    }
    data.samples = this->smpls;
    data.sampleCount = SAMPLE_RATE * BUFFER_LENGTH_S * PANNING;
    this->time += BUFFER_LENGTH_S;
    std::chrono::time_point t2 = std::chrono::system_clock::now();

    double deltaT = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    //std::cout << "CALC buffer time = " << deltaT << " ms" << std::endl;

    // Return true to continue playing
    return true;
}

void C0deTrackerStream::onSeek(sf::Time timeOffset) {
    sf::Lock lock(this->mutex);
    this->time = timeOffset.asSeconds();
    // Change the current position in the stream source
}


