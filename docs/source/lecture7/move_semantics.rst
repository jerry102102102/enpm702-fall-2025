Move Semantics
=====================================

Overview
--------

Move semantics, introduced in C++11, allow the **transfer of resources** from one object to another rather than copying them.  
This improves performance by eliminating unnecessary deep copies of temporary or large objects such as containers, strings, or dynamically allocated resources.

At its core, move semantics enable **efficient ownership transfer** between objects through *move constructors* and *move assignment operators*.

------------------------------------------------------------

Motivation
----------

Copying large objects can be expensive because it duplicates every element or resource:

.. code-block:: cpp

   std::vector<int> v1(1'000'000, 42);
   std::vector<int> v2 = v1;  // copies one million integers!

With move semantics, you can **reuse** the data from a temporary object instead of duplicating it:

.. code-block:: cpp

   std::vector<int> make_vector() {
       std::vector<int> temp(1'000'000, 42);
       return temp;  // uses move constructor if available
   }

   int main() {
       std::vector<int> v = make_vector();  // moves, not copies
   }

When returning from functions, the compiler can “move” the temporary ``temp`` instead of copying all of its elements.

------------------------------------------------------------

Rvalue References
-----------------

Move semantics rely on **rvalue references**, declared using ``T&&``.

An rvalue reference can bind to a **temporary** (an rvalue), allowing the function to “steal” its resources.

.. code-block:: cpp

   void process(std::string&& s) {  // s binds to a temporary string
       std::cout << "Received: " << s << '\n';
   }

   int main() {
       process("temporary");  // binds to std::string&&
   }

------------------------------------------------------------

Copy vs. Move
-------------

.. list-table::
   :header-rows: 1
   :widths: 20 40 40

   * - Operation
     - Definition
     - Behavior
   * - Copy Constructor
     - ``T(const T&)``
     - Creates a new object by duplicating another.
   * - Move Constructor
     - ``T(T&&)``
     - Transfers ownership of resources from a temporary object.
   * - Copy Assignment
     - ``T& operator=(const T&)``
     - Replaces contents by copying.
   * - Move Assignment
     - ``T& operator=(T&&)``
     - Replaces contents by transferring ownership.

------------------------------------------------------------

Example: Move Constructor and Move Assignment
---------------------------------------------

.. code-block:: cpp

   #include <iostream>
   #include <vector>

   struct Buffer {
       std::vector<int> data;

       Buffer(size_t n) : data(n) {
           std::cout << "Constructed with size " << n << '\n';
       }

       // Move constructor
       Buffer(Buffer&& other) noexcept : data(std::move(other.data)) {
           std::cout << "Moved!\n";
       }

       // Move assignment
       Buffer& operator=(Buffer&& other) noexcept {
           std::cout << "Move assigned!\n";
           if (this != &other) {
               data = std::move(other.data);
           }
           return *this;
       }
   };

   int main() {
       Buffer b1(5);
       Buffer b2 = std::move(b1);  // Move constructor
       Buffer b3(3);
       b3 = std::move(b2);         // Move assignment
   }

------------------------------------------------------------

The ``std::move`` Utility
-------------------------

``std::move()`` is a **cast** that converts an expression into an **rvalue reference**,  
signaling that the resource can be “moved from.”

.. code-block:: cpp

   std::string a = "Hello";
   std::string b = std::move(a);  // Move instead of copy

   std::cout << "a after move: '" << a << "'\n";  // a is in a valid but unspecified state
   std::cout << "b: " << b << '\n';

------------------------------------------------------------

Rules of Thumb
--------------

- A **move constructor** or **move assignment** should leave the source in a *valid but unspecified* state.
- Always mark move operations as ``noexcept`` for better optimization (especially with ``std::vector`` reallocation).
- Use ``std::move`` only when you no longer need the source object.
- Avoid moving from the same object twice — results are undefined.
- Prefer ``std::move`` over ``std::forward`` unless writing template forwarding functions.
- If a class defines a move operation, also define or default its copy operations explicitly.

------------------------------------------------------------

Move Semantics with STL Containers
----------------------------------

Standard containers (``std::vector``, ``std::string``, ``std::map``) are fully move-aware:

.. code-block:: cpp

   std::vector<std::string> v1;
   v1.push_back("Hello");

   std::vector<std::string> v2 = std::move(v1);  // transfers internal buffer

   std::cout << "v1 size: " << v1.size() << '\n';  // 0 or unspecified
   std::cout << "v2[0]: " << v2[0] << '\n';        // "Hello"

Move semantics make container resizing and return-value optimization (RVO) efficient and safe.

------------------------------------------------------------

When the Compiler Generates Move Operations
-------------------------------------------

The compiler automatically generates a move constructor and move assignment operator **if**:

1. No user-declared copy constructor, copy assignment, or destructor exists.
2. The class’s data members are all movable.

Otherwise, they must be defined explicitly.

Example:

.. code-block:: cpp

   struct Data {
       std::vector<int> v;
       // Compiler automatically generates move constructor and assignment
   };

------------------------------------------------------------

Best Practices
--------------

- Implement move operations when your class manages a heap resource (e.g., dynamic arrays, file handles, sockets).
- Always combine move semantics with RAII to ensure exception safety.
- Prefer ``std::make_unique`` or ``std::make_shared`` to construct smart pointers directly.
- Pass large temporary objects by value and move them internally if needed.
- Use ``noexcept`` with move operations to enable efficient container operations.

------------------------------------------------------------

Example Summary
---------------

.. code-block:: cpp

   #include <iostream>
   #include <utility>

   struct Example {
       Example() { std::cout << "Default constructor\n"; }
       Example(const Example&) { std::cout << "Copy constructor\n"; }
       Example(Example&&) noexcept { std::cout << "Move constructor\n"; }
   };

   int main() {
       Example e1;
       Example e2 = std::move(e1);  // Move constructor
       Example e3 = e2;             // Copy constructor
   }

Output:
::

   Default constructor
   Move constructor
   Copy constructor

------------------------------------------------------------

Summary
-------

Move semantics are essential to writing efficient modern C++.  
They minimize unnecessary copies, improve performance, and integrate naturally with smart pointers and STL containers.

.. tip::
   Always use ``std::move`` intentionally — it expresses ownership transfer clearly.
   If you don’t need a copy, move it!
