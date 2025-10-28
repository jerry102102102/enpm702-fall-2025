Smart Pointers
=====================================

Overview
--------

Smart pointers are class templates in the C++ Standard Library that **automatically manage the lifetime of dynamically allocated objects**.  
They encapsulate raw pointers to provide **exception-safe**, **memory-leak-free**, and **ownership-aware** resource management.

When a smart pointer goes out of scope, it automatically releases the owned resource according to well-defined semantics — eliminating the need for explicit ``delete`` operations and reducing the risk of undefined behavior.

Smart pointers are defined in the ``<memory>`` header and implement **RAII (Resource Acquisition Is Initialization)** principles.

------------------------------------------------------------

Why Smart Pointers?
-------------------

In traditional C++, developers must manually allocate and free memory using ``new`` and ``delete``:

.. code-block:: cpp

   int* ptr = new int(42);
   // ... use ptr ...
   delete ptr;  // must remember to free it manually!

If an exception is thrown or an early return occurs before ``delete``, the resource leaks.  
Smart pointers automatically handle this cleanup through destructors.

------------------------------------------------------------

Types of Smart Pointers
-----------------------

C++17 provides three primary smart pointer types, each serving a distinct ownership model:

.. list-table::
   :header-rows: 1
   :widths: 20 65

   * - Smart Pointer
     - Description
   * - ``std::unique_ptr<T>``
     - Exclusive ownership. Only one smart pointer can own a given resource at a time. The resource is released automatically when the ``unique_ptr`` goes out of scope.
   * - ``std::shared_ptr<T>``
     - Shared ownership. Multiple smart pointers can refer to the same resource through a shared control block. The resource is deleted when the last ``shared_ptr`` is destroyed.
   * - ``std::weak_ptr<T>``
     - Non-owning observer of a ``std::shared_ptr``. It does not affect the reference count but can safely check whether the resource still exists.

------------------------------------------------------------

Comparison Summary
------------------

.. list-table::
   :header-rows: 1
   :widths: 20 25 25 30

   * - Feature
     - ``std::unique_ptr``
     - ``std::shared_ptr``
     - ``std::weak_ptr``
   * - Ownership
     - Exclusive
     - Shared
     - Observing (non-owning)
   * - Reference Count
     - None
     - Maintains strong & weak counts
     - Refers to shared control block only
   * - Overhead
     - Minimal
     - Moderate (control block)
     - Low (depends on shared control block)
   * - Thread Safety
     - Not thread-safe
     - Reference counting is thread-safe
     - Thread-safe for observation
   * - Best Use
     - RAII, unique resources
     - Shared ownership, graphs
     - Breaking circular dependencies

------------------------------------------------------------

Best Practices
--------------

- Prefer ``std::unique_ptr`` by default — it expresses clear ownership and has minimal overhead.
- Use ``std::shared_ptr`` **only** when ownership must be shared across multiple entities.
- Use ``std::weak_ptr`` to **observe** shared objects or **break circular references**.
- Avoid manually using ``new`` or ``delete`` — use ``std::make_unique`` or ``std::make_shared`` instead.
- Keep smart pointer usage localized; avoid passing them unnecessarily across APIs if only observation is required.

Example:

.. code-block:: cpp

   #include <iostream>
   #include <memory>

   int main() {
       auto p = std::make_unique<int>(42);
       std::cout << *p << '\n';  // 42

       auto s = std::make_shared<int>(100);
       std::weak_ptr<int> w{s};

       if (auto sp = w.lock()) {
           std::cout << "Shared value: " << *sp << '\n';
       }
   }

------------------------------------------------------------

Detailed Topics
---------------

The following sections explore each smart pointer type in detail:

.. toctree::
   :maxdepth: 2
   :caption: Smart Pointer Types

   smart_pointers/unique_pointers
   smart_pointers/shared_pointers
   smart_pointers/weak_pointers
