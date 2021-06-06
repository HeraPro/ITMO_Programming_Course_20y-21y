cmake_minimum_required(VERSION 3.19)
project(lab_05)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lab_05
        circular_buffer-impl.hpp
        circular_buffer.hpp
        main.cpp)
