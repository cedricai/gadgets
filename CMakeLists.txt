cmake_minimum_required(VERSION 3.0.0)
project(gadgets VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 11)

set(INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(${INCLUDE_PATH})

file(GLOB ALL_SOURCES *.cpp *.c)
file(GLOB ALL_INCLUDES ${INCLUDE_PATH}/*.hpp ${INCLUDE_PATH}/*.h)

set(ALL_SRCS ${ALL_SOURCES} ${ALL_INCLUDES})

add_library(gadgets ${ALL_SRCS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
