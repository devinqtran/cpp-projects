#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <cctype>
#include "Token.h"

using namespace std;

class Scanner {
private:
    string input;
    int line = 1;

public:
    Scanner(const string& input) : input(input) { }

    Token scanToken() {
        // Hard-coded test values
        TokenType type = COMMA;
        string value = ",";
        int line = 4;
        
        // Check if white space
        while(!input.empty() && isspace(input.at(0))) {
            input = input.substr(1);
            
        }

        // Check for a comma
        if (!input.empty() && input.at(0) == ',') {
                input = input.substr(1);
                TokenType type = COMMA;
                string value = ",";
                return Token(type, value, line);
            }
        return Token(type, value, line);
    }

};