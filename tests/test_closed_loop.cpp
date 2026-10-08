#include <gtest/gtest.h>
#include <cmath>
#include "aircraft.h"
#include "pid.h"

// Fly the aircraft with the controller for 60 s and check that it
// reaches the target altitude without overshooting.
TEST(ClosedLoopTest, ReachesTargetWithoutOvershoot) {
    Aircraft plane(1000.0, 60.0);
    PidController pid(0.1, 0.0, 0.0, -10.0, 10.0);
    const double target = 1100.0;
    const double dt = 0.02;
    double max_altitude = 0.0;

    for (int i = 0; i < 3000; ++i) {
        plane.setPitchDeg(pid.update(target, plane.altitude(), dt));
        plane.update(dt);
        max_altitude = std::fmax(max_altitude, plane.altitude());
    }

    EXPECT_NEAR(plane.altitude(), target, 1.0);
    EXPECT_LE(max_altitude, target + 1.0);
}

TEST(ClosedLoopTest, DescendsToLowerTarget) {
    Aircraft plane(1000.0, 60.0);
    PidController pid(0.1, 0.0, 0.0, -10.0, 10.0);
    const double dt = 0.02;

    for (int i = 0; i < 3000; ++i) {
        plane.setPitchDeg(pid.update(900.0, plane.altitude(), dt));
        plane.update(dt);
    }
    EXPECT_NEAR(plane.altitude(), 900.0, 1.0);
}