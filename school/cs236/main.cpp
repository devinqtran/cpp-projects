#include <iostream>
#include "Token.h"
#include "Scanner.h"
#include <fstream>

// argv[1] == filepath passed on cmd line
int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    cout << "Usage: " << argv[0] << " <input file>" << "\n";
  }

  ifstream file(argv[1]);
  if (!file.is_open())
  {
    cout << "Could not open file: " << argv[1] << "\n";
    return 1;
  }

  // Create stringstream called buffer
  stringstream buffer;

  // Read entire file into stringstream without looping
  buffer << file.rdbuf();

  // Convert that buffer to a string for input into scanner
  string contents = buffer.str();
  file.close();

  // New scanner s using the file contents converted into a string
  Scanner s = Scanner(contents);

  int count = 0;
  Token t = s.scanToken();
  count++;

  while (t.getType() != END)
  {
    cout << t.toString() << "\n";
    t = s.scanToken();
    count++;
  }

  cout << t.toString() << "\n";

  cout << "Total Tokens = " << count << "\n";
}