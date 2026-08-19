#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    cout << "You provided " << argc << " total arguments.\n\n";

    // Loop through all arguments
    for (int i = 0; i < argc; ++i)
    {
        // Convert the char* to a std::string for easier comparisons
        string arg = argv[i];

        cout << "argv[" << i << "] : " << arg << "\n";

        // Example of handling a specific flag
        if (arg == "--verbose")
        {
            cout << "  -> Verbose mode activated!\n";
        }
    }

    return 0;
}