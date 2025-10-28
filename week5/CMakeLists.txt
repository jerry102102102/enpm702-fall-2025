cmake_minimum_required(VERSION 3.28)
project(week5 VERSION 1.0 LANGUAGES C CXX)



add_executable(week5_cpp src/main.cpp)
# target_include_directories(week5_cpp PRIVATE include)

# Set C++17 standard for the targets
set_property(TARGET week5_cpp PROPERTY CXX_STANDARD 17)
set_property(TARGET week5_cpp PROPERTY CXX_STANDARD_REQUIRED ON)

