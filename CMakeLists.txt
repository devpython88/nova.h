cmake_minimum_required(VERSION 3.10)
project(nova VERSION 1.0.0 LANGUAGES CXX)

# Enable ccache if available
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    message(STATUS "ccache found: ${CCACHE_PROGRAM}")
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
endif()

# Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fconcepts -pthread")

# Core Nova
set(NOVA_H src/nova.h)
set(NOVA_SRC src/nova.cpp)

# Nova file
set(NOVAFILE_H src/novafile.h)
set(NOVAFILE_SRC src/novafile.cpp)

# Nova time and text tools and upcoming features
set(NOVAEXTRA_H src/novatime.h
        src/novastr.h src/json.hpp src/novajson.h src/novamisc.h)
set(NOVAEXTRA_SRC src/novatime.cpp
        src/novastr.cpp src/novajson.cpp src/novamisc.cpp)

# Target and main file
set(TARGET test)
set(MAIN src/main.cpp)

# API test
add_executable(${TARGET} ${MAIN} ${NOVA_H} ${NOVA_SRC} ${NOVAFILE_H} ${NOVAFILE_SRC} ${NOVAEXTRA_H} ${NOVAEXTRA_SRC})

# Link Libraries
target_link_libraries(${TARGET} raylib stdc++)

# Add Library
add_library(nova STATIC ${NOVA_SRC} ${NOVAFILE_SRC} ${NOVAEXTRA_SRC})
