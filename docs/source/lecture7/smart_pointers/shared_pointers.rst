``std::shared_ptr``
===================

A ``std::shared_ptr<T>`` provides **shared ownership** of a dynamically allocated object.  
Multiple ``shared_ptr`` instances can own the same resource through a shared **control block**.

Basics
------

.. code-block:: cpp

   #include <iostream>
   #include <memory>

   int main() {
       auto s1 = std::make_shared<int>(42);  // reference count = 1
       auto s2 = s1;                         // reference count = 2
       std::cout << *s1 << '\n';
       std::cout << "use_count = " << s1.use_count() << '\n';
   }

Rules of Thumb
--------------

- Each ``shared_ptr`` increases the **strong reference count** in its control block.
- The resource is deleted automatically when the last ``shared_ptr`` goes out of scope.
- Use ``std::make_shared<T>()`` for a single, efficient heap allocation.
- Avoid using raw pointers to share ownership manually.
- Use ``weak_ptr`` to observe shared resources without extending their lifetime.

Use Cases
---------

- When multiple owners need access to the same resource.
- Sharing ownership across multiple scopes or threads.
- Managing graph-like or tree-like structures where nodes reference each other.

Example
-------

.. code-block:: cpp

   struct Node {
       int value;
       std::shared_ptr<Node> next;
       Node(int v) : value(v) {}
   };

   int main() {
       auto n1 = std::make_shared<Node>(1);
       auto n2 = std::make_shared<Node>(2);
       n1->next = n2;  // shared ownership
   }
