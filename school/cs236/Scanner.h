#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <cctype>
#include "Token.h"

using namespace std;

class Scanner
{
private:
    string input;
    int line = 1;

public:
    Scanner(const string &input) : input(input) {}

    Token scanToken()
    {
        // Skip any white space and track new lines
        while (!input.empty() && isspace(input.at(0)))
        {
            if (input.at(0) == '\n')
            {
                line++;
            }
            input = input.substr(1);
        }

        // Check for end of input
        if (input.empty())
        {
            return Token(END, "", line);
        }

        // c is the first character in the input string
        char c = input.at(0);

        // Case switch for handling symbols
        switch (c)
        {
        case ',':
            input = input.substr(1);
            return Token(COMMA, ",", line);
        case '.':
            input = input.substr(1);
            return Token(PERIOD, ".", line);
        case '?':
            input = input.substr(1);
            return Token(Q_MARK, "?", line);
        case '(':
            input = input.substr(1);
            return Token(LEFT_PAREN, "(", line);
        case ')':
            input = input.substr(1);
            return Token(RIGHT_PAREN, ")", line);
        case '*':
            input = input.substr(1);
            return Token(MULTIPLY, "*", line);
        case '+':
            input = input.substr(1);
            return Token(ADD, "+", line);
        case ':':
            if (input.size() >= 2 && input.at(1) == '-')
            {
                input = input.substr(2);
                return Token(COLON_DASH, ":-", line);
            }
            input = input.substr(1);
            return Token(COLON, ":", line);
        }

        // Check for all other options
        input = input.substr(1);
        return Token(UNDEFINED, string(1, c), line);
    }
};