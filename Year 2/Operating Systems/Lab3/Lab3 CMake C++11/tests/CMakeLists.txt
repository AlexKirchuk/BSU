cmake_minimum_required(VERSION 3.15)

enable_testing()

add_executable(tests
    test.cpp
    ${PROJECT_SOURCE_DIR}/src/array.cpp
    ${PROJECT_SOURCE_DIR}/src/marker.cpp
)

target_include_directories(tests PRIVATE
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/include
)

set_property(TARGET tests PROPERTY CXX_STANDARD 11)
set_property(TARGET tests PROPERTY CXX_STANDARD_REQUIRED ON)

add_test(NAME MyTest COMMAND tests)