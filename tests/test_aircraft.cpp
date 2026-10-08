#include <gtest/gtest.h>
#include "aircraft.h"

TEST(AircraftTest, LevelPitchKeepsAltitude) {
    Aircraft plane(1000.0, 60.0);
    plane.setPitchDeg(0.0);
    for (int i = 0; i < 500; ++i) plane.update(0.02);
    EXPECT_NEAR(plane.altitude(), 1000.0, 1e-9);
}

TEST(AircraftTest, PositivePitchClimbs) {
    Aircraft plane(1000.0, 60.0);
    plane.setPitchDeg(5.0);
    for (int i = 0; i < 500; ++i) plane.update(0.02);   // 10 s
    // 60 * sin(5 deg) * 10 = about 52.3 m
    EXPECT_NEAR(plane.altitude(), 1052.3, 0.1);
    EXPECT_NEAR(plane.verticalSpeed(), 5.23, 0.01);
}

TEST(AircraftTest, NegativePitchDescends) {
    Aircraft plane(1000.0, 60.0);
    plane.setPitchDeg(-5.0);
    for (int i = 0; i < 500; ++i) plane.update(0.02);
    EXPECT_LT(plane.altitude(), 1000.0);
}