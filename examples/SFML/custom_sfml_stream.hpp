//
// Created by Abdulmajid, Olivier NASSER on 20/09/2020.
//
#ifndef CODETRACKER_CUSTOM_SFML_STREAM_HPP
#define CODETRACKER_CUSTOM_SFML_STREAM_HPP

#include <SFML/Audio.hpp>
#include <SFML/System/Lock.hpp>
#include <SFML/System/Mutex.hpp>
#include "../../include/c0de_tracker.hpp"
#include <iostream>
#include <chrono>

#define BITS_16 0xFFFF

class C0deTrackerStream : public sf::SoundStream {
public:
    bool init(C0deTracker::Track *t);
    void changeTrack(C0deTracker::Track *t);
    bool isPlaying();
    static bool saveWave(C0deTracker::Track* tracker, C0deTracker::Track_Data* data, const std::string& filename, float loopcount=1);
    ~C0deTrackerStream() override;

private:
    double time = 0;
    C0deTracker::Track *track = nullptr;
    sf::Mutex mutex;
    sf::Int16* smpls;

    bool onGetData(Chunk &data) override;
    void onSeek(sf::Time timeOffset) override;
};
#endif //CODETRACKER_CUSTOM_SFML_STREAM_HPP
