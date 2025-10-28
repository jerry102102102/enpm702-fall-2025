Lecture 6 - Functions (Advanced Topics)
=========================================

This site accompanies *ENPM702 - Lecture 6: Functions — Advanced Topics*. It organizes the lecture into concise, browsable pages with examples, short exercises, and instructor notes.

Learning Outcomes
-----------------

- Use **struct** idiomatically (aggregate initialization, structured bindings).
- Write **generic functions** with **templates**; understand deduction and specialization.
- Apply **decltype** and **trailing return types** when return types depend on parameters.
- Use function specifiers: **constexpr**, **inline**, **noexcept**.
- Use attributes: ``[[nodiscard]]``, ``[[maybe_unused]]``, ``[[deprecated]]``.
- Master **callables**: function pointers, functors, lambdas, and ``std::function``.

.. tip::
   Compile examples with ``-std=c++17 -Wall -Wextra -Wpedantic -Werror`` for strong diagnostics.

Detailed Topics
---------------

The following sections explore each topic in Lecture 6:

.. toctree::
   :maxdepth: 2
   :caption: Lecture 6
   :titlesonly:

   struct
   templates
   function_specifiers
   callables            
   exercises
   glossary
   notes
   references
