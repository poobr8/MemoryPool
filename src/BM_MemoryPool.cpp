#include "../vendor/google/benchmark/include/benchmark/benchmark.h"
#include "Coordinates.cpp"
#include "MemoryPool.cpp"

// Benchmarking the alloc method in MemoryPool
static void BM_Allocation(benchmark::State& state) {
    MemoryPool<Coordinates> memoryPool;

    for (auto _ : state)
        memoryPool.alloc();
}

BENCHMARK(BM_Allocation);

// Benchmarking the free method in MemoryPool
static void BM_Free(benchmark::State& state) {
    MemoryPool<Coordinates> memoryPool;
    Coordinates* ptr = memoryPool.alloc();

    for (auto _ : state)
        memoryPool.free(ptr);
}

BENCHMARK(BM_Free);

BENCHMARK_MAIN();
