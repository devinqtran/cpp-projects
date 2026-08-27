#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Scanner.h"
#include "Parser.h"
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

    try {
        // 4. Run the Parser
        Parser parser(tokens);
        parser.parse();
        
        // 5. Run the Interpreter
        DatalogProgram program = parser.getProgram();
        Interpreter interpreter(program);
        
        interpreter.interpret();

    } catch (const exception& e) {
        cout << "Exception: " << e.what() << endl;
    }

    return 0;
}