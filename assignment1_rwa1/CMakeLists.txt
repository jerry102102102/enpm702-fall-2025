cmake_minimum_required(VERSION 3.20)

# This standalone CMake file builds the ENPM702 RWA1 executable without touching the root configuration.
project(enpm702_rwa1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Debug)
add_compile_options(-Wall -Wextra)
add_executable(rwa1
    src/main.cpp
)

# Place runtime outputs under the local build tree so all artifacts stay with this directory.
set_target_properties(rwa1 PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
