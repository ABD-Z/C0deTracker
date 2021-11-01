cmake_minimum_required(VERSION 3.15)

project(C0deTracker-SFML)

# find SFML
find_package(SFML REQUIRED COMPONENTS audio)

add_executable(C0deTrackerSFML main.cpp custom_sfml_stream.cpp)
target_include_directories(C0deTrackerSFML PRIVATE ../../include)
target_link_libraries(C0deTrackerSFML PRIVATE C0deTracker C0deTrackersongs sfml-audio)
set_target_properties(C0deTrackerSFML PROPERTIES RUNTIME_OUTPUT_DIRECTORY bin)
