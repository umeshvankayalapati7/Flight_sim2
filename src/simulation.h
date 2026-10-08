#pragma once
#include <fstream>
#include <string>
#include "aircraft.h"
#include "pid.h"

class Simulation {
public:
    Simulation(Aircraft& aircraft, PidController& pid,
               double target_altitude_m, double rate_hz,
               const std::string& log_path);

    void run(double duration_s, bool realtime);

    double simTime() const { return sim_time_; }
    long overruns() const { return overruns_; }

private:
    void step();

    Aircraft& aircraft_;
    PidController& pid_;
    double target_altitude_m_;
    double dt_;
    double last_pitch_cmd_deg_ = 0.0;
    long step_count_ = 0;
    double sim_time_ = 0.0;
    long overruns_ = 0;
    std::ofstream log_;
};