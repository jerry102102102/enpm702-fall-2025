Templates in Modern C++
=======================

Overview
--------

Templates enable writing **generic**, **type-independent** code in C++.
They are the foundation for reusable algorithms and libraries like the STL.

Templates allow you to:
- Write a function or class once and reuse it with many types.
- Rely on compile-time type deduction for efficiency and safety.
- Specialize behavior for certain types when necessary.

Types of Templates
------------------

C++ provides several kinds of templates:

1. **Function templates** — for generic algorithms.  
2. **Class templates** — for type-parameterized data structures.  
3. **Variable templates** — for parameterized constants.  
4. **Alias templates** — for reusable type aliases.  

.. note::
   Templates are instantiated at **compile time**. The compiler generates a
   concrete version of the template for each unique type combination used.

Quick Comparison
----------------

.. list-table:: Template Categories
   :header-rows: 1
   :widths: 20 25 55

   * - Template Type
     - Example
     - Typical Use
   * - Function template
     - ``template<typename T> T add(T a, T b);``
     - Generic algorithms or utilities.
   * - Class template
     - ``template<typename T> class Vector;``
     - Data structures (STL containers, smart pointers).
   * - Variable template
     - ``template<typename T> constexpr T pi = T(3.14159);``
     - Type-safe constants.
   * - Alias template
     - ``template<typename T> using Ptr = std::shared_ptr<T>;``
     - Simplified type aliases.

Detailed Topics
---------------

The following sections explore each area of templates in detail:

.. toctree::
   :maxdepth: 2
   :caption: Template Topics

   templates/overview
   templates/syntax
   templates/specialization
   templates/deduction

Interoperability with Generic Code
----------------------------------

Templates integrate with:
- **Type traits** and **concepts** (in C++20+) for constraints and static checks.
- **constexpr** and **decltype** for compile-time computation and type inference.

Example
-------

.. code-block:: cpp

   #include <iostream>

   template <typename T>
   auto multiply(const T& a, const T& b) -> decltype(a * b) {
       return a * b;
   }

   int main() {
       std::cout << multiply(3, 5) << '\n';       // int
       std::cout << multiply(2.5, 4.0) << '\n';   // double
   }


Summary
-------

- Templates are **compile-time generators** of code.  
- They allow **zero-cost abstractions** and strong type safety.  
- Modern C++ encourages constrained templates using **concepts**.  
- For common generic utilities, prefer STL templates (e.g., ``std::vector``).  
