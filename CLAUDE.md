# C++ Core Guidelines — Agent-Oriented Implementation Guide (English)

**Purpose**  
This document distills the C++ Core Guidelines into a practical, agent‑ready checklist and set of auto‑fix strategies. The goal is to help an AI coding assistant (or code‑gen agent) produce safe, modern, and maintainable C++ (C++17/20+) by default.

---

## 0) Scope & Philosophy (What to optimize for)
- Prefer **clarity, safety, and simplicity** while preserving **zero‑overhead abstractions**. Favor compile‑time guarantees (types, `constexpr`, `static_assert`) over run‑time checks.
- Target **modern ISO C++** usage; adopt rules **gradually** in existing codebases.
- Design for **static type safety**, **resource safety**, and **invariant correctness**. When two options exist, choose the one with fewer historical errors and clearer intent.
- Think in terms of **interfaces** and **RAII**. Hide incidental complexity behind well‑specified types and functions.
- Be prescriptive: every “avoid” should be paired with a recommended “do instead.”

---

## 1) Enforcement Profiles & Tooling
Use (and encourage) automated enforcement wherever possible.
- **Profiles to satisfy**:  
  **type** (no type violations), **bounds** (no out-of-bounds access), **lifetime** (no leaks or dangling).  
  Treat these as non‑negotiable for generated code.
- **Static analysis**: enable `clang-tidy` (cppcoreguidelines-*, modernize-*, readability-*), compiler warnings (`-Wall -Wextra -Wconversion`), and sanitizers in tests (ASan/UBSan/TSan).
- **Contract-like checks**: Prefer GSL’s `Expects()` / `Ensures()` in public boundaries; prefer compile‑time proofs where possible.
- **Code review bot rules (minimum)**:
  - 🚫 “Naked” `new`/`delete` in application code.
  - 🚫 Raw owning pointers as data members or return types.
  - 🚫 C‑style arrays and casts in new code.
  - 🚫 Exceptions used for non‑error control flow.
  - ✅ RAII handles (smart pointers/containers) for ownership.
  - ✅ `std::vector`, `std::string`, `std::array`, `std::unique_ptr`/`std::shared_ptr` as appropriate.
  - ✅ `gsl::span`/views for array parameters; `gsl::not_null` for non‑nullable references.
  - ✅ Clear ownership in interfaces; non‑owning raw pointers/references only for observation.

---

## 2) Interfaces (I) — Make contracts explicit
**Goals**
- Make **ownership**, **lifetime**, and **nullability** explicit in function signatures and types.
- Keep interfaces **narrow** and **cohesive**; avoid hidden global state and “action at a distance.”

**Do**
- Prefer **value semantics** for small types and **`string_view`/`span`** for non‑owning views.
- Use **`const` correctness**; pass read‑only references (`const T&`) for large types.
- Use **strong types** (enums, wrappers) instead of primitive “flag soup.”
- State **preconditions** and **postconditions** with `Expects(cond)` / `Ensures(cond)` at module boundaries.
- Model **optional** results with `std::optional<T>`; model **sum types** with `std::variant`.

**Avoid**
- Overloaded booleans and ambiguous parameter packs; prefer named structs for clarity.
- Globals/singletons as implicit dependencies; prefer dependency injection via interfaces.

---

## 3) Functions (F) — Small, single‑purpose, explicit
**Do**
- Keep functions **short** and **single‑responsibility**; name them by intent.
- Prefer **`noexcept`** when a function cannot throw (or must not propagate) to simplify reasoning.
- Prefer **`constexpr`** when semantics allow; push checks/types to compile‑time.
- Return **rich results** (e.g., `optional`, `expected`‑like, or struct) instead of out‑params.

**Avoid**
- Output parameters; if unavoidable, document and prefer references with clear names.
- Catch‑all exception handling at leaf functions; establish strategy at the boundary.

---

## 4) Classes & Hierarchies (C) — Invariants first, rule of zero
**Do**
- Preserve a **class invariant**; have constructors establish it, and destructors never fail.
- Prefer **rule of zero** (no custom copy/move/dtor) by composing RAII members.
- Use **`final`** and **`override`** to clarify virtual overrides.
- Prefer **composition** over inheritance; keep hierarchies shallow and interface‑oriented.
- If you need a pure interface, use an abstract base with a **virtual destructor** and no data members.

**Avoid**
- Owning raw pointers as data members; store ownership in smart handles.
- Public data members (except for simple passive aggregates/`struct` for plain data).

---

## 5) Resource Management (R) — RAII everywhere
**Do**
- Express ownership via **`std::unique_ptr`** (exclusive) or **`std::shared_ptr`** (shared), with custom deleters as needed.
- Prefer **scoped objects** and **automatic storage**; allocate on the free store only when lifetime requires it.
- Use **STL containers** (`vector`, `string`, `array`) and **views** (`string_view`, `span`) over raw arrays.
- Centralize low‑level resource acquisition in **resource wrappers**; keep application code at the “no naked `new`” level.
- Use **`std::lock_guard` / `std::unique_lock`** for mutexes; prefer **RAII** for all OS resources (files, sockets, handles).

**Avoid**
- Manual `new`/`delete` outside of resource wrappers.  
- Non‑`const` globals; avoid hidden shared state.
- Owning raw pointers in APIs; denote non‑ownership with raw pointer/reference explicitly.

---

## 6) Error Handling (E) — Exceptions for errors, not control flow
**Strategy**
- Decide early: **exception‑based** or **no‑exceptions** build mode at module boundaries. Be consistent.
- Use exceptions to **signal failure to perform the function’s contract**. Keep normal code paths exception‑free.
- Keep objects in a **valid state** across throws; rely on RAII for cleanup.
- Mark functions **`noexcept`** only when they truly cannot throw.

**If exceptions are off**
- Use a consistent strategy: **return types that encode error + value** (e.g., struct or `expected`‑like) and **fail‑fast** where recovery is impossible.
- Simulate RAII for cleanup and prefer **small functions** to contain error paths.

**Do**
- Throw by value; catch by reference to base hierarchy.
- Log before failing fast in unrecoverable states, especially in services.

**Avoid**
- Using exceptions for “found”/“not found” or regular branching.
- Global error state (e.g., relying solely on `errno`) in modern code.

---

## 7) Expressions & Statements (ES) — Simplicity over cleverness
**Do**
- Prefer **initialization** over assignment; use brace initialization to avoid narrowing.
- Prefer **`auto`** when it improves readability and avoids repetition; keep types explicit when it clarifies intent.
- Use **range‑for** and STL algorithms; avoid manual index arithmetic where possible.

**Avoid**
- Long, complex expressions with subtle sequencing; break into named steps.
- C‑style casts; prefer `static_cast`/`const_cast`/`reinterpret_cast` explicitly and sparingly.

---

## 8) Constants & Immutability (Con)
**Do**
- Use `const`, `constexpr`, and **immutable views** by default.
- Prefer **`enum class`** over plain enums to avoid implicit conversions.
- Prefer **free functions** over macros; avoid preprocessor for logic.

---

## 9) Templates & Generic Programming (T)
**Do**
- Use **concepts** or constraints to clearly state template requirements.
- Prefer **`std::span`**, iterator pairs, and ranges‑style interfaces for generic code.
- Keep template code readable; don’t optimize prematurely.

**Avoid**
- Over‑generic designs with no concrete use cases; start from real call‑sites.

---

## 10) The Standard Library (SL)
**Do**
- Prefer **standard containers/algorithms** over hand‑rolled ones.
- Use **`std::string_view`** for read‑only text views and **`std::filesystem`** for paths.
- Prefer **`std::chrono`** types for time; avoid raw integers for durations.

---

## 11) Concurrency & Parallelism (CP)
**Do**
- **Avoid shared mutable state**; prefer message passing or immutable data where feasible.
- Guard all shared data with **RAII lock wrappers**; keep critical sections minimal.
- Use **thread‑safe constructs** (`std::atomic`, concurrency‑safe containers/patterns) where sharing is unavoidable.
- Prefer **`std::jthread`**, `std::async`, and higher‑level executors/tasks when available.
- Design for **cancellation** and **time‑bounded waits**.

**Avoid**
- Data races, ad‑hoc double‑checked locking, and manually managed thread lifetimes without clear ownership.

---

## 12) C‑style Code (CPL)
**Do**
- Replace C arrays with `std::array` / `std::vector`; replace `char*` strings with `std::string` / `string_view`.
- Replace varargs with variadic templates or standard facilities.
- Use `<c*>` headers (e.g., `<cstdlib>`) and modern facilities.

**Avoid**
- `malloc`/`free` for C++ objects; prefer `new`/`delete` only inside wrappers, or better, avoid them in favor of RAII handles.

---

## 13) Naming & Layout (NL) — Light guidance
- Use names to convey **ownership, units, and intent** (e.g., `Bytes`, `Seconds`, `Index` types).
- Be consistent within a project. Prefer **lower_snake_case** for functions and **UpperCamelCase** for types if your project lacks a style guide (adjust if one exists).
- Don’t encode ownership/nullability in names; use **types** to express those.

---

## 14) GSL (Guidelines Support Library)
**Prefer using**:
- `gsl::span<T>` for array/view parameters.
- `gsl::not_null<T*>` to state non‑nullable pointers.
- `gsl::owner<T*>` to mark raw ownership only inside low‑level wrappers.
- `Expects(cond)`, `Ensures(cond)` for checked contracts at boundaries.

**Notes**
- GSL is header‑only and intended to be zero‑overhead; use instrumentation modes for debug builds if available.

---

## 15) Modernization Strategy (Appendix‑style)
- Adopt rules incrementally: **wrap resources**, **replace raw arrays**, **remove naked `new`**, **add spans/views**, **clarify ownership**.
- Write **adapters** at the edges of legacy modules; don’t try to rewrite everything at once.
- Add tests around legacy seams before refactors; run sanitizers in CI.

---

## 16) Agent Auto‑Fix Playbook (suggested transformations)
1. **Ownership**: Replace owning `T*` members with `std::unique_ptr<T>`; add `= default`ed special members (rule of zero).
2. **Arrays & Buffers**: Convert raw array parameters `(T*, size_t)` to `gsl::span<T>`; use `std::vector`/`std::array` internally.
3. **Nullability**: Replace nullable references with `std::optional<T>` or `T*` + `not_null` as appropriate; remove ambiguous booleans by introducing strong types.
4. **Error Flow**: Replace control‑flow via exceptions with normal returns; conversely, replace error‑code plumbing with exceptions where policy allows.
5. **Casts**: Replace C‑style casts with explicit `static_cast` / `reinterpret_cast` only when justified.
6. **Concurrency**: Introduce RAII locks; replace shared mutable state with message queues or copies; add `std::atomic` where minimal sharing is required.
7. **Contracts**: Insert `Expects`/`Ensures` at module boundaries; add `[[nodiscard]]` to important return values.
8. **Chrono/FS**: Replace raw ints for time with `std::chrono` durations; replace ad‑hoc paths with `std::filesystem::path`.
9. **Initialization**: Switch to brace initialization to avoid narrowing; prefer `= default` / `= delete` for special members.
10. **Thread Lifetime**: Replace manual `std::thread` with `std::jthread` (if available) and cooperative cancellation.

---

## 17) Minimal Code Templates (ready to paste)

### Resource wrapper (RAII)
```cpp
class File {
public:
  explicit File(std::filesystem::path p) : f_(std::fopen(p.string().c_str(), "rb")) {
    if (!f_) throw std::runtime_error("open failed");
  }
  ~File() { if (f_) std::fclose(f_); }
  File(const File&) = delete;
  File& operator=(const File&) = delete;
  File(File&& other) noexcept : f_(std::exchange(other.f_, nullptr)) {}
  File& operator=(File&& other) noexcept {
    if (this != &other) { if (f_) std::fclose(f_); f_ = std::exchange(other.f_, nullptr); }
    return *this;
  }
  std::size_t read(gsl::span<std::byte> buf) noexcept { return std::fread(buf.data(), 1, buf.size(), f_); }
private:
  std::FILE* f_{}; // owner
};
```

### Span‑based interface
```cpp
void fill_buffer(gsl::span<std::byte> out);

std::vector<std::byte> data(4096);
fill_buffer(data);
```

### Contracts at boundaries
```cpp
int dot(gsl::span<const int> a, gsl::span<const int> b) {
  Expects(a.size() == b.size());
  long long acc = 0;
  for (size_t i = 0; i < a.size(); ++i) acc += 1LL * a[i] * b[i];
  Ensures(acc >= 0); // example postcondition
  return static_cast<int>(acc);
}
```

---

## 18) Project Checklist (quick pass before merge)
- [ ] No naked `new`/`delete` in application code.
- [ ] No owning raw pointers; ownership expressed via RAII handles.
- [ ] Public APIs make nullability/ownership explicit; spans for buffers.
- [ ] Exceptions used only for error signaling; policy is consistent (or a no‑exceptions strategy is applied consistently).
- [ ] Constructors establish invariants; destructors don’t fail; rule of zero preferred.
- [ ] No C‑style arrays/casts in new code; explicit casts are rare and justified.
- [ ] Concurrency primitives wrapped in RAII; no unguarded shared mutable state.
- [ ] Contracts (`Expects`/`Ensures`) or equivalent checks at module boundaries.
- [ ] Standard library used preferentially; chrono/filesystem in place of ad‑hoc types.
- [ ] clang-tidy and sanitizers clean in CI; warnings treated as errors in release branches.

---

## 19) Notes
- This guide is intentionally **opinionated for agents**: it selects defaults and auto‑fixes aligned with modern C++ best practices to maximize safety and maintainability.
- When interfacing with legacy modules, generate adapters at the boundary and confine exceptions/ownership decisions there.

---

*End of document.*
