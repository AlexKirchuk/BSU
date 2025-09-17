# CMakeList.txt : CMake project for Lab1 CMake, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (CMakeTarget "Lab1 CMake.cpp" "Lab1 CMake.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeTarget PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
