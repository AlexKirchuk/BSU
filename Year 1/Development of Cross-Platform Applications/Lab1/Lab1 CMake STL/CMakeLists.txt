cmake_minimum_required(VERSION 4.1)
project(Lab1_CMake_STL)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab1_CMake_STL main.cpp
        Number.cpp
        Number.h
        Array.cpp
        Array.h
        Matrix.cpp
        Matrix.h)
