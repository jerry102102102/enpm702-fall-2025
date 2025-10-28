``constexpr`` Functions
=======================

Meaning
-------

``constexpr`` marks an expression or function as eligible for **compile-time evaluation**. If all arguments are constant expressions, the compiler computes the result at compile time.

.. code-block:: cpp

   constexpr int square(int x) { return x * x; }
   constexpr int n = square(5);     // compile-time
   int m = 7;
   int r = square(m);               // runtime

Why It Matters
--------------

- Eliminates runtime cost for pure computations.
- Enables use in contexts that require compile-time constants (array bounds, template args).
- Surfaces logic errors earlier (at compile time).

Guidelines
----------

- Keep functions pure and deterministic.
- From C++14 onward, loops and conditionals are permitted in ``constexpr`` bodies.
