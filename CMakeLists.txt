cmake_minimum_required(VERSION 3.5)

project(csv LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(csv main.cpp csv.hpp)

target_compile_options(csv PRIVATE -O2 -Wall -W -Wextra -pedantic
        -Wno-unused-parameter -Wsign-compare  -march=native -pipe -g
        -fwrapv)
