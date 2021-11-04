#include "custom_sfml_stream.hpp"
#include <cstdlib>
#include <thread>
#include <chrono>

#include "../songs/tutorial.hpp"//include your song
#include "../songs/examples.hpp"

#define REALTIME
#define TIME_RECORDING_SECONDS 5
#define NUMBER_OF_TRACKS 7

void clear_console(){
#ifdef __linux__
    system("clear");
#elif _WIN32
    system("cls");
#else

#endif

}

int main() {
    auto time1 = std::chrono::system_clock::now();
    int index = 0;
    C0deTracker::Track* t0 = new TutoTrack();
    C0deTracker::Track* t1 = new SuperStreetFighterII_CreditTheme();
    C0deTracker::Track* t2 = new FrereJacques();
    C0deTracker::Track* t3 = new FZERO_MenuTheme();
    C0deTracker::Track* t4 = new SuperMarioBros_OverworldTheme();
    C0deTracker::Track* t5 = new KirbysDreamland_GreenGreensTheme();
    C0deTracker::Track* t6 = new Sonic_GreenHillZoneTheme();

    C0deTracker::Track* tracks[] = {t0,t1,t2,t3,t4,t5,t6};
    for(auto* tr : tracks){
        tr->init();
    }
    C0deTracker::Track* track;
    track = tracks[index];

    auto time2 = std::chrono::system_clock::now();

    double deltaT = std::chrono::duration_cast<std::chrono::milliseconds>(time2 - time1).count();

    std::cout << "Time for  tracks creation = " << deltaT << " ms" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds (2));
    clear_console();

    //Method to play sound in real time with the custom stream
#ifdef REALTIME
    C0deTrackerStream cts;
    cts.init(tracks[index]);
    cts.play();
    clear_console();

    while(cts.getStatus() == sf::SoundSource::Status::Playing){
        int select = index;
        std::cout<<""<<std::endl;std::cout<<""<<std::endl;std::cout<<""<<std::endl;
        for(uint8_t i = 0; i<NUMBER_OF_TRACKS; ++i){
            std::cout << "\t\t";
            if(i == index){
                std::cout << " * ";
            }else{
                std::cout << " " << +i <<". ";
            }
            std::cout << tracks[i]->getName() << std::endl;
        }
        std::cout << "Select track number : ";
        std::cin >> select;
        if(select != index  && +NUMBER_OF_TRACKS - +select > 0){
            index = select;
            std::cout << " Track selected " << tracks[index]->getName() << std::endl;
            cts.changeTrack(tracks[index]);
            cts.play();
            std::this_thread::sleep_for(std::chrono::seconds (1));
        }
        std::this_thread::sleep_for(std::chrono::seconds (1));//sleep to reduce CPU usage
        clear_console();
    }
    /************************************************************/
#else
    //Method to save in a file the song. Comment previous method to save song in file.
    std::string FILENAME(track->getName());
    FILENAME += ".wav";
    sf::SoundBuffer buffer;
    std::vector<sf::Int16> samples;
    std::cout << "Begin sampling" << std::endl;

    float number_of_samples = SAMPLE_RATE * TIME_RECORDING_SECONDS * PANNING;
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
#endif

    return 0;
}