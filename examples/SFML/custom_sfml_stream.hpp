//
// Created by Abdulmajid, Olivier NASSER on 20/09/2020.
//
#include <SFML/Audio.hpp>
#include <SFML/System/Lock.hpp>
#include <SFML/System/Mutex.hpp>
#include "../../include/c0de_tracker.hpp"
#include <iostream>
#include <chrono>

#ifndef CODETRACKER_CUSTOM_SFML_STREAM_HPP
#define CODETRACKER_CUSTOM_SFML_STREAM_HPP
#define SAMPLE_RATE 48000.
#define BUFFER_LENGTH_S 0.5
#define PANNING 2
#define BITS_16 0xFFFF
class C0deTrackerStream : public sf::SoundStream {
public:
    double time = 0;
    bool init(C0deTracker::Track *t);

private:
    C0deTracker::Track *track = nullptr;
    sf::Mutex mutex;
    std::vector <sf::Int16> samples;
    sf::Int16 smpls[static_cast<int>(SAMPLE_RATE * BUFFER_LENGTH_S * PANNING)]{0};

    bool onGetData(Chunk &data) override;

    void onSeek(sf::Time timeOffset) override;
};
#endif //CODETRACKER_CUSTOM_SFML_STREAM_HPP
