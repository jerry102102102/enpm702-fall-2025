cmake_minimum_required(VERSION 3.28)
project(week3 VERSION 1.0 LANGUAGES C CXX)



include_directories(include)
add_executable(week3_cpp src/week3.cpp)
add_executable(week3_exercise src/week3_exercise.cpp)

# Set C++17 standard for the targets
set_property(TARGET week3_cpp PROPERTY CXX_STANDARD 17)
set_property(TARGET week3_cpp PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET week3_exercise PROPERTY CXX_STANDARD 17)
set_property(TARGET week3_exercise PROPERTY CXX_STANDARD_REQUIRED ON)

# --- Add this section to integrate Valgrind ---
# Find the valgrind executable on the system
find_program(VALGRIND_EXECUTABLE valgrind)

# Only create the targets if valgrind is found
if(VALGRIND_EXECUTABLE)

    # --- Target for Memory Leak Checking (memcheck) ---
    add_custom_target(memcheck)

    add_custom_command(
        TARGET memcheck
        COMMAND ${VALGRIND_EXECUTABLE} --leak-check=full --track-origins=yes $<TARGET_FILE:week3_cpp>
        COMMENT "Running Valgrind Memcheck on week3_cpp"
    )

    # add_custom_command(
    #     TARGET memcheck
    #     COMMAND ${VALGRIND_EXECUTABLE} --leak-check=full --track-origins=yes $<TARGET_FILE:week3_exercise>
    #     COMMENT "Running Valgrind Memcheck on week3_exercise"
    # )


    # Ensure executables are built before any tool runs
    # add_dependencies(memcheck week3_cpp week3_exercise)
    add_dependencies(memcheck week3_cpp)

endif()
