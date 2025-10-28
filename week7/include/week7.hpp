/**
 * @brief Simulating a legacy function which takes a raw pointer
 *
 * @param ptr Pointer to an integer
 */
void legacy_function(int* ptr);

/**
 * @brief Display the value of the resource pointed by @p v
 *
 * @param v Unique pointer
 */
void display(std::unique_ptr<int> v);

/**
 * @brief Function to demonstrate how to reseat a unique pointer
 *
 * @param v Unique pointer to be reseated
 */
void reseat_unique(std::unique_ptr<int>& v);

/**
 * @brief Create a resource object and return it
 *
 * @note This function is used to show NRVO is used when a unique pointer is
 * returned by value
 * @return std::unique_ptr<int>
 */
std::unique_ptr<int> create_resource();

/**
 * @brief Demonstrates how to sink a shared pointer
 * 
 * @param ptr Shared pointer passed by value
 */
void sink_shared(std::shared_ptr<int> ptr);

/**
 * @brief Demonstrates how to reseat a shared pointer
 * 
 * @param ptr Shared pointer passed by reference
 */
void reseat_shared(std::shared_ptr<int>& ptr);

/**
 * @brief Create a shared resource object
 * 
 * @return std::shared_ptr<int> 
 */
std::shared_ptr<int> create_shared_resource();