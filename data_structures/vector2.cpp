#include <iostream>
#include <vector>

using namespace std;

class Vec : public vector<int>
{
public:
    Vec(int s) : vector<int>(s) {}
    Vec(const Vec &);
    ~Vec() {}

    // Operator overloading

    // vec1.operator=(vec2)
    void operator=(const Vec &); // if someone puts an = between two vec objects run copy assignment operator

    // overload *= operator to work with another vector (vec1 *= vec2)
    void operator*=(const Vec &); // multiply elements of one vector by the elements of another

    // overloads *= but for an integer(scalar)
    void operator*=(int); // allows for scaling a vector by a single number
};

int main()
{

    return 0;
}