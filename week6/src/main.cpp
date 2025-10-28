/**
 * @file week5.cpp
 * @author Zeid Kootbally (zeidk@umd.edu)
 * @brief Code snippets for lecture 6 on Functions (Advanced Topics)
 * @version 1.0
 * @date 2025-10-19
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <string>
#include <tuple>    // Required for std::tuple
#include <utility>  // For std::pair
#include <vector>

#include "week6.hpp"

// //====</2>// //====
// Point get_start_point() {
//   return {1.0, 2.0};
// }

// int get_value() {
//   return 42;
// }

// double calculate(double a, double b) {
//   return a * b;
// }

// constexpr int square(int x) {
//   return x * x;
// }

// int add(int a, int b) {
//   return a + b;
// }

// void might_throw(){};
// void never_throw() noexcept{};

// // Will NOT be noexcept
// void demo1() noexcept(noexcept(might_throw())) {
//   might_throw();  // Might throw
// }

// // WILL be noexcept
// void demo2() noexcept(noexcept(never_throw())) {
//   never_throw();  // Never throws
// }

// //====</33>====// //
// int multiply(int a, int b) {
//   return a * b;
// }
// int add(int a, int b) {
//   return a + b;
// }

// //====</35>====// //

// // This function takes a callback: void (*operation)(int)
// void process_list(int* arr, int size, void (*operation)(int)) {
//   for (int i{0}; i < size; ++i) {
//     operation(arr[i]);  // "Calling back" the operation
//   }
// }

// void print_number(int n) {
//   std::cout << "Value: " << n << '\n';
// }
// void double_number(int n) {
//   std::cout << "Double: " << n * 2 << '\n';
// }

// //====</44>====// //
// int double_value(int a) {
//   return a * 2;
// }

// [[nodiscard]] int compute_total(int i) {
//   return i;
// }

int main() {
  // std::string s;
  
  // compute_total(5);
  // //====</1>// //====
  // // Aggregate Initialization
  // Point p1 = {10.0, 20.0, "center"};  // Initializes x, y, label
  // Point p2 = {10.0, 20.0};  // Initializes x, y. label uses its default.

  // std::cout << p1.label << '\n';  // "center"
  // std::cout << p2.label << '\n';  // "default"

  // //====</2>// //====
  //   Point p = get_start_point();
  //   auto [x, y, label] = p;  // Magic!

  //   // Variables x, y, and label are created and populated
  //   std::cout << "X: " << x << ", Y: " << y << ", Label: " << label << '\n';

  // //====</3>// //====
  //   Point p = {10.0, 20.0};
  //   auto& [x_ref, y_ref, label_ref] = p;
  //   x_ref = 100.0;  // This modifies p.x

  //   std::cout << p.x << '\n';  // Prints 100.0

  // //====TEMPLATE INSTATIATION====// //
  // int result1{multiply(3, 4)};         // instantiates multiply<int>
  // double result2{multiply(2.6, 4.0)};  // instantiates multiply<double>
  // int result3{multiply(5, 6)};         // reuses multiply<int> (no new code)

  // std::cout << result1 << '\n';
  // std::cout << result2 << '\n';
  // std::cout << result3 << '\n';

  // //====</4a>====// //
  //   add(3, 4);  // Linker error!
  // undefined reference to `int add<int>(int, int)'

  // //====</4b>====// //
  //   std::cout << add(3, 4) << '\n';  // Works!
  //                                    // Compiler sees definition,
  //                                    // instantiates add<int>

  // //====</6>====// //
  //   int r1{add_different(3, 4)};       // int
  //   double r2{add_different(3, 4.5)};  // double
  //   double r3{add_different(3.5, 4)};  // double
  //   std::cout << r1 << " " << r2 << " " << r3 << '\n';

  // //====</7>====// //
  //   print_twice(10);       // T deduced as int
  //   print_twice<int>(10);  // explicitly T = int (same result)

  // //====</8>====// //
  //   display_pair<int>(5, 3.14);  // T fixed to int, U deduced as double

  // //====</9>====// //
  //   int result{add(3, 5)};  // deduces T = int
  //   std::cout << result << '\n';

  // //====</10>====// //
  //   int x{10};
  //   modify(x);  // T deduced as int; x becomes 20
  //   std::cout << x << '\n';

  // //====</11>====// //
  //   int x{42};
  //   print(x);  // T deduced as int

  //   const int y{99};
  //   print(y);  // T deduced as int (const is applied by the parameter type)

  // //====</12>====// //
  //   short s{42};
  //   process(s);       // T is short
  //   process<int>(s);  // force T = int (converts before call)

  // //====</17>====// //
  // int max_int{get_max(3, 5)};                                // generic
  // version std::string max_str{get_max<std::string>("hi", "hello")};  //
  // specialization std::cout << "max_int = " << max_int << '\n'; std::cout <<
  // "max_str = " << max_str << '\n';

  // //====</18>====// //
  // process(42);    // generic
  // process(true);  // specialized

  // //====</19>====// //
  // int x{42};
  // decltype(x) y{10};                        // y has same type as x (int)
  // decltype(average(1.0, 2.0)) result{0.0};  // deduces double
  // std::cout << typeid(y).name() << '\n';
  // std::cout << typeid(result).name() << '\n';

  // //====</20>====// //

  // int n{10};
  // int& ref{n};
  // const int c{5};

  // decltype(n) a{0};    // int
  // decltype(ref) b{n};  // int&   (reference preserved)
  // decltype(c) d{7};    // const int (const preserved)
  // decltype((n)) e{n};  // int&   (parentheses → lvalue expression)

  // //====</21>====// //
  // int x{10};

  // // decltype with identifiers (no parentheses)
  // decltype(x) a{0};  // int       (x's declared type)

  // // decltype with expressions (parentheses or operations)
  // decltype((x)) b{x};    // int&      (x is an lvalue expression)
  // decltype(x + 0) c{0};  // int       (x + 0 is a prvalue)
  // decltype(*(&x)) d{x};  // int&      (*(&x) is an lvalue)

  // //====</22>====// //
  // int arr[5]{1, 2, 3, 4, 5};
  // const int c{100};

  // decltype(arr[0]) v1{arr[1]};  // int&       (arr[0] is lvalue)
  // decltype(arr[0] + 1) v2{0};   // int        (arithmetic → prvalue)
  // decltype(c) v3{50};           // const int  (const preserved)
  // decltype((c)) v4{c};          // const int& (lvalue expression)

  // decltype(get_value()) v5{0};  // int (function call → prvalue)

  // //====</23>====// //
  // int x{10};
  // int y{20};

  // // Declare a variable with the same type as an expression
  // decltype(x + y) sum{x + y};  // sum is int

  // // With function calls
  // decltype(calculate(2.0, 3.0)) result{calculate(2.5, 4.0)};  // double

  // //====</26>====// //
  // constexpr int n{square(5)};  // evaluated at compile time
  // int m{7};
  // int result = square(m);  // evaluated at runtime

  // //====</27>====// //
  // // Record start time
  // auto start = std::chrono::high_resolution_clock::now();

  // // Called in a loop...
  // int total{0};
  // for (int i{0}; i < 1000000; ++i) {
  //   total = add(total, i);  // A million function calls!
  // }
  // // Record end time
  // auto end = std::chrono::high_resolution_clock::now();

  // // Compute elapsed time
  // std::chrono::duration<double, std::milli> duration_ms = end - start;

  // std::cout << "Total: " << total << '\n';
  // std::cout << "Execution time: " << duration_ms.count() << " ms\n";

  // //====</28>====// //

  // bool check1{noexcept(never_throw())};  // true
  // std::cout << check1 << '\n';
  // bool check2{noexcept(might_throw())};  // false
  // std::cout << check2 << '\n';
  // bool check3{noexcept(1 + 2)};  // true
  // std::cout << check3 << '\n';

  // //====</29>====// //
  // bool check1{noexcept(demo1())};  // false
  // std::cout << check1 << '\n';
  // bool check2{noexcept(demo2())};  // true
  // std::cout << check2 << '\n';

  // //====</33>====// //
  // // Declare a function pointer
  //   int (*func_ptr)(int, int);
  //   // Initialize it (the & is optional)
  //   func_ptr = &multiply; // or func_ptr = multiply ;
  //   // It's a variable, so it can be changed
  //   func_ptr = add;

  // //====</34>====// //
  // int (*func_ptr)(int, int){&multiply};

  // Call using explicit dereference
  // int result1{(*func_ptr)(5, 10)};  // result1 is 50
  // std::cout << "Result 1: " << result1 << '\n';

  // // Change what it points to
  // func_ptr = &add;  // of func_ptr = add;

  // // Call using implicit dereference
  // int result2{func_ptr(5, 10)};  // result2 is 15
  // std::cout << "Result 2: " << result2 << '\n';

  // //====</35>====// //
  // constexpr size_t array_size{3};
  // int my_list[array_size] = {1, 2, 3};
  // std::cout << "--- Printing ---\n";
  // process_list(my_list, array_size, print_number);

  // std::cout << "--- Doubling ---\n";
  // process_list(my_list, array_size, double_number);

  // //====</36>====// //
  // Counter my_counter;  // Create an instance of our functor

  // // Call the object as if it's a function
  // my_counter();  // Output: Called 1 times.
  // my_counter();  // Output: Called 2 times.

  // // We can still access its state directly
  // std::cout << "Final count: " << my_counter.count << '\n';  // Output: 2

  // //====</37>====// //
  // std::vector<int> numbers{1, 2, 3, 4, 5};
  // std::vector<int> result(numbers.size());

  // // Apply the functor to each element
  // std::transform(numbers.begin(), numbers.end(), result.begin(), Doubler{});

  // std::cout << "After transform (doubled): ";
  // for (int n : result)
  //   std::cout << n << ' ';
  // std::cout << '\n';

  // //====</38>====// //
  // std::vector<int> numbers = {5, 2, 8, 3, 1};

  // // Use a lambda for custom sorting
  // std::sort(numbers.begin(), numbers.end(), [](int a, int b) {
  //   return a > b;  // Sort in descending order
  // });

  // for (int n : numbers) {
  //   std::cout << n << " ";
  // }
  // // Output: 8 5 3 2 1
  // std::cout << '\n';

  // //====</39>====// //
  // int x{10};
  // int y{20};

  // // Captures x by value (a copy) and y by reference (the original)
  // auto my_lambda = [x, &y]() {
  //   std::cout << "x = " << x << '\n'; // x is 10
  //   // x = 15; // ERROR! x is const (captured by value)
  //   y = 30;  // OK! y is a reference
  // };

  // my_lambda();
  // std::cout << y << '\n'; // Output: 30

  // //====</40>====// //
  // // No parameters
  // [] { std::cout << "Hello!\n"; }();

  // // // Single parameter
  // [](int x) { std::cout << x << '\n'; }(3);

  // // // Multiple parameters
  
  // auto var = [](int a, int b) { return a + b; };
  // std::cout << var(2,3) << '\n';;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  // //====</41>====// //

  // int counter{0};

  // auto my_counter = [counter]() mutable {
  //   counter++;  // Modifies the lambda's internal copy
  //   return counter;
  // };

  // std::cout << my_counter() << '\n';  // Output: 1
  // std::cout << my_counter() << '\n';  // Output: 2
  // std::cout << counter << '\n';       // Output: 0 (original is unchanged)

  // //====</44>====// //
  // // A std::function that needs an "int(int)" signature
  // std::function<int(int)> operation;
  // // 1. Store a lambda
  // operation = [](int x) { return x + 10; };
  // std::cout << operation(5) << '\n';  // Output: 15
  // // 2. Store a functor
  // Multiplier times_5(5);
  // operation = times_5;
  // std::cout << operation(5) << '\n';  // Output: 25
  // // 3. Store a (compatible) free function
  // operation = double_value;           // assign the function itself
  // std::cout << operation(5) << '\n';  // Output: 10
}
