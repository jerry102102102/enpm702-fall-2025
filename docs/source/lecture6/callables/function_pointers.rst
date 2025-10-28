Function Pointers
=================

Definition
----------

A function pointer stores the address of a function with a compatible signature.

.. code-block:: cpp

   int add(int a, int b);
   int (*ptr)(int,int) = &add;   // '&' optional; function name decays to pointer
   int r = ptr(2,3);             // 5

Callbacks
---------

.. code-block:: cpp

   void process(int* arr, int n, void (*op)(int)) {
     for (int i=0;i<n;++i) op(arr[i]);
   }

Cautions
--------

- Signature must match exactly.
- No state capture (unlike lambdas/functors).
