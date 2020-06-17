if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "Create a separate build directory")
endif()

cmake_minimum_required (VERSION 3.12)

project(test DESCRIPTION "BloomFilter"
              LANGUAGES CXX)

set (TEST_VERSION_MAJOR 0)
set (TEST_VERSION_MINOR 0)
set (TEST_VERSION_PATCH 1)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -ggdb -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_PROFILE "-O3 -pg -g")
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

add_subdirectory(bloomfilter)

add_executable(test
               main.cc)

target_link_libraries(test
                      LINK_PUBLIC
                      bloomfilter)
