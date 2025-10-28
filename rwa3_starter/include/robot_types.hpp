/**
 * @file robot_types.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-25
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#pragma once
#include <iostream>

//----------------------------------------------
// TODO: POD structs (Task 1)
// TODO: Remove this block of comment before submission
//----------------------------------------------
/**
 * @brief 
 * 
 */
struct JointState {
    double theta1;        // Joint 1 angle [rad]
    double theta2;        // Joint 2 angle [rad]
    // Default member initializers for velocities (Task 1 requirement)
    double dtheta1 = 0.0; // Joint 1 velocity [rad/s]
    double dtheta2 = 0.0; // Joint 2 velocity [rad/s]
};

struct EndEffectorPose {
    double x; // [m]
    double y; // [m]
};

// print function (non-template -> implemented in .cpp)
void print_joint_state(const JointState& js);

//----------------------------------------------
// Suggested constexpr configuration (starter)
// TODO: You are allowed to adjust as needed
// TODO: Remove this block of comment before submission
//----------------------------------------------
inline constexpr double k_link1{0.5};      // [m]
inline constexpr double k_link2{0.3};      // [m]
inline constexpr double k_vel_limit{1.0};   // [rad/s]
inline constexpr int    k_num_samples{21};  // includes endpoints
inline constexpr double k_alpha_step{1.0 / (k_num_samples - 1)};
