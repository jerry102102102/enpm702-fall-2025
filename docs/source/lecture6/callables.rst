Callables in Modern C++
=======================

Overview
--------

A :term:`Callable` is any entity that can be invoked with parentheses `()`.  
C++ provides multiple mechanisms for representing and using callables, from raw
function pointers to high-level polymorphic wrappers like ``std::function``.

Callables unify **functions**, **objects**, and **expressions** that perform
actions. Understanding their differences is crucial for writing generic and
flexible code, especially when working with the STL, callbacks, or modern
functional-style programming.

.. note::
   In generic programming, callables allow code to treat functions, lambdas,
   and functors uniformly through template type deduction or ``std::invoke``.

Types of Callables
------------------

C++ supports several categories of callables:

1. **Function pointers** — addresses of free functions.  
2. **Functors (function objects)** — structs or classes that overload ``operator()``.  
3. **Lambdas** — unnamed function objects defined inline.  
4. **std::function** — a type-erased wrapper for any callable with a compatible signature.

.. image:: /_static/images/callables_diagram.png
   :alt: Callables overview diagram
   :align: center
   :width: 80%

Quick Comparison
----------------

.. list-table:: Quick Comparison
   :header-rows: 1
   :widths: 22 18 16 28

   * - Callable Type
     - Captures State?
     - Overhead
     - Typical Use
   * - Function pointer
     - No
     - None
     - Callbacks; C APIs
   * - Functor
     - Yes
     - None
     - STL algorithms
   * - Lambda
     - Yes
     - Minimal
     - Inline logic
   * - ``std::function``
     - Yes (erased)
     - Possible heap
     - Generic storage

Detailed Topics
---------------

The following sections explore each callable category in detail:

.. toctree::
   :maxdepth: 2
   :caption: Callable Types

   callables/function_pointers
   callables/functors
   callables/lambdas
   callables/std_function

Interoperability
----------------

All callable types can be used with ``std::invoke`` and ``std::is_invocable`` to
determine at compile time whether they can be called with specific arguments.

Example
-------

.. code-block:: cpp

   #include <functional>
   #include <iostream>

   int add(int a, int b) { return a + b; }

   struct Multiplier {
     int factor;
     int operator()(int x) const { return x * factor; }
   };

   int main() {
     auto lambda = [](int x) { return x * 3; };
     std::function<int(int)> generic;

     generic = add;                 // Function pointer
     std::cout << generic(2, 3) << "\\n"; // 5

     generic = Multiplier{4};       // Functor
     std::cout << generic(5) << "\\n";    // 20

     generic = lambda;              // Lambda
     std::cout << generic(6) << "\\n";    // 18
   }

.. tip::
   Prefer lambdas for inline, short-lived operations. Use ``std::function`` when
   the callable must be stored, passed around, or reassigned dynamically.

Summary
-------

- **Function pointers** are the most lightweight but least flexible.  
- **Functors** offer state and are ideal for STL algorithms.  
- **Lambdas** provide concise syntax for local or temporary callables.  
- **``std::function``** generalizes callables through runtime type erasure.

Understanding these options helps you design APIs that are both efficient and expressive.
