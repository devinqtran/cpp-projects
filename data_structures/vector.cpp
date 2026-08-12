#include <iostream>

class vector
{
    int *v;
    int sz;

public:
    vector(int);
    ~vector();

    int size() { return sz; }
    void set_size(int);
    // return type int& means it will return an alias directly to the memory slot in the array
    int &operator[](int);             // operator overloading allows using [] on this custom object like an array
    int &elem(int i) { return v[i]; } // identical functionality to operator[] if someone uses my_vec.elem(2) = 10,
                                      // it will access v and grab integer at index i, then return reference
};

// Vector implementation allowing for specifying start and end indices

// create a new class named vec, copy everything from original vector class
class vec : public vector {
    // private member variables (lowest index, highest index)
    int low, high;

public:
    // Constructor - to create this object pass two numbers (vec my_years(2020, 2026))
    vec(int, int);

    // Redefining functions that already exist in parent class (Overloading)
    int& elem(int); // New logic bc index may not be 0
    int& operator[](int); // both return int& so you can say (my_years[2022] = 5;) directly change the data

};