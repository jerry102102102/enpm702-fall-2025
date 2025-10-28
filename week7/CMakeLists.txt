cmake_minimum_required(VERSION 3.28)
project(week7 VERSION 1.0 LANGUAGES C CXX)



add_executable(week7_cpp src/main.cpp src/week7.cpp)
target_include_directories(week7_cpp PRIVATE include)

# Set C++17 standard for the targets
set_property(TARGET week7_cpp PROPERTY CXX_STANDARD 17)
set_property(TARGET week7_cpp PROPERTY CXX_STANDARD_REQUIRED ON)

