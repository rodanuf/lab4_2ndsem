cmake_minimum_required(VERSION 3.10)
project(lab4_2ndsem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(gtest_force_shared_crt ON CACHE BOOL "Use shared CRT for GoogleTest" FORCE)

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "" FORCE)
set(BENCHMARK_DOWNLOAD_DEPENDENCIES OFF CACHE BOOL "" FORCE)

set(LAB3_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/../lab3_2ndsem/headers")
message(STATUS "LAB3 headers: ${LAB3_INCLUDE_DIR}")

file(GLOB HEADERS "headers/*.hpp")
file(GLOB TEMPLATES "templates/*.tpp")
file(GLOB UI_HEADERS "ui_headers/*.hpp")
file(GLOB UI_SOURCES "ui_sources/*.cpp") 
file(GLOB TYPES_HEADERS "types_headers/*.hpp")
file(GLOB TYPES_SOURCES "types_sources/*.cpp")

option(BUILD_GMOCK "Build gmock" OFF)
add_subdirectory(googletest EXCLUDE_FROM_ALL)

add_subdirectory(external/benchmark EXCLUDE_FROM_ALL)

add_executable(lab4_2ndsem
    ui_sources/lab.cpp
    ${UI_SOURCES}
    ${TYPES_SOURCES}
    ${TEMPLATES}
)

add_executable(tests 
    tests/main_tests.cpp 
)

add_executable(benchmarks
    tests/main_benchmarks.cpp
)

target_include_directories(tests PRIVATE 
    ${CMAKE_SOURCE_DIR}/headers
    ${CMAKE_SOURCE_DIR}/googletest/googletest/include
    ${CMAKE_SOURCE_DIR}/tests
    ${LAB3_INCLUDE_DIR}
)

target_include_directories(benchmarks PRIVATE
    ${CMAKE_SOURCE_DIR}/headers
    ${CMAKE_SOURCE_DIR}/types_headers
    ${LAB3_INCLUDE_DIR}
)

target_include_directories(lab4_2ndsem PRIVATE
    ${CMAKE_SOURCE_DIR}/headers
    ${CMAKE_SOURCE_DIR}/types_headers
    ${CMAKE_SOURCE_DIR}/ui_headers
    ${LAB3_INCLUDE_DIR}
)

target_link_libraries(tests PRIVATE gtest gtest_main)
target_link_libraries(benchmarks PRIVATE benchmark::benchmark)

enable_testing()
add_test(NAME AllTests COMMAND tests)