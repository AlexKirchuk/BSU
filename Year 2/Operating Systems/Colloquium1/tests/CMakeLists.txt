cmake_minimum_required(VERSION 3.15)

enable_testing()

add_executable(tests
    test_factorial.cpp
    test_unique.cpp
    test_linked_list.cpp
)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
set(gtest_disable_pthreads ON CACHE BOOL "Disable pthreads for GTest" FORCE)
FetchContent_MakeAvailable(googletest)

target_include_directories(tests PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

set_property(TARGET tests PROPERTY CXX_STANDARD 17)
set_property(TARGET tests PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(tests PRIVATE
    GTest::gtest
    GTest::gtest_main
    core
)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL" CACHE STRING "" FORCE)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

add_test(NAME MyTest COMMAND tests)
add_test(NAME APITests
  COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/test_api.py
)