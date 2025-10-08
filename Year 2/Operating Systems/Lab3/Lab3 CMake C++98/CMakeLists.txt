cmake_minimum_required(VERSION 3.8)

project(Lab3CMake98)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BOOST_ROOT "D:/Programming/C++ libs/boost_1_89_0")
set(BOOST_INCLUDEDIR "${BOOST_ROOT}")
include_directories(${BOOST_INCLUDEDIR} include)

set(SOURCES
    src/main.cpp
    src/array.cpp
    src/marker.cpp
)

add_executable(Lab3CMake98 ${SOURCES})

if(POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()
