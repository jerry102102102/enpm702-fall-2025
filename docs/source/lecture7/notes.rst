Important Notes
===============

- **Move semantics** transfer ownership instead of copying; use ``std::move`` to enable efficient resource reuse.
- Rvalue references (``T&&``) bind to temporaries, enabling move constructors and move assignments.
- ``std::unique_ptr`` provides exclusive ownership—cannot be copied, only moved.
- ``std::shared_ptr`` enables shared ownership—resource deleted when the last owner is destroyed.
- ``std::weak_ptr`` observes a ``shared_ptr`` without extending its lifetime; use ``lock()`` to check validity.
