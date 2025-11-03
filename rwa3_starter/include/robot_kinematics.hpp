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

#include <cmath>

#include "robot_types.hpp"

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
EndEffectorPose forward_kinematics(const State& s, double L1 = k_link1,
                                   double L2 = k_link2) {
  EndEffectorPose pose{};
  const double theta12 = s.theta1 + s.theta2;
  // compute forward kinematics
  pose.x = L1 * std::cos(s.theta1) + L2 * std::cos(theta12);
  pose.y = L1 * std::sin(s.theta1) + L2 * std::sin(theta12);
  return pose;
}

/**
 * @brief Check if the joint angles are within the defined limits.
 *
 * @tparam State Type exposing theta1 and theta2 members.
 * @param s Joint state to check.
 * @return true If both joint angles are within limits.
 * @return false If any joint angle exceeds limits.
 */
template <typename State>
bool check_joint_limits(const State& s) {
  return (s.theta1 >= -k_joint_limit && s.theta1 <= k_joint_limit) &&
         (s.theta2 >= -k_joint_limit && s.theta2 <= k_joint_limit);
}
