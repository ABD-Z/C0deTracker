//
// Created by Abdulmajid, Olivier NASSER on 30/09/2025.
//
#ifndef CODETRACKER_CUSTOM_SDL2_STREAM_HPP
#define CODETRACKER_CUSTOM_SDL2_STREAM_HPP

#include <SDL.h>
#include <mutex>
#include "../../include/c0de_tracker.hpp"
#include <iostream>
#include <chrono>
#include <fstream>
#include <atomic>
#include <thread>

#define BITS_16 0xFFFF

class C0deTrackerStream {
public:
    bool init(C0deTracker::Track *t);
    void play();
    void stop();
    bool isPlaying() const;
    void changeTrack(C0deTracker::Track *t);
    bool saveWave(const std::string& filename, float loopcount=1);
    ~C0deTrackerStream();

private:
    double time = 0;
    C0deTracker::Track *track = nullptr;
    std::mutex mutex;
    int16_t* smpls;

    std::thread sampler_thread;
    SDL_AudioDeviceID device = 0;
    std::atomic<bool> playing{false};

    bool ongetData(int16_t* samples, std::size_t sampleCount);

    void openAudioDevice();
    void samplerLoop();


};
#endif //CODETRACKER_CUSTOM_SDL2_STREAM_HPP
