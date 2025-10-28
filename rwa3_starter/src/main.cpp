/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-25
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "robot_types.hpp"
#include "robot_kinematics.hpp"
#include "robot_control.hpp"

#include <iostream>
#include <memory>
#include <vector>
#include <cmath>

int main() {
    std::cout << "=== Robot Kinematics & Control (Starter Skeleton) ===\n\n";

    // 1) Start/Goal (you may tweak these if you want)
    const JointState start{0.0, 0.0};                 // θ1=0, θ2=0
    const JointState goal{M_PI / 4.0, -M_PI / 6.0};   // θ1=45°, θ2=-30°
    print_joint_state(start);
    print_joint_state(goal);
    std::cout << '\n';

    // 2) Trajectory container (ownership requirement)
    auto traj = std::make_unique<std::vector<JointState>>();
    traj->reserve(k_num_samples);

    // TODO: (Task 3) Generate trajectory samples into *traj using interpolate_linear(...)
    // for (int i = 0; i < kNumSamples; ++i) {
    //     const double alpha = static_cast<double>(i) * kAlphaStep;
    //     traj->push_back(interpolate_linear(start, goal, alpha));
    // }

    // 3) Define & apply velocity-limit filter (lambda) — you have to write the lambda
    // TODO: (Task 3) Create a lambda that clamps |dθ| ≤ k_vel_limit and call apply_filter(*traj, your_lambda);

    // 4) End-effector poses (shared ownership)
    auto ee_poses = std::make_shared<std::vector<EndEffectorPose>>();
    ee_poses->reserve(traj->size());

    // TODO: (Task 2 & 4) For each state in *traj, compute FK and push_back to *ee_poses

    // 5) Reporting: you should flesh this out
    // TODO: Print a brief summary (counts, first/last states, a few (x,y) samples).

    // avoid unused-variable warnings until you implement
    (void)start; (void)goal; (void)traj; (void)ee_poses;

    std::cout << "\n[Note] Implement the TODOs in main() and the header functions to see results.\n";
}
