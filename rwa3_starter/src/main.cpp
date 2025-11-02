/**
 * @file main.cpp
 * @author Jerry C
 * @brief Demonstration program for ENPM702 RWA3: kinematics and control.
 * @version 1.0
 * @date 2025-10-30
 *
 * @copyright Copyright (c) 2025
 */

#include "robot_control.hpp"
#include "robot_kinematics.hpp"
#include "robot_types.hpp"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>

int main()
{
    std::cout << "=== Robot Kinematics & Control (RWA3) ===\n";
    std::cout << "Link lengths: L1 = " << std::fixed << std::setprecision(2) << k_link1
              << " m, L2 = " << k_link2 << " m\n\n";

    const double pi = std::acos(-1.0);
    const JointState start{0.0, 0.0};
    const JointState goal{pi / 4.0, -pi / 6.0};

    std::cout << "Start state:\n";
    print_joint_state(start);
    std::cout << "Goal state:\n";
    print_joint_state(goal);
    std::cout << '\n';

    // 2) Trajectory container (ownership requirement)
    auto traj = std::make_unique<std::vector<JointState>>();
    traj->reserve(k_num_samples);

    // TODO: (Task 3) Generate trajectory samples into *traj using interpolate_linear(...)
    for (std::size_t i = 0; i < k_num_samples; ++i)
    {
        const double alpha = static_cast<double>(i) * k_alpha_step;
        traj->push_back(interpolate_linear(start, goal, alpha));
    }

    std::cout << "Trajectory points: " << traj->size() << '\n';

    // 3) Define & apply velocity-limit filter (lambda) — you have to write the lambda
    // TODO: (Task 3) Create a lambda that clamps |dθ| ≤ k_vel_limit and call apply_filter(*traj, your_lambda);
    auto clamp_to_limit = [](double value, double limit) {
        const double magnitude = std::min(std::abs(value), limit);
        return (value == 0.0) ? 0.0 : std::copysign(magnitude, value);
    };

    auto clamp_vel = [clamp_to_limit](const JointState& state) {
        JointState filtered = state;
        filtered.dtheta1 = clamp_to_limit(state.dtheta1, k_vel_limit);
        filtered.dtheta2 = clamp_to_limit(state.dtheta2, k_vel_limit);
        return filtered;
    };

    std::cout << "Applying velocity-limit filter: |dθ| ≤ " << std::setprecision(4)
              << k_vel_limit << " rad/s\n";
    apply_filter(*traj, clamp_vel);

    // 4) End-effector poses (shared ownership)
    auto ee_poses = std::make_unique<std::vector<EndEffectorPose>>();
    ee_poses->reserve(traj->size());

    // TODO: (Task 2 & 4) For each state in *traj, compute FK and push_back to *ee_poses
    for (const auto &state : *traj)
    {
        ee_poses->push_back(forward_kinematics(state));
    }

    // 5) Reporting: you should flesh this out
    // TODO: Print a brief summary (counts, first/last states, a few (x,y) samples).
    std::cout << "\nFiltered start state:\n";
    print_joint_state(traj->front());
    std::cout << "Filtered goal state:\n";
    print_joint_state(traj->back());

    std::cout << '\n' << std::fixed << std::setprecision(4);
    std::cout << "End-effector path (x, y in meters):\n";
    for (std::size_t i = 0; i < ee_poses->size(); ++i)
    {
        const auto &pose = (*ee_poses)[i];
        std::cout << "  [" << std::setw(2) << i << "] x = " << std::setw(7) << pose.x
                  << " m, y = " << std::setw(7) << pose.y << " m\n";
    }

    const auto &final_pose = ee_poses->back();
    std::cout << "\nSummary:\n";
    std::cout << "  Samples: " << traj->size() << '\n';
    std::cout << "  Final end-effector position: x = " << final_pose.x << " m, y = "
              << final_pose.y << " m\n";
    std::cout << "  Velocity limit enforced: ±" << k_vel_limit << " rad/s\n";

    return 0;
}
