cmake_minimum_required(VERSION 3.15)

project(C0deTracker-SDL2)

# find SDL
find_package(SDL2 REQUIRED CONFIG)

add_executable(C0deTrackerSDL2 main.cpp custom_sdl2_stream.cpp)
target_include_directories(C0deTrackerSDL2 PRIVATE ../../include)
target_link_libraries(C0deTrackerSDL2 PRIVATE C0deTracker C0deTrackersongs SDL2::SDL2 SDL2::SDL2main)
set_target_properties(C0deTrackerSDL2 PROPERTIES RUNTIME_OUTPUT_DIRECTORY bin)
