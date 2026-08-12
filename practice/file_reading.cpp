#include <iostream>
#include <fstream> // Needed for file streams like ifstream
#include <string>  // Needed for string variables

using namespace std;

int main()
{
    // 1. Create the input stream and attempt to open "data.txt"
    // Avoid unknown escape sequence by using \\ or /
    ifstream my_file("C:/Users/devin/OneDrive/Desktop/cpp-projects/practice/data.txt");

    // 2. Check if the stream successfully connected to the file
    if (!my_file.is_open())
    {
        cout << "Error: Could not open the file!" << endl;
        return 1; // Exit the program with an error code
    }

    string line;

    // 3. The safe reading loop
    // getline() grabs a line, puts it in our string, and returns the stream.
    // When there are no more lines, it fails and the loop stops.
    while (getline(my_file, line))
    {
        cout << line << endl; // Print the line to the console
    }

    // 4. Clean up
    my_file.close();

    return 0;
}