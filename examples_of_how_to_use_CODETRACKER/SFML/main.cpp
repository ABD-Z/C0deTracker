#include "custom_sfml_stream.hpp"
#include <vector>
#include <thread>

#include "../../songs/examples.hpp"//include your song
#include "../../songs/tutorial.hpp"//include your song

int main() {
#define SONG fzero_intro
    std::chrono::time_point t1 = std::chrono::system_clock::now();

    C0deTracker::Channel* chans;//declare a pointer of channels
    uint_fast8_t  size_of_chans = SONG::CHANNELS; //get the number of channel needed of the song
    chans = new C0deTracker::Channel[size_of_chans];//allocate channels
     //chans[0].disable();
     //chans[1].disable();
     //chans[2].disable();
    //chans[3].disable();
    //chans[4].disable();
    //chans[5].disable();
    //chans[6].disable();
    //chans[7].disable();
    C0deTracker::Track* track = SONG::init_track();//initialise the track

    std::chrono::time_point t2 = std::chrono::system_clock::now();

    double deltaT = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

    std::cout << "Time for track creation = " << deltaT << " ms" << std::endl;

    //Method to play sound in real time with the custom stream
    C0deTrackerStream cts;
    cts.init(track, chans, size_of_chans);
    cts.play();

    while(cts.getStatus() == sf::SoundSource::Status::Playing){
        std::this_thread::sleep_for(std::chrono::seconds (10));//sleep to reduce CPU usage
    }
    /************************************************************/

    //Method to save in a file the song. Comment previous method to save song in file.
    sf::SoundBuffer buffer;
    std::vector<sf::Int16> samples;
    std::cout << "Begin sampling" << std::endl;

    float duration_in_sec = 30.f;
    float number_of_samples = SAMPLE_RATE * duration_in_sec * PANNING;
    samples.reserve(number_of_samples);

    for (uint_fast64_t i = 0; i < number_of_samples; ++++i) {
        float* s = track->play(0.5 * double(i) / SAMPLE_RATE, chans, size_of_chans);
        samples.push_back((s[0]) * BITS_16*0.5);//left speaker
        samples.push_back((s[1]) * BITS_16*0.5);//right speaker
    }

    buffer.loadFromSamples(&samples[0], samples.size(), PANNING, SAMPLE_RATE);
    buffer.saveToFile("fzero.wav");
    std::cout << "End sampling" << std::endl;


    delete track;
    delete[] chans;

    return 0;
}