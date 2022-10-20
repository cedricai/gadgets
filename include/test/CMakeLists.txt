cmake_minimum_required(VERSION 3.0.0)

project(main_test VERSION 0.1.0)

enable_testing()

set(CMAKE_CXX_STANDARD 11)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../third_party)

add_subdirectory(${THIRD_PARTY_DIR}/googletest googletest)

include(GoogleTest)

add_executable(${PROJECT_NAME} test.cpp)
target_link_libraries(${PROJECT_NAME} GTest::gtest_main)

gtest_discover_tests(${PROJECT_NAME})
