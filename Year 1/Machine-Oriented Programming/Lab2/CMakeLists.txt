cmake_minimum_required(VERSION 3.10)
project(Lab2)

if(MSVC)

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    
    if(CMAKE_SIZEOF_VOID_P EQUAL 4)
        add_compile_options(/arch:SSE2)
    else()
        message(WARNING "__asm {} only in x86")
    endif()
endif()

add_executable(Lab2 main.cpp)