#include <iostream>
#include "aircraft.h"
#include "pid.h"
#include "simulation.h"

int main() {
    Aircraft plane(1000.0, 60.0);             // start at 1000 m
    PidController pid(0.1, 0.0, 0.0,          // Kp, Ki, Kd
                      -10.0, 10.0);           // pitch limits: ±10 deg

        Simulation sim(plane, pid, 1100.0, 50.0, "sim_log.csv");
    sim.run(60.0, false);                     // 60 s, as fast as possible

    std::cout << "Final altitude: " << plane.altitude() << " m\n";
    return 0;
}