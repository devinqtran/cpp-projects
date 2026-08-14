#include <iostream>
#include <vector>

int* pi; 
char** cpp; // pointer to char
int (*vp)[10]; // pointer to a vector of 10 ints
int (*fp)(char, char*); // pointer to a function


int main () {
    char c1 = 'a';
    char* p = &c1; // p holds the address of c1
    char c2 = *p; // c2 = 'a'

    std::cout << c2 << "\n";
    return 0;

}