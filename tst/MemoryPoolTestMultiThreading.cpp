#include <thread>
#include "limits.h"
#include "MacTypes.h"
#include "../src/Coordinates.cpp"
#include "../vendor/google/googletest/googletest/include/gtest/gtest.h"

#include "../src/MemoryPool.cpp"

class MemoryPoolTestMultiThreading : public testing::Test {
protected:
    void SetUp() override {
        // allocate two co-ordinates object
        ptr1 = memoryPool.alloc();
        ptr2 = memoryPool.alloc();
    }

    MemoryPool<Coordinates> memoryPool;
    Coordinates* ptr1;
    Coordinates* ptr2;
};

TEST_F(MemoryPoolTestMultiThreading, ALLOC_ONLY) {
    auto t1 = std::thread( [&]{ memoryPool.alloc(); } );
    auto t2 = std::thread( [&]{ memoryPool.alloc(); } );

    t1.join();
    t2.join();

    ASSERT_EQ(32, memoryPool.getCurrentUsage());
}

TEST_F(MemoryPoolTestMultiThreading, FREE_ONLY) {
    auto t1 = std::thread( [&]{ memoryPool.free(ptr1); } );
    auto t2 = std::thread( [&]{ memoryPool.free(ptr2); } );

    t1.join();
    t2.join();

    ASSERT_EQ(2, memoryPool.getAvailableSlots());
}