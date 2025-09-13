#include "custom_sfml_stream.hpp"
#include <cstdlib>
#include <thread>
#include <chrono>

#include "../songs/tutorial.hpp" // include your tracks
#include "../songs/examples.hpp"

#define REALTIME
//#define NUMBER_OF_TRACKS 1
#define NUMBER_OF_TRACKS 8

void clear_console(){
#ifdef __linux__
    system("clear");
#elif _WIN32
    system("cls");
#else

#endif

}

int main() {
    C0deTrackerStream cts;
    initGlobalInstruments();
    int index = 0;

    C0deTracker::Track_Data *tracks_data[] = {new Track_Test, new TutoTrack, new FrereJacques(),
                                              new FZERO_MenuTheme(), new SuperMarioBros_OverworldTheme(),
                                              new KirbysDreamland_GreenGreensTheme(), new Sonic_GreenHillZoneTheme(),
                                              new SuperStreetFighterII_CreditTheme()
    };

    //Method to play sound in real time with the custom stream
    C0deTracker::Track track_processor(C0deTracker::AudioConfig(48000, 0.064f, true));
#ifdef REALTIME
    auto time1 = std::chrono::system_clock::now();
    tracks_data[index]->load_data();
    auto time2 = std::chrono::system_clock::now();
    auto deltaT = std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count();
    std::cout << "Time for " << tracks_data[index]->getName() <<"  tracks creation = " << deltaT << " micro seconds" << std::endl;
    track_processor.changeTrack(tracks_data[index]);
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
        cts.init(&track_processor);
        std::cout << "Begin sampling " << td->getName() << std::endl;
        cts.writeWav(FILENAME, 1);
        std::cout << "End sampling " << td->getName() << std::endl;
        delete td;
    }
#endif

    return 0;
}