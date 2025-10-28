``decltype`` Operator
=====================

``decltype(expr)`` inspects the **type** of an expression at compile time without evaluating it.

Basics
------

.. code-block:: cpp

   int x{42};
   decltype(x) a{0};               // int
   decltype((x)) b{x};             // int&  (lvalue expression yields T&)
   decltype(x + 0) c{0};           // int   (prvalue yields T)

Rules of Thumb
--------------

- ``decltype(id)`` → declared type of ``id``.
- ``decltype(lvalue-expr)`` → ``T&``.
- ``decltype(prvalue-expr)`` → ``T``.

Use Cases
---------

- Mirror another variable's exact type (including refs/const).
- Trailing return type in templates: ``auto f(...) -> decltype(expr)``.
