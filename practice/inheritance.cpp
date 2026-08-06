#include <iostream>
using namespace std;

class Base
{
public:
    int x = 0;
};

// Derived class using public mode only Derived can access x
class Derived : protected Base
{
public:
    void print()
    {
        cout << x << "\n";
    }
};

class Derived1 : public Derived
{
public:
    void print1()
    {
        cout << x << "\n";
    }
};

int main()
{

    Derived d;
    d.print();
    Base b;
    // cout << d.x << "\n";
    cout << b.x << "\n";

    Derived d1;
    d1.print();

    return 0;
}