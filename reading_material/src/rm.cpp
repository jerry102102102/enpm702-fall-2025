#include <iostream>

int some_function() { return 1; }

int main()
{
    //==============
    //======== 1
    //==============
    // if statement example
    std::cout << "Enter your age: ";
    unsigned short age{};
    std::cin >> age;
    if (age >= 18)
        std::cout << "You can vote!\n";

    // //==============
    // //======== 2
    // //==============
    // // Implicit block warning example
    // int a{2};
    // if (a > 0)
    //     std::cout << "a is positive\n";
    // a = -a; // this is always executed

    // // is equivalent to …
    // int a2{2};
    // if (a2 > 0)
    // {
    //     std::cout << "a is positive\n";
    // }
    // a2 = -a2; // this is always executed

    // // Did you want the following instead?
    // int a3{2};
    // if (a3 > 0)
    // {
    //     std::cout << "a is positive\n";
    //     a3 = -a3; // executed only if a is positive
    // }

    // //==============
    // //======== 3
    // //==============
    // // if-else statement example
    // int b{1};
    // if (b >= 0)
    //     std::cout << "b is positive\n"; // executed only if b>=0 is true
    // else
    //     std::cout << "b is negative\n"; // executed only if b<0 is true

    // //==============
    // //======== 4
    // //==============
    // // Conditional operator example 1 - CORRECTED
    // int x{1};
    // if (x % 2)
    //     std::cout << x << " is odd\n";  // CORRECTED: non-zero remainder means odd
    // else
    //     std::cout << x << " is even\n"; // CORRECTED: zero remainder means even

    // // Here is the same code using the conditional operator.
    // int x2{1};
    // std::cout << ((x2 % 2) ? "x is odd\n" : "x is even\n"); // CORRECTED

    // //==============
    // //======== 5
    // //==============
    // // Conditional operator example 2
    // constexpr int c{3};
    // constexpr int d{2};
    // constexpr int larger_value{c > d ? c : d};                    // initialize larger_value
    // std::cout << "The larger value is: " << larger_value << '\n'; // 3

    // //==============
    // //======== 6
    // //==============
    // // Conditional operator example 3 (compilation error)
    // /*
    // constexpr int x{3};
    // constexpr int y{2};

    // if (x > y)
    //     constexpr int larger_value{x};
    // else
    //     constexpr int larger_value{y};

    // std::cout << "The larger value is: " << larger_value << '\n';
    // // Error: larger_value will be out of scope
    // */

    // //==============
    // //======== 7
    // //==============
    // // else-if statement example
    // int e{1};
    // if (e > 0)
    //     std::cout << "Value is positive\n"; // if e > 0 is true
    // else if (e < 0)
    //     std::cout << "Value is negative\n"; // if e < 0 is true
    // else
    //     std::cout << "Value is zero\n"; // if e > 0 AND e < 0 are false

    // //==============
    // //======== 8
    // //==============
    // // Implicit conversion example
    // if (2)                                   // converted to true
    //     std::cout << "Condition1 is true\n"; // executed
    // if (0.01)                                // converted to true
    //     std::cout << "Condition2 is true\n"; // executed
    // if (0)                                   // converted to false
    //     std::cout << "Condition3 is true\n"; // not executed
    // if (0.0)                                 // converted to false
    //     std::cout << "Condition4 is true\n"; // not executed

    // //==============
    // //======== 9
    // //==============
    // // Dangling else example
    // int f{5};
    // int g{10};

    // if (f > 0)
    //     if (g > 0)
    //         std::cout << "f and g are positive\n";
    //     else
    //         std::cout << "f is non-positive\n"; // This is misleading - actually means g is non-positive

    // //==============
    // //======== 10
    // //==============
    // // Dangling else clarification
    // int f2{5};
    // int g2{10};
    // if (f2 > 0)
    // {
    //     if (g2 > 0)
    //     {
    //         std::cout << "f and g are positive\n";
    //     }
    //     else
    //     {
    //         std::cout << "g is non-positive\n"; // CORRECTED: should say g, not f
    //     }
    // }

    // //==============
    // //======== 11
    // //==============
    // // switch default label example
    // int h{3};
    // switch (h)
    // {
    // case 1: // no match
    //     std::cout << "one\n";
    //     break;
    // case 2: // no match
    //     std::cout << "two\n";
    //     break;
    // default: // executed since no cases matched
    //     std::cout << "unknown\n";
    //     break;
    // }

    // //==============
    // //======== 12
    // //==============
    // // switch break statement example
    // int i{1};
    // switch (i)
    // {
    // case 1:
    //     std::cout << "one\n";
    //     break;
    // case 2:
    //     std::cout << "two\n";
    //     break;
    // default:
    //     std::cout << "unknown\n";
    //     break;
    // }
    // std::cout << "switch has terminated\n";

    // //==============
    // //======== 13
    // //==============
    // // Fallthrough example
    // int choice{1};
    // switch (choice)
    // {
    // case 1:                           // we have a match here
    //     std::cout << "Choice is 1\n"; // this is executed
    // case 2:
    //     std::cout << "Choice is 2\n"; // I want to execute this as well
    //     break;
    // default:
    //     std::cout << "Unknown choice\n";
    // }

    // //==============
    // //======== 14
    // //==============
    // // [[fallthrough]] attribute example
    // int choice2{1};
    // switch (choice2)
    // {
    // case 1:                           // we have a match here
    //     std::cout << "Choice is 1\n"; // this is executed
    //     [[fallthrough]];              // compiler will not raise a warning
    // case 2:
    //     std::cout << "Choice is 2\n"; // I want to execute this as well
    //     break;
    // default:
    //     std::cout << "Unknown choice\n";
    // }

    // //==============
    // //======== 15
    // //==============
    // // Sequential case labels example
    // int j{2};
    // std::cout << "Do you want to double the value of variable j? (y/n) ";
    // char input{};
    // std::cin >> input;
    // switch (input)
    // {
    // case 'y':
    // case 'Y':
    //     j *= 2; // double the number
    //     break;
    // case 'n':
    // case 'N':
    //     break; // not doing anything
    // default:
    //     std::cout << "unknown input\n";
    //     break;
    // }
    // std::cout << "Value of j: " << j << '\n';

    // //==============
    // //======== 16
    // //==============
    // // Jump to case label example (error and fix)
    // // FIXED VERSION:
    // int k{1};
    // switch (k)
    // {
    // case 1:
    // {
    //     int i{10};
    //     std::cout << i << '\n';
    //     break;
    // }
    // case 2:
    // {
    //     int j{20};
    //     std::cout << j << '\n';
    //     break;
    // }
    // }

    // //==============
    // //======== 17
    // //==============
    // // Initialization in if statement (C++17)
    // if (int l{some_function()}; l > 0)
    // {
    //     std::cout << "l is positive: " << l << '\n';
    // }
    // else
    // {
    //     std::cout << "l is non-positive: " << l << '\n';
    // }

    // //==============
    // //======== 18
    // //==============
    // // Initialization in switch statement (C++17)
    // switch (int m = some_function(); m)
    // {
    // case 1:
    //     std::cout << "m is 1\n";
    //     break;
    // case 2:
    //     std::cout << "m is 2\n";
    //     break;
    // default:
    //     std::cout << "m is something else: " << m << '\n';
    //     break;
    // }

    // //==============
    // //======== 19
    // //==============
    // // while statement example
    // int counter{1};
    // while (counter <= 10)
    // {
    //     std::cout << counter << ' ';
    //     ++counter;
    // }
    // std::cout << '\n';

    // //==============
    // //======== 20
    // //==============
    // // Infinite loop example
    // while (true)
    // { // infinite loop
    //     std::cout << "Loop again (y/n)? ";
    //     char input2{};
    //     std::cin >> input2;
    //     if (input2 == 'n')
    //     {
    //         std::cout << "Stopping the loop\n";
    //         break;
    //     }
    // }

    // //==============
    // //======== 21
    // //==============
    // // Nested loop example
    // // outer loop loops 5 times
    // int outer{1};
    // while (outer <= 5)
    // {
    //     int inner{1};
    //     // inner loop loops 10 times
    //     while (inner <= 10)
    //     {
    //         std::cout << outer * inner << ' ';
    //         ++inner;
    //     }
    //     // print a newline at the end of each row
    //     std::cout << '\n';
    //     ++outer;
    // }

    // //==============
    // //======== 22
    // //==============
    // // do-while statement example
    // // selection must be declared outside of the do/while so we can use it later
    // int selection{};
    // do
    // {
    //     std::cout << "Which approach do you want to use (1 or 2)?:\n";
    //     std::cout << "1) Breadth-first search\n";
    //     std::cout << "2) Depth-first search\n";
    //     std::cout << "Please select an approach: ";
    //     std::cin >> selection;
    // } while (selection != 1 && selection != 2);

    // switch (selection)
    // {
    // case 1:
    //     std::cout << "You selected: Breadth-first\n";
    //     break;
    // case 2:
    //     std::cout << "You selected: Depth-first search\n";
    //     break;
    // }

    // //==============
    // //======== 23
    // //==============
    // // for statement basic example
    // for (int n{0}; n < 10; ++n)
    //     std::cout << n << " ";
    // std::cout << '\n';

    // //==============
    // //======== 24
    // //==============
    // // Omitted expressions in for loop
    // int count{0};
    // for (; count < 10;)
    // { // no init_statement or end_expression
    //     std::cout << count << ' ';
    //     ++count;
    // }
    // std::cout << '\n';
    // std::cout << "The final value of count is: " << count << '\n';

    // //==============
    // //======== 25
    // //==============
    // // for statement examples
    // // decrement is also possible. Also note the use of auto keyword.
    // for (auto i{9}; i >= 0; --i)
    //     std::cout << i << " ";
    // std::cout << "\n---------\n";

    // // although not often used, multiple counters are also possible
    // for (auto i{0}, j{0}; i < 3; ++i, --j)
    //     std::cout << i << ' ' << j << '\n';
    // std::cout << "---------\n";

    // // nested loops
    // for (auto i{1}; i < 6; ++i)
    // {
    //     for (auto j{1}; j < 11; ++j)
    //     {
    //         std::cout << i * j << ' ';
    //     }
    //     std::cout << '\n';
    // }

    // //==============
    // //======== 26
    // //==============
    // // break with for loop
    // // iterate 10 times
    // for (auto i{0}; i < 10; ++i)
    // {
    //     // exit loop if i is 3
    //     if (i == 3)
    //         break; // exit the loop now

    //     // otherwise print i
    //     std::cout << i << ' ';
    // }

    // // execution will continue here after the break
    // std::cout << "\nResuming program execution\n";

    // //==============
    // //======== 27
    // //==============
    // // break with while loop
    // while (true)
    // { // infinite loop
    //     std::cout << "Loop again (y/n)? ";
    //     char input3{};
    //     std::cin >> input3;
    //     if (input3 == 'n')
    //         break;
    // }
    // // execution will continue here after the break
    // std::cout << "Resuming program execution\n";

    // //==============
    // //======== 28
    // //==============
    // // break with do-while loop
    // int num{};
    // do
    // {
    //     std::cout << "Enter a number (-1 to exit): ";
    //     std::cin >> num;
    //     if (num == -1)
    //     {
    //         break; // Exit the loop when -1 is entered
    //     }
    //     std::cout << "You entered: " << num << '\n';
    // } while (true); // Infinite loop, but we have a break condition inside
    // std::cout << "You chose to exit.\n";

    // //==============
    // //======== 29
    // //==============
    // // continue with do-while
    // int o{0};
    // do
    // {
    //     if (o == 2)
    //     {
    //         o++;      // increment o
    //         continue; // skip everything else in the body of the do statement
    //     }
    //     std::cout << "Value of o: " << o << '\n';
    //     o++;
    // } while (o < 5);

    // //==============
    // //======== 30
    // //==============
    // // continue with for loop
    // for (auto i{0}; i < 10; ++i)
    // {
    //     // if the number is divisible by 3, skip this iteration
    //     if ((i % 3) == 0)
    //         continue; // go to next iteration

    //     // If the number is not divisible by 3, print it
    //     std::cout << i << ' ';
    // }
    // std::cout << '\n';

    // //==============
    // //======== 31
    // //==============
    // // continue with while loop
    // auto count2{1};
    // while (count2 < 11)
    // {
    //     if ((count2 % 3) == 0)
    //     {
    //         ++count2;  // infinite loop if we omit this line
    //         continue; // go to next iteration
    //     }

    //     // If the number is not divisible by 3, keep going
    //     std::cout << count2 << ' ';
    //     ++count2;
    // }

    // //==============
    // //======== 32
    // //==============
    // // Unary operators example
    // int p{5};
    // int q{-3};
    // std::cout << +p << '\n'; // 5
    // std::cout << -p << '\n'; // -5
    // std::cout << +q << '\n'; // -3
    // std::cout << -q << '\n'; // 3

    // //==============
    // //======== 33
    // //==============
    // // Division operator example
    // std::cout << 4 / 3 << '\n';     // 1
    // std::cout << 4.0 / 3 << '\n';   // 1.33333
    // std::cout << 4 / 3.0 << '\n';   // 1.33333
    // std::cout << 4.0 / 3.0 << '\n'; // 1.33333

    // int r{3};
    // int s{2};
    // std::cout << r / s << '\n';                      // 1
    // std::cout << static_cast<double>(r) / s << '\n'; // 1.5

    // //==============
    // //======== 34
    // //==============
    // // Compound assignment operators example
    // int t{4};
    // t = t + 3;              // add 3 to existing value of t. t = 4 + 3 = 7
    // t = t % 3;              // put the remainder of t % 3 in t. t = 7 % 3 = 1
    // std::cout << t << '\n'; // 1

    // // Better version:
    // int u{4};
    // u += 3;                 // add 3 to existing value of u. u = 4 + 3 = 7
    // u %= 3;                 // put the remainder of u % 3 in u. u = 7 % 3 = 1
    // std::cout << u << '\n'; // 1

    // //==============
    // //======== 35
    // //==============
    // // Prefix and postfix increment/decrement
    // // Prefix increment/decrement
    // int v{2};
    // int w{++v};                                     // increment v first then initialize w
    // int x3{--v};                                    // decrement v first then initialize x3
    // std::cout << v << ' ' << w << ' ' << x3 << '\n'; // 2 3 2

    // // Postfix increment/decrement
    // int y2{2};
    // int z{y2++};                                     // initialize z and then increment y2
    // int aa{y2--};                                    // initialize aa and then decrement y2
    // std::cout << y2 << ' ' << z << ' ' << aa << '\n'; // 2 2 3

    // //==============
    // //======== 36
    // //==============
    // // Comma operator example
    // int bb{1};
    // int cc{2};
    // auto dd{(++bb, ++cc)};                             // increment bb, increment cc, return cc
    // std::cout << bb << ' ' << cc << ' ' << dd << '\n'; // 2 3 3

    // //==============
    // //======== 37
    // //==============
    // // Better version without comma operator
    // int ee{1};
    // int ff{2};
    // ++ee;                                            // increment ee
    // auto gg{++ff};                                    // increment ff and use its incremented value to initialize gg
    // std::cout << ee << ' ' << ff << ' ' << gg << '\n'; // 2 3 3

    // //==============
    // //======== 38
    // //==============
    // // Relational operators example
    // std::cout << "Enter two integers: ";
    // int hh{};
    // int ii{};
    // std::cin >> hh >> ii;

    // if (hh == ii)
    //     std::cout << hh << " equals " << ii << '\n';
    // if (hh != ii)
    //     std::cout << hh << " does not equal " << ii << '\n';
    // if (hh > ii)
    //     std::cout << hh << " is greater than " << ii << '\n';
    // if (hh < ii)
    //     std::cout << hh << " is less than " << ii << '\n';
    // if (hh >= ii)
    //     std::cout << hh << " is greater than or equal to " << ii << '\n';
    // if (hh <= ii)
    //     std::cout << hh << " is less than or equal to " << ii << '\n';

    // //==============
    // //======== 39
    // //==============
    // // Boolean comparison best practice
    // // Bad practice:
    // bool jj{true};
    // if (jj == true)
    // {
    //     std::cout << std::boolalpha << jj << '\n'; // true
    // }

    // // Better practice:
    // bool kk{true};
    // if (kk)
    // {
    //     std::cout << std::boolalpha << kk << '\n'; // true
    // }

    // //==============
    // //======== 40
    // //==============
    // // Logical NOT example
    // int ll{2};
    // int mm{4};
    // if (!(ll > mm))
    // {
    //     std::cout << mm << " is greater than " << ll << '\n';
    // }

    // //==============
    // //======== 41
    // //==============
    // // Logical NOT precedence warning
    // int nn{2};
    // int oo{4};
    // if (!nn > oo)
    // { // we removed the parentheses
    //     std::cout << oo << " is greater than " << nn << '\n';
    // }
    // // This becomes if ((!nn) > oo) which is if (0 > 4) = false

    // //==============
    // //======== 42
    // //==============
    // // Logical OR example
    // int pp{2};
    // if (pp == 1 || pp == 2 || pp == 4)
    // {
    //     std::cout << "pp is 1, 2, or 4\n";
    // }

    // //==============
    // //======== 43
    // //==============
    // // Logical AND example
    // int qq{2};
    // if (qq > 0 && qq < 6 && qq != 3)
    // {
    //     std::cout << "qq is between 1 and 5 and is not 3\n";
    // }

}