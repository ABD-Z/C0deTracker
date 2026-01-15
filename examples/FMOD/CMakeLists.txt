cmake_minimum_required(VERSION 3.15)

project(C0deTracker-FMOD)

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCH_TARGET x64)
else()
    set(ARCH_TARGET x86)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(WIN32)
        set(FMOD_LIB fmodL_vc.lib)
        set(FMOD_DLL fmodL.dll)
    elseif(UNIX)
        set(FMOD_LIB libfmodl.so)
    endif()
else(CMAKE_BUILD_TYPE STREQUAL "Release")
    if(WIN32)
        set(FMOD_LIB fmod_vc.lib)
        set(FMOD_DLL fmod.dll)
    elseif(UNIX)
        set(FMOD_LIB libfmod.so)
    endif()
endif()

set(FMOD_LIB_PATH "${FMOD_ROOT}/api/core/lib/${ARCH_TARGET}/${FMOD_LIB}")

add_executable(C0deTrackerFMOD main.cpp custom_fmod_stream.cpp)
target_include_directories(C0deTrackerFMOD PRIVATE ../../include "${FMOD_ROOT}/api/core/inc")
target_link_libraries(C0deTrackerFMOD PRIVATE C0deTracker C0deTrackersongs "${FMOD_LIB_PATH}")
set_target_properties(C0deTrackerFMOD PROPERTIES RUNTIME_OUTPUT_DIRECTORY bin)

if (WIN32)
    set(FMOD_DLL_PATH "${FMOD_ROOT}/api/core/lib/${ARCH_TARGET}/${FMOD_DLL}")
    add_custom_command(
            TARGET C0deTrackerFMOD POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy "${FMOD_DLL_PATH}" $<TARGET_FILE_DIR:C0deTrackerFMOD>
            COMMENT "Copying ${FMOD_DLL} to bin folder"
    )
endif()