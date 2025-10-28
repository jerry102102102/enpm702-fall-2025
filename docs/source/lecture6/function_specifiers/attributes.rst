Function Attributes
===================

``[[nodiscard]]``
-----------------

Warn if a return value is ignored.

.. code-block:: cpp

   [[nodiscard]] int compute_total(int x, int y) { return x + y; }
   // compute_total(1,2); // warning

``[[maybe_unused]]``
--------------------

Silence warnings for intentionally-unused entities.

.. code-block:: cpp

   [[maybe_unused]] void debug_print(const std::string& s) { /* ... */ }

``[[deprecated]]``
------------------

Emit a warning when obsolete APIs are used.

.. code-block:: cpp

   [[deprecated("Use compute_area instead")]]
   double calc_area(double r);

Guidelines
----------

Use attributes to convey **intent** and improve diagnostics without changing semantics.
