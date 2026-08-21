#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "..//Project1//Token.h"
#include "..\\Project1\\Scanner.h"
#include "Parser.h"

using namespace std;

// C:\Users\devin\OneDrive\Desktop\cpp-projects\school\cs236\Project2\test.txt

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    
    string fileName = argv[1];

    ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open file " << fileName << endl;
        return 1;
    }
    
    stringstream buffer;
    buffer << inputFile.rdbuf();
    string fileContents = buffer.str();

    Scanner scanner(fileContents);

    vector<Token> tokens; 
    Token t = scanner.scanToken();
    tokens.push_back(t);

    while(t.getType() != END) {
      t = scanner.scanToken();
      tokens.push_back(t);
    }

    Parser parser(tokens);
    parser.parse();

    return 0;
}