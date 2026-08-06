#include <iostream>
using namespace std;

class Animal
{
public:
    bool isLiving = true;
    std::string sound;

    void talk()
    {
        cout << sound << "\n";
    }
};

class Dog : public Animal
{
private:
public:
    Dog()
    {
        sound = "Woof";
    }

    std::string getSound()
    {
        return sound;
    }
};

class Cat : public Animal
{
private:
    std::string name;

public:
    Cat()
    {
        sound = "Meow";
    }
};

int main()
{
    Dog lucky;
    cout << std::boolalpha << lucky.isLiving << "\n";
    lucky.getSound();
    lucky.talk();

    Cat rascal;
    rascal.talk();
    cout << rascal.isLiving << "\n";

    return 0;
}