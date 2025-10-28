Lecture 7 - Move Semantics and Smart Pointers
===============================================

This site accompanies *ENPM702 - Lecture 7: Move Semantics & Smart Pointers*. It organizes the lecture into concise, browsable pages with examples, short exercises, and instructor notes.

Learning Outcomes
-----------------

By the end of this session, you will be able to:

- Explain **move semantics** and distinguish between **lvalues**, **prvalues**, and **xvalues** in \CC.
- Use **rvalue references** and **std::move** to efficiently transfer ownership of resources.
- Implement and manage **smart pointers** from ``<memory>`` to ensure safe and automatic resource cleanup.
- Create and use **std::unique_ptr** with proper initialization, exclusive ownership, and member methods (``get()``, ``release()``, ``reset()``, ``swap()``).
- Apply **move semantics** when passing or returning ``std::unique_ptr`` to convey ownership transfer clearly.
- Use **std::shared_ptr** to manage shared ownership, explain its **control block structure**, and utilize methods like ``use_count()`` and ``unique()``.
- Pass and return **std::shared_ptr** correctly using **copy semantics** and understand **reference counting** and **Return Value Optimization (RVO)**.
- Use **std::weak_ptr** for non-owning observation, employ ``lock()`` and ``expired()`` safely, and explain how it breaks **circular dependencies**.
- Choose the appropriate **smart pointer type** (``unique_ptr``, ``shared_ptr``, or ``weak_ptr``) for various ownership and lifetime management scenarios.

.. tip::
   Compile examples with ``-std=c++17 -Wall -Wextra -Wpedantic -Werror`` for strong diagnostics.

Detailed Topics
---------------

The following sections explore each topic in Lecture 6:

.. toctree::
   :maxdepth: 2
   :caption: Lecture 7
   :titlesonly:

   move_semantics
   smart_pointers          
   exercises
   glossary
   notes
   references
