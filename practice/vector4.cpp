#include <iostream>
#include <vector>

using namespace std;

// mult-dimensional array
char v[2][5] = {
    'a', 'b', 'c', 'd', 'e',
    '0', '1', '2', '3', '4'};

char alpha[] = {"abcdefghijklmnopqrstuvwxyz"};
char *p = alpha; // Character pointer p pointing to alpha's first character
// Can also be written char* p = &alpha[0]
char ch; // Declare character ch

int main()
{

    // Modify character located at v[1][4]
    v[1][4] = '0';

    // Nested loop for printing each element in the multi-dimensional vector
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << "v[" << i << "][" << j << "]=" << v[i][j] << "\n";
        }
    }

    // Print the 11th letter of alphabet and onwards (does not stop until \0) by using p + 10
    cout << p + 10 << "\n";

    // Dereference the pointer to print just the letter 'k'
    cout << *(p + 10) << "\n";

    // Print the alphabet
    while (ch = *p++)
    { // while p is pointing at a character, do this...
        cout << ch << "\n";
    }
}
