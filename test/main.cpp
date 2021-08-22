
#include "gtest/gtest.h"
#include <spdlog/spdlog.h>

int main(int argc, char **argv) {
    spdlog::set_level(spdlog::level::debug); // Set global log level 
    ::testing::InitGoogleTest(&argc, argv);
    // ::testing::GTEST_FLAG(filter) = "FindAssetTest.*";
    return RUN_ALL_TESTS();
}
