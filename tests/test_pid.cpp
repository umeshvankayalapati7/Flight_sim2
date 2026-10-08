#include <gtest/gtest.h>
#include "pid.h"

TEST(PidTest, ZeroErrorGivesZeroOutput) {
    PidController pid(0.1, 0.0, 0.0, -10.0, 10.0);
    EXPECT_NEAR(pid.update(100.0, 100.0, 0.02), 0.0, 1e-12);
}

TEST(PidTest, ProportionalTermScalesWithError) {
    PidController pid(0.1, 0.0, 0.0, -10.0, 10.0);
    EXPECT_NEAR(pid.update(110.0, 100.0, 0.02), 1.0, 1e-9);  // 0.1 * 10
}

TEST(PidTest, OutputIsClampedToLimits) {
    PidController pid(0.1, 0.0, 0.0, -10.0, 10.0);
    EXPECT_DOUBLE_EQ(pid.update(10000.0, 0.0, 0.02), 10.0);
    EXPECT_DOUBLE_EQ(pid.update(0.0, 10000.0, 0.02), -10.0);
}

TEST(PidTest, ResetClearsIntegral) {
    PidController pid(0.0, 1.0, 0.0, -10.0, 10.0);
    pid.update(10.0, 0.0, 1.0);   // integral builds up
    pid.reset();
    EXPECT_NEAR(pid.update(0.0, 0.0, 1.0), 0.0, 1e-12);
}