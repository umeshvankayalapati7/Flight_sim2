#include "simulation.h"
#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <thread>

Simulation::Simulation(Aircraft& aircraft, PidController& pid,
                       double target_altitude_m, double rate_hz,
                       const std::string& log_path)
    : aircraft_(aircraft), pid_(pid),
      target_altitude_m_(target_altitude_m), dt_(1.0 / rate_hz),
      log_(log_path) {
    if (!log_.is_open()) {
        throw std::runtime_error("Could not open log file: " + log_path);
    }
    log_ << std::fixed << std::setprecision(4);
    log_ << "time_s,altitude_m,target_m,pitch_cmd_deg,vertical_speed_mps\n";
}

void Simulation::step() {
    last_pitch_cmd_deg_ = pid_.update(target_altitude_m_, aircraft_.altitude(), dt_);
    aircraft_.setPitchDeg(last_pitch_cmd_deg_);
    aircraft_.update(dt_);

    ++step_count_;
    sim_time_ = step_count_ * dt_;

    log_ << sim_time_ << ','
         << aircraft_.altitude() << ','
         << target_altitude_m_ << ','
         << last_pitch_cmd_deg_ << ','
         << aircraft_.verticalSpeed() << '\n';
}

void Simulation::run(double duration_s, bool realtime) {
    using clock = std::chrono::steady_clock;

    const auto period = std::chrono::duration_cast<clock::duration>(
        std::chrono::duration<double>(dt_));
    const long total_steps = std::lround(duration_s / dt_);
    const long steps_per_second = std::lround(1.0 / dt_);

    auto next_tick = clock::now() + period;

    for (long i = 0; i < total_steps; ++i) {
        step();

        if (step_count_ % steps_per_second == 0) {
            std::cout << "t=" << sim_time_
                      << "s  alt=" << aircraft_.altitude()
                      << " m  target=" << target_altitude_m_
                      << "  pitch_cmd=" << last_pitch_cmd_deg_ << " deg\n";
        }

        if (realtime) {
            if (clock::now() > next_tick) {
                ++overruns_;
            } else {
                std::this_thread::sleep_until(next_tick);
            }
            next_tick += period;
        }
    }
    log_.flush();
}