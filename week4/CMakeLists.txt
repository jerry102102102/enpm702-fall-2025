cmake_minimum_required(VERSION 3.28)
project(week4 VERSION 1.0 LANGUAGES C CXX)



include_directories(include)
add_executable(week4_cpp src/week4.cpp)
# add_executable(week3_exercise src/week3_exercise.cpp)

# Set C++17 standard for the targets
set_property(TARGET week4_cpp PROPERTY CXX_STANDARD 17)
set_property(TARGET week4_cpp PROPERTY CXX_STANDARD_REQUIRED ON)
# set_property(TARGET week3_exercise PROPERTY CXX_STANDARD 17)
# set_property(TARGET week3_exercise PROPERTY CXX_STANDARD_REQUIRED ON)

