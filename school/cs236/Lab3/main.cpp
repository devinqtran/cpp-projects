#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "C:\Users\devin\OneDrive\Desktop\cpp-projects\school\cs236\Project1\Scanner.h"
#include "C:\Users\devin\OneDrive\Desktop\cpp-projects\school\cs236\Project2\Parser.h"
#include "Interpreter.h"
#include "Relation.h"
#include "Tuple.h"
#include "Scheme.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Please provide an input file." << endl;
        return 1;
    }

    // 1. Read the file into a single string
    ifstream file(argv[1]);
    stringstream buffer;
    buffer << file.rdbuf();
    string input = buffer.str();

    // 2. Initialize the Scanner
    Scanner scanner(input);
    vector<Token> tokens;

    // 3. Loop to get all tokens
    Token currentToken = scanner.scanToken();
    while (currentToken.getType() != END) {
        tokens.push_back(currentToken);
        currentToken = scanner.scanToken();
    }
    tokens.push_back(currentToken); // add END token

    // 4. Run the Parser
    Parser parser(tokens);
    parser.parse();
    
    // 5. Run the Interpreter Schemes test
    DatalogProgram program = parser.getProgram();
    Interpreter interpreter(program);
    interpreter.interpret();

    // print the database for testing
    // interpreter.getDatabase().printDatabase();

    return 0;
}