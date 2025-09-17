cmake_minimum_required(VERSION 3.8)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL" CACHE STRING "" FORCE)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(EmployeeTests test.cpp)
target_link_libraries(EmployeeTests PRIVATE EmployeeLib gtest)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_target_properties(EmployeeTests PROPERTIES CXX_STANDARD 20)
endif()

add_test(NAME MyTest COMMAND EmployeeTests)