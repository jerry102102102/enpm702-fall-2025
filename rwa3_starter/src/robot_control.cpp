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

void apply_filter(std::vector<JointState>& traj,
                  std::function<JointState(const JointState&)> filter) {
  for (auto& s : traj) {
    s = filter(s);
  }
}
