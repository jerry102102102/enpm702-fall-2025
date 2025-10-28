Template Syntax & Organization
==============================

Function Template
-----------------

.. code-block:: cpp

   template<typename T>
   ReturnT func(T x) { /* ... */ }

``typename`` and ``class`` are interchangeable in template parameter lists.

Where to Place Definitions
--------------------------

**Place template definitions in headers** (``.hpp``). The compiler must see the full definition to instantiate it.

.. code-block:: cpp
   :caption: Header-only template (recommended)

   // math_utils.hpp
   #pragma once
   template<typename T>
   T multiply(T a, T b) { return a * b; }

Doxygen Documentation
---------------------

Use ``@tparam``, ``@param``, ``@return``, and ``@note``:

.. code-block:: cpp

   /// @brief Returns the larger value.
   /// @tparam T Totally ordered type.
   template<typename T>
   T max_value(T a, T b) { return (a > b) ? a : b; }
