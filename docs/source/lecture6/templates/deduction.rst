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
