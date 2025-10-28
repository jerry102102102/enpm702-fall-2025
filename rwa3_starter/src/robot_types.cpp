/**
 * @file robot_types.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-25
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "robot_types.hpp"
#include <iomanip>

void print_joint_state(const JointState& js) {
    std::cout << std::fixed << std::setprecision(4)
              << "θ1 = " << js.theta1 << " rad | "
              << "θ2 = " << js.theta2 << " rad | "
              << "dθ1 = " << js.dtheta1 << " rad/s | "
              << "dθ2 = " << js.dtheta2 << " rad/s\n";
}
