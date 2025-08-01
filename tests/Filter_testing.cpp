#include <gtest/gtest.h>

// Tests must 
TEST(HelloTest,BasicAssertions) {
    EXPECT_STRNE("hello","world");

    EXPECT_EQ(7*6,42);
}