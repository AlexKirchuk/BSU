cmake_minimum_required(VERSION 3.8)

project(Colloquium1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(include)

set(SOURCES
    src/main.cpp
    src/factorial.cpp
    src/unique.cpp
    src/linked_list.cpp)

add_executable(Colloquium1 ${SOURCES})

enable_testing()
add_subdirectory(tests)

if(POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()