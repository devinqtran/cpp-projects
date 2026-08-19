#include <iostream>
#include <fstream>

using namespace std;

// Update main to accept command-line arguments
int main(int argc, char *argv[])
{
    // Check if the user provided an output path
    if (argc < 2)
    {
        cerr << "Usage: ./my_program <output_file_path>\n";
        return 1;
    }

    // argv[1] contains the path you typed in the terminal
    string outputPath = argv[1];
    ofstream file2(outputPath);

    if (!file2.is_open())
    {
        cerr << "Error: could not open output file at " << outputPath << "\n";
        return 1;
    }

    file2 << "Writing to a custom location!" << endl;
    file2.close();

    return 0;
}