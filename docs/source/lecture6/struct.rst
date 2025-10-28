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
