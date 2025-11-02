/**
 * @file robot_control.cpp
 * @author Jerry C
 * @brief Implementation of trajectory filtering utilities.
 * @version 1.0
 * @date 2025-10-30
 *
 * @copyright Copyright (c) 2025
 */

#include "robot_control.hpp"

/*
TODO: Simple in-place filter application loop (Task 3)
TODO: Remove this block of comment before submission
*/

void apply_filter(std::vector<JointState> &traj,
                  std::function<JointState(const JointState &)> filter)
{
    // TODO [Task 3]: You may extend this to report how many states were clamped, etc.
    for (auto &s : traj)
    {
        s = filter(s);
    }
}
