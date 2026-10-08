#include "pid.h"
#include <algorithm>

PidController::PidController(double kp, double ki, double kd,
                             double out_min, double out_max)
    : kp_(kp), ki_(ki), kd_(kd), out_min_(out_min), out_max_(out_max) {}

void PidController::reset() {
    integral_ = 0.0;
    has_prev_ = false;
}

double PidController::update(double setpoint, double measurement, double dt) {
    const double error = setpoint - measurement;

    // Integral term, clamped so it can't wind up without limit
    integral_ += error * dt;
    if (ki_ > 0.0) {
        integral_ = std::clamp(integral_, out_min_ / ki_, out_max_ / ki_);
    }

    // Derivative on the measurement (avoids a spike when the setpoint changes)
    double derivative = 0.0;
    if (has_prev_) {
        derivative = -(measurement - prev_measurement_) / dt;
    }
    prev_measurement_ = measurement;
    has_prev_ = true;

    const double output = kp_ * error + ki_ * integral_ + kd_ * derivative;
    return std::clamp(output, out_min_, out_max_);
}