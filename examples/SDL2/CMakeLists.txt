cmake_minimum_required(VERSION 3.15)

project(C0deTracker-SDL2)

# find SDL
find_package(SDL2 REQUIRED CONFIG)

add_executable(C0deTrackerSDL2 main.cpp custom_sdl2_stream.cpp)
target_include_directories(C0deTrackerSDL2 PRIVATE ../../include)
target_link_libraries(C0deTrackerSDL2 PRIVATE C0deTracker C0deTrackersongs SDL2::SDL2)
set_target_properties(C0deTrackerSDL2 PROPERTIES RUNTIME_OUTPUT_DIRECTORY bin)

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCH_TARGET "x64")
else()
    set(ARCH_TARGET "x86")
endif()

set(SDL2_DLL "${SDL2_DIR}/../lib/${ARCH_TARGET}/SDL2.dll")

if (WIN32)
    add_custom_command(
            TARGET C0deTrackerSDL2 POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_DLL} $<TARGET_FILE_DIR:C0deTrackerSDL2>
            COMMENT "Copying SDL2.dll to bin folder"
    )
endif()