//
// Created by Abdulmajid, Olivier NASSER on 20/09/2020.
//
#ifndef CODETRACKER_CUSTOM_SDL2_STREAM_HPP
#define CODETRACKER_CUSTOM_SDL2_STREAM_HPP

#include <SDL.h>
#include <mutex>
#include "../../include/c0de_tracker.hpp"
#include <iostream>
#include <chrono>
#include <fstream>

#define BITS_16 0xFFFF

class C0deTrackerStream {
public:
    double time = 0;
    bool init(C0deTracker::Track *t);
    void play();
    void stop();
    bool isPlaying() const;
    void changeTrack(C0deTracker::Track *t);
    bool saveWave(const std::string& filename, float loopcount=1);
    ~C0deTrackerStream();

private:
    C0deTracker::Track *track = nullptr;
    std::mutex mutex;
    SDL_AudioDeviceID device = 0;
    bool playing = false;
    void openAudioDevice();
    // SDL audio callback
    static void audioCallback(void *userdata, Uint8 *stream, int len);

};
#endif //CODETRACKER_CUSTOM_SDL2_STREAM_HPP
