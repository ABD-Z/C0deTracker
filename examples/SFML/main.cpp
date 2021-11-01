#include "custom_sfml_stream.hpp"
#include <vector>
#include <thread>
#include <chrono>

#include "../songs/tutorial.hpp"//include your song
#define FILENAME "tutotrack.wav"

int main() {
    auto t1 = std::chrono::system_clock::now();

    C0deTracker::Track* track = new TutoTrack();
    track->init();
    /*chans[0].disable();
   chans[1].disable();
    chans[2].disable();
   chans[3].disable();
   chans[4].disable();
   chans[5].disable();
  chans[6].disable();
   chans[7].disable();*/


    auto t2 = std::chrono::system_clock::now();

    double deltaT = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

    std::cout << "Time for track creation = " << deltaT << " ms" << std::endl;

    //Method to play sound in real time with the custom stream
    C0deTrackerStream cts;
    cts.init(track);
    cts.play();


    while(cts.getStatus() == sf::SoundSource::Status::Playing){
        std::this_thread::sleep_for(std::chrono::seconds (1000000));//sleep to reduce CPU usage
    }
    /************************************************************/

    //Method to save in a file the song. Comment previous method to save song in file.
    sf::SoundBuffer buffer;
    std::vector<sf::Int16> samples;
    std::cout << "Begin sampling" << std::endl;

    float duration_in_sec = 4.f*2;
    float number_of_samples = SAMPLE_RATE * duration_in_sec * PANNING;
    samples.reserve(number_of_samples);

    for (uint_fast64_t i = 0; i < number_of_samples; ++++i) {
        float* s = track->play(0.5 * double(i) / SAMPLE_RATE);
        samples.push_back((s[0]) * BITS_16*0.5);//left speaker
        samples.push_back((s[1]) * BITS_16*0.5);//right speaker
    }

    buffer.loadFromSamples(&samples[0], samples.size(), PANNING, SAMPLE_RATE);
    buffer.saveToFile(FILENAME);
    std::cout << "End sampling" << std::endl;


    delete track;


    return 0;
}