cmake_minimum_required(VERSION 3.16)
project(rwa2 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(rwa2 src/main.cpp)
target_include_directories(rwa2 PRIVATE include)

target_compile_options(rwa2 PRIVATE -Wall -Wextra -pedantic-errors)
