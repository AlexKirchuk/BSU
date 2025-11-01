cmake_minimum_required(VERSION 3.8)

project(Lab4CMake98)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(Lab4CMake98 src/receiver.cpp)
add_executable(sender src/sender.cpp)

add_dependencies(Lab4CMake98 sender)

enable_testing()
add_subdirectory(tests)

if(POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()