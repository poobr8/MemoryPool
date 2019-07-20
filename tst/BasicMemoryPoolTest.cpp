#include "limits.h"
#include "MacTypes.h"
#include "../src/Coordinates.cpp"
#include "../vendor/google/googletest/googletest/include/gtest/gtest.h"

#include "../src/MemoryPool.cpp"

TEST(BasicMemoryPoolTest, ALLOC_FREE_INT) {
    MemoryPool<int> memoryPool;

    int* ptr = memoryPool.alloc();

    EXPECT_EQ(sizeof(int), sizeof(*ptr));
    EXPECT_EQ(sizeof(int), memoryPool.getCurrentUsage());
}

TEST(BasicMemoryPoolTest, ALLOC_COORDINATES) {
    MemoryPool<Coordinates> memoryPool;

    Coordinates* ptr = memoryPool.alloc();

    EXPECT_EQ(8, sizeof(*ptr));
    EXPECT_EQ(8, memoryPool.getCurrentUsage());
}

TEST(BasicMemoryPoolTest, FREE_COORDINATES) {
    MemoryPool<Coordinates> memoryPool;

    EXPECT_EQ(0, memoryPool.getCurrentUsage());

    Coordinates* ptr = memoryPool.alloc();
    memoryPool.free(ptr);

    EXPECT_EQ(1, memoryPool.getAvailableSlots());
}
