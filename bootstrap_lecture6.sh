#!/usr/bin/env bash
set -euo pipefail

ROOT="docs"
SRC="$ROOT/source"

echo "Creating folder structure..."
mkdir -p "$SRC"/lecture6/templates
mkdir -p "$SRC"/lecture6/function_specifiers
mkdir -p "$SRC"/lecture6/callables
mkdir -p "$SRC"/_static/images
mkdir -p "$SRC"/_templates

########################################
# requirements.txt
########################################
cat > "$ROOT/requirements.txt" <<'EOF'
sphinx>=7.3
sphinx-rtd-theme>=1.3
sphinx-design>=0.6
EOF

########################################
# conf.py
########################################
cat > "$SRC/conf.py" <<'EOF'
import os, sys
from datetime import date

project = 'ENPM702 Lecture 6 — Functions: Advanced Topics'
author = 'Z. Kootbally'
copyright = f'{date.today().year}, {author}'
release = 'v1.0'

extensions = [
    'sphinx.ext.autodoc',
    'sphinx.ext.napoleon',
    'sphinx.ext.intersphinx',
    'sphinx_design',
]

intersphinx_mapping = {
    'python': ('https://docs.python.org/3', {}),
}

templates_path = ['_templates']
exclude_patterns = []
html_theme = 'sphinx_rtd_theme'
html_static_path = ['_static']
html_theme_options = {
    'collapse_navigation': False,
    'navigation_depth': 3,
}
master_doc = 'index'
EOF

########################################
# index.rst
########################################
cat > "$SRC/index.rst" <<'EOF'
ENPM702 Lecture 6 — Functions: Advanced Topics
==============================================

.. meta::
   :description: Read the Docs site for ENPM702 Lecture 6 (Functions — Advanced Topics): struct, templates, decltype, trailing return types, constexpr, inline, noexcept, attributes, and callables.

.. toctree::
   :maxdepth: 2
   :caption: Contents

   lecture6/introduction
   lecture6/struct
   lecture6/templates/overview
   lecture6/templates/syntax
   lecture6/templates/specialization
   lecture6/templates/deduction
   lecture6/function_specifiers/decltype
   lecture6/function_specifiers/trailing_return
   lecture6/function_specifiers/constexpr
   lecture6/function_specifiers/inline
   lecture6/function_specifiers/noexcept
   lecture6/function_specifiers/attributes
   lecture6/callables/function_pointers
   lecture6/callables/functors
   lecture6/callables/lambdas
   lecture6/callables/std_function
   lecture6/exercises
   lecture6/glossary
   lecture6/notes
   lecture6/references
EOF

########################################
# introduction.rst
########################################
cat > "$SRC/lecture6/introduction.rst" <<'EOF'
Introduction
============

This site accompanies *ENPM702 – Lecture 6: Functions — Advanced Topics*. It organizes the lecture into concise, browsable pages with examples, short exercises, and instructor notes.

Learning Outcomes
-----------------

- Use **struct** idiomatically (aggregate initialization, structured bindings).
- Write **generic functions** with **templates**; understand deduction and specialization.
- Apply **decltype** and **trailing return types** when return types depend on parameters.
- Use function specifiers: **constexpr**, **inline**, **noexcept**.
- Use attributes: ``[[nodiscard]]``, ``[[maybe_unused]]``, ``[[deprecated]]``.
- Master **callables**: function pointers, functors, lambdas, and ``std::function``.

.. tip::
   Compile examples with ``-std=c++20 -Wall -Wextra -Werror`` for strong diagnostics.
EOF

########################################
# struct.rst
########################################
cat > "$SRC/lecture6/struct.rst" <<'EOF'
struct
======

Overview
--------

In modern C++, ``struct`` and ``class`` are identical except for default access: ``struct`` members are public; ``class`` members are private. Prefer ``struct`` for simple passive aggregates and ``class`` when encapsulation is required.

Aggregate Initialization
------------------------

A type with no user-declared constructors and no private/protected non-static members is an **aggregate** and supports brace initialization:

.. code-block:: cpp

   struct Point {
     double x;
     double y;
     std::string label{"default"};
   };

   Point p1{10.0, 20.0, "center"};
   Point p2{10.0, 20.0};  // label -> "default"

Structured Bindings
-------------------

Create named variables for members, by value or by reference.

.. code-block:: cpp

   Point p{1.0, 2.0, "start"};
   auto [x, y, label] = p;     // copies
   auto& [xr, yr, lr] = p;     // references; writing xr modifies p.x
EOF

########################################
# templates/overview.rst
########################################
cat > "$SRC/lecture6/templates/overview.rst" <<'EOF'
Templates — Overview
====================

A **function template** is a blueprint the compiler uses to generate concrete overloads. Write the algorithm once; the compiler **instantiates** versions for used types.

.. code-block:: cpp

   template<typename T>
   T add(T a, T b) { return a + b; }

Benefits
--------

- Maintainability: fix once, apply everywhere.
- Consistency: identical logic across types.
- Flexibility: new types work without new overloads.
- Zero-overhead abstraction at compile time.

Templates vs Overloading
------------------------

- Same logic across types → templates.
- Different logic per type → overloading or specialization.
EOF

########################################
# templates/syntax.rst
########################################
cat > "$SRC/lecture6/templates/syntax.rst" <<'EOF'
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
EOF

########################################
# templates/specialization.rst
########################################
cat > "$SRC/lecture6/templates/specialization.rst" <<'EOF'
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
EOF

########################################
# templates/deduction.rst
########################################
cat > "$SRC/lecture6/templates/deduction.rst" <<'EOF'
Type Deduction & Failures
=========================

Basic Deduction
---------------

.. code-block:: cpp

   template<typename T>
   T add(T a, T b) { return a + b; }

   int r = add(3, 5); // T := int

References and ``const``
------------------------

.. code-block:: cpp

   template<typename T>
   void modify(T& v) { v *= 2; }  // T := int; parameter type is T&

   template<typename T>
   void print(const T& v) { /* ... */ }  // T := int; const applies in param

Explicit Arguments
------------------

.. code-block:: cpp

   short s{42};
   auto a = add(s, s);     // T := short
   auto b = add<int>(s,s); // force T := int (converts before call)

When Deduction Fails
--------------------

- No parameters to deduce from:

.. code-block:: cpp

   template<typename T> T make() { return T{}; }
   // auto v = make(); // error
   auto v = make<int>();   // OK

- Conflicting parameter types:

.. code-block:: cpp

   template<typename T> T pick(T a, T b) { return a; }
   // pick(3, 4.5); // error: T cannot be both int and double
EOF

########################################
# function_specifiers/decltype.rst
########################################
cat > "$SRC/lecture6/function_specifiers/decltype.rst" <<'EOF'
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
EOF

########################################
# function_specifiers/trailing_return.rst
########################################
cat > "$SRC/lecture6/function_specifiers/trailing_return.rst" <<'EOF'
Trailing Return Types
====================

Motivation
----------

When the return type depends on parameter types, place it *after* parameters.

.. code-block:: cpp

   template<typename T, typename U>
   auto multiply(const T& a, const U& b) -> decltype(a * b) {
     return a * b;
   }

C++14+ Shortcut
---------------

For simple cases, let ``auto`` deduce the return:

.. code-block:: cpp

   template<typename T, typename U>
   auto add(T a, U b) { return a + b; }

Note: plain ``auto`` drops top-level ``const`` and references. Use ``decltype(auto)`` or an explicit trailing return to preserve qualifiers.
EOF

########################################
# function_specifiers/constexpr.rst
########################################
cat > "$SRC/lecture6/function_specifiers/constexpr.rst" <<'EOF'
``constexpr`` Functions
=======================

Meaning
-------

``constexpr`` marks an expression or function as eligible for **compile-time evaluation**. If all arguments are constant expressions, the compiler computes the result at compile time.

.. code-block:: cpp

   constexpr int square(int x) { return x * x; }
   constexpr int n = square(5);     // compile-time
   int m = 7;
   int r = square(m);               // runtime

Why It Matters
--------------

- Eliminates runtime cost for pure computations.
- Enables use in contexts that require compile-time constants (array bounds, template args).
- Surfaces logic errors earlier (at compile time).

Guidelines
----------

- Keep functions pure and deterministic.
- From C++14 onward, loops and conditionals are permitted in ``constexpr`` bodies.
EOF

########################################
# function_specifiers/inline.rst
########################################
cat > "$SRC/lecture6/function_specifiers/inline.rst" <<'EOF'
``inline`` and the ODR
=====================

Inlining vs Linkage
-------------------

``inline`` is a hint for inlining, but more importantly it **relaxes the One Definition Rule (ODR)** so the same function definition can appear in multiple translation units (e.g., in a header).

.. code-block:: cpp

   // utils.hpp
   #pragma once
   inline int add(int a, int b) { return a + b; } // legal to define in a header

Notes
-----

- Compilers may inline regardless of the keyword.
- Avoid inlining large, recursive, or virtual functions for performance reasons.
EOF

########################################
# function_specifiers/noexcept.rst
########################################
cat > "$SRC/lecture6/function_specifiers/noexcept.rst" <<'EOF'
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
EOF

########################################
# function_specifiers/attributes.rst
########################################
cat > "$SRC/lecture6/function_specifiers/attributes.rst" <<'EOF'
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
EOF

########################################
# callables/function_pointers.rst
########################################
cat > "$SRC/lecture6/callables/function_pointers.rst" <<'EOF'
Function Pointers
=================

Definition
----------

A function pointer stores the address of a function with a compatible signature.

.. code-block:: cpp

   int add(int a, int b);
   int (*ptr)(int,int) = &add;   // '&' optional; function name decays to pointer
   int r = ptr(2,3);             // 5

Callbacks
---------

.. code-block:: cpp

   void process(int* arr, int n, void (*op)(int)) {
     for (int i=0;i<n;++i) op(arr[i]);
   }

Cautions
--------

- Signature must match exactly.
- No state capture (unlike lambdas/functors).
EOF

########################################
# callables/functors.rst
########################################
cat > "$SRC/lecture6/callables/functors.rst" <<'EOF'
Functors (Function Objects)
===========================

A **functor** is a type that overloads ``operator()``. It is callable **and** can hold state.

.. code-block:: cpp

   struct Counter {
     int count{0};
     void operator()() { ++count; }
   };

Use Cases
--------

- Predicates and transformations for STL algorithms.
- Stateful callbacks.
EOF

########################################
# callables/lambdas.rst
########################################
cat > "$SRC/lecture6/callables/lambdas.rst" <<'EOF'
Lambdas
=======

An **anonymous** function object created inline.

Syntax
------

.. code-block:: cpp

   [captures](params) mutable noexcept -> return_type { body }

Comparator Example
------------------

.. code-block:: cpp

   std::sort(v.begin(), v.end(), [](int a, int b){ return a>b; });

Captures
--------

- ``[]`` none, ``[=]`` by value, ``[&]`` by reference, ``[x]`` specific, ``[=,&y]`` mixed.
- ``mutable`` permits modifying value-captures inside the lambda.
EOF

########################################
# callables/std_function.rst
########################################
cat > "$SRC/lecture6/callables/std_function.rst" <<'EOF'
``std::function`` and Type Erasure
=================================

A polymorphic wrapper that can store **any callable** with a compatible signature.

.. code-block:: cpp

   #include <functional>
   std::function<int(int)> op;
   op = [](int x){ return x+10; };
   op = [](int x){ return x*2; };

Notes
-----

- Adds indirection and possible heap allocation.
- Prefer direct callables in tight loops; use ``std::function`` for flexibility.
EOF

########################################
# exercises.rst
########################################
cat > "$SRC/lecture6/exercises.rst" <<'EOF'
Exercises
=========

1) Template Instantiation & Deduction
-------------------------------------

- Implement ``template<typename T> T multiply(T a, T b);``.
- Test with ``int``, ``double``, and ``std::string`` (concatenation).
- Create a failure on purpose (mismatched types) and explain the error.

2) Lambda Capture and ``mutable``
---------------------------------

- Write a lambda counter using ``[counter]() mutable``.
- Show behavior difference vs. capturing by reference ``[&counter]``.

3) ``decltype`` & Trailing Return Type
--------------------------------------

- Implement ``auto dot(T a, U b) -> decltype(a*b);``.
- Show that ``decltype`` preserves references using ``decltype(auto)``.

4) ``constexpr`` Utilities
--------------------------

- Implement a ``constexpr`` ``powi(int base, int exp)`` using a loop (C++14+).
- Use it in a compile-time context (array bound or ``static_assert``).

5) Attributes & ``noexcept``
----------------------------

- Mark a function ``[[nodiscard]]`` and demonstrate the warning.
- Write a function that forwards to a ``noexcept`` callee using conditional ``noexcept``.
EOF

########################################
# glossary.rst
########################################
cat > "$SRC/lecture6/glossary.rst" <<'EOF'
Glossary
========

.. glossary::

   Aggregate Initialization
     Brace initialization of a type without user constructors.

   Callable
     Any entity invokable with ``()``: function, pointer, functor, lambda, bound member, etc.

   Type Erasure
     Technique that hides the concrete type behind a uniform interface (e.g., ``std::function``).

   Trailing Return Type
     Placing the return type after parameters via ``auto f(...) -> ReturnType``.

   Value Category
     Classification of expressions: lvalue, prvalue, xvalue; affects ``decltype`` results.
EOF

########################################
# notes.rst
########################################
cat > "$SRC/lecture6/notes.rst" <<'EOF'
Important Notes
===============

- ``decltype`` inspects types without evaluating expressions; parentheses affect results.
- ``auto`` may drop top-level ``const`` and references; use ``decltype(auto)`` to preserve.
- ``constexpr`` shifts pure computation to compile time.
- ``inline`` helps with ODR when defining functions in headers.
- ``noexcept`` conveys and enforces exception guarantees; use deliberately.
- ``std::function`` provides flexibility at a runtime cost—choose it when needed.
EOF

########################################
# references.rst
########################################
cat > "$SRC/lecture6/references.rst" <<'EOF'
References
==========

- ISO/IEC 14882:2020 — *C++20 Standard*.
- B. Stroustrup, *The C++ Programming Language*, 4th Ed.
- cppreference — https://en.cppreference.com/
- ENPM702 Lecture 6 slides (Fall 2025).
EOF

echo "Done. Docs scaffold and content created under: $ROOT"
echo
echo "Build instructions:"
echo "  python -m venv .venv && source .venv/bin/activate"
echo "  pip install -r docs/requirements.txt"
echo "  sphinx-build -b html docs/source docs/_build/html"
