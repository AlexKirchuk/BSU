cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 98) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (Lab3CMake98)

include_directories(${PROJECT_SOURCE_DIR}/include)
set(SOURCES
    src/main.cpp
    src/array.cpp
    src/marker.cpp
)

add_executable(Lab3CMake98 src/main.cpp "src/marker.cpp")