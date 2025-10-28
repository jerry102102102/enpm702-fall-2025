``std::function`` and Type Erasure
====================================

A polymorphic wrapper that can store **any callable** with a compatible signature.

.. code-block:: cpp

   #include <functional>
   std::function<int(int)> op;
   op = [](int x){ return x+10; };
   op = [](int x){ return x*2; };

Notes
-----

- Adds indirection and possible heap allocation.
- Prefer direct callables in tight loops; use ``std::function`` for flexibility.
