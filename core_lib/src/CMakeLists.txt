file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_executable(cradle "${SOURCES}")
add_library(cradle_lib "${SOURCES}")

target_link_libraries(cradle PRIVATE yaml-cpp)
target_link_libraries(cradle PRIVATE cpr)