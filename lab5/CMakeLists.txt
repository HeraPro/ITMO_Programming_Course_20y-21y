cmake_minimum_required(VERSION 3.16)
project(lab5)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(lab5
        circular_buffer-impl.hpp
        circular_buffer.hpp
        main.cpp)
