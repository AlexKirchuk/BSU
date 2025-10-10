cmake_minimum_required(VERSION 3.15)

enable_testing()

add_executable(tests test_threads.cpp)
target_link_libraries(tests datalib threadlib)

target_include_directories(tests PRIVATE
    ${PROJECT_SOURCE_DIR}/libs/doctest
    ${PROJECT_SOURCE_DIR}/include
)

set_property(TARGET tests PROPERTY CXX_STANDARD 98)
set_property(TARGET tests PROPERTY CXX_STANDARD_REQUIRED ON)

add_test(NAME MyTest COMMAND tests)
