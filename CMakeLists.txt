cmake_minimum_required(VERSION 3.28)
project(enpm702)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Common settings for all lectures
set(CMAKE_BUILD_TYPE Debug)
add_compile_options(-Wall -Wextra)

# Optionally add all lecture subdirectories
# add_subdirectory(week1)
add_subdirectory(week2)
# add_subdirectory(week3)
# add_subdirectory(reading_material)