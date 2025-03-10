cmake_minimum_required(VERSION 3.8)
project(cpp-benchmark CXX)

set(CMAKE_CXX_STANDARD 17)

# Testing
add_subdirectory(lib/gtest)
enable_testing()

# Benchmark
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Suppressing benchmark's tests" FORCE)
add_subdirectory(lib/benchmark)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -fdiagnostics-color=auto -fmax-errors=2 -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

# Kokkos
add_subdirectory(lib/kokkos)

add_subdirectory(benchmark)
