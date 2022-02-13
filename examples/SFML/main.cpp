#include "custom_sfml_stream.hpp"
#include <cstdlib>
#include <thread>
#include <chrono>

#include "../songs/tutorial.hpp"//include your song
#include "../songs/nokia3310_DUSHMAN_REMOVER.hpp"

#define REALTIME
#define NUMBER_OF_TRACKS 1

void clear_console(){
#ifdef __linux__
    system("clear");
#elif _WIN32
    system("cls");
#else

#endif

}

int main() {
    initGlobalInstruments();
    int index = 0;
    C0deTracker::Track_Data* tracks_data[] = {new Nokia3310_DUSHMAN_REMOVER_Battle()/*, new TutoTrack, new SuperStreetFighterII_CreditTheme(), new FrereJacques(),
                                              new FZERO_MenuTheme(), new SuperMarioBros_OverworldTheme(), new KirbysDreamland_GreenGreensTheme(),
                                              new Sonic_GreenHillZoneTheme()*/};


    //Method to play sound in real time with the custom stream
    C0deTracker::Track track_processor;
#ifdef REALTIME
    auto time1 = std::chrono::system_clock::now();
    tracks_data[index]->load_data();
    auto time2 = std::chrono::system_clock::now();
    auto deltaT = std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count();
    std::cout << "Time for " << tracks_data[index]->getName() <<"  tracks creation = " << deltaT << " micro seconds" << std::endl;
    track_processor.changeTrack(tracks_data[index]);
    C0deTrackerStream cts;
    cts.init(&track_processor);
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
            std::cout << tracks_data[i]->getName() << std::endl;
        }
        std::cout << "Select track number : ";
        std::cin >> select;
        if(select != index  && +NUMBER_OF_TRACKS - +select > 0){
            cts.stop();
            tracks_data[index]->free_data();
            index = select;
            std::cout << " Track selected " << tracks_data[index]->getName() << std::endl;
            time1 = std::chrono::system_clock::now();
            tracks_data[index]->load_data();
            time2 = std::chrono::system_clock::now();
            deltaT = std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count();
            std::cout << "Time for " << tracks_data[index]->getName() <<"  tracks creation = " << deltaT << " micro seconds" << std::endl;
            track_processor.changeTrack(tracks_data[index]);
            cts.play();
            std::this_thread::sleep_for(std::chrono::seconds (1));
        }
        std::this_thread::sleep_for(std::chrono::seconds (1));//sleep to reduce CPU usage
        clear_console();
    }
    /************************************************************/
#else
    //Method to save in a file the song. Comment previous method to save song in file.

    for(auto* td : tracks_data) {
        td->load_data();
        track_processor.changeTrack(td);
        std::string FILENAME(td->getName());
        FILENAME += ".wav";
        sf::SoundBuffer buffer;
        std::vector<sf::Int16> samples;

        std::cout << "Begin sampling " << td->getName() << std::endl;

        unsigned int number_of_samples = SAMPLE_RATE * track_processor.getDuration()*2 * PANNING;
        samples.reserve(number_of_samples);

        for (uint_fast64_t i = 0; i < number_of_samples; ++++i) {
            float* s = track_processor.play(0.5 * double(i) / SAMPLE_RATE);
            samples.push_back((s[0]) * BITS_16*0.5);//left speaker
            samples.push_back((s[1]) * BITS_16*0.5);//right speaker
        }

        buffer.loadFromSamples(&samples[0], samples.size(), PANNING, SAMPLE_RATE);
        buffer.saveToFile(FILENAME);
        std::cout << "End sampling " << td->getName() << std::endl;

        delete td;
    }
#endif

    return 0;
}