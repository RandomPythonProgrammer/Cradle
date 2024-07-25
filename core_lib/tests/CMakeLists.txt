file(GLOB_RECURSE TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_executable(cradle_test "${TEST_SOURCES}" "${SOURCES}")

target_link_libraries(cradle_test PRIVATE Catch2)
target_link_libraries(cradle_test PRIVATE yaml-cpp)
target_link_libraries(cradle_test PRIVATE cpr)
target_link_libraries(cradle_test PRIVATE cradle_lib)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(cradle_test)

set_property(TARGET cradle PROPERTY CXX_STANDARD 20)