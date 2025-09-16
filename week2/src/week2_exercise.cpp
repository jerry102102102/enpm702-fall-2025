#include <iostream>
#include <typeinfo>  // needed for typeid

int main() {
  //==============
  //======== Exercise #2
  //==============
    int a;
    int b = 3.2;
    int c(1.3);
    int d{3.5};
    std::cout << a << '\n';
    std::cout << b << '\n';
    std::cout << c << '\n';
    std::cout << d << '\n';

  //==============
  //======== Exercise #3
  //==============
  //   int a{3};
  //   int b{2};
  //   std::cout << "Type of result: " << typeid(a / b).name() << '\n';
  //   std::cout << "Type of result: " << typeid(a).name() << '\n';
  //   std::cout << "Type of result: " << typeid(b).name() << '\n';
  //   std::cout << "Value of result: " << a / b << '\n';

  //==============
  //======== Exercise #5
  //==============
  //   std::cout << "Enter a number: ";
  //   int user_input{};
  //   std::cin >> user_input;

  //   const int a;                  // Error 1: Fix this
  //   constexpr int b{user_input};  // Error 2: Fix this
  //   const int c{42};
  //   c = 50;  // Error 3: Fix this

  //   std::cout << a << " " << b << " " << c << '\n';

  //==============
  //======== Exercise #6
  //==============
  //   short s{10};
  //   int i{20};
  //   float f{3.5f};
  //   double d{2.7};

  //   // What type and value will these have?
  //   auto result1{s + i};  // Type: _____ Value: _____
  //   std::cout << "Type: " << typeid(result1).name() << ", Value: " << result1
  //             << '\n';

  //   auto result2{i * f};  // Type: _____ Value: _____
  //   std::cout << "Type: " << typeid(result2).name() << ", Value: " << result2
  //             << '\n';
  //   auto result3{f / d};  // Type: _____ Value: _____
  //   std::cout << "Type: " << typeid(result3).name() << ", Value: " << result3
  //             << '\n';
  //   auto result4{s + 5.0};  // Type: _____ Value: _____
  //   std::cout << "Type: " << typeid(result4).name() << ", Value: " << result4
  //             << '\n';

  //==============
  //======== Exercise #7
  //==============
//   int x{10};
//   std::cout << x << '\n';  // Output?

//   {
//     int y{20};
//     int x{30};
//     std::cout << x << '\n';  // Output?
//     std::cout << y << '\n';  // Output?
//   }

//   std::cout << x << '\n';  // Output?
//   std::cout << y << '\n';  // Output?
}