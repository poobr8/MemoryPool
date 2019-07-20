cmake_minimum_required(VERSION 3.13)
project(ThreadSafeMemoryPool)

set(CMAKE_CXX_STANDARD 11)
set(GOOGLETEST_VERSION 1.8.1)

# build google benchmark (target: benchmark)
# do not build tests of benchmarking lib
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Suppressing benchmark's tests" FORCE)
add_subdirectory(vendor/google/benchmark)

# build tests (targets: gtest_main, gtest)
add_subdirectory(vendor/google/googletest/googletest)

add_library(ThreadSafeMemoryPoolLib
        src/MemoryPool.cpp)

add_executable(ThreadSafeMemoryPoolTests
        main.cpp
        src/Coordinates.cpp
        tst/MemoryPoolTestMultiThreading.cpp
        tst/BasicMemoryPoolTest.cpp)

target_link_libraries(ThreadSafeMemoryPoolTests
        gtest
        ThreadSafeMemoryPoolLib)

add_executable(ThreadSafeMemoryPoolBenchmark
        src/BM_MemoryPool.cpp)

target_link_libraries(ThreadSafeMemoryPoolBenchmark
        benchmark
        ThreadSafeMemoryPoolLib)

