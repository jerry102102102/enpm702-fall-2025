/**
 * @file main.cpp
 * @author TODO Add your name
 * @brief TODO Add a description
 * @version 1.0
 * @date 09-30-2025
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <algorithm>
#include <array>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "sensor_types.hpp"

int main() {
  std::cout << "=== ROBOT TRIPLE-SENSOR SYSTEM ===\n\n";
  std::cout << "Generating sensor data for " << num_timestamps
            << " timestamps...\n\n";

  // ========================================================================
  // Step 1: Data Generation and Storage
  // ========================================================================

  std::vector<TimestampData> sensor_readings;
  sensor_readings.reserve(num_timestamps);

  std::random_device random_source;
  std::mt19937 random_engine{random_source()};
  std::uniform_real_distribution<double> lidar_distribution{lidar_min_range,
                                                            lidar_max_range};
  std::uniform_int_distribution<int> camera_distribution{rgb_min, rgb_max};
  std::uniform_real_distribution<double> imu_distribution{imu_min_rotation,
                                                          imu_max_rotation};

  for (int timestamp{0}; timestamp < num_timestamps; ++timestamp) {
    LidarData lidar_readings(lidar_readings_count);
    for (auto &reading : lidar_readings) {
      reading = lidar_distribution(random_engine);
    }

    const int red{camera_distribution(random_engine)};
    const int green{camera_distribution(random_engine)};
    const int blue{camera_distribution(random_engine)};
    const CameraData camera_readings{red, green, blue};

    const ImuData imu_readings{imu_distribution(random_engine),
                               imu_distribution(random_engine),
                               imu_distribution(random_engine)};

    sensor_readings.push_back(TimestampData{
        std::move(lidar_readings), camera_readings, imu_readings, timestamp});
  }

  // ========================================================================
  // Step 2: Data Processing Loop
  // ========================================================================

  const std::unordered_map<std::string, int> initial_counts{
      {"LIDAR", 0}, {"Camera", 0}, {"IMU", 0}};
  std::unordered_map<std::string, int> valid_readings{initial_counts};
  std::unordered_map<std::string, int> total_readings{initial_counts};

  double total_lidar_avg_distance{0.0};
  double total_camera_brightness{0.0};
  double total_imu_rotation{0.0};
  int total_obstacles_detected{0};
  int day_mode_count{0};
  int night_mode_count{0};
  int stable_mode_count{0};
  int unstable_mode_count{0};

  std::vector<double> lidar_average_history;
  std::vector<double> camera_brightness_history;
  std::vector<double> imu_rotation_history;
  std::vector<int> processed_timestamps;

  lidar_average_history.reserve(num_timestamps);
  camera_brightness_history.reserve(num_timestamps);
  imu_rotation_history.reserve(num_timestamps);
  processed_timestamps.reserve(num_timestamps);

  std::cout << std::fixed << std::setprecision(2);

  for (const auto &timestamp_data : sensor_readings) {
    // ========================================================================
    // Step 3: Sensor-Specific Processing
    // ========================================================================
    std::cout << "Processing Timestamp: " << timestamp_data.timestamp << '\n';
    processed_timestamps.push_back(timestamp_data.timestamp);

    const auto &lidar_values{timestamp_data.lidar_readings};
    const double lidar_sum{
        std::accumulate(lidar_values.cbegin(), lidar_values.cend(), double{})};
    const double lidar_average{lidar_sum /
                               static_cast<double>(lidar_values.size())};
    lidar_average_history.push_back(lidar_average);
    const int obstacle_count{static_cast<int>(std::count_if(
        lidar_values.cbegin(), lidar_values.cend(),
        [](double reading) { return reading < obstacle_threshold; }))};
    const bool lidar_valid{
        std::all_of(lidar_values.cbegin(), lidar_values.cend(),
                    [](double reading) { return reading > lidar_min_valid; })};
    const std::string lidar_status{lidar_valid ? "GOOD" : "POOR"};

    std::cout << "LIDAR: [";
    for (std::size_t index{0}; index < lidar_values.size(); ++index) {
      std::cout << lidar_values[index];
      if ((index + 1U) < lidar_values.size()) {
        std::cout << ", ";
      }
    }
    std::cout << "] Avg: " << lidar_average
              << " m, Obstacles: " << obstacle_count
              << ", Status: " << lidar_status << '\n';

    // ========================================================================
    // Step 4: Quality Assessment and Status Determination
    // ========================================================================

    ++total_readings["LIDAR"];
    if (lidar_valid) {
      ++valid_readings["LIDAR"];
    }
    total_lidar_avg_distance += lidar_average;
    total_obstacles_detected += obstacle_count;

    const auto [red_value, green_value,
                blue_value]{timestamp_data.camera_readings};
    const double channel_count{
        static_cast<double>(std::tuple_size<CameraData>::value)};
    const double brightness{
        static_cast<double>(red_value + green_value + blue_value) /
        channel_count};
    camera_brightness_history.push_back(brightness);
    const bool is_day{brightness > day_night_threshold};
    const bool camera_good{brightness > brightness_threshold};
    const std::string camera_mode{is_day ? "DAY" : "NIGHT"};
    const std::string camera_status{camera_good ? "GOOD" : "POOR"};

    std::cout << "Camera: RGB(" << red_value << ", " << green_value << ", "
              << blue_value << "), Brightness: " << brightness
              << ", Mode: " << camera_mode << ", Status: " << camera_status
              << '\n';

    ++total_readings["Camera"];
    if (camera_good) {
      ++valid_readings["Camera"];
    }
    total_camera_brightness += brightness;
    if (is_day) {
      ++day_mode_count;
    } else {
      ++night_mode_count;
    }

    const auto [roll, pitch, yaw]{timestamp_data.imu_readings};
    const double total_rotation{
        std::sqrt((roll * roll) + (pitch * pitch) + (yaw * yaw))};
    imu_rotation_history.push_back(total_rotation);
    const bool stable_mode{std::abs(roll) < imu_stability_threshold &&
                           std::abs(pitch) < imu_stability_threshold &&
                           std::abs(yaw) < imu_stability_threshold};
    const bool imu_in_range{
        roll >= imu_min_rotation && roll <= imu_max_rotation &&
        pitch >= imu_min_rotation && pitch <= imu_max_rotation &&
        yaw >= imu_min_rotation && yaw <= imu_max_rotation};
    const std::string imu_mode{stable_mode ? "STABLE" : "UNSTABLE"};
    const std::string imu_status{imu_in_range ? "GOOD" : "POOR"};

    std::cout << "IMU: RPY(" << roll << ", " << pitch << ", " << yaw
              << "), Total Rotation: " << total_rotation
              << " deg, Mode: " << imu_mode << ", Status: " << imu_status
              << "\n\n";

    ++total_readings["IMU"];
    if (imu_in_range) {
      ++valid_readings["IMU"];
    }
    total_imu_rotation += total_rotation;
    if (stable_mode) {
      ++stable_mode_count;
    } else {
      ++unstable_mode_count;
    }
  }

  // ========================================================================
  // STEP 5: Summary Statistics and Display
  // ========================================================================

  const int total_operations{std::accumulate(
      total_readings.cbegin(), total_readings.cend(), 0,
      [](int sum, const auto &entry) { return sum + entry.second; })};
  const int total_valid{std::accumulate(
      valid_readings.cbegin(), valid_readings.cend(), 0,
      [](int sum, const auto &entry) { return sum + entry.second; })};
  constexpr int percentage_scale{100};
  const double valid_percentage{total_operations > 0
                                    ? (static_cast<double>(total_valid) /
                                       static_cast<double>(total_operations)) *
                                          static_cast<double>(percentage_scale)
                                    : 0.0};

  const double average_lidar_distance{
      total_readings["LIDAR"] > 0
          ? total_lidar_avg_distance /
                static_cast<double>(total_readings["LIDAR"])
          : 0.0};
  const double average_camera_brightness{
      total_readings["Camera"] > 0
          ? total_camera_brightness /
                static_cast<double>(total_readings["Camera"])
          : 0.0};
  const double average_imu_rotation{
      total_readings["IMU"] > 0
          ? total_imu_rotation / static_cast<double>(total_readings["IMU"])
          : 0.0};

  std::cout << "=== SUMMARY STATISTICS ===\n";
  std::cout << "Total Sensor Processing Operations: " << total_operations
            << '\n';
  std::cout << "Valid Sensor Readings: " << total_valid << " / "
            << total_operations << " (" << valid_percentage << "%)\n";

  std::cout << "Reliability by Sensor:\n";
  const std::array<std::string, 3> sensor_names{"LIDAR", "Camera", "IMU"};
  for (const auto &sensor_name : sensor_names) {
    const int sensor_total{total_readings[sensor_name]};
    const int sensor_valid{valid_readings[sensor_name]};
    const double reliability{sensor_total > 0
                                 ? (static_cast<double>(sensor_valid) /
                                    static_cast<double>(sensor_total)) *
                                       static_cast<double>(percentage_scale)
                                 : 0.0};
    std::cout << "  - " << sensor_name << ": " << reliability << "%\n";
  }

  std::cout << "Average LIDAR Distance: " << average_lidar_distance << " m\n";
  std::cout << "Average Camera Brightness: " << average_camera_brightness
            << '\n';
  std::cout << "Average IMU Total Rotation: " << average_imu_rotation
            << " deg\n";
  std::cout << "Total Obstacles Detected: " << total_obstacles_detected << '\n';
  std::cout << "DAY/NIGHT Count: " << day_mode_count << " / "
            << night_mode_count << '\n';
  std::cout << "STABLE/UNSTABLE Count: " << stable_mode_count << " / "
            << unstable_mode_count << "\n\n";

  if (!lidar_average_history.empty()) {
    const auto lidar_minmax{std::minmax_element(lidar_average_history.cbegin(),
                                                lidar_average_history.cend())};
    const std::size_t lidar_min_index{static_cast<std::size_t>(
        std::distance(lidar_average_history.cbegin(), lidar_minmax.first))};
    const std::size_t lidar_max_index{static_cast<std::size_t>(
        std::distance(lidar_average_history.cbegin(), lidar_minmax.second))};
    std::cout << "LIDAR Average Range: " << *lidar_minmax.first
              << " m (Timestamp " << processed_timestamps[lidar_min_index]
              << ") to " << *lidar_minmax.second << " m (Timestamp "
              << processed_timestamps[lidar_max_index] << ")\n";
  }

  if (!camera_brightness_history.empty()) {
    const auto brightness_minmax{std::minmax_element(
        camera_brightness_history.cbegin(), camera_brightness_history.cend())};
    const std::size_t brightness_min_index{
        static_cast<std::size_t>(std::distance(
            camera_brightness_history.cbegin(), brightness_minmax.first))};
    const std::size_t brightness_max_index{
        static_cast<std::size_t>(std::distance(
            camera_brightness_history.cbegin(), brightness_minmax.second))};
    std::cout << "Camera Brightness Range: " << *brightness_minmax.first
              << " (Timestamp " << processed_timestamps[brightness_min_index]
              << ") to " << *brightness_minmax.second << " (Timestamp "
              << processed_timestamps[brightness_max_index] << ")\n";
  }

  if (!imu_rotation_history.empty()) {
    const auto rotation_minmax{std::minmax_element(
        imu_rotation_history.cbegin(), imu_rotation_history.cend())};
    const std::size_t rotation_min_index{static_cast<std::size_t>(
        std::distance(imu_rotation_history.cbegin(), rotation_minmax.first))};
    const std::size_t rotation_max_index{static_cast<std::size_t>(
        std::distance(imu_rotation_history.cbegin(), rotation_minmax.second))};
    std::cout << "IMU Rotation Range: " << *rotation_minmax.first
              << " deg (Timestamp " << processed_timestamps[rotation_min_index]
              << ") to " << *rotation_minmax.second << " deg (Timestamp "
              << processed_timestamps[rotation_max_index] << ")\n";
  }

  std::cout << '\n';

  std::cout << "=== END OF PROGRAM ===\n";
}
