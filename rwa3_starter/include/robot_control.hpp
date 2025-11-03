/**
 * @file robot_control.hpp
 * @author Jerry C
 * @brief Trajectory generation and filtering utilities for the 2-DOF arm.
 * @version 1.0
 * @date 2025-10-30
 *
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <algorithm>
#include <functional>
#include <vector>

#include "robot_types.hpp"

/**
 * @brief Interpolate between two joint states with a clamped alpha parameter.
 * @tparam State Type exposing theta1/theta2/dtheta1/dtheta2 members.
 * @param start Initial joint state.
 * @param goal Target joint state.
 * @param alpha Interpolation factor (clamped to [0, 1]).
 * @return State Interpolated joint configuration.
 */
template <typename State>
State interpolate_linear(const State& start, const State& goal, double alpha) {
  // clamp alpha to [0, 1] just in case
  if (alpha < 0.0) alpha = 0.0;
  if (alpha > 1.0) alpha = 1.0;
  State out{};
  // Linear interpolation for joint angles
  const double delta_theta1 = goal.theta1 - start.theta1;
  const double delta_theta2 = goal.theta2 - start.theta2;
  out.theta1 = start.theta1 + alpha * delta_theta1;
  out.theta2 = start.theta2 + alpha * delta_theta2;
  out.dtheta1 = k_velocity_gain * delta_theta1;
  out.dtheta2 = k_velocity_gain * delta_theta2;
  return out;
}

/**
 * @brief Apply an in-place filter to each sample of a trajectory.
 *
 * @param traj Trajectory to be modified.
 * @param filter Unary functor operating on a joint state.
 */
void apply_filter(std::vector<JointState>& traj,
                  std::function<JointState(const JointState&)> filter);
