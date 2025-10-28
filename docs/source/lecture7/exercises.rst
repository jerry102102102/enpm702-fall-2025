Exercises
=========

1. Exclusive Ownership With ``std::unique_ptr``
-----------------------------------------------

Manage a dynamically allocated buffer with **exclusive** ownership and demonstrate move-only behavior.

**Tasks:**

- Define ``struct Buffer { std::size_t n; int* data; };`` and wrap it in ``std::unique_ptr<Buffer>`` using ``std::make_unique``.
- Write a function ``std::unique_ptr<Buffer> make_buffer(std::size_t n)`` that allocates and initializes.
- Show that copy construction fails to compile, but ``auto b2 = std::move(b1);`` transfers ownership.
- Use ``get()`` only for non-owning observation; print the address before and after the move.


2. ``unique_ptr`` With a Custom Deleter
---------------------------------------

Some resources require special destruction (e.g., ``FILE*``, sockets, or ``malloc``-allocated memory).

**Tasks:**

- Write ``struct FreeDeleter { void operator()(int* p) const noexcept { std::free(p); } };``.
- Create ``std::unique_ptr<int, FreeDeleter> p{ static_cast<int*>(std::malloc(4*sizeof(int))) };`` and initialize the array.
- Verify the custom deleter runs by printing in the deleter (optional).
- Explain why ``std::make_unique`` cannot be used with a custom deleter.


3. ``unique_ptr`` in Containers (No Copies)
-------------------------------------------

Store multiple move-only tasks in a vector.

**Tasks:**

- Define ``struct Task { int id; };``.
- Create ``std::vector<std::unique_ptr<Task>> v;`` and insert with ``emplace_back(std::make_unique<Task>(i))`` for ``i = 0..4``.
- Iterate and print IDs; then move one element out: ``auto t = std::move(v[2]);`` and show ``v[2] == nullptr``.
- Try to copy an element and confirm the compiler error documents move-only semantics.


4. ``shared_ptr``: Copy vs. Move, and ``use_count()``
-------------------------------------------------------

Observe the control block’s strong count under different operations.

**Tasks:**

- Create ``auto s1 = std::make_shared<int>(42);`` then ``auto s2 = s1;`` and print ``s1.use_count()``.
- Move ``s2`` into ``auto s3 = std::move(s2);`` and print counts again; explain why the count did not change on move.
- Call ``s3.reset();`` and verify when the object is destroyed (optional: add a custom type with a destructor that prints).


5. Breaking Cycles With ``weak_ptr``
------------------------------------

Prevent a leak-like cycle in a doubly linked pair.

**Tasks:**

- Define:

  .. code-block:: cpp

     struct Node {
         int v;
         std::shared_ptr<Node> next;
         std::weak_ptr<Node> prev;
     };

- Link two nodes A↔B with ``next`` (strong) forward and ``prev`` (weak) back.
- Exit scope; confirm both destructors run (print messages in destructors).
- Explain why making ``prev`` a ``shared_ptr`` would keep the objects alive.


6. ``weak_ptr::lock()`` Usage Pattern
----------------------------------------

Safely access an optionally alive object.

**Tasks:**

- Create ``auto s = std::make_shared<int>(100); std::weak_ptr<int> w{s};``.
- Write ``void print_if_alive(std::weak_ptr<int> w)`` that does:

  .. code-block:: cpp

     if (auto sp = w.lock()) {
         std::cout << *sp << '\n';
     } else {
         std::cout << "expired\n";
     }

- Call it before and after ``s.reset();`` to demonstrate both paths.


7. ``make_unique`` / ``make_shared`` vs. ``new`` (Exception Safety)
---------------------------------------------------------------------

Show why factory helpers are preferred.

**Tasks:**

- Write a function that takes two arguments, one expression throws after ``new T`` succeeds.
- Demonstrate potential leak with ``std::unique_ptr<T>(new T(...))`` embedded in a larger expression.
- Fix by splitting statements or, better, using ``auto p = std::make_unique<T>(...);`` and explain why it is exception-safe.


8. Sharing a Subobject (Aliasing ``shared_ptr``)
--------------------------------------------------

Manage a subobject without extending its lifetime independently.

**Tasks:**

- Define:

  .. code-block:: cpp

     struct Packet {
         std::vector<int> payload;
     };
     auto sp = std::make_shared<Packet>();

- Create an aliasing ``shared_ptr`` to the first element:
  ``std::shared_ptr<int> head(sp, sp->payload.data());``
- Show that ``head`` keeps the **Packet** alive (via the same control block) even though it points to an ``int`` subobject.
- Verify destruction happens only after both ``sp`` and all aliasing owners are gone.


9. ``get_deleter`` and ``owner_before``
-----------------------------------------

Explore control-block features used in associative containers.

**Tasks:**

- Create a ``std::shared_ptr<int> s = std::make_shared<int>(7);`` with a custom deleter type (e.g., a struct that prints).
- Retrieve it via ``auto* d = std::get_deleter<YourDeleter>(s);`` and confirm it is non-null.
- Put several ``shared_ptr<int>`` into ``std::set`` using a comparator based on ``owner_before``; demonstrate that the ordering is by ownership, not by raw pointer value.


10. Migrating Ownership: ``unique_ptr`` → ``shared_ptr`` (Exactly Once)
-------------------------------------------------------------------------

Hand off exclusive ownership to shared ownership safely.

**Tasks:**

- Start with ``auto up = std::make_unique<int>(55);``.
- Transfer to shared ownership **once**: ``auto sp = std::shared_ptr<int>(std::move(up));`` and show ``up == nullptr``.
- Add another owner ``auto sp2 = sp;`` then reset both; verify the object’s lifetime ends when the last ``shared_ptr`` is destroyed.
- Discuss why converting back from ``shared_ptr`` to ``unique_ptr`` is generally unsafe or impossible.
