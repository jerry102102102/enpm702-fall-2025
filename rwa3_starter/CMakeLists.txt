cmake_minimum_required(VERSION 3.16)
project(rwa3 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(rwa3
    src/main.cpp
    src/robot_control.cpp
    src/robot_types.cpp
)

target_include_directories(rwa3 PRIVATE include)

if(MSVC)
    target_compile_options(rwa3 PRIVATE /W4 /permissive- /WX)
else()
    target_compile_options(rwa3 PRIVATE -Wall -Wextra -Werror -pedantic-errors)
endif()
