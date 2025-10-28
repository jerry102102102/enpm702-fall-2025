Glossary
========

.. glossary::

   RAII (Resource Acquisition Is Initialization)
     Idiom where a resource’s lifetime is tied to an object’s lifetime; cleanup happens in the destructor.

     See also: :doc:`Smart pointers overview <smart_pointers>`.

   Smart Pointer
     Class template that manages a dynamically allocated object’s lifetime according to a defined ownership model.

     See also:
     :doc:`unique_ptr <smart_pointers/unique_pointers>`,
     :doc:`shared_ptr <smart_pointers/shared_pointers>`,
     :doc:`weak_ptr <smart_pointers/weak_pointers>`.

   ``std::unique_ptr``
     Smart pointer with **exclusive** ownership; non-copyable, movable.

     See also: :doc:`unique_ptr <smart_pointers/unique_pointers>`.

   ``std::shared_ptr``
     Smart pointer with **shared** ownership via a control block and reference counts.

     See also: :doc:`shared_ptr <smart_pointers/shared_pointers>`.

   ``std::weak_ptr``
     **Non-owning** observer of a ``shared_ptr``; can be promoted with ``lock()`` if the object still exists.

     See also: :doc:`weak_ptr <smart_pointers/weak_pointers>`.

   Control Block
     Heap-allocated bookkeeping structure for ``shared_ptr``/``weak_ptr`` (stores strong/weak counts, deleter, pointer).

     See also: :doc:`shared_ptr <smart_pointers/shared_pointers>`.

   Strong Count (``use_count``)
     Number of active ``shared_ptr`` owners of the managed object (when it reaches zero, the object is deleted).

     See also: :doc:`shared_ptr <smart_pointers/shared_pointers>`.

   Weak Count
     Number of ``weak_ptr`` observers **plus** the control block’s self-reference; when both strong and weak counts hit zero, the control block is destroyed.

     See also: :doc:`weak_ptr <smart_pointers/weak_pointers>`.

   Custom Deleter
     Callable stored in the control block (or in ``unique_ptr``) that defines how to destroy the managed object.

     See also:
     :doc:`unique_ptr <smart_pointers/unique_pointers>`,
     :doc:`shared_ptr <smart_pointers/shared_pointers>`.

   ``std::make_unique`` / ``std::make_shared``
     Factory helpers that construct the object and its smart pointer safely (and efficiently for ``shared_ptr`` via single allocation).

     See also:
     :doc:`unique_ptr <smart_pointers/unique_pointers>`,
     :doc:`shared_ptr <smart_pointers/shared_pointers>`.

   Circular Dependency
     A cycle of ``shared_ptr`` ownership preventing deletion; break with a ``weak_ptr`` on at least one link.

     See also: :doc:`weak_ptr <smart_pointers/weak_pointers>`.

   Move Semantics
     Transfer of resources from one object to another instead of copying, enabled by rvalue references.

     See also: :doc:`Move semantics <move_semantics>`.

   Rvalue Reference (``T&&``)
     Reference type that can bind to temporaries; enables moving resources out of objects.

     See also: :doc:`Move semantics <move_semantics>`.

   ``std::move``
     Cast that treats an expression as an rvalue, allowing move construction/assignment.

     See also: :doc:`Move semantics <move_semantics>`.

   Move Constructor / Move Assignment
     Special member functions that transfer ownership/state from a source object, leaving it valid but unspecified.

     See also: :doc:`Move semantics <move_semantics>`.

   Copy Elision / RVO
     Optimization where the compiler elides copy/move of temporaries; guaranteed in some cases (C++17).

     See also: :doc:`Move semantics <move_semantics>`.

   Perfect Forwarding / Forwarding Reference
     Technique and reference category (``T&&`` with type deduction) that preserves value category when passing arguments.

     See also: :doc:`Move semantics <move_semantics>`.
