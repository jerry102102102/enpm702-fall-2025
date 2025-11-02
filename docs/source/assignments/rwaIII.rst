.. default-domain:: cpp
.. _rwaIII:

====================================================
Assignment 3 - Robot Kinematics and Control
====================================================

- **Course:** ENPM702 - C++ for Robotics  
- **Duration:** 1.5 weeks  
- **Due Date:** 11/05/2025  
- **Total Points:** 36  
- **Language:** C++17  

.. admonition:: Changelog

   **Version 1.2.0** (2025-10-30)

   - Simplified the terminal output
   - Removed shared pointer. Only use `std::unique_ptr`
   - Updated the pseudocode for lambdas. Both lambdas must be created in the `main()` function


----------------------------------------------------
Assignment Overview
----------------------------------------------------

This assignment integrates **modern C++17 programming constructs** (templates, lambdas, and smart pointers) with **fundamental robotics concepts**.  
You will build a simplified **2-DOF planar robot arm controller** that demonstrates how software models, plans, and manages a robot's motion.

You will:

- Represent robot states and end-effector positions using **Plain Old Data (POD)** structs.
- Implement **forward kinematics** to compute the end-effector pose from joint angles.
- Generate a **smooth linear trajectory** between two configurations.
- Apply a **velocity-limit filter** using a **lambda callable**.
- Manage memory safely using **smart pointers** under the **RAII** principle.

The assignment emphasizes clear structure, modularity, and adherence to the **C++ Core Guidelines**.

----------------------------------------------------
Guidelines
----------------------------------------------------

This assignment is to be completed **individually**, and all instructions must be followed carefully. Not adhering to these guidelines may result in a zero for the assignment.

- Do **not** use solutions or components created by others.
- Keep your work private; do **not** share your files or code.
- Any GitHub repository used for development **must be private**.
- You may discuss **general concepts** with classmates, but sharing **specific implementation details** is strictly forbidden.
- The use of **AI-generated code** (e.g., ChatGPT, Copilot) is **not permitted** unless explicitly allowed by the instructor for this assignment.
- Use **modern C++17** and follow the **C++ Core Guidelines**.

.. warning::

   **Respect the header/implementation contract.**  

   - Templates **must be defined entirely in** ``.hpp`` files.  
   - Non-templates: **declare in** ``.hpp`` and **implement in** ``.cpp``.  
   - Do **not** change function signatures provided in the instructions unless explicitly stated.

.. note::

   **Avoid “Magic Numbers.”**  
   Replace hard-coded values with named ``constexpr`` constants (e.g., velocity limit, default link lengths, sampling steps).  
   This improves readability and maintainability and will be graded under **Code Quality**.

.. _starter_project_section:

----------------------------------------------------
Starter Project
----------------------------------------------------

   - Use the course's **Assignment 3 starter** (``rwa3_starter``) from the course GitHub (clone or pull the latest).
   - The starter includes the expected layout and a minimal ``CMakeLists.txt``.
   - Complete all TODOs in each file.
   - Complete all Doxygen comment blocks provided in the source and header files. Each comment has been pre-generated as a template; ensure that every description, parameter, and return value is clearly documented.

      - Here is an example from **main.cpp** that you need to complete:

      .. code-block:: cpp
         :linenos:

         /**
         * @file main.cpp
         * @author your name (you@domain.com)
         * @brief 
         * @version 0.1
         * @date 2025-10-25
         * 
         * @copyright Copyright (c) 2025
         * 
         */

----------------------------------------------------
Submission Requirements
----------------------------------------------------

- Develop your solution in your **private** repository or local workspace.
- Ensure your code **compiles without warnings**.
- Final submission:

  - Remove **unused headers** and dead code (commented code).
  - Zip the **entire project** (source + CMake files).
  - Name the archive: ``rwa3_firstname_lastname.zip``.
  - Upload the zip to **Canvas** before the deadline.

**Your submission must include:**

- ``CMakeLists.txt`` (properly configured for C++17 and warnings)
- All source files from the :ref:`starter_project_section` section
- A program that runs and produces output similar to the :ref:`example_terminal_section` section

.. tip::

   **Self-check before submitting**

   - Clean build (delete ``build/``), reconfigure, rebuild, run.
   - Verify the printed trajectory counts, velocity clamping, and end-effector samples.
   - Ensure function/templates live in the correct files per the contract.

----------------------------------------------------
Concept Reference
----------------------------------------------------

Forward Kinematics
==================

Forward kinematics computes the **end-effector position** from a known set of **joint angles**.  
It answers the question: *“Where is the robot's tool tip given the current joint configuration?”*

For a **2-DOF planar arm**, the link lengths are :math:`L_1` and :math:`L_2`, and the joint angles are :math:`\theta_1` and :math:`\theta_2`.  
The first joint angle :math:`\theta_1` is measured between the x-axis and the first link :math:`L_1`, while the second joint angle :math:`\theta_2` is measured between the first and second links.


.. only:: html

   .. figure:: /_static/2DPlanar-light.png
      :alt: Forward kinematics of a 2-DOF planar arm
      :align: center
      :width: 90%
      :class: only-light

   .. figure:: /_static/2DPlanar-dark.png
      :alt: Forward kinematics of a 2-DOF planar arm (dark theme)
      :align: center
      :width: 90%
      :class: only-dark


.. only:: latex

   .. figure:: /_static/2DPlanar-light.png
      :alt: Forward kinematics of a 2-DOF planar arm
      :align: center
      :width: 90%



The end-effector position :math:`(x, y)` is calculated as:

.. math::

   x = L_1\cos(\theta_1) + L_2\cos(\theta_1 + \theta_2), \quad
   y = L_1\sin(\theta_1) + L_2\sin(\theta_1 + \theta_2)

This equation provides the Cartesian position of the end-effector and is essential for determining reachability, validating motion commands, and visualizing robot configurations.


Smooth Linear Trajectory
========================

A **trajectory** is a sequence of robot states that defines how a robot moves from one configuration to another over time.  
A **smooth linear trajectory** ensures continuous, predictable motion without sudden jumps.

In this assignment, you will:

- Linearly interpolate joint angles between the start and goal positions using a scalar :math:`\alpha \in [0,1]`.
- Compute joint velocities corresponding to the rate of change in joint angles.

This process simulates a motion planner that generates intermediate waypoints for smooth robot motion.

Velocity-Limit Filter
=====================

Real robots must respect **joint velocity constraints** to prevent mechanical stress or instability.  
The **velocity-limit filter** ensures each joint's angular velocity remains within safe limits (:math:`|d\theta| \le 1.0` rad/s).

You will implement this filter as a **lambda function**, which:

- Takes a ``JointState`` as input.
- Checks its joint velocities.
- Clamps them to the allowed maximum if necessary.
- Returns the filtered ``JointState``.

This demonstrates how to use **lambda expressions** for inline, real-time control operations.


----------------------------------------------------
Task 1 - Robot State POD Structs (6 pts)
----------------------------------------------------

**Objective:**  
Define the core data structures representing the robot's joint states and end-effector pose.

**Instructions:**

1. Define a ``JointState`` struct containing:

   - ``theta1`` and ``theta2``: joint angles (in radians).
   - ``dtheta1`` and ``dtheta2``: joint velocities (in radians per second).

2. Use **default member initializers** for velocities:

   .. code-block:: cpp

      struct JointState {
          double theta1;     // radians
          double theta2;     // radians
          double dtheta1 = 0.0;  // Default velocity
          double dtheta2 = 0.0;  // Default velocity
      };

   This allows:

   .. code-block:: cpp

      JointState q{M_PI/4, -M_PI/6};  // velocities default to 0.0

3. Define an ``EndEffectorPose`` struct containing ``x`` and ``y`` (in meters).
4. Implement ``void print_joint_state(const JointState&)`` in ``robot_types.cpp`` to print joint values and velocities clearly.
5. Demonstrate **aggregate initialization** (no constructors).

----------------------------------------------------
Task 2 - Forward Kinematics Template (8 pts)
----------------------------------------------------

**Objective:**  
Compute the robot's end-effector position from its joint angles.

**Instructions:**

1. Implement ``forward_kinematics()`` as a **templated function** in ``robot_kinematics.hpp``.

   - **Input**: any type with members ``theta1`` and ``theta2``.
   - **Output**: an ``EndEffectorPose`` with (x, y) coordinates.

2. Use ``<cmath>`` functions (``std::cos``, ``std::sin``).
3. Return the computed pose.

**Implementation Example:**

.. code-block:: cpp

   #pragma once
   #include "robot_types.hpp"
   #include <cmath>

   template <typename State>
   EndEffectorPose forward_kinematics(const State& s,
                                      double L1 = 0.5,
                                      double L2 = 0.3) {
       EndEffectorPose pose;
       // pose.x = ??;
       // pose.y = ??;
       return pose;
   }

----------------------------------------------------------
Task 3 - Linear Trajectory and Velocity Filtering (8 pts)
----------------------------------------------------------

**Objective:**  
Generate intermediate robot states between a start and goal configuration, and apply a velocity-limit filter.

**Instructions:**

1. Implement ``interpolate_linear()`` (templated) in ``robot_control.hpp``:

   - **Input**: start and goal states, scalar :math:`\alpha \in [0,1]`.
   - **Output**: interpolated ``State``.
   - **Behavior**:

     - Interpolates ``theta1`` and ``theta2`` linearly.
     - Computes ``dtheta1`` and ``dtheta2`` proportionally to the angle change.

2. Implement ``apply_filter()`` in ``robot_control.cpp``:

   - **Input**: ``std::vector<JointState>&`` and ``std::function<JointState(const JointState&)>``.
   - Apply the filter in-place to each element.

3. In ``main.cpp``, define a **lambda** that limits joint velocities (:math:`|d\theta| \le 1.0` rad/s) and pass it to ``apply_filter()``.


.. admonition:: Pseudocode (for reasoning, not code)

   The linear interpolation of angles is defined by:

   .. math::

      \theta_1(\alpha) = \theta_{1}^{\text{start}} + \alpha \left( \theta_{1}^{\text{goal}} - \theta_{1}^{\text{start}} \right), \qquad
      \theta_2(\alpha) = \theta_{2}^{\text{start}} + \alpha \left( \theta_{2}^{\text{goal}} - \theta_{2}^{\text{start}} \right)

   A simple proportional velocity assignment may be based on the angle change over the interpolation span:

   .. math::

      d\theta_1(\alpha) \propto \left( \theta_{1}^{\text{goal}} - \theta_{1}^{\text{start}} \right), \qquad
      d\theta_2(\alpha) \propto \left( \theta_{2}^{\text{goal}} - \theta_{2}^{\text{start}} \right)

   Velocity clamping ensures joint rates stay within the bound :math:`|d\theta| \le 1.0`:

   .. math::

      d\theta \leftarrow \operatorname{sign}(d\theta)\,\min\!\left(|d\theta|,\, 1.0\right)

   .. admonition:: Pseudocode: **interpolate_linear(start, goal, α)**
      :class: pseudocode

      .. line-block::

         INPUT: start (:math:`\theta_1`, :math:`\theta_2`, :math:`d\theta_1`, :math:`d\theta_2`),
               goal  (:math:`\theta_1`, :math:`\theta_2`, :math:`d\theta_1`, :math:`d\theta_2`),
               :math:`\alpha` in [0, 1]

         1) :math:`\alpha \leftarrow \text{clamp}(\alpha, 0, 1)`

         2) :math:`out.\theta_1 \leftarrow \text{start}.\theta_1 + \alpha \times (\text{goal}.\theta_1 - \text{start}.\theta_1)`
            :math:`out.\theta_2 \leftarrow \text{start}.\theta_2 + \alpha \times (\text{goal}.\theta_2 - \text{start}.\theta_2)`

         3) :math:`\Delta\theta_1 \leftarrow (\text{goal}.\theta_1 - \text{start}.\theta_1)`
            :math:`\Delta\theta_2 \leftarrow (\text{goal}.\theta_2 - \text{start}.\theta_2)`

         4) Assign velocities proportional to :math:`\Delta\theta`:
            :math:`out.d\theta_1 \leftarrow k \times \Delta\theta_1`
            :math:`out.d\theta_2 \leftarrow k \times \Delta\theta_2`

         5) RETURN :math:`out`
   

   .. admonition:: Pseudocode: **apply_filter(traj, filter)**
      :class: pseudocode
      
      .. line-block::

         INPUT: traj: vector of JointState
                filter: function JointState :math:`\rightarrow` JointState

         FOR each index :math:`i` in :math:`[0 \dots \text{traj.size()}-1]`:
            :math:`\text{traj}[i] \leftarrow \text{filter}(\text{traj}[i])`


   .. admonition:: Pseudocode **Lambda: clamp_to_limit(v, limit)**
      :class: pseudocode
      
      .. line-block::

         IF :math:`v > \text{limit}`:
            RETURN :math:`\text{limit}`
         IF :math:`v < -\text{limit}`:
            RETURN :math:`-\text{limit}`
         RETURN :math:`v`

   .. admonition:: Pseudocode: **Lambda: clamp_vel(s)**
      :class: pseudocode
      
      .. line-block::

         INPUT: s (JointState)
         RETURNS: JointState

         :math:`out \leftarrow s`
         :math:`out.d\theta_1 \leftarrow \text{clamp_to_limit}(out.d\theta_1, 1.0)`
         :math:`out.d\theta_2 \leftarrow \text{clamp_to_limit}(out.d\theta_2, 1.0)`
         RETURN :math:`out`
      



-----------------------------------------------------------
Task 4 - Trajectory Management with Smart Pointers (8 pts)
-----------------------------------------------------------

**Objective:**  
Integrate all components into a single simulation demonstrating motion planning, filtering, and memory safety.

**Instructions:**

1. Use ``std::make_unique`` to create a vector of ``JointState`` representing the trajectory.
2. Generate 21 states using ``interpolate_linear()`` (from :math:`\alpha=0` to 1 in steps of 0.05).
3. Apply the velocity filter using ``apply_filter()``.
4. Use ``std::make_unique`` to create a vector of ``EndEffectorPose``.
5. For each filtered state, compute the end-effector pose using ``forward_kinematics()``.
6. Print:

   - Trajectory size.
   - Start and end states (use ``print_joint_state()``).

7. Demonstrate that all resources are released automatically (RAII).

----------------------------------------------------------------------------
Task 5 - Joint Limit Validation (Optional, Not Graded)
----------------------------------------------------------------------------

In real robot systems, each joint can only move within a specific range of motion.  
For example, a shoulder joint may rotate roughly :math:`\pm180^{\circ}`, while an elbow joint might only bend between :math:`0^{\circ}` and :math:`90^{\circ}`.  
Exceeding these limits could cause physical damage or unsafe motion.

For extra practice, you can create a small helper function that checks whether a given robot configuration stays within valid joint limits.

In plain terms:

- Write a function that takes the current robot joint state as input.
- Inside, check that both joint angles are within reasonable limits (for instance, between :math:`-\pi` and :math:`\pi`).
- Return *true* if both joints are within limits, or *false* otherwise.
- You can make this a **templated helper function** so that it works with any state type that has ``theta1`` and ``theta2`` members.

This is **not graded**, but it is a valuable addition for testing safety and reliability in your robot control code.


.. _example_terminal_section:

----------------------------------------------------
Example Terminal Output
----------------------------------------------------

.. code-block:: console

   === Robot Kinematics & Control ===

   Generating smooth trajectory between:
   Start  -> θ1 = 0.0000 rad | θ2 = 0.0000 rad | dθ1 = 0.0000 rad/s | dθ2 = 0.0000 rad/s
   Goal   -> θ1 = 0.7854 rad | θ2 = -0.5236 rad | dθ1 = 0.0000 rad/s | dθ2 = 0.0000 rad/s

   Trajectory points: 21
   Unfiltered Trajectory (every 5th point shown):
   [0] θ1 = 0.0000 rad | θ2 = 0.0000 rad | dθ1 = 0.7854 rad/s | dθ2 = -0.5236 rad/s
   [5] θ1 = 0.1963 rad | θ2 = -0.1309 rad | dθ1 = 0.7854 rad/s | dθ2 = -0.5236 rad/s
   [10] θ1 = 0.3927 rad | θ2 = -0.2618 rad | dθ1 = 0.7854 rad/s | dθ2 = -0.5236 rad/s
   [15] θ1 = 0.5890 rad | θ2 = -0.3927 rad | dθ1 = 0.7854 rad/s | dθ2 = -0.5236 rad/s
   [20] θ1 = 0.7854 rad | θ2 = -0.5236 rad | dθ1 = 0.7854 rad/s | dθ2 = -0.5236 rad/s

   Applying velocity-limit filter: |dθ| ≤ 1.0000 rad/s
   -> Filter applied successfully, all values within limits.

   Filtered Trajectory (first 5 points):
   [0] θ1 = 0.0000 rad | θ2 = 0.0000 rad | dθ1 = 0.7854 rad/s | dθ2 = -0.5236 rad/s
   [1] θ1 = 0.0393 rad | θ2 = -0.0262 rad | dθ1 = 0.7854 rad/s | dθ2 = -0.5236 rad/s
   [2] θ1 = 0.0785 rad | θ2 = -0.0524 rad | dθ1 = 0.7854 rad/s | dθ2 = -0.5236 rad/s
   [3] θ1 = 0.1178 rad | θ2 = -0.0785 rad | dθ1 = 0.7854 rad/s | dθ2 = -0.5236 rad/s
   [4] θ1 = 0.1571 rad | θ2 = -0.1047 rad | dθ1 = 0.7854 rad/s | dθ2 = -0.5236 rad/s

   Computing end-effector poses for filtered trajectory...
   Link lengths: L1 = 0.50 m, L2 = 0.30 m

   End-Effector Trajectory (all points):
   [0]  x = 0.8000 m,  y = 0.0000 m
   [1]  x = 0.7996 m,  y = 0.0236 m
   [2]  x = 0.7984 m,  y = 0.0471 m
   [3]  x = 0.7963 m,  y = 0.0705 m
   [4]  x = 0.7934 m,  y = 0.0939 m
   [5]  x = 0.7898 m,  y = 0.1172 m
   [6]  x = 0.7853 m,  y = 0.1403 m
   [7]  x = 0.7800 m,  y = 0.1632 m
   [8]  x = 0.7739 m,  y = 0.1859 m
   [9]  x = 0.7670 m,  y = 0.2083 m
   [10]  x = 0.7594 m,  y = 0.2305 m
   [11]  x = 0.7510 m,  y = 0.2524 m
   [12]  x = 0.7418 m,  y = 0.2739 m
   [13]  x = 0.7319 m,  y = 0.2951 m
   [14]  x = 0.7213 m,  y = 0.3159 m
   [15]  x = 0.7100 m,  y = 0.3363 m
   [16]  x = 0.6980 m,  y = 0.3563 m
   [17]  x = 0.6853 m,  y = 0.3758 m
   [18]  x = 0.6719 m,  y = 0.3948 m
   [19]  x = 0.6579 m,  y = 0.4132 m
   [20]  x = 0.6433 m,  y = 0.4312 m


   Summary
   --------
   • Total joint states: 21
   • Velocity filter: active (|dθ| ≤ 1.0000)

   Program finished successfully.


----------------------------------------------------
Code Quality and C++ Guidelines (6 pts)
----------------------------------------------------

Your code will be graded for adherence to **C++ Core Guidelines**:

- No raw pointers (``new`` or ``delete``).
- Correct ownership semantics using ``std::unique_ptr``.
- Const-correctness and pass-by-reference for non-owning parameters.
- Uniform initialization (``{}``) used consistently.
- Clean compilation with ``-Wall -Werror -Wextra -pedantic-errors``.
- Clear naming, concise comments, and documented units (radians, meters, rad/s).

----------------------------------------------------
Evaluation Rubric (36 pts)
----------------------------------------------------

Performance Levels (used below)
-------------------------------

- **Exceeds**: Fully correct, robust, and idiomatic; anticipates edge cases.
- **Meets**: Correct and idiomatic; minor issues that do not affect correctness.
- **Partial**: Partially correct or missing important elements.
- **Insufficient**: Incorrect, incomplete, or non-functional.

.. note::
   Points for each sub-criterion are **all-or-nothing** unless otherwise noted. “Partial” earns **half** of the listed points for that sub-criterion when applicable.

Task 1 — POD Structs, Defaults, and Printing (6 pts)
-----------------------------------------------------

.. list-table::
   :header-rows: 1
   :widths: 42 43 15

   * - **Sub-criterion**
     - **Evidence of Exceeds / Meets / Partial / Insufficient**
     - **Pts**
   * - POD structs with appropriate fields
     - *Exceeds/Meets*: Correct fields; no invariants required; trivially copyable design.  
       *Partial*: Missing a field or uses class features that break POD intent.  
       *Insufficient*: Wrong or unusable structure.
     - 2
   * - Default member initializers for all fields
     - *Exceeds/Meets*: Sensible defaults set in-class; no uninitialized state.  
       *Partial*: Defaults incomplete.  
       *Insufficient*: No defaults; UB risk.
     - 2
   * - Formatted printing (readable, labeled, consistent units)
     - *Exceeds*: Clear labels, alignment, and units; no `std::endl` misuse; newline `'\n'`.  
       *Meets*: Clear output; minor formatting nits.  
       *Partial/Insufficient*: Hard to read or missing fields.
     - 2

Task 2 — Forward Kinematics Template Implementation (8 pts)
-----------------------------------------------------------

.. list-table::
   :header-rows: 1
   :widths: 42 43 15

   * - **Sub-criterion**
     - **Evidence of Exceeds / Meets / Partial / Insufficient**
     - **Pts**
   * - Correct FK equations and frame conventions
     - *Exceeds/Meets*: Angles and link lengths used with correct trigonometry and ordering; frames documented.  
       *Partial*: Minor sign or frame confusion with test mismatch.  
       *Insufficient*: Incorrect mapping.
     - 3
   * - Generic template design (types, constants)
     - *Exceeds*: Template parameters or `auto` enable `float`/`double`; no unnecessary casts.  
       Meets: Works for primary type with clean template signature.  
       *Partial/Insufficient*: Hard-coded type or broken templating.
     - 2
   * - Numerical sanity and edge cases
     - *Exceeds*: Handles zero angles, extreme values, and boundary inputs; tests or asserts where appropriate.  
       Meets: Works on nominal cases.  
       *Partial/Insufficient*: Fails common cases.
     - 2
   * - Clear API and documentation
     - *Exceeds/Meets*: Function name, params, and returned pose are unambiguous; brief comment.  
       *Partial/Insufficient*: Ambiguous or missing.
     - 1

Task 3 — Linear Interpolation and Velocity Filtering (8 pts)
------------------------------------------------------------

.. list-table::
   :header-rows: 1
   :widths: 42 43 15

   * - **Sub-criterion**
     - **Evidence of Exceeds / Meets / Partial / Insufficient**
     - **Pts**
   * - Interpolation correctness with clamped :math:`\\alpha`
     - *Exceeds/Meets*: Implements `alpha = clamp(alpha, 0, 1)`; linear blend for all fields as specified.  
       *Partial*: Forgets clamping or a field.  
       *Insufficient*: Incorrect formula.
     - 3
   * - Velocity assignment proportional to :math:`\\Delta\\theta`
     - *Exceeds/Meets*: Uses `k * Δθ` consistently; rationale or constant visible.  
       *Partial*: Applies to one joint only or mixes units.  
       *Insufficient*: Missing or wrong.
     - 2
   * - Filter application over trajectory (in-place transform)
     - *Exceeds/Meets*: Iterates safely over all states; no copies unless required; lambda friendly.  
       *Partial*: Inefficient copying or off-by-one.  
       *Insufficient*: Incorrect application.
     - 2
   * - Readability and test snippet
     - *Exceeds/Meets*: Small demo or asserts; clear variable names.  
       *Partial/Insufficient*: Hard to follow.
     - 1

Task 4 — Smart Pointers, Safety, and RAII (8 pts)
--------------------------------------------------

.. list-table::
   :header-rows: 1
   :widths: 42 43 15

   * - **Sub-criterion**
     - **Evidence of Exceeds / Meets / Partial / Insufficient**
     - **Pts**
   * - Correct `std::unique_ptr` ownership
     - *Exceeds/Meets*: Uses `std::make_unique`; no raw `new` in user code; `reset` only when justified.  
       *Partial*: Mixed ownership patterns.  
       *Insufficient*: Leaks or double-delete risks.
     - 3
   * - RAII integration and lifetime clarity
     - *Exceeds/Meets*: Resources released deterministically; no manual `delete`; scopes well defined.  
       *Partial*: Lifetime unclear.  
       *Insufficient*: Dangling usage.
     - 2
   * - Avoids anti-patterns
     - *Exceeds/Meets*: No `std::move` into same object; no copying `unique_ptr`; no ``naked`` owning raw pointers.  
       *Partial/Insufficient*: One or more anti-patterns present.
     - 2
   * - Minimal, focused example
     - *Exceeds/Meets*: Short example that compiles; comments explain ownership.  
       *Partial/Insufficient*: Confusing or non-compiling.
     - 1

Code Quality — C++ Core Guidelines and Best Practices (6 pts)
-------------------------------------------------------------

.. list-table::
   :header-rows: 1
   :widths: 42 43 15

   * - **Checklist**
     - **Evidence**
     - **Pts**
   * - Warnings clean: `-Wall -Wextra -pedantic-errors`
     - Builds without warnings; uses `'\n'` instead of `std::endl`.
     - 2
   * - Naming, constants, and initialization
     - Consistent snake_case for vars; `constexpr` or `const` for magic numbers; uniform initialization `{}`.
     - 2
   * - Documentation and structure
     - Doxygen header present; files named per spec; functions short and single-purpose.
     - 2

Deductions (Flat)
-----------------

.. list-table::
   :header-rows: 1
   :widths: 75 25
   :class: deductions-table

   * - **Issue**
     - **Penalty**
   * - Wrong file naming or extra files in archive
     - −4 pts each
   * - Project does not compile or compiles with warnings/errors
     - −5 pts
   * - Missing or incomplete Doxygen header
     - −3 pts
   * - Late submission (UMD policy)
     - 20% per day (max 3 days); after 3 days, 0



----------------------------------------------------
Learning Outcomes
----------------------------------------------------

Upon completing this assignment, you will:

- Implement **forward kinematics** using modern C++ templates.
- Generate **smooth robot trajectories** with interpolation and filtering.
- Apply **lambda functions** and ``std::function`` for modular control.
- Use **smart pointers** to ensure memory safety and proper ownership.
- Write maintainable, standard-compliant C++ code following the **C++ Core Guidelines**.

----------------------------------------------------
References and Further Reading
----------------------------------------------------

.. raw:: html

   <ul>
     <li><a href="https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines" target="_blank" rel="noopener noreferrer">
     C++ Core Guidelines</a></li>
     <li><a href="https://en.cppreference.com/w/cpp/language/raii" target="_blank" rel="noopener noreferrer">
     RAII Explained (cppreference)</a></li>
     <li><a href="https://en.cppreference.com/w/cpp/memory" target="_blank" rel="noopener noreferrer">
     Smart Pointers (cppreference)</a></li>
     <li><a href="https://en.cppreference.com/w/cpp/language/lambda" target="_blank" rel="noopener noreferrer">
     Lambda Expressions (cppreference)</a></li>
   </ul>

