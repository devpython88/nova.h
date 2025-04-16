cmake_minimum_required(VERSION 3.10)
project(nova VERSION 1.0.0 LANGUAGES CXX)

# Core Nova
set(NOVA_H src/nova.h)
set(NOVA_SRC src/nova.cpp)

# Nova file
set(NOVAFILE_H src/novafile.h)
set(NOVAFILE_SRC src/novafile.cpp)

# Target and main file
set(TARGET test)
set(MAIN src/main.cpp)

# API test
add_executable(${TARGET} ${MAIN} ${NOVA_H} ${NOVA_SRC} ${NOVAFILE_H} ${NOVAFILE_SRC})

# Link Libraries
target_link_libraries(${TARGET} raylib stdc++)

# Add Library
add_library(nova STATIC ${NOVA_SRC} ${NOVAFILE_SRC})