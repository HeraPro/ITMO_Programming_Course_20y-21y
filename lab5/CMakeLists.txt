cmake_minimum_required(VERSION 3.16)
project(lab_05)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(lab_05
        circular_buffer-impl.hpp
        circular_buffer.hpp
        main.cpp)
