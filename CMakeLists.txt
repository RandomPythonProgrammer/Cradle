cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
project(cradle)

include(FetchContent)

FetchContent_Declare(yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
)
FetchContent_MakeAvailable(yaml-cpp)

FetchContent_Declare(cpr 
  GIT_REPOSITORY https://github.com/libcpr/cpr.git
)
FetchContent_MakeAvailable(cpr)

include_directories("${CMAKE_SOURCE_DIR}/include")
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
add_executable(cradle "${SOURCES}")

target_link_libraries(cradle PRIVATE yaml-cpp)
target_link_libraries(cradle PRIVATE cpr)

set_property(TARGET cradle PROPERTY CXX_STANDARD 20)
