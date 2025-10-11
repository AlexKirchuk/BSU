cmake_minimum_required(VERSION 3.15)
project(Lab1CMake98)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_library(employee_lib
    src/employee.cpp
)

add_executable(Lab1CMake98 src/main.cpp)
target_link_libraries(Lab1CMake98 PRIVATE employee_lib)

add_executable(Creator src/creator.cpp)
target_link_libraries(Creator PRIVATE employee_lib)

add_executable(Reporter src/reporter.cpp)
target_link_libraries(Reporter PRIVATE employee_lib)

add_dependencies(Lab1CMake98 Creator Reporter)

enable_testing()
add_subdirectory(tests)

if(POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT
      "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()