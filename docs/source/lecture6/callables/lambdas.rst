Lambdas
=======

An **anonymous** function object created inline.

Syntax
------

.. code-block:: cpp

   [captures](params) mutable noexcept -> return_type { body }

Comparator Example
------------------

.. code-block:: cpp

   std::sort(v.begin(), v.end(), [](int a, int b){ return a>b; });

Captures
--------

- ``[]`` none, ``[=]`` by value, ``[&]`` by reference, ``[x]`` specific, ``[=,&y]`` mixed.
- ``mutable`` permits modifying value-captures inside the lambda.
