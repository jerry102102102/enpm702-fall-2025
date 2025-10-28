/**
 * @file robot_control.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-25
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#pragma once
#include "robot_types.hpp"
#include <vector>
#include <functional>

//---------------------------------------------------------
// TODO: interpolate_linear (Task 3, template)
// - TEMPLATE must be defined in header (no .cpp)
// - STARTER does minimal work; you must complete
// TODO: Remove this block of comment before submission
//---------------------------------------------------------
/**
 * @brief 
 * 
 * @tparam State 
 * @param start 
 * @param goal 
 * @param alpha 
 * @return State 
 */
template <typename State>
State interpolate_linear(const State& start, const State& goal, double alpha)
{
    // clamp alpha to [0, 1] just in case
    if (alpha < 0.0) alpha = 0.0;
    if (alpha > 1.0) alpha = 1.0;

    State out{};
    // TODO [Task 3]:
    //  - Interpolate theta1, theta2 linearly
    //  - Set dtheta1, dtheta2 proportional to (goal - start)
    //
    // Starter: angles interpolated, velocities placeholder (0)
    out.theta1 = start.theta1 + alpha * (goal.theta1 - start.theta1);
    out.theta2 = start.theta2 + alpha * (goal.theta2 - start.theta2);
    out.dtheta1 = 0.0; // replace with finite-difference or proportional velocity
    out.dtheta2 = 0.0; // replace with finite-difference or proportional velocity
    return out;
}

//---------------------------------------------------------
// TODO: apply_filter (Task 3, non-template)
// - declared here, implemented in .cpp
// TODO: Remove this block of comment before submission
//---------------------------------------------------------
/**
 * @brief 
 * 
 * @param traj 
 * @param filter 
 */
void apply_filter(std::vector<JointState>& traj,
                  std::function<JointState(const JointState&)> filter);
