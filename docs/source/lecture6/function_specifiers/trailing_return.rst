Trailing Return Types
=======================

Motivation
-----------

When the return type depends on parameter types, place it *after* parameters.

.. code-block:: cpp

   template<typename T, typename U>
   auto multiply(const T& a, const U& b) -> decltype(a * b) {
     return a * b;
   }

C++14+ Shortcut
----------------

For simple cases, let ``auto`` deduce the return:

.. code-block:: cpp

   template<typename T, typename U>
   auto add(T a, U b) { return a + b; }

Note: plain ``auto`` drops top-level ``const`` and references. Use ``decltype(auto)`` or an explicit trailing return to preserve qualifiers.
