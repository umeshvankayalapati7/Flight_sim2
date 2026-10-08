#include "aircraft.h"
#include <cmath>

namespace {
constexpr double kPi = 3.14159265358979323846;
constexpr double kDegToRad = kPi / 180.0;
}

Aircraft::Aircraft(double initial_altitude_m, double airspeed_mps)
    : altitude_m_(initial_altitude_m), airspeed_mps_(airspeed_mps) {}

void Aircraft::setPitchDeg(double pitch_deg) {
    pitch_rad_ = pitch_deg * kDegToRad;
}

double Aircraft::pitchDeg() const {
    return pitch_rad_ / kDegToRad;
}

void Aircraft::update(double dt) {
    vertical_speed_mps_ = airspeed_mps_ * std::sin(pitch_rad_);
    altitude_m_ += vertical_speed_mps_ * dt;
}