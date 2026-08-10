#include <iostream>

using namespace std;

// Create a ptr in cpp of type int, named ptr
// int *ptr; // Holds the address of something it is pointing to
// *ptr has the meaning "tell us value of thing that ptr is pointing to"

// int var = 7; // integer variable

// int foo = 21;

// ptr = &var; // ptr is assigned to the address of var
// *ptr        // would print 7, the dereferenced value of ptr

// Pointers can point to many things
// ptr = &foo;

// int &ref = var; // both var and ref would reference 7
// Pointers can move around, references stay in one spot

int main()
{
    cout << "Declaring a pointer of type integer int *ptr \n";
    int *ptr;

    cout << "This is what *ptr prints: " << *ptr << "\n";
    cout << "This is what ptr prints: " << ptr << "\n";

    cout << "-----------------------------------------\n";

    cout << "Declaring a variable of type integer int var = 7 \n";
    int var = 7;

    cout << "This is what var prints: " << var << "\n";
    cout << "This is what &var prints: " << &var << "\n";

    cout << "-----------------------------------------\n";

    cout << "Setting ptr to point to the address of var ptr = &var \n";
    ptr = &var;
    cout << "This is what ptr prints after assigning to point to address of var: " << ptr << "\n";
    cout << "This is what *ptr prints: " << *ptr << "\n";

    cout << "-----------------------------------------\n";

    cout << "Declaring a variable of the type integer foo = 21\n";
    int foo = 21;

    cout << "This is what foo prints: " << foo << "\n";
    cout << "This is what &foo prints: " << &foo << "\n";

    cout << "-----------------------------------------\n";

    cout << "Setting ptr to point to the address of foo ptr = &foo \n";
    ptr = &foo;

    cout << "This is what *ptr prints: " << *ptr << "\n";
    cout << "This is what ptr prints: " << ptr << "\n";

    cout << "-----------------------------------------\n";

    cout << "Setting the address of ref to var int &ref = var";
    int &ref = var;

    cout << "This is what &ref prints: " << &ref << "\n";
    cout << "This is what var prints: " << var << "\n";

    cout << "-----------------------------------------\n";

    cout << "Setting ptr to the address of foo ptr = &foo\n";
    ptr = &foo;
    cout << "This is what ptr prints after ptr = &foo: " << ptr << "\n";
    cout << "This is what *ptr prints after ptr = &foo: " << *ptr << "\n";

    cout << "-----------------------------------------\n";

    cout << "This is what var prints after &ref = var: " << var << "\n";
    cout << "This is what &var prints: " << &var << "\n";
    cout << "This is what &ref prints: " << &ref << "\n";

    return 0;
}
