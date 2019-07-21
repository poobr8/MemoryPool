# MemoryPool
A thread safe memory pool

## Prerequisites

* Need to have installed cmake 3.13 or higher

## How to build

```
$ cmake .
$ mkdir build
$ cmake --build build/
```

### Clean up build and cache

```
$ rm -rf build/
$ rm -rf CMakeFiles
```

## Run the benchmark

```
$ ./build/ThreadSafeMemoryPoolBenchmark
```

## Execute the unit tests

```
$ ./build/ThreadSafeMemoryPoolTests
```