cmake_minimum_required (VERSION 3.8)

project (Lab2CMake)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(include)

add_library(datalib STATIC libs/datalib/data.cpp)
add_library(threadlib STATIC libs/threadlib/minmax.cpp libs/threadlib/average.cpp)
target_link_libraries(datalib threadlib)

add_executable(Lab2CMake src/main.cpp)
target_link_libraries(Lab2CMake datalib threadlib)

enable_testing()
add_subdirectory(tests)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()