/**
 * @file sensor_types.hpp
 * @author TODO Include your name
 * @brief TODO Include a description
 * @version 1.0
 * @date 09-30-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include <vector>
#include <tuple>
#include <string>

// Data structures for different sensor types
using LidarData = std::vector<double>;          // 8 distance readings in meters
using CameraData = std::tuple<int, int, int>;   // RGB values (0-255 each)
using ImuData = std::tuple<double, double, double>; // Roll, Pitch, Yaw in degrees

// General configuration
constexpr int num_timestamps{5};

// LIDAR configuration constants
constexpr int lidar_readings_count{8};
constexpr double lidar_min_range{0.01};
constexpr double lidar_max_range{10.0};
constexpr double lidar_min_valid{0.05};
constexpr double obstacle_threshold{2.0};

// Camera configuration constants
constexpr int rgb_min{0};
constexpr int rgb_max{255};
constexpr double brightness_threshold{20.0};
constexpr double day_night_threshold{100.0};

// IMU configuration constants
constexpr double imu_min_rotation{-90.0};
constexpr double imu_max_rotation{90.0};
constexpr double imu_stability_threshold{5.0};


// Structure to hold sensor readings at each timestamp
struct TimestampData {
    LidarData lidar_readings;
    CameraData camera_readings;
    ImuData imu_readings;
    int timestamp;
};
