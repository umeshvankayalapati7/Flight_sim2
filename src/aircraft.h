#pragma once

class Aircraft {
public:
    Aircraft(double initial_altitude_m, double airspeed_mps);

    // Advance the aircraft state by dt seconds
    void update(double dt);

    // Set pitch in degrees (positive = nose up)
    void setPitchDeg(double pitch_deg);

    double altitude() const { return altitude_m_; }
    double verticalSpeed() const { return vertical_speed_mps_; }
    double pitchDeg() const;

private:
    double altitude_m_;
    double airspeed_mps_;
    double vertical_speed_mps_ = 0.0;
    double pitch_rad_ = 0.0;
};