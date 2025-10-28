#include <cassert>  // for assert
#include <chrono>   // For timing utilities
#include <iostream>
#include <memory>       // For smart pointers
#include <type_traits>  // For std::is_lvalue_reference_v
#include <vector>

#include "week7.hpp"

using namespace std::chrono;

//==== default ====//
int main(){}

//====</1>====//
// int main() {

//   std::vector<std::vector<long long>> matrix;

//   // Create a large vector representing a row of sensor data
//   std::vector<long long> row(10'000'000);

//   auto start{high_resolution_clock::now()};  // Start timer

//   for (long long i{0}; i < 10'000'000; i++) {
//     row[i] = i;
//   }

//   // Copy this row to our matrix
//   matrix.push_back(row);  // This COPIES all 1 million integers!

//   auto end{high_resolution_clock::now()};  // End timer

//   // Compute elapsed time
//   auto duration_ms = duration_cast<milliseconds>(end - start).count();
//   auto duration_s = duration_cast<duration<double>>(end - start).count();

//   std::cout << "Loop and copy completed in " << duration_ms << " ms ("
//             << duration_s << " s)\n";
// }

// //====</2>====//
// int main() {

//   std::vector<std::vector<long long>> matrix;

//   // Create a large vector representing a row of sensor data
//   std::vector<long long> row(10'000'000);

//   auto start{high_resolution_clock::now()};  // Start timer

//   for (long long i{0}; i < 10'000'000; i++) {
//     row[i] = i;
//   }

//   // Copy this row to our matrix
//   matrix.push_back(std::move(row));  // This MOVES row into matrix

//   auto end{high_resolution_clock::now()};  // End timer

//   // Compute elapsed time
//   auto duration_ms = duration_cast<milliseconds>(end - start).count();
//   auto duration_s = duration_cast<duration<double>>(end - start).count();

//   std::cout << "Loop and copy completed in " << duration_ms << " ms ("
//             << duration_s << " s)\n";
// }

// //====</3>====//
// int main() {
//   int x{10 + 20};  // "10 + 20" is a prvalue
//   int y{x + 5};    // "x + 5" is a prvalue

//   42;       // Literal - prvalue
//   3.14159;  // Literal - prvalue
//   true;     // Literal - prvalue

//   std::vector<int>{1, 2, 3};  // Temporary object - prvalue
//   x + y;                      // Result of operation - prvalue
// }

// //==== rvalue references ====//
// int main() {
//   int&& rref{10 + 20};  // The result of 10+20 is stored in memory
//                         // and lives as long as rref exists
//   std::cout << rref << '\n';  // Output: 30
//   rref = 100;                 // We can even modify it!
//   std::cout << rref << '\n';  // Output: 100
// }

// //====</4>====//
// int main() {
//   int&& rref{10 + 20};
//   // rref is an lvalue even though its type is int&&
//   static_assert(std::is_lvalue_reference_v<decltype((rref))>);
//   std::cout << "rref is an lvalue reference: "
//             << std::boolalpha
//             << std::is_lvalue_reference_v<decltype((rref))> << '\n';
// }

// //==== unique_ptr exclusive ownership ====//
// int main() {
//   std::unique_ptr<int> u = std::make_unique<int>(10);
//   std::unique_ptr<int> v{u};  // Error
// }

// //====</5>====//
// int main() {
//   {
//     // Create managed resource on heap
//     auto u = std::make_unique<int>(10);
//     std::cout << *u << '\n';  // Output: 10 (dereference to access value)
//     *u = 20;                  // modify the managed resource
//     std::cout << *u << '\n';  // Output: 20
//     // std::cout << u << '\n';   // Error: no operator<< for unique_ptr
//   }  // u destructor automatically calls delete on managed resource
// }

// //====</6>====//
// int main() {
//   // Create managed resource on heap
//   auto u = std::make_unique<int>(10);
//   if (u) {  // check if u!=nullptr
//     std::cout << "Value at " << u.get() << " is " << *u << '\n';
//   }
//   //---------------------------------
//   // Create managed resource on heap
//   auto v = std::make_unique<int>(10);
//   int* raw_ptr{v.get()};  // get a copy of the raw pointer for observation
//   if (raw_ptr) {          // check if raw_ptr!=nullptr
//     std::cout << "Value at " << raw_ptr << " is " << *raw_ptr << '\n';
//   }
// }

// //====</7>====//
// int main() {
//   auto u = std::make_unique<int>(10);
//   auto ptr = u.release();  // transfer ownership to ptr

//   std::cout << *ptr << '\n';   // Output: 10
//   assert(u.get() == nullptr);  // u no longer owns the resource
//   assert(u == nullptr);        // implicit bool conversion check

//   delete ptr;  // Mandatory: prevent memory leak
// }

// //====</8>====//
// int main() {
//   auto u = std::make_unique<int>(10);
//   u.release();
// }

// //====</9>====//
// int main() {
//   auto u = std::make_unique<int>(42);
//   // Transfer ownership to raw pointer for legacy interface
//   int* ptr{u.release()};
//   // Verify ownership transfer
//   assert(u == nullptr);  // u no longer owns resource
//   // Pass to legacy system that expects raw pointer ownership
//   legacy_function(ptr);  // ptr now responsible for deletion
// }

// //====</10>====//
// int main() {
//   auto u1 = std::make_unique<int>(10);
//   int* ptr{u1.release()};
//   std::unique_ptr<int> u2(ptr);  // u2 assumes ownership
//   assert(u1 == nullptr);
// }

// //====</11>====//
// int main() {
//   auto u = std::make_unique<int>(10);
//   u.reset();                   // cleans up managed resource, set to nullptr
//   assert(u.get() == nullptr);  // verification: u is now null
// }

// //====</12>====//
// int main() {
//   auto u = std::make_unique<int>(10);
//   u.reset(new int(20));  // clean up old resource, manage new one
//   std::cout << *u << '\n';
// }

// //====</13>====//
// int main() {
//   auto u = std::make_unique<int>(10);
//   auto v = std::make_unique<int>(20);
//   u.swap(v);
//   std::cout << *u << '\n';
//   std::cout << *v << '\n';
// }

// //====</14>====//
// int main() {
//   auto u = std::make_unique<int>(10);
//   display(u);
// }

// //====</15>====//
// int main() {
//   auto u = std::make_unique<int>(10);
//   // Transfer ownership to function
//   display(std::move(u));  // u is now nullptr - ownership transferred
//   assert(u == nullptr);
// }

// //====</16>====//
// int main() {
//   // Create managed resource on heap
//   auto u = std::make_unique<int>(10);
//   std::cout << "u: " << u.get() << '\n';  // @1

//   // Transfer ownership using move constructor
//   auto v{std::move(u)};                   // u transfers ownership to v
//   std::cout << "v: " << v.get() << '\n';  // @1 (same address)
//   assert(u == nullptr);                   // u is now empty

//   // u can be reused for new resource management
//   u.reset(new int{20});
//   std::cout << u.get() << '\n';  // @2 (different address)
// }

// //====</17>====//
// int main() {
//   auto u = std::make_unique<int>(10);     // Create managed resource
//   std::cout << "*u: " << *u << '\n';      // 10
//   std::cout << "u: " << u.get() << '\n';  // @1
//   reseat_unique(u);  // u will be modified to point to new resource
//   std::cout << "*u: " << *u << '\n';      // 20
//   std::cout << "u: " << u.get() << '\n';  // @2
// }

// //====</18>====//
// int main() {
//   auto u{create_resource()};
//   std::cout << *u << '\n';  // 10
//   std::cout << &u << '\n';  // @1 (same address due to optimization)
// }

// //====</19>====//
// //TODO Test with the debugger
// int main() {
//   auto s1 = std::make_shared<int>(10);
//   auto s2{s1};
//   auto s3 = s2;
// }

// //====</20>====//
// int main() {
//   auto s1 = std::make_shared<int>(10);
//   std::cout << s1.use_count() << '\n';
//   auto s2{s1};
//   std::cout << s2.use_count() << '\n';
//   s1.reset();
//   std::cout << s1.use_count() << '\n';
//   s2.reset();
//   std::cout << s2.use_count() << '\n';
// }

// //====</21>====//
// int main() {
//   auto s1 = std::make_shared<int>(10);
//   std::cout << "A: " << s1.use_count() << '\n';  // A: ??

//   auto s2{s1};
//   std::cout << "B: " << s1.use_count() << ' ';   // B: ??
//   std::cout << "C: " << s2.use_count() << '\n';  // C: ??

//   auto s3 = s2;
//   std::cout << "D: " << s1.use_count() << ' ';   // D: ??
//   std::cout << "E: " << s2.use_count() << ' ';   // E: ??
//   std::cout << "F: " << s3.use_count() << '\n';  // F: ??

//   s1.reset();
//   std::cout << "G: " << s1.use_count() << ' ';   // G: ??
//   std::cout << "H: " << s2.use_count() << ' ';   // H: ??
//   std::cout << "I: " << s3.use_count() << '\n';  // I: ??

//   s1.swap(s2);
//   std::cout << "J: " << s1.use_count() << ' ';   // J: ??
//   std::cout << "K: " << s2.use_count() << ' ';   // K: ??
//   std::cout << "L: " << s3.use_count() << '\n';  // L: ??

//   s2.reset(new int(20));
//   std::cout << "M: " << s1.use_count() << ' ';   // M: ??
//   std::cout << "N: " << s2.use_count() << ' ';   // N: ??
//   std::cout << "O: " << s3.use_count() << '\n';  // O: ??

//   auto s4 = std::make_shared<int>(10);
//   s1.swap(s4);
//   std::cout << "P: " << s1.use_count() << ' ';   // P: ??
//   std::cout << "Q: " << s4.use_count() << '\n';  // Q: ??
// }

// //====</22>====//
// int main() {
//   auto original = std::make_shared<int>(10);
//   std::cout << original.use_count() << '\n';  // 1
//   sink_shared(original);                      // Pass by value creates copy
//   std::cout << original.use_count()
//             << '\n';  // 1 (copy destroyed after function)
// }

// //====</23>====//
// int main() {
//   auto original = std::make_shared<int>(10);
//   std::cout << original.use_count() << '\n';  // 1
//   reseat_shared(original);                    // Pass by reference
//   std::cout << original.use_count() << '\n';  // 1 (no copy made)
// }

// //====</24>====//
// int main() {
//   auto result{create_shared_resource()};
//   std::cout << &result << '\n';  // @1 (same address due to RVO)
// }

// //====</25>====//
// int main() {
//   auto s = std::make_shared<int>(10);
//   std::cout << s.use_count() << '\n';
//   // Create a weak_ptr from a shared_ptr
//   std::weak_ptr<int> w1{s};
//   std::cout << w1.use_count() << '\n';
//   // Create another weak_ptr from an existing weak_ptr
//   std::weak_ptr<int> w2{w1};
//   std::cout << w2.use_count() << '\n';
// }

// //====</26>====//
// int main() {
//   auto s = std::make_shared<int>(10);
//   // Create weak_ptr from shared_ptr
//   std::weak_ptr<int> w{s};

//   // std::cout << *w << '\n';       // Error: No operator*
//   // std::cout << w.get() << '\n';  // Error: No get() method
// }

// //====</27>====//
// int main() {
//   auto sp = std::make_shared<int>(42);  // s_count=1, w_count=1 (implicit)
//   std::cout << sp.use_count() << '\n';
//   std::weak_ptr<int> w1{sp};            // s_count=1, w_count=2
//   std::cout << w1.use_count() << '\n';
//   std::weak_ptr<int> w2{sp};            // s_count=1, w_count=3
//   std::cout << w2.use_count() << '\n';

//   sp.reset();  // s_count -> 0, object destroyed
//   // implicit w_count dropped → w_count becomes 2 (w1, w2)
//   std::cout << sp.use_count() << '\n';

//   std::cout << std::boolalpha << "expired? w1=" << w1.expired() << ", w2=" <<
//   w2.expired()
//             << '\n';  // both true

//   w1.reset();  // w_count -> 1
//   w2.reset();  // w_count -> 0, control block destroyed here
// }

// //====</28>====//
// int main() {
//   std::weak_ptr<int> weak;

//   {
//     auto shared = std::make_shared<int>(42);
//     weak = shared;  // weak observes shared

//     if (auto sp = weak.lock()) {
//       std::cout << "Value: " << *sp << '\n';
//     } else {
//       std::cout << "Object no longer exists.\n";
//     }
//   }  // shared destroyed here → object deleted

//   if (auto sp = weak.lock()) {
//     std::cout << "Value: " << *sp << '\n';
//   } else {
//     std::cout << "Object no longer exists.\n";
//   }
// }

// //====</29>====//
// int main() {
//   std::weak_ptr<int> weak_observer;
//   {
//     auto shared_resource = std::make_shared<int>(10);
//     weak_observer = shared_resource;  // weak_observer now observes the resource
//     if (weak_observer.expired())
//       std::cout << "Resource has been destroyed\n";
//     else
//       std::cout << "Resource is still valid\n";
//   }  // shared_resource destroyed, resource deallocated

//   if (weak_observer.expired())
//     std::cout << "Resource has been destroyed\n";
//   else
//     std::cout << "Resource is still valid\n";
// }
