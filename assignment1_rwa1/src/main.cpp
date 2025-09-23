#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>

int main() {
  // stable two decimal places, cout welcome message
  std::cout << std::fixed << std::setprecision(2);
  std::cout << "Welcome to the Robot Simulator\n";

  // initialize robot state
  double robot_x_position{0.0};
  double robot_y_position{0.0};
  double robot_orientation_deg{0.0};
  // pi constant
  constexpr double pi{3.14159};
  int menu_choice{};
  // main loop for control menu and user input
  while (true) {
    // display menu]
    std::cout << "\n‐‐‐ Robot Menu ‐‐‐\n"
                 " 1. Move Forward\n"
                 " 2. Turn Left\n"
                 " 3. Turn Right\n"
                 " 4. Get Robot Status\n"
                 " 5. Exit\n"
                 " 6. Backward\n"
                 " 7. Reset Pose\n";

    // get user input for menu choice
    std::cout << "Enter your choice: ";
    // if encounter wrong input, cin clear error and ignore the rest of the line
    if (!(std::cin >> menu_choice)) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input. Please enter a valid number.\n";
      continue;
    }
    // check for trailing characters
    {
      int ch = std::cin.peek();
      while (std::isspace(ch) && ch != '\n') {
        std::cin.get();
        ch = std::cin.peek();
      }
      if (ch != '\n') {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a valid number.\n";
        continue;
      }
    }
    // ignore the rest of the line in case of extra input
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // check if input is in range
    if (menu_choice < 1 || menu_choice > 7) {
      std::cout << "Invalid choice. Please enter a number between 1 and 7\n";
      continue;
    }

    // action branches
    switch (menu_choice) {
      case 1:  // Move Forward
      {
        double distance{};
        std::cout << "Enter distance to move forward (e.g., 5.5):";
        // validate input
        if (!(std::cin >> distance)) {
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          std::cout << "Invalid input. Please enter a valid number.\n";
          continue;
        }
        // check for trailing characters
        {
          int ch = std::cin.peek();
          while (std::isspace(ch) && ch != '\n') {
            std::cin.get();
            ch = std::cin.peek();
          }
          if (ch != '\n') {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid number.\n";
            continue;
          }
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (distance <= 0.0) {
          std::cout << "Invalid distance. Please enter a positive number.\n";
          continue;
        }

        // calculate new position
        const double angle_rad = robot_orientation_deg * pi / 180.0;
        robot_x_position += distance * std::cos(angle_rad);
        robot_y_position += distance * std::sin(angle_rad);

        // output new position
        std::cout << "Robot moved " << distance
                  << " meters forward. New position: " << "("
                  << robot_x_position << ", " << robot_y_position << ")\n";
        break;
      }
      case 2: {  // Turn Left
        double angle{};
        std::cout << "Enter angle to turn left in degrees s (e.g., 45.0): ";
        // validate input
        if (!(std::cin >> angle)) {
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          std::cout << "Invalid input. Please enter a valid number.\n";
          continue;
        }
        // check for trailing characters
        {
          int ch = std::cin.peek();
          while (std::isspace(ch) && ch != '\n') {
            std::cin.get();
            ch = std::cin.peek();
          }
          if (ch != '\n') {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid number.\n";
            continue;
          }
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (angle <= 0.0) {
          std::cout << "Angle must be > 0.\n";
          continue;
        }
        // update orientation
        robot_orientation_deg += angle;
        // normalize to [0, 360)
        robot_orientation_deg = std::fmod(robot_orientation_deg, 360.0);
        // if negative, wrap around
        if (robot_orientation_deg < 0.0) robot_orientation_deg += 360.0;

        // output new orientation
        std::cout << "Robot turned left by " << angle
                  << " degrees. New orientation: " << robot_orientation_deg
                  << " degrees\n";
        break;
      }
      case 3: {  // Turn Right
        double angle{};
        std::cout << "Enter angle to turn right in degrees (e.g., 45.0): ";
        // validate input
        if (!(std::cin >> angle)) {
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          std::cout << "Invalid input. Please enter a valid number.\n";
          continue;
        }
        // check for trailing characters
        {
          int ch = std::cin.peek();
          while (std::isspace(ch) && ch != '\n') {
            std::cin.get();
            ch = std::cin.peek();
          }
          if (ch != '\n') {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid number.\n";
            continue;
          }
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (angle <= 0.0) {
          std::cout << "Angle must be > 0.\n";
          continue;
        }
        // update orientation(turn right means decrease angle)
        robot_orientation_deg -= angle;
        // normalize to [0, 360)
        robot_orientation_deg = std::fmod(robot_orientation_deg, 360.0);
        // if negative, wrap around
        if (robot_orientation_deg < 0.0) robot_orientation_deg += 360.0;

        // output new orientation
        std::cout << "Robot turned right by " << angle
                  << " degrees. New orientation: " << robot_orientation_deg
                  << " degrees\n";
        break;
      }
      case 4:  // Get Robot Status
        std::cout << "Robot Status:\n"
                  << " Position: (" << robot_x_position << ", "
                  << robot_y_position << ")\n"
                  << " Orientation: " << robot_orientation_deg << " degrees\n";
        break;
      case 5:  // Exit
        std::cout << "Exiting Robot Simulator. Goodbye!\n";
        return 0;
        break;
      case 6:  // Backward
      {
        double distance{};
        std::cout << "Enter distance to move backward (e.g., 5.5):";
        // validate input
        if (!(std::cin >> distance)) {
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          std::cout << "Invalid input. Please enter a valid number.\n";
          continue;
        }
        // check for trailing characters
        {
          int ch = std::cin.peek();
          while (std::isspace(ch) && ch != '\n') {
            std::cin.get();
            ch = std::cin.peek();
          }
          if (ch != '\n') {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid number.\n";
            continue;
          }
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (distance <= 0.0) {
          std::cout << "Invalid distance. Please enter a positive number.\n";
          continue;
        }

        // calculate new position
        const double angle_rad = robot_orientation_deg * pi / 180.0;
        robot_x_position -= distance * std::cos(angle_rad);
        robot_y_position -= distance * std::sin(angle_rad);

        // output new position
        std::cout << "Robot moved " << distance
                  << " meters backward. New position: " << "("
                  << robot_x_position << ", " << robot_y_position << ")\n";
        break;
      }
      case 7:  // Reset Pose
      {
        robot_x_position = 0.0;
        robot_y_position = 0.0;
        robot_orientation_deg = 0.0;
        std::cout << "Robot pose has been reset to the origin with 0 degrees "
                     "orientation.\n";
        break;
      }
      default:  // should not reach here due to prior validation
        std::cout << "Invalid choice. Please enter a number between 1 and 7.\n";
        break;
    }
  }
  // should never reach here
  return 0;
}