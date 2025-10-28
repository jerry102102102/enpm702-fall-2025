#include <iostream>
#include <memory>

void legacy_function(int* ptr) {
  if (ptr) {
    std::cout << "Processing: " << *ptr << '\n';
    delete ptr;  // Legacy code handles cleanup
  }
}

void display(std::unique_ptr<int> v) {
  // Implicit: std::unique_ptr<int> v{u};
  std::cout << *v << '\n';
}

void reseat_unique(
    std::unique_ptr<int>& v) {  // Pass by reference to modify original
  v.reset(new int(20));         // Destroy current resource, create new one
}

std::unique_ptr<int> create_resource() {
  auto v = std::make_unique<int>(10);
  std::cout << *v << '\n';  // 10
  std::cout << &v << '\n';  // @1 (address of local variable)
  return v;                 // Ownership transferred to caller
}

void sink_shared(std::shared_ptr<int> ptr) { // Copy constructor increments ref count
  std::cout << ptr.use_count() << '\n';     // 2 (original + copy)
}

void reseat_shared(std::shared_ptr<int>& ptr) { // Pass by reference - no copy
  std::cout << ptr.use_count() << '\n';     // 1 (same instance, no increment)
  // Could modify ptr here: ptr.reset(std::make_shared<int>(20));
}

std::shared_ptr<int> create_shared_resource() { 
  auto local_ptr = std::make_shared<int>(10);
  std::cout << &local_ptr << '\n';   // @1 (local variable address)
  return local_ptr; // RVO: no copy, direct construction in caller's context
}