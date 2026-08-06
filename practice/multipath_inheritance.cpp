#include <iostream>
using namespace std;

template <typename T>
void dataMemberSummary()
{
}

class Human
{
public:
    void breathing()
    {
        cout << "I am breathing\n";
    }
};

// virtual prevents multiple Human data members
class Youtuber : public virtual Human
{
};

// Virtual keyword solves diamond problem allowing virtual inheritance (only one Human data member)
class Developer : public virtual Human
{
};

class Devin : public Youtuber, public Developer
{
private:
};

int main()
{
    Youtuber y;
    Developer dv;

    Devin d;
    d.breathing();

    return 0;
}