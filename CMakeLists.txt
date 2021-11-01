cmake_minimum_required(VERSION 3.15)
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

add_subdirectory(examples/songs)
if (BUILD_SFML_EXAMPLE)
    message(STATUS "CodeTrackerSFML target available.")
    add_subdirectory(examples/SFML)
endif()

