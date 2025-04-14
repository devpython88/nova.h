cmake_minimum_required(VERSION 3.10)
project(nova VERSION 1.0.0 LANGUAGES CXX)

option(BUILD_LIBRARY "Build library only" OFF)

set(NOVA_H src/nova.h)
set(NOVA_SRC src/nova.cpp)

set(TARGET test)
set(MAIN src/main.cpp)

add_executable(${TARGET} ${MAIN} ${NOVA_H} ${NOVA_SRC})
target_link_libraries(${TARGET} raylib stdc++)
add_library(nova STATIC ${NOVA_SRC})