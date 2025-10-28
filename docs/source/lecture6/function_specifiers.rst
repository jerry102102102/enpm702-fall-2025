Operators, Specifiers, and Attributes
=====================================

Overview
--------

This section focuses on three closely related aspects of modern C++17:

1. **Operators** — provide concise, expressive syntax for operations and relationships between values or objects.  
2. **Function specifiers** — modify compilation, linkage, or evaluation behavior of functions.  
3. **Attributes** — convey intent and metadata to the compiler for clearer diagnostics and optimization.

Together, these constructs improve expressiveness, efficiency, and maintainability in C++ programs.

------------------------------------------------------------

Operators
---------

Operators are special symbols that represent computations, comparisons, or logical relationships.
They can be classified as **arithmetic**, **relational**, **logical**, **assignment**, and **special purpose** operators.

Common operators include:

.. list-table::
   :header-rows: 1
   :widths: 20 60

   * - Category
     - Examples
   * - Arithmetic
     - ``+``, ``-``, ``*``, ``/``, ``%``
   * - Relational
     - ``==``, ``!=``, ``<``, ``>``, ``<=``, ``>=``
   * - Logical
     - ``&&``, ``||``, ``!``
   * - Bitwise
     - ``&``, ``|``, ``^``, ``~``, ``<<``, ``>>``
   * - Assignment
     - ``=``, ``+=``, ``-=`` etc.
   * - Special
     - ``sizeof``, ``typeid``, ``noexcept``, ``alignof``

Example: The ``noexcept`` Operator
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In addition to being a *specifier*, ``noexcept`` can also be used as an *operator* to query
whether a given expression or function call can throw exceptions.

.. code-block:: cpp

   #include <iostream>

   void safe() noexcept {}
   void risky() {}

   int main() {
       std::cout << std::boolalpha;
       std::cout << "safe() is noexcept? " << noexcept(safe()) << '\n'; //Output: 1
       std::cout << "risky() is noexcept? " << noexcept(risky()) << '\n'; //Output: 0
   }




.. tip::
   Use the ``noexcept`` operator to verify exception guarantees at compile time.
   This is particularly useful for template metaprogramming and static analysis.

------------------------------------------------------------

Function Specifiers
-------------------

Function specifiers refine how a function is compiled, linked, and optimized.
They impact both semantics and performance.

.. list-table::
   :header-rows: 1
   :widths: 18 40 52

   * - Specifier
     - Example
     - Purpose
   * - ``inline``
     - ``inline int add(int a, int b) { return a + b; }``
     - Suggests merging identical definitions across translation units. Allows safe inclusion in headers.
   * - ``constexpr``
     - ``constexpr int square(int x) { return x * x; }``
     - Enables compile-time evaluation when arguments are constant expressions.
   * - ``noexcept``
     - ``void process() noexcept {}``
     - Declares a function that cannot throw exceptions.
   * - ``static``
     - ``static void helper();``
     - Restricts linkage to the current translation unit (internal linkage).
   * - ``virtual`` / ``override`` / ``final``
     - ``virtual void speak() override;``
     - Used for polymorphism and overriding in class hierarchies.

.. tip::
   Combine specifiers carefully — for instance, ``constexpr`` implies ``inline``.

------------------------------------------------------------

Attributes
----------

C++17 standardizes attribute syntax, which allows programmers to annotate code
with compiler-recognized metadata enclosed in ``[[...]]``.

.. list-table::
   :header-rows: 1
   :widths: 20 65

   * - Attribute
     - Purpose
   * - ``[[nodiscard]]``
     - Warns if a function’s return value is ignored.
   * - ``[[maybe_unused]]``
     - Suppresses warnings about unused variables or parameters.
   * - ``[[deprecated]]``
     - Marks an entity as deprecated; generates warnings upon use.
   * - ``[[fallthrough]]``
     - Documents intentional fall-through in ``switch`` statements.

Example:

.. code-block:: cpp

   [[nodiscard]] int compute() {
       return 42;
   }

   void example() {
       compute();  // Warning: return value ignored
   }

------------------------------------------------------------

Best Practices
--------------

- Use the ``noexcept`` operator to validate compile-time exception safety.
- Apply ``constexpr`` and ``noexcept`` specifiers consistently for predictable, efficient behavior.
- Use attributes to make developer intent explicit and reduce compiler warnings.
- Always compile examples using:

  ``g++ -std=c++17 -Wall -Wextra -Wpedantic -Werror <file>.cpp -o <executable>``

------------------------------------------------------------

Detailed Topics
---------------

The following sections explore each callable category in detail:

.. toctree::
   :maxdepth: 2
   :caption: Callable Types

   function_specifiers/decltype
   function_specifiers/trailing_return
   function_specifiers/attributes
   function_specifiers/constexpr
   function_specifiers/inline
   function_specifiers/noexcept
