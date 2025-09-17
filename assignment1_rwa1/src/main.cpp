#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>

int main() {
  // 固定兩位小數、歡迎訊息
  std::cout << std::fixed << std::setprecision(2);
  std::cout << "Welcome to ENPM702 RWA1 (simplified).\n";

  // 機器人狀態（以大括號初始化）
  double robot_x_position{0.0};
  double robot_y_position{0.0};
  double robot_orientation_deg{0.0};
  const double pi{3.14159};

  // 主迴圈：直到使用者選擇 Exit
  while (true) {
    // --- 顯示選單 ---
    std::cout << "\n----- Menu -----\n"
                 " 1) Move Forward (meters)\n"
                 " 2) Turn Left   (degrees)\n"
                 " 3) Turn Right  (degrees)\n"
                 " 4) Get Robot Status\n"
                 " 5) Exit\n"
                 " 6) Backward (Bonus, meters)\n"
                 " 7) Reset Pose (Bonus)\n";

    // 讀選項（只做最基本檢查：是否為數字、是否在 1~7）
    int menu_choice{};
    std::cout << "Select (1-7): ";
    if (!(std::cin >> menu_choice)) {
      // 遇到非數字：清除錯誤並丟棄整行，回到下一輪
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input. Please enter a number 1-7.\n";
      continue;
    }
    // 丟棄本行殘留（包含換行）
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // 只接受 1~7
    if (menu_choice < 1 || menu_choice > 7) {
      std::cout << "Out of range. Choose between 1 and 7.\n";
      continue;
    }

    // --- 動作分支 ---
    if (menu_choice == 1 || menu_choice == 6) {
      // Move Forward / Backward（Backward 只是距離取負號）
      const bool is_backward = (menu_choice == 6);
      const char* label = is_backward ? "Backward" : "Forward";

      double distance{};
      std::cout << label << " distance (meters, > 0): ";
      if (!(std::cin >> distance)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Distance must be a number.\n";
        continue;
      }
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      if (distance <= 0.0) {
        std::cout << "Distance must be > 0.\n";
        continue;
      }

      // Backward 就把距離改為負值，公式相同
      if (is_backward) distance = -distance;

      // 角度轉弧度 → 更新位置
      const double theta = robot_orientation_deg * (pi / 180.0);
      robot_x_position += distance * std::cos(theta);
      robot_y_position += distance * std::sin(theta);

      std::cout << label << " OK. Position -> x: " << robot_x_position
                << " m, y: " << robot_y_position << " m\n";

    } else if (menu_choice == 2 || menu_choice == 3) {
      // Turn Left / Right（Right 就是減角，最後做正規化）
      const bool is_left = (menu_choice == 2);
      const char* label = is_left ? "left" : "right";

      double angle{};
      std::cout << "Turn " << label << " by (degrees, > 0): ";
      if (!(std::cin >> angle)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Angle must be a number.\n";
        continue;
      }
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      if (angle <= 0.0) {
        std::cout << "Angle must be > 0.\n";
        continue;
      }

      // 更新角度並正規化到 [0, 360)
      robot_orientation_deg += (is_left ? angle : -angle);
      robot_orientation_deg = std::fmod(robot_orientation_deg, 360.0);
      if (robot_orientation_deg < 0.0) robot_orientation_deg += 360.0;

      std::cout << "Turn OK. Orientation: " << robot_orientation_deg << " deg\n";

    } else if (menu_choice == 4) {
      // 顯示狀態
      std::cout << "Status -> x: " << robot_x_position
                << " m, y: " << robot_y_position
                << " m, theta: " << robot_orientation_deg << " deg\n";

    } else if (menu_choice == 7) {
      // Reset Pose（Bonus）
      robot_x_position = 0.0;
      robot_y_position = 0.0;
      robot_orientation_deg = 0.0;
      std::cout << "Pose reset to (0.00, 0.00, 0.00 deg).\n";

    } else { // menu_choice == 5
      std::cout << "Goodbye!\n";
      break;
    }
  }

  return 0;
}
