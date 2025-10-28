Templates — Overview
====================

A **function template** is a blueprint the compiler uses to generate concrete overloads. Write the algorithm once; the compiler **instantiates** versions for used types.

.. code-block:: cpp

   template<typename T>
   T add(T a, T b) { return a + b; }

Benefits
--------

- Maintainability: fix once, apply everywhere.
- Consistency: identical logic across types.
- Flexibility: new types work without new overloads.
- Zero-overhead abstraction at compile time.

Templates vs Overloading
------------------------

- Same logic across types → templates.
- Different logic per type → overloading or specialization.
