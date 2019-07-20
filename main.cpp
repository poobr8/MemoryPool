#include <iostream>
#include "vendor/google/googletest/googletest/include/gtest/gtest.h"


int main(int argc, char **argv) {
    std::cout << "Executing the unit tests..." << std::endl;

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}