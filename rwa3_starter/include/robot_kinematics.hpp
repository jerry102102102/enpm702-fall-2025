/**
 * @file robot_kinematics.hpp
 * @author Jerry C
 * @brief Forward kinematics utilities for the planar 2-DOF arm.
 * @version 1.0
 * @date 2025-10-30
 *
 * @copyright Copyright (c) 2025
 */

#pragma once

#include "robot_types.hpp"

#include <cmath>

//---------------------------------------------------------
// TODO: forward_kinematics (Task 2)
// - TEMPLATE must be defined in header (no .cpp)
// - STARTER returns a placeholder; you must implement
// TODO: Remove this block of comment before submission
//---------------------------------------------------------

/**
 * @brief Compute the planar forward kinematics for a two-link manipulator.
 *
 * @tparam State Type exposing theta1 and theta2 members.
 * @param state Joint configuration used for the computation.
 * @param L1 Length of link 1 [m].
 * @param L2 Length of link 2 [m].
 * @return EndEffectorPose Cartesian position of the end-effector.
 */
template <typename State>
EndEffectorPose forward_kinematics(const State& s,
                                   double L1 = k_link1,
                                   double L2 = k_link2)
{
    // TODO [Task 2]:
    // Implement the FK equations:
    // x = L1*cos(theta1) + L2*cos(theta1 + theta2)
    // y = L1*sin(theta1) + L2*sin(theta1 + theta2)

    EndEffectorPose pose{};
    const double theta12 = s.theta1 + s.theta2;
    pose.x = L1 * std::cos(s.theta1) + L2 * std::cos(theta12);
    pose.y = L1 * std::sin(s.theta1) + L2 * std::sin(theta12);
    return pose;
}


// TODO: Optional
// You can optionally write a small function to check if the robot's joint angles are within valid limits.
// For example, real robot joints cannot rotate indefinitely, they usually have mechanical constraints (e.g., ±180° for a revolute joint).

//     - Write a function that takes a robot's joint state as input and checks whether each joint angle stays within acceptable limits.
//     - Pick reasonable limits for both joints (e.g., around ±π radians).
//     - The function should return true if both joints are within range, and false otherwise.

// This can be a small helper template function and is not required for grading, but it is useful practice for adding safety checks in robot control software.

// template <typename State>
// bool check_joint_limits(const State& s) {}
// TODO: Remove this block of comment before submission
