#include <iostream>
#include <string>

using namespace std;

int main () {
    string str = "Devin";
    string& alias = str;

    cout << alias << "\n";

    return 0;
}