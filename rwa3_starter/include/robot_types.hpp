/**
 * @file robot_types.hpp
 * @author Jerry C
 * @brief Fundamental data types and constants for the 2-DOF robot arm example.
 * @version 1.0
 * @date 2025-10-30
 *
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <cstddef>

/**
 * @brief Joint-space description for a planar 2-DOF manipulator.
 */
struct JointState {
  double theta1{};      ///< Joint 1 angle [rad]
  double theta2{};      ///< Joint 2 angle [rad]
  double dtheta1{0.0};  ///< Joint 1 angular velocity [rad/s]
  double dtheta2{0.0};  ///< Joint 2 angular velocity [rad/s]
};

struct EndEffectorPose {
  double x{};  ///< [m]
  double y{};  ///< [m]
};

/**
 * @brief Print a joint state with consistent units.
 *
 * @param state Joint configuration and velocity to display.
 */
void print_joint_state(const JointState& state);
inline constexpr double k_link1{0.5};            ///< [m]
inline constexpr double k_link2{0.3};            ///< [m]
inline constexpr double k_vel_limit{1.0};        ///< [rad/s]
inline constexpr std::size_t k_num_samples{21};  ///< includes endpoints
inline constexpr double k_alpha_step{1.0 / (k_num_samples - 1)};
inline constexpr double k_velocity_gain{
    1.0};  ///< Gain relating angle difference to velocity
inline constexpr double k_joint_limit{3.14159265358979323846};  ///< [rad]
