#pragma once

class PidController {
public:
    PidController(double kp, double ki, double kd,
                  double out_min, double out_max);

    // Returns the control output for this timestep
    double update(double setpoint, double measurement, double dt);
    void reset();

private:
    double kp_, ki_, kd_;
    double out_min_, out_max_;
    double integral_ = 0.0;
    double prev_measurement_ = 0.0;
    bool has_prev_ = false;
};