//
// Created by Abdulmajid, Olivier NASSER on 06/01/2026.
//
#ifndef CODETRACKER_CUSTOM_FMOD_STREAM_HPP
#define CODETRACKER_CUSTOM_FMOD_STREAM_HPP

#include <fmod.hpp>
#include <fmod_dsp.h>
#include <fmod_errors.h>
#include "../../include/c0de_tracker.hpp"
#include <mutex>
#include <iostream>
#include <chrono>
#include <fstream>
#include <atomic>
#include <vector>

#define BITS_16 0xFFFF

class C0deTrackerStream {
public:
    bool init(C0deTracker::Track *t);
    void play();
    void stop();
    bool isPlaying() const;
    void changeTrack(C0deTracker::Track *t);
    void setPosition(double time);
    ~C0deTrackerStream();

    static bool saveWave(C0deTracker::Track* tracker, C0deTracker::Track_Data* data, const std::string& filename, float loopcount=1);

private:
    double time = 0;
    FMOD::System* system = nullptr;
    FMOD::DSP* dsp = nullptr;
    FMOD::Channel *channel = nullptr;
    C0deTracker::Track *track = nullptr;
    std::mutex mutex;

    std::atomic<bool> playing{false};

    bool ongetData(float* samples, unsigned int sampleCount);
    void onSeek(double time);

    static FMOD_RESULT F_CALL DSPRead(FMOD_DSP_STATE* dsp_state, float* inbuffer, float* outbuffer, unsigned int length,
                                      int inchannels, int* outchannels);
    static FMOD_RESULT F_CALL DSPSeek(FMOD_DSP_STATE* dsp_state, unsigned int pos);
};

#endif //CODETRACKER_CUSTOM_FMOD_STREAM_HPP
