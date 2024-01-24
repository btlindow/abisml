cmake_minimum_required(VERSION 3.16.5)
project(abisml)

set(CMAKE_BUILD_TYPE Debug)
file(GLOB SOURCES src/*.c)

add_executable(abisml ${SOURCES})
include_directories(inc)