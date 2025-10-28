/**
 * @file week5.cpp
 * @author Zeid Kootbally (zeidk@umd.edu)
 * @brief Code snippets for lecture 5 on Functions (Basic Topics)
 * @version 1.0
 * @date 2025-10-07
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <iostream>

#include <string>
#include <vector>
#include <tuple>   // Required for std::tuple
#include <utility> // For std::pair


// //==================
// /*      </1>      */
// //==================

// //==================
// /*      </2>      */
// //==================
// void print_hello()
// {
//     print_world(); // ERROR!
//     // Compiler has not seen
//     // print_world() yet.
// }

// void print_world() { /* ... */ }

// void prompt_user()
// {
//     std::cout << "Enter a number: ";
//     int num{};
//     std::cin >> num;

//     print_number(num); // ERROR!
// }

// void print_number(int n)
// {
//     if (n <= 0)
//         prompt_user(); // ERROR!
// }

// //==================
// /*      </4>      */
// //==================
// void print_number(int number)
// {
//     if (number < 0)
//     {
//         std::cout << "Error: Negative numbers not allowed.\n";
//         return; // Exit the function immediately
//     }
//     std::cout << "The number is: " << number << "\n";
// }

// //==================
// /*      </5>      */
// //==================
// int calculate_sum(int a, int b)
// {
//     int result{a + b};
//     return result; // Send the value of 'result' back
// }

// //==================
// /*      </6>      */
// //==================
// int truncate_double()
// {
//     double value{99.99};
//     return value; // The double 99.99 is converted to the int 99
// }

// //==================
// /*      </7>      */
// //==================
// // This function returns both a bool and a string
// std::pair<bool, std::string> get_user_data()
// {
//     // ... logic to get data ...
//     bool success{true};
//     std::string name{"Zayd"};
//     return {success, name};
// }

// //==================
// /*      </8>      */
// //==================
// // This function returns three values: status code, success flag, and content.
// std::tuple<int, bool, std::string> parse_http_response() {
//     // ... imagine parsing a network response ...
//     int status_code{200};
//     bool is_success{true};
//     std::string response_body {"{\"user\":\"Zayd\"}"};

//     return {status_code, is_success, response_body};
// }
// //==================
// /*      </9>      */
// //==================
// // Define a struct to hold the related data
// struct UserQueryResult
// {
//     bool found;
//     std::string user_name;
// };

// // The function now returns our custom struct
// UserQueryResult find_user()
// {
//     // ... logic to find a user in a database ...
//     return {true, "Zayd"}; // C++ aggregate initialization
// }

// //==================
// /*     </10>      */
// //==================
// // The compiler looks at `a + b` and sees that int + double = double.
// // It deduces that the return type of this function must be `double`.
// auto add(int a, double b)
// {
//     return a + b;
// }
// //==================
// /*     </11>      */
// //==================
// void add_ten(int x)
// {
//     // int x{a};
//     x += 10; // Modifies the copy
// }

// //==================
// /*     </12>      */
// //==================
// void add_ten(int &x)
// {
//     // int &x{a}
//     x += 10; // Modifies the original 'a'
// }

// //==================
// /*     </13>      */
// //==================
// void print_vector(const std::vector<int> &v)
// {
//     // We get the efficiency of pass-by-reference without the risk.
//     for (const int &item : v)
//     {
//         std::cout << item << " ";
//     }
//     // v.push_back(100); // COMPILER ERROR: v is const!
// }
// //==================
// /*     </14>      */
// //==================
// void add_ten(int *p)
// {
//     if (p != nullptr)
//     {
//         *p += 10; // Modifies original 'a'
//     }
// }
// //==================
// /*     </15>      */
// //==================
// std::vector<int> generate_data()
// {
//     std::vector<int> local_data;
//     local_data.reserve(100);
//     // ... operations on local_data ...
//     for (int i = 0; i < 100; ++i)
//     {
//         local_data.push_back(i);
//     }
//     // Returning a named object.
//     return local_data;
// }
// //==================
// /*     </16>      */
// //==================
// // This function returns a reference to an element in the vector
// int &get_element(std::vector<int> &vec, size_t index)
// {
//     return vec.at(index);
// }

// //==================
// /*     </17>      */
// //==================
// // This function returns a pointer to the first element found, or nullptr.
// int *find_value(std::vector<int> &vec, int value)
// {
//     for (int &element : vec)
//     {
//         if (element == value)
//         {
//             return &element; // Return the address of the element
//         }
//     }
//     return nullptr; // Return nullptr if nothing was found
// }

// //===============================
// /*     </static variable>      */
// //===============================
// void static_counter()
// {
//     static int count{0}; // Created ONCE
//     count++;
//     // Prints 1, then 2
//     std::cout << count << '\n';
// }

// //==================
// /*     </18>      */
// //==================
// int add(int a, int b) { return a + b; }
// int add(int a, float b) { return a + b; }
// int add(int a, double b) { return a + b; }

// //==================
// /*     </19>      */
// //==================
// // Function with default parameters
// void print_config(int id, bool logging = false, const std::string &mode = "auto")
// {
//     std::cout << "ID: " << id << ", Logging: " << std::boolalpha
//               << logging << ", Mode: " << mode << '\n';
// }

// //==================
// /*     </20>      */
// //==================
// void f(int &x, int y, int z)
// {
//     x += y + z;
// }

// int g(int a, int b)
// {
//     int result{};
//     result = a + b;
//     f(result, a, b);
//     return result;
// }

// //==================
// /*     </21>      */
// //==================
// long long factorial(int n)
// {
//     // Base Case: Stops the recursion
//     if (n <= 1)
//     {
//         return 1;
//     }
//     // Recursive Step
//     return n * factorial(n - 1);
// }

int main(int argc, char* argv[])
{
    //==================
    /*     Exercise   */
    //==================

    //==================
    /*   Definition   */
    //==================
    // std::cout << add_numbers(3, 5) << '\n';

    //==================
    /*      </1>      */
    //==================

    // //==================
    // /*      </2>      */
    // //==================
    // print_hello();
    // prompt_user();

    // //==================
    // /*      </3>      */
    // //==================
    // print_hello();
    // std::cout << "Exit main\n";

    // //==================
    // /*      </4>      */
    // //==================
    // print_number(10); // Prints "The number is: 10"
    // print_number(-5); // Prints error and returns

    // //==================
    // /*      </5>      */
    // //==================
    // // The returned value is used
    // // to initialize the 'sum' variable.
    // int sum{calculate_sum(5, 3)};

    // std::cout << sum << '\n'; // 8

    // //==================
    // /*      </6>      */
    // //==================
    // int truncated{truncate_double()};
    // std::cout << truncated << '\n'; // Prints 99

    // //==================
    // /*      </7>      */
    // //==================
    // // The returned pair is automatically unpacked
    // // into two new variables: 'success' and 'user_name'.
    // auto [success, user_name] = get_user_data();

    // if (success)
    // {
    //     std::cout << "Welcome, " << user_name << "!\n";
    // }
    // //==================
    // /*      </8>      */
    // //==================
    // // Structured bindings work perfectly with std::tuple,
    // // unpacking the elements in the order they are defined.
    // auto [code, success, body] = parse_http_response();

    // if (success)
    // {
    //     std::cout << "Response OK (Code " << code << "): " << body << '\n';
    // }
    // //==================
    // /*      </9>      */
    // //==================
    // // Structured bindings work seamlessly with structs.
    // // The members are unpacked in the order they are defined.
    // auto [user_found, name] = find_user();

    // if (user_found)
    // {
    //     std::cout << "User found: " << name << "!\n";
    // }

    // //==================
    // /*     </10>      */
    // //==================
    // // 'result' will correctly be of type 'double'.
    // auto result{add(5, 3.14)};
    // std::cout << result << '\n';

    // //==================
    // /*     </11>      */
    // //==================
    // int a{5};
    // add_ten(a);             // A copy of 'a' is sent
    // std::cout << a << '\n'; // 'a' is still 5

    // //==================
    // /*     </12>      */
    // //==================
    // int a{5};
    // add_ten(a);             // 'a' itself is shared
    // std::cout << a << '\n'; // 'a' is now 15

    // //==================
    // /*     </13>      */
    // //==================
    // std::vector<int> num_vect{1, 2, 3};
    // print_vector(num_vect); // No expensive copy is made.
    // //==================
    // /*     </14>      */
    // //==================
    // int a{5};
    // add_ten(&a); // Pass the address of 'a'
    // // 'a' is now 15
    // std::cout << a << '\n';
    // //==================
    // /*     </15>      */
    // //==================
    // NRVO may construct local_data
    // directly inside `my_data`.
    // auto my_data{generate_data()};
    // //==================
    // /*     </16>      */
    // //==================
    // std::vector<int> my_vec = {10, 20, 30};
    // // get_element returns a reference to my_vec[1], not a copy of 20.
    // get_element(my_vec, 1) = 99; // We are modifying the original vector directly!
    // std::cout << my_vec[1] << '\n';// my_vec is now {10, 99, 30}

    // //==================
    // /*     </17>      */
    // //==================
    // std::vector<int> my_vec = {10, 20, 30};
    // int *ptr{find_value(my_vec, 20)};

    // // ALWAYS check a returned pointer before using it!
    // if (ptr != nullptr)
    // {
    //     *ptr = 99; // Modify the original vector via the pointer
    // }
    // // my_vec is now {10, 99, 30}

    // //===============================
    // /*     </static variable>      */
    // //===============================
    // static_counter(); // count becomes 1
    // static_counter(); // count becomes 2

    // //==================
    // /*     </18>      */
    // //==================
    // std::cout << add(2, 3) << '\n';       // ???
    // std::cout << add(2.5, 3) << '\n';     // ???
    // std::cout << add('h', false) << '\n'; // ???
    // std::cout << add("hello", 3) << '\n'; // ???

    // //==================
    // /*     </19>      */
    // //==================
    // print_config(1, true, "manual"); // ???
    // print_config(2, true);           // ???
    // print_config(3);                 // ???
    // print_config();                  // ???

    // //==================
    // /*     </20>      */
    // //==================
    // int x{10};
    // int y{20};
    // int z{};
    // z = g(x, y);
    // std::cout << z << '\n';

    // //==================
    // /*     </21>      */
    // //==================
    // long long result{factorial(4)};
    // std::cout << result << '\n';

    // //==================
    // /*     </22>      */
    // //==================
    // std::cout << "Number of arguments provided: " << argc << '\n';

    // for (int i = 0; i < argc; ++i)
    // {
    //     std::cout << "Argument " << i << ": " << argv[i] << '\n';
    // }
}