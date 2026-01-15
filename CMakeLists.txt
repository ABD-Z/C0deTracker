cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD  17)

project(C0deTracker)

if (MSVC)
    message(STATUS "Using MSVC")
    #add_compile_options(/FA)
    if(CMAKE_BUILD_TYPE MATCHES  Release)
        add_compile_options(/O2x)
    endif()
else()
    if(CMAKE_BUILD_TYPE MATCHES  Release)
        add_compile_options(-O3)
    endif()
endif()

#find_package(OpenMP REQUIRED)

# get source files
file(GLOB_RECURSE Src src/*.cpp)
file(GLOB_RECURSE Inc include/*.hpp)

# create the static lib target
add_library(C0deTracker STATIC ${Src} ${Inc})


# set include directory for build and install
target_include_directories(C0deTracker PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
target_include_directories(C0deTracker INTERFACE $<INSTALL_INTERFACE:include>)
#target_link_libraries(C0deTracker OpenMP::OpenMP_CXX)

# set lib target properties
set_target_properties(C0deTracker PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY lib
        DEBUG_POSTFIX -d
        )


option(BUILD_SFML_EXAMPLE   "Build an example using C0deTracker with SFML." OFF)
option(BUILD_SDL_EXAMPLE   "Build an example using C0deTracker with SDL." OFF)
option(BUILD_FMOD_EXAMPLE   "Build an example using C0deTracker with FMOD." OFF)

add_subdirectory(examples/songs)

if (BUILD_SFML_EXAMPLE)
    if (CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(SFML_ROOT ${SFML_ROOT_x64})
    else()
        set(SFML_ROOT ${SFML_ROOT_x86})
    endif()
    set(SFML_ROOT ${SFML_ROOT} CACHE PATH "Selected SFML root")
    message(STATUS "CodeTrackerSFML target available.")
    add_subdirectory(examples/SFML)
endif()

if (BUILD_SDL2_EXAMPLE)
    message(STATUS "CodeTrackerSDL2 target available.")
    add_subdirectory(examples/SDL2)
endif()

if (BUILD_FMOD_EXAMPLE)
    message(STATUS "CodeTrackerFMOD target available.")
    add_subdirectory(examples/FMOD)
endif()
