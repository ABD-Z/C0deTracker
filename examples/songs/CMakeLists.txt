cmake_minimum_required(VERSION 3.15)

project(C0deTracker-songs)

# get source files
file(GLOB_RECURSE Src *.cpp)
add_library(C0deTrackersongs STATIC ${Src})
target_include_directories(C0deTrackersongs PRIVATE ../../include)
target_link_libraries(C0deTrackersongs PRIVATE C0deTracker)
set_target_properties(C0deTrackersongs PROPERTIES ARCHIVE_OUTPUT_DIRECTORY lib)
