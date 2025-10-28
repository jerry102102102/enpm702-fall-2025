Exercises
=========


1. Lidar-IMU Fusion: Weighted Blend Without Precision Loss
   Your robot combines a Lidar range (often ``double``) with an IMU drift correction (maybe ``float`` or ``int``).
   You want a single function that blends two values using a weight in ``[0, 1]`` without forcing a specific type.

   **Tasks:**

   - Write ``template <typename A, typename B, typename W>`` ``auto blend(A a, B b, W w) -> decltype(a*(W{}) + b*(W{}));`` and implement the logic.
   - Add ``[[nodiscard]]`` to the function to prevent ignoring the result.
   - Test with combinations like ``float + double``, ``int + double``, and confirm the return type matches what you expect.


2. ``constexpr`` Sampling of a Trapezoidal Profile
   The robot uses a simple trapezoidal motion profile for a short approach to a docking station.
   Positions at discrete ticks should be computed at compile time for a fixed test profile.

   **Tasks:**

   - Implement a ``constexpr`` function that returns the position at time-step ``i`` given ``a`` (acceleration), ``vmax``, total distance ``D``, and ``dt``.
   - Use small integer parameters so a few sample steps can be checked with ``static_assert``.
   - Show the same function works at runtime when the values come from user input.


3. Callable Pipeline: Function Pointers, Lambdas, and Struct Functors
   Your robot executes a small pipeline: pre-process sensor, compute control, log status.
   You want to assemble this pipeline from different callable forms.

   **Tasks:**

   - Create a free function (e.g., ``void preprocess()``), a lambda that captures a counter, and a **struct** with ``void operator()()`` as a functor.
   - Store them in ``std::vector<std::function<void()>>`` and execute in order with a simple ``run_all(const std::vector<std::function<void()>>& t)``.
   - Print the order and confirm the captured state in the lambda changes between invocations.


4. ``noexcept`` in the Control Loop (specifier + operator)
   Your low-level control loop must not throw. You wrap a helper that might throw if input is invalid.

   **Tasks:**

   - Write ``int safe_step(int input)`` that **does not** throw, and ``int risky_step(int input)`` that **may** throw (you can simulate with a condition and ``throw``).
   - Implement ``int control_step(int x) noexcept`` that internally calls the safe path.
   - Use the **``noexcept`` operator** to print whether ``control_step(x)`` and ``risky_step(x)`` are noexcept at compile time (``std::cout << noexcept(...)``).
   - Add a code comment explaining that if a ``noexcept`` function throws, the program calls ``std::terminate``.


5. PID Gains from a Struct Functor
   You want to decouple "how you compute gains" from the place where they are used.
   Since you haven't covered classes, implement the policy as a **struct** functor.

   **Tasks:**

   - Define a **struct** ``FixedGains`` with members ``double kp, ki, kd;`` and an ``operator()(double error, double dt)`` that returns a control effort.
   - Define a **struct** ``AdaptiveGains`` that holds a scalar ``double alpha`` and computes a slightly different effort using ``alpha``.
   - Show a function ``double apply_controller(auto gains, double error, double dt)`` (use a template) that calls the passed callable and returns the effort.
   - Use ``[[maybe_unused]]`` to silence any unused local variables in your quick tests.


6. Detecting ``update(dt)``
   You integrate two third-party controllers: one exposes ``update(double dt)``, the other only ``compute()``.
   Choose the call path with **overloads** rather than SFINAE.

   **Tasks:**

   - Create two **structs**, ``HasUpdate`` with ``void update(double)`` and ``NoUpdate`` with ``void compute()``.
   - Write two overloads of ``step_controller``:

     - ``void step_controller(HasUpdate& c, double dt)`` that calls ``c.update(dt)``.
     - ``void step_controller(NoUpdate& c, double dt)`` that prints "no update(dt)".

   - Demonstrate both paths compile and run by constructing the respective structs and calling the same function name.


7. Strongly Typed Velocity Units (Structs Only)
   A bug mixed up cm/s and m/s. Prevent it with tiny **struct** wrappers.

   **Tasks:**

   - Define ``struct MetersPerSecond { double v; explicit MetersPerSecond(double x) : v{x} {} };``
   - Define ``struct CentimetersPerSecond { double v; explicit CentimetersPerSecond(double x) : v{x} {} };``
   - Overload ``MetersPerSecond operator+(MetersPerSecond a, MetersPerSecond b)`` and scaling by ``double``.
   - Provide a named conversion: ``MetersPerSecond from_cmps(CentimetersPerSecond c)``.
   - Show that adding different units does **not** compile until you explicitly convert.


8. Compile-Time Waypoints Table (``constexpr``)
   A fixed test path uses up to 8 waypoints. You want a fast, compile-time table.

   **Tasks:**

   - Define ``struct Waypoint { double x; double y; };`` and a ``constexpr`` array of 4-8 waypoints.
   - Implement ``constexpr Waypoint waypoint_at(std::size_t i)`` that returns by value (okay for small structs).
   - If an index is known at compile time, check it with ``static_assert(i < N)`` (you can demonstrate this in a templated helper).
   - Mark the accessor ``[[nodiscard]]`` so a call like ``waypoint_at(0);`` warns if ignored.


9. Generic Matrix Multiply With Type Deduction (Struct Matrix)
   You have a simple matrix type used in a simulator. Keep it as a **struct** with a nested 2-D container.

   **Tasks:**

   - Define ``template <typename T> struct Matrix { std::vector<std::vector<T>> a; };`` with ``rows()``, ``cols()``, and element accessors.
   - Write ``template <typename A, typename B> auto matmul(const Matrix<A>& X, const Matrix<B>& Y) -> Matrix<decltype(A{} * B{})>;`` and implement standard multiplication.
   - Verify with small tests for ``int`` and ``double`` that dimensions match and the results are correct.


10. Priority Queue of Tasks Using Lambdas and Structs
    Your robot must process (sensor read, control, logging) by priority. You also want FIFO among equal priorities.

    **Tasks:**
    
    - Define ``struct Task { int priority; std::size_t order; std::function<void()> run; };``
    - Use ``std::priority_queue<Task, std::vector<Task>, /* comparator */>`` with a comparator that sorts by higher priority, then lower ``order`` (so earliest inserted among equals runs first).
    - Create tasks as lambdas that print their name and capture a small local counter by value.
    - Push several tasks and pop/execute, printing the order to verify correctness.
