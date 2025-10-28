
#pragma once
#include <iostream>
#include <string>

// //====</1>// //====
// struct Point {
//   double x;
//   double y;
//   std::string label{"default"};  // C++11 default member initializer
// };

// //====TEMPLATE INSTATIATION====// //
// template <typename T>
// T multiply(T a, T b) {
//   return a * b;
// }

// //====</4a>====// //
// template <typename T>
// T add(T a, T b);  // Declaration only

// //====</4b>====// //
// template <typename T>
// T add(T a, T b) {
//   return a + b;
// }

// //====</5>====// //

// /**
//  * @brief Returns the greater of two values.
//  *
//  * @tparam T A totally ordered type (requires operator>).
//  * @param a First value.
//  * @param b Second value.
//  * @return The larger of \p a and \p b.
//  * @note Use explicit template arguments if deduction is ambiguous.
//  * @code
//  * auto m{max_value<int>(3, 4)};
//  * @endcode
//  */
// template <typename T>
// T max_value(T a, T b) {
//   return (a > b) ? a : b;
// }

// //====</6>====// //
// template <typename T, typename U>
// auto add_different(T a, U b) {
//   return a + b;  // deduce from operator+
// }

// //====</7>====// //
// template <typename T>
// void print_twice(T value) {
//   std::cout << value << " " << value << '\n';
// }

// //====</8>====// //
// template<typename T, typename U>
// void display_pair(T a, U b) {
//     std::cout << a << ", " << b << '\n';
// }

// //====</9>====// //
// template <typename T>
// T add(T a, T b) {
//   return a + b;
// }

// //====</10>====// //
// template <typename T>
// void modify(T& value) {
//   value *= 2;
// }

// //====</11>====// //
// template <typename T>
// void print(const T& value) {
//   std::cout << value << '\n';
// }

// //====</12>====// //
// template<typename T>
// void process(T value) {
//     std::cout << typeid(T).name() << '\n';
// }

// //====</17>====// //
// template <typename T>  // generic
// T get_max(T a, T b) {
//   return (a > b) ? a : b;
// }

// template<>
// std::string get_max<std::string>(std::string a, std::string b) {
//     std::cout << "Using string specialization!\n";
//     return (a.length() > b.length()) ? a : b;
// }

// //====</18>====// //
// template <typename T>
// void process(T value) {
//   std::cout << "Processing generic value: " << value << '\n';
// }

// template <>  // full specialization
// void process<bool>(bool value) {
//   std::cout << "Processing bool: " << (value ? "true" : "false") << '\n';
// }

// //====</19>====// //
// double average(double a, double b) {
//   return (a + b) / 2.0;
// }

// //====</36>====// //
// struct Counter {
//   int count = 0;  // 1. The State
//   // 2. The Overloaded Call Operator
//   // This is what makes it a functor.
//   void operator()() {
//     ++count;
//     std::cout << "Called " << count << " times.\n";
//   }
// };

// //====</37>====// //
// A functor that doubles a number
// struct Doubler {
//     int operator()(int x) const {
//         return x * 2;
//     }
// };

// //====</44>====// //
// struct Multiplier {
//     int factor;
//     Multiplier(int f) : factor(f) {}
//     int operator()(int x) const { return x * factor; }
// };


// plate <typename T>  // generic
// T get_max(T a, T b) {
//   return (a > b) ? a : b;
// }

// template<>
// std::string get_max<std::string>(std::string a, std::string b) {
//     std::cout << "Using string specialization!\n";
//     return (a.length() > b.length()) ? a : b;
// }