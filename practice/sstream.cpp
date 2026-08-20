#include <iostream>
#include <sstream> // string stream
#include <string>

using namespace std;

int main() {
    // string stream is used to parse and format strings
    // basically iostream but instead of input/oputput with console, you have strings

    int a = 50;
    int b = 100;
    int result = a + b;
    string display;

    // display = a + " + " + b + " = " + result; // cannot concatenate an integer 

    // display = to_string(a) + " + " + to_string(b) + " = " + to_string(result); // use to_string() to convert each integer to a string

    // string stream - import <sstream> - similar syntax to <iostream> - "<<" ">>"

    // create a stringstream called ss
    stringstream ss;
    cout << "stringstream output: \n";
    ss << a << " + " << b << " = " << result << "\n";
    ss << a << " * " << b << " = " << a*b << "\n"; // second equation

    // streams separate input by spaces
    getline(ss, display); // gets everything until endline
    cout << display << endl;

    display = ss.str(); // this gets everything inside stringstream, converts it to a string, and assigns it to display variable
    cout << display << endl;

    ss.str("Devin"); // replaces stringstream contents with "Devin"
    display = ss.str();
    cout << display << endl;

    ss.clear(); // clears anything within the stream
    display = ss.str();
    cout << display << endl;


    

    
}