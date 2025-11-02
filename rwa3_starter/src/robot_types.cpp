/**
 * @file robot_types.cpp
 * @author Jerry C
 * @brief Implementation of helper utilities for robot state reporting.
 * @version 1.0
 * @date 2025-10-30
 *
 * @copyright Copyright (c) 2025
 */

#include "robot_types.hpp"

#include <iomanip>
#include <iostream>

void print_joint_state(const JointState& state) {
    std::cout << std::fixed << std::setprecision(4)
              << "  θ1 = " << state.theta1 << " rad"
              << " | θ2 = " << state.theta2 << " rad"
              << " | dθ1 = " << state.dtheta1 << " rad/s"
              << " | dθ2 = " << state.dtheta2 << " rad/s\n";
}
