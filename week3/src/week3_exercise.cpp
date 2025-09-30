/**
 * @file week3_exercise.cpp
 * @author Zeid Kootbally (zeidk@umd.edu)
 * @brief Code snippets for exercises on normal pointers
 * @version 1.0
 * @date 2025-09-15
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <iomanip>
#include <iostream>
#include <typeinfo>  // needed for typeid

int main() {
  //======== 1
  // int a{10};
  // int *p{&a};

  // Modify the value of a through p
  // *p = 20;

  // std::cout << a << '\n';  // 20
  // std::cout << *p << '\n'; // 20

  // //======== 2-1
  // int a{10};
  // int *p{&a};

  // *p *= 2;

  // std::cout << a << '\n';
  // std::cout << *p << '\n';

  // //======== 2-2
  // int a{2};
  // int *p{&a};
  // int **q{&p};
  // int ***r{&q};

  // std::cout << *p << '\n';
  // std::cout << **q << '\n';
  // std::cout << ***r << '\n';

  // //======== 3
  int a{5};
  int b{5};

  int *p1{&a}; // p1 points to a
  int *p2{&b}; // p2 points to b
  int *p3{&a}; // p3 points to a

  std::cout << std::boolalpha; // print bools as true/false
  std::cout << (p1 == p2) << '\n';
  std::cout << (p1 == p3) << '\n';

  // //======== 4
  // int a{10};
  // int b{20};

  // int *p1{&a};
  // int *p2{&b};
  // int *p3{&a};

  // std::cout << std::boolalpha; // print bools as true/false
  // std::cout << (*p1 == *p2) << '\n';
  // std::cout << (*p1 == *p3) << '\n';
  // std::cout << (*p1 > *p2) << '\n';
  // std::cout << (*p1 >= *p2) << '\n';
  // std::cout << (*p1 < *p2) << '\n';
  // std::cout << (*p1 <= *p2) << '\n';
  // std::cout << (*p1 != *p2) << '\n';

  // //======== 5
  // int a{10};
  // int b{20};

  // int *p1{&a};
  // int *p2{&b};
  // int *p3{&a};

  // // write your code here

  // //======== 6
  int *p1{new int{2}};
  int *p2{p1};

  delete p1;
  p1 = nullptr;

  delete p2; // UB

  // //======== 7
  int *p1{new int(10)};
  int *p2{new int(20)};
  int &ref{*p1};

  ref = *p2;
  *p2 = 30;
  p1 = new int(40);
  delete p2;
  *p1 = *p2;
  int *p3{p2};
  ref = 50;
  delete p3;
}