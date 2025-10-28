.. default-domain:: cpp

=====================================
C++ Topics Overview
=====================================

This document provides a concise overview of the material covered in **ENPM702 (fall 2025)**.

Source Code
------------

Source code for all lectures is available at

.. raw:: html

   <a href="https://github.com/zeidk/enpm702-fall-2025" target="_blank" rel="noopener noreferrer">
       https://github.com/zeidk/enpm702-fall-2025
   </a>


Lecture 6 - Functions: Advanced Topics
=======================================

Lecture 6 explores modern function-related features in C++, focusing on flexibility, safety, and performance. Students learn how C++ enables generic programming and compile-time computation through templates and modern specifiers.

See the full lecture here → :doc:`lecture6/lecture6`

**Core Concepts**

- **Structs and Aggregates:** Using C-style structs as lightweight data containers, including aggregate initialization and structured bindings.
- **Function Templates:** Defining type-independent functions, template deduction, and specialization.
- **Modern Function Syntax:** Using ``decltype``, trailing return types, and the ``constexpr``, ``inline``, and ``noexcept`` specifiers.
- **Attributes:** Applying ``[[nodiscard]]``, ``[[maybe_unused]]``, and ``[[deprecated]]`` to improve code safety and clarity.
- **Callables:** Understanding and using function pointers, functors, lambdas, and ``std::function`` for flexible function invocation.

Lecture 7 - Move Semantics and Smart Pointers
===============================================

Lecture 7 introduces efficient resource handling techniques through **move semantics** and **smart pointers**, two foundational concepts from C++11 that promote performance and memory safety.

See the full lecture here → :doc:`lecture7/lecture7`

**Core Concepts**

- **Move Semantics:** Transferring ownership of resources instead of copying, enabled by rvalue references (``&&``) and ``std::move``.
- **Smart Pointers:** Managing dynamic memory automatically using classes from ``<memory>``.
  - ``std::unique_ptr`` - Exclusive ownership and move-only semantics.
  - ``std::shared_ptr`` - Shared ownership with reference counting.
  - ``std::weak_ptr`` - Non-owning observer used to prevent circular references.

**Learning Outcome**

Together, these lectures provide a deeper understanding of how modern C++ supports **generic, safe, and efficient programming**, preparing students to write expressive and resource-aware software.
