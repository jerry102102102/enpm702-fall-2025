/**
 * @file main.cpp
 * @author Jerry C
 * @brief Demonstration program for ENPM702 RWA3: kinematics and control.
 * @version 1.0
 * @date 2025-10-30
 *
 * @copyright Copyright (c) 2025
 */

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>

#include "robot_control.hpp"
#include "robot_kinematics.hpp"
#include "robot_types.hpp"

int main() {
  std::cout << "=== Robot Kinematics & Control ===\n\n";
  // Not sure if there's a better way to get pi in C++17
  constexpr double pi = {3.14159265358979323846};
  JointState start = {0.0, 0.0};
  // According to the smample output
  JointState goal = {pi / 4.0, -pi / 6.0};

  // Set output formatting for floating-point values
  std::cout << std::fixed << std::setprecision(4);
  std::cout << "Generating smooth trajectory between:\n";
  std::cout << "Start  -> θ1 = " << start.theta1
            << " rad | θ2 = " << start.theta2
            << " rad | dθ1 = " << start.dtheta1
            << " rad/s | dθ2 = " << start.dtheta2 << " rad/s\n";
  std::cout << "Goal   -> θ1 = " << goal.theta1 << " rad | θ2 = " << goal.theta2
            << " rad | dθ1 = " << goal.dtheta1
            << " rad/s | dθ2 = " << goal.dtheta2 << " rad/s\n\n";
  // Use uniuque_ptr to manage trajectory memory
  auto traj = std::make_unique<std::vector<JointState>>();
  // reserve space ahead of time
  traj->reserve(k_num_samples);
  // Store raw interpolated trajectory
  std::vector<JointState> raw_traj;
  raw_traj.reserve(k_num_samples);
  // Lambda to clamp joint angles within limits
  const auto clamp_joint_angles = [](JointState state) {
    if (!check_joint_limits(state)) {
      state.theta1 = std::clamp(state.theta1, -k_joint_limit, k_joint_limit);
      state.theta2 = std::clamp(state.theta2, -k_joint_limit, k_joint_limit);
    }
    return state;
  };
  // Generate trajectory samples
  for (std::size_t i = 0; i < k_num_samples; ++i) {
    // Compute interpolation factor
    const double alpha = static_cast<double>(i) * k_alpha_step;
    JointState sample = interpolate_linear(start, goal, alpha);
    // Store unfiltered sample
    raw_traj.push_back(sample);

    JointState filtered = sample;
    // Clamp joint angles if out of limits (for safety)
    if (!check_joint_limits(filtered)) {
      filtered = clamp_joint_angles(filtered);
    }
    traj->push_back(filtered);
  }
  // Display unfiltered trajectory summary
  std::cout << "Trajectory points: " << raw_traj.size() << '\n';
  std::cout << "Unfiltered Trajectory (every 5th point shown):\n";
  for (std::size_t i = 0; i < raw_traj.size(); i += 5) {
    const auto& s = raw_traj[i];
    print_joint_state(s);
  }

  std::cout << '\n';

  // Lambda to clamp velocities within limits
  auto clamp_to_limit = [](double value, double limit) {
    const double magnitude = std::min(std::abs(value), limit);
    return value == 0.0 ? 0.0 : std::copysign(magnitude, value);
  };

  // Lambda filter to clamp joint velocities
  auto clamp_vel = [clamp_to_limit](const JointState& state) {
    JointState filtered = state;
    filtered.dtheta1 = clamp_to_limit(state.dtheta1, k_vel_limit);
    filtered.dtheta2 = clamp_to_limit(state.dtheta2, k_vel_limit);
    return filtered;
  };

  // Display and apply velocity filter
  std::cout << "Applying velocity-limit filter: |dθ| ≤ " << k_vel_limit
            << " rad/s\n";
  // Apply the velocity clamping filter lambda
  apply_filter(*traj, clamp_vel);

  // Check if all velocities are within limits after filtering
  const bool velocities_within_limit =
      std::all_of(traj->begin(), traj->end(), [](const JointState& state) {
        return std::abs(state.dtheta1) <= k_vel_limit &&
               std::abs(state.dtheta2) <= k_vel_limit;
      });
  std::cout
      << "-> "
      << (velocities_within_limit
              ? "Filter applied successfully, all values within limits.\n\n"
              : "Filter applied; values exceeding limits were clamped.\n\n");

  std::cout << "Filtered Trajectory (first 5 points):\n";
  const std::size_t samples_to_show{5};
  for (std::size_t i = 0; i < samples_to_show; ++i) {
    const auto& s = (*traj)[i];
    print_joint_state(s);
  }
  // Use unique_ptr to manage end-effector poses memory
  auto end_effecotr_poses = std::make_unique<std::vector<EndEffectorPose>>();
  end_effecotr_poses->reserve(traj->size());
  // Compute end-effector poses for the filtered trajectory
  for (const auto& state : *traj) {
    end_effecotr_poses->push_back(forward_kinematics(state));
  }
  // Display end-effector poses
  std::cout << "\nComputing end-effector poses for filtered trajectory...\n";
  std::cout << std::setprecision(2);
  std::cout << "Link lengths: L1 = " << k_link1 << " m, L2 = " << k_link2
            << " m\n\n";
  std::cout << std::setprecision(4);
  std::cout << "End-Effector Trajectory (all points):\n";
  for (std::size_t i = 0; i < end_effecotr_poses->size(); ++i) {
    const auto& pose = (*end_effecotr_poses)[i];
    std::cout << '[' << i << "]  x = " << pose.x << " m,  y = " << pose.y
              << " m\n";
  }
  // Display summary
  std::cout << "\nSummary\n";
  std::cout << "--------\n";
  std::cout << "\u2022 Total joint states: " << traj->size() << '\n';
  std::cout << "\u2022 Velocity filter: active (|dθ| ≤ " << k_vel_limit
            << ")\n\n";
  std::cout << "Program finished successfully.\n";

  return 0;
}
