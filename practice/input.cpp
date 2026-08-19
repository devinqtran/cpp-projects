#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

using namespace std;

int main()
{
    cout << "Current working directory: " << filesystem::current_path() << "\n";

    // 1. Create an input file stream and open the file
    ifstream file("C:\\Users\\devin\\OneDrive\\Desktop\\cpp-projects\\practice\\input.txt"); // C:\Users\devin\OneDrive\Desktop\cpp-projects\practice\input.txt --- use \\ to escape backslashes

    // Create a second output file in current directory
    // ofstream file2("output.txt");

    ofstream file2("C:\\Users\\devin\\OneDrive\\Desktop\\cpp-projects\\practice\\output.txt"); // Send the output to a specific directory using absolute path C:\Users\devin\OneDrive\Desktop\cpp-projects\practice

    // 2. Check to see if the file opened successfully
    if (!file.is_open())
    {
        cerr << "Error: could not open the file!" << "\n";
        return 1; // Exit with error code
    }

    // Check if second file is open
    if (!file2.is_open())
    {
        cerr << "Error: output file is not open!" << "\n";
        return 1;
    }

    string line;

    // 3. Read the file line by line until end
    while (getline(file, line))
    {
        cout << "Read: " << line << "\n";
        file2 << line << endl;
    }

    // 4. Close the file
    file.close();

    // Close file2
    file2.close();

    return 0;
}