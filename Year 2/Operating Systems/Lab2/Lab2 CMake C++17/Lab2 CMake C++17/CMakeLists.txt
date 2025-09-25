# CMakeList.txt : CMake project for Lab2 CMake C++17, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (CMakeTarget "Lab2 CMake C++17.cpp" "Lab2 CMake C++17.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeTarget PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
