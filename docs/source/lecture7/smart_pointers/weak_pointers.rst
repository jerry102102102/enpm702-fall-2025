``std::weak_ptr``
=================

A ``std::weak_ptr<T>`` provides a **non-owning** reference to a resource managed by a ``std::shared_ptr``.  
It allows safe observation without affecting the object’s lifetime.

Basics
------

.. code-block:: cpp

   #include <iostream>
   #include <memory>

   int main() {
       auto s = std::make_shared<int>(42);
       std::weak_ptr<int> w{s};  // observes s

       if (auto sp = w.lock())   // promotes to shared_ptr if still valid
           std::cout << *sp << '\n';
       else
           std::cout << "expired\n";
   }

Rules of Thumb
--------------

- Does **not** change the reference count of the managed object.
- Can be converted to a ``shared_ptr`` using ``lock()`` — only if the object still exists.
- ``expired()`` checks whether the resource has already been destroyed.
- Useful for **breaking circular dependencies** between ``shared_ptr`` objects.
- Control block remains valid until both strong and weak counts reach zero.

Use Cases
---------

- Observing shared resources without extending their lifetime.
- Avoiding ownership cycles (e.g., parent ↔ child relationships).
- Checking if a shared object still exists before accessing it.

Example
-------

.. code-block:: cpp

   struct Parent;
   struct Child {
       std::shared_ptr<Parent> parent;
   };

   struct Parent {
       std::weak_ptr<Child> child;  // prevents circular ownership
   };

   int main() {
       auto p = std::make_shared<Parent>();
       auto c = std::make_shared<Child>();
       p->child = c;
       c->parent = p;
   }
