#include <iostream>
#include <vector>

using namespace std;

// User-Defined class

// Wrapper to hide user-defined class from user
template <typename T>
class VectorWrapper
{
private:
    std::vector<T> vec_;

public:
    // Constructor
    VectorWrapper() {}

    // Destructor
    ~VectorWrapper() {}

    // Method for adding an element of type T to the vector allows you to check if elements meet your criteria
    void addElement(const T &element)
    {
        vec_.push_back(element);
    }

    // Method for returning the size of the vector
    size_t getSize() const
    {
        return vec_.size();
    }

    // Method for printing elements of vector
    void print() const
    {
        for (const auto &element : vec_)
        {
            std::cout << element << " ";
        }
        std::cout << "\n";
    }
};

int main()
{
    // Instantiate new VectorWrapper intVectorWrapper storing integers
    VectorWrapper<int> intVectorWrapper;

    // Add elements to the vector
    intVectorWrapper.addElement(10);
    intVectorWrapper.addElement(20);
    intVectorWrapper.addElement(30);

    std::cout << "Size of Vector: " << intVectorWrapper.getSize() << "\n";
    intVectorWrapper.print();

    return 0;
}