// shared_ptr.cpp
// std::shared_ptr is a smart pointer in C++ that retains shared ownership of a dynamically allocated object through a pointer
// multiple shared_ptr instances can point to the same object (shared_ptr<GameSession> player1_, shared_ptr<GameSession> player2_)
// 1. A pointer to the managed object
// 2. A pointer to a control block: contains reference count
// copying increments the reference count
// destroying or resetting a shared_ptr decrements a reference count
// after count reaches 0 the object is deleted

#include <iostream>
#include <memory> // Required header for shared_ptr

int main()
{
    // 1. Preferred initialization using std::make_shared
    std::shared_ptr<int> ptr1 = std::make_shared<int>(42);

    // 2. Sharing ownership (increments reference count)
    std::shared_ptr<int> ptr2 = ptr1;

    // Check the reference count (prints 2)
    std::cout << "Reference Count: " << ptr1.use_count() << "\n";

    // Accessing the underlying value
    std::cout << "Value: " << *ptr1 << "\n";
    std::cout << "Accessing value with other shared ptr *ptr2: " << *ptr2 << "\n";

    // 3. Releasing ownership
    ptr1.reset();

    // ptr2 still keeps the object alive (prints 1)
    std::cout << "Reference Count after reset: " << ptr2.use_count() << "\n";

    return 0;
} // When ptr2 goes out of scope, memory is automatically freed.

/*
    Common Member Functions:
    use_count() returns the current number of shared_ptr instances managing the object
    get() returns the underlying raw pointer (use with caution)
    reset() releases ownership; if it was the last owner deletes the object (shared game session, end deletes)
    unique() checks if use_count() == 1
*/