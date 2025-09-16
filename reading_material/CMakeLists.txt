cmake_minimum_required(VERSION 3.28)
project(reading_material VERSION 0.1.0 LANGUAGES C CXX)



# include_directories(include)
add_executable(rm_cpp src/rm.cpp)

# Set C++17 standard for the target
set_property(TARGET rm_cpp PROPERTY CXX_STANDARD 17)
set_property(TARGET rm_cpp PROPERTY CXX_STANDARD_REQUIRED ON)