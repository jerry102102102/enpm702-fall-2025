``std::unique_ptr``
===================

A ``std::unique_ptr<T>`` provides **exclusive ownership** of a dynamically allocated resource.  
Only one ``unique_ptr`` can own a given object at a time.

Basics
------

.. code-block:: cpp

   #include <iostream>
   #include <memory>

   int main() {
       auto p = std::make_unique<int>(42);  // creates and owns an int
       std::cout << *p << '\n';             // access value

       auto q = std::move(p);               // transfer ownership
       if (!p) std::cout << "p is null\n";  // p no longer owns the resource
   }

Rules of Thumb
--------------

- Ownership is **unique** — cannot be copied, only moved.
- Resource is automatically destroyed when the last ``unique_ptr`` owning it is destroyed.
- Use ``std::make_unique<T>()`` instead of ``new`` for exception safety.
- ``get()`` returns a non-owning raw pointer for observation.
- ``reset()`` releases ownership (optionally replaces it with another resource).

Use Cases
---------

- Representing exclusive ownership of resources.
- Managing dynamic allocations within classes (RAII pattern).
- Avoiding leaks when exceptions occur.
- Safely returning dynamically allocated objects from functions.

Example
-------

.. code-block:: cpp

   std::unique_ptr<int> create_value() {
       return std::make_unique<int>(10);
   }

   int main() {
       auto value = create_value();
       std::cout << *value << '\n';
   }
