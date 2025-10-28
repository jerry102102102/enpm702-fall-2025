``inline`` and the ODR
=======================

Inlining vs Linkage
-------------------

``inline`` is a hint for inlining, but more importantly it **relaxes the One Definition Rule (ODR)** so the same function definition can appear in multiple translation units (e.g., in a header).

.. code-block:: cpp

   // utils.hpp
   #pragma once
   inline int add(int a, int b) { return a + b; } // legal to define in a header

Notes
-----

- Compilers may inline regardless of the keyword.
- Avoid inlining large, recursive, or virtual functions for performance reasons.
