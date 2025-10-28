Template Specialization
=======================

Full Specialization
-------------------

Override behavior for a **specific type** when semantics or performance differ.

.. code-block:: cpp

   template<typename T>
   T get_max(T a, T b) { return (a > b) ? a : b; }

   template<>
   std::string get_max<std::string>(std::string a, std::string b) {
     return (a.size() > b.size()) ? a : b;
   }

Guidance
--------

- Specialize for clear semantic differences.
- Specialize for performance when a type admits a faster path.
- Keep generic correctness first; specialize narrowly.
