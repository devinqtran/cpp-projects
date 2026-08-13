#include <iostream>
#include <vector>

using namespace std;

// Vector is a template, you have to tell it what it holds
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

    // standalone function that overrides the + operator and allows for Vec c = a + b
    Vec operator+(const Vec& a, const Vec& b) { // returns a brand new Vec not a reference, creates a new sum
        int s = a.size(); // check size of a
        if (s != b.size()) error("Bad vector size for +"); // guard to ensure both vectors have same number of elements
        Vec sum(s); // new container sum, initialized to be same size as the inputs
        for (int i=0; i < s; i++)
            sum.elem(i) = a.elem(i) + b.elem(i);
        return sum;
    }
};

int main()
{

    return 0;
}