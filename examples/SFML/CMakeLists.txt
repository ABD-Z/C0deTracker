cmake_minimum_required(VERSION 3.15)

project(C0deTracker-SFML)

# find SFML
find_package(SFML REQUIRED COMPONENTS audio)

add_executable(C0deTrackerSFML main.cpp custom_sfml_stream.cpp)
target_include_directories(C0deTrackerSFML PRIVATE ../../include)
target_link_libraries(C0deTrackerSFML PRIVATE C0deTracker C0deTrackersongs sfml-audio)
set_target_properties(C0deTrackerSFML PROPERTIES RUNTIME_OUTPUT_DIRECTORY bin)

if (WIN32)
    add_custom_command(
            TARGET C0deTrackerSFML POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy "${SFML_ROOT}/bin/openal32.dll" $<TARGET_FILE_DIR:C0deTrackerSFML>
            COMMENT "Copying openal32.dll to bin folder"
    )
endif()