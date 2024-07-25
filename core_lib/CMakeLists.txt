include(FetchContent)

FetchContent_Declare(yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
)
FetchContent_MakeAvailable(yaml-cpp)

FetchContent_Declare(cpr 
  GIT_REPOSITORY https://github.com/libcpr/cpr.git
)
FetchContent_MakeAvailable(cpr)

FetchContent_Declare(Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.6.0
)
FetchContent_MakeAvailable(Catch2)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

add_subdirectory(src)
add_subdirectory(tests)