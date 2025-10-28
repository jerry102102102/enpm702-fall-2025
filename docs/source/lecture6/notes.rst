Important Notes
===============

- ``decltype`` inspects types without evaluating expressions; parentheses affect results.
- ``auto`` may drop top-level ``const`` and references; use ``decltype(auto)`` to preserve.
- ``constexpr`` shifts pure computation to compile time.
- ``inline`` helps with ODR when defining functions in headers.
- ``noexcept`` conveys and enforces exception guarantees; use deliberately.
- ``std::function`` provides flexibility at a runtime cost—choose it when needed.
