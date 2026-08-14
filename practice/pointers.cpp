#include <iostream>
#include <vector>

int *pi;
char **cpp;              // pointer to char
int (*vp)[10];           // pointer to a vector of 10 ints
int (*fp)(char, char *); // pointer to a function

int strlen(char *p)
{
    int i = 0;
    while (*p++)
        i++;
    return i;
}

int strlen2(char *p)
{
    char *q = p; // new pointer q (stepper) set to same address as p (anchor)

    // while checks if that character is a 0 (null terminator)
    while (*q++)
        ;             // *q grabs character at current memory address q is pointing to, ++ post-increment after evaluation
    return q - p - 1; // q - p results in total steps or elements between, -1 because the last step was \0
}

int main()
{
    char c1 = 'a';
    char *p = &c1; // p holds the address of c1
    char c2 = *p;  // c2 = 'a'

    std::cout << c2 << "\n";

    std::cout << strlen(p);

    return 0;
}