``noexcept`` Specifier & Operator
=================================

Specifies that a function **will not throw**. The compiler can optimize accordingly.

.. code-block:: cpp

   void safe() noexcept { /* ... */ }
   void risky(); // may throw

Conditional ``noexcept``
------------------------

.. code-block:: cpp

   void never_throw() noexcept;
   void demo() noexcept(noexcept(never_throw()));

Best Practices
--------------

- Mark small, low-level functions that cannot throw.
- Do not mark functions ``noexcept`` if they might legitimately throw.
