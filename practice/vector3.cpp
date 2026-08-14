#include <iostream>
#include <vector>
#include <cstring> // 1. Include the standard library for strlen

// Returns a single char from an integer ASCII code
char chr(int ascii_code) {
    return static_cast<char>(ascii_code);
}

char alpha[] = "abcdefghijklmnopqrstuvwxyz";

int main () {
    float v[3]; 
    int a[2][5]; 
    char* vpc[32]; 

    int sz = strlen(alpha);
    for (int i = 0; i < sz; i++) {
        char ch = alpha[i];
        
        // 3. Fixed the stream manipulators and added integer casting
        std::cout << "'" << chr(ch) << "'"
             << " = " << ch
             << " = 0" << std::oct << static_cast<int>(ch)
             << " = 0x" << std::hex << static_cast<int>(ch) 
             << std::dec << "\n"; // Reset to decimal format
    }

    return 0;
}