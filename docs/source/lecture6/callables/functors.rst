Functors (Function Objects)
===========================

A **functor** is a type that overloads ``operator()``. It is callable **and** can hold state.

.. code-block:: cpp

   struct Counter {
     int count{0};
     void operator()() { ++count; }
   };

Use Cases
-----------

- Predicates and transformations for STL algorithms.
- Stateful callbacks.
