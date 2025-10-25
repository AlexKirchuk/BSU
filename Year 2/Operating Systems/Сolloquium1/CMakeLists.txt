cmake_minimum_required(VERSION 3.15)

project(Colloquium1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  nlohmann_json
  URL https://github.com/nlohmann/json/archive/refs/heads/develop.zip
)
FetchContent_MakeAvailable(nlohmann_json)

FetchContent_Declare(
  httplib
  URL https://github.com/yhirose/cpp-httplib/archive/refs/heads/master.zip
)
FetchContent_MakeAvailable(httplib)

enable_testing()
add_subdirectory(tests)

add_library(core
    src/factorial.cpp
    src/unique.cpp
    src/linked_list.cpp
)

target_include_directories(core PUBLIC include)

add_executable(Colloquium1 src/main.cpp)
target_link_libraries(Colloquium1 PRIVATE core)

add_executable(server src/server.cpp)
target_include_directories(server PRIVATE include ${httplib_SOURCE_DIR})
target_link_libraries(server PRIVATE core nlohmann_json::nlohmann_json)

if(POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT
      "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,\
      $<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,\
      $<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()