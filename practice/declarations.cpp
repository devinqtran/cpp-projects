#include <iostream>

using namespace std;

// declare global variable x
int x;

int a = 1; // declare a globally

void f() {
    int b = 1;
    static int c = 1;
    cout << " a = " << a++
         << " b = " << b++
         << " c = " << c++ << "\n";
}

int main()
{
    // hide global x
    int x = 1;

    // scope resolution operator to assign to global x
    ::x = 2;

    const char *name = "Bjarne"; // pointer called name, pointing to the first letter of string literal "Bjarne"

    // A user defined type 'struct', this is a definition because iot defines layout of the complex type
    struct complex
    {
        float re, im;
    }; // compiler now knows a complex object takes up two floats (float re, im)

    // a variable named cvar of type complex
    complex cvar; // definition because compiler will carve out enough memory for cvar (two floats)

    // a function named sqrt is the entity (pure declaration)
    extern complex sqrt(complex); // extern means that this function is defined externally/in some other file

    extern int error_number;

    // declaring that 'point' is now a valid synonym for the 'complex' struct can be written "using point = complex;"
    typedef complex point;

    // a function named real that receives a pointer to an object of the complex type
    //float real(complex * p) { return p->re; }; // returns the float re from the object

    // a constant variable
    const double pi = 3.141592653897932385;

    // forward declaration (struct user exists but not saying what is inside of it)
    struct user; // allows for creating a pointer to a user prior to defining it

    // Compiler will print until \0 which is hidden in the text "Bjarne\0"
    cout << name << "\n";

    while (a < 4) f();

    // declare multiple in one line
    int l, m, a, o;

    void f();
    void* pv; // pointer to an object of unknown type


    return 0;
}