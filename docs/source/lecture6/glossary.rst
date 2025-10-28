Glossary
========

.. glossary::

   Aggregate Initialization
     Brace initialization of a type without user constructors.

     See also: :doc:`struct </lecture6/struct>`.

   Callable
     Any entity invokable with ``()``: function, pointer, functor, lambda, bound member, etc.

     See also:
     :doc:`Callables overview </lecture6/callables>`,
     :doc:`Function pointers </lecture6/callables/function_pointers>`,
     :doc:`Functors </lecture6/callables/functors>`,
     :doc:`Lambdas </lecture6/callables/lambdas>`,
     :doc:`std::function </lecture6/callables/std_function>`.

   Type Erasure
     Technique that hides a concrete type behind a uniform interface (e.g., ``std::function``).

     See also: :doc:`std::function </lecture6/callables/std_function>`.

   Trailing Return Type
     Placing the return type after parameters via ``auto f(...) -> ReturnType``.

     See also: :doc:`Trailing return types </lecture6/function_specifiers/trailing_return>`.

   ``decltype``
     An operator that inspects the **type** of an expression at compile time without evaluating it.

     See also: :doc:`decltype page </lecture6/function_specifiers/decltype>`.

   Value Category
     Classification of expressions (lvalue, prvalue, xvalue) that affects ``decltype`` results and overload resolution.

     See also: :doc:`decltype page </lecture6/function_specifiers/decltype>`.

   ``constexpr``
     Marks expressions/functions as eligible for compile-time evaluation when arguments are constant expressions.

     See also: :doc:`constexpr functions </lecture6/function_specifiers/constexpr>`.

   ``inline``
     Hint and ODR relaxation enabling the same function definition in multiple translation units (e.g., headers).

     See also: :doc:`inline and ODR </lecture6/function_specifiers/inline>`.

   ``noexcept``
     Declares that a function does not throw; may enable optimizations.

     See also: :doc:`noexcept specifier </lecture6/function_specifiers/noexcept>`.

   Attributes
     Standard attributes conveying intent to the compiler (e.g., ``[[nodiscard]]``, ``[[maybe_unused]]``, ``[[deprecated]]``).

     See also: :doc:`Function attributes </lecture6/function_specifiers/attributes>`.
