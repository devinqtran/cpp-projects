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

        // Check for keywords and identifiers
        if (isalpha(c))
        {
            string word;
            while (!input.empty() && isalnum(input.at(0)))
            {
                word += input.at(0);
                input = input.substr(1);
            }

            // Check for the keywords
            if (word == "Schemes")
                return Token(SCHEMES, word, line);
            if (word == "Facts")
                return Token(FACTS, word, line);
            if (word == "Rules")
                return Token(RULES, word, line);
            if (word == "Queries")
                return Token(QUERIES, word, line);

            // Default to ID
            return Token(ID, word, line);
        }

        // Checking for strings
        if (c == '\'') // Single quotes
        {
            int startLine = line;
            string value = "'";
            input = input.substr(1); // Take the opening quote

            while (true)
            {
                if (input.empty())
                {
                    return Token(UNDEFINED, value, startLine);
                }

                char c_ = input.at(0);

                // Check for quotes next to eachother
                if (c_ == '\'')
                {
                    if (input.size() >= 2 && input.at(1) == '\'')
                    {
                        value += "''";
                        input = input.substr(2);
                        continue;
                    }

                    // Default closing quote
                    value += "'";
                    input = input.substr(1);
                    return Token(STRING, value, startLine);
                }

                if (c_ == '\n')
                {
                    line++;
                }

                // Add current char to value and consume char
                value += c_;
                input = input.substr(1);
            }
        }

        // Check for comments
        // Line comment # - consume through \nl
        // Block comment start #| end |#
        // Multiline comment
        if (c == '#')
        {
            int startLine = line;

            // Check for block comment start
            if (input.size() >= 2 && input.at(1) == '|')
            {
                string value = "#|";
                input = input.substr(2); // take first two characters #|

                // Looop until one of the cases is met, regular loop will just consume char and move on
                while (true)
                {
                    // Case: only opening #|
                    if (input.empty())
                    {
                        return Token(UNDEFINED, value, startLine); // never found "|#"
                    }

                    // Case: both sets |#
                    if (input.at(0) == '|' && input.size() >= 2 && input.at(1) == '#')
                    {
                        value += "|#";
                        input = input.substr(2);
                        return Token(COMMENT, value, startLine);
                    }

                    // New line
                    if (input.at(0) == '\n')
                    {
                        line++;
                    }
                    value += input.at(0);
                    input = input.substr(1);
                }
            }

            // Line comment
            string value = "#";
            input = input.substr(1);
            while (!input.empty() && input.at(0) != '\n')
            {
                value += input.at(0);
                input = input.substr(1);
            }
            return Token(COMMENT, value, startLine);
        }

        // Check for all other options
        input = input.substr(1);
        return Token(UNDEFINED, string(1, c), line);
    }

    // Method for tokenizing
    vector<Token> tokenize() {
        vector<Token> tokens;
        Token currentToken = scanToken();
        
        while (currentToken.getType() != END) {
            tokens.push_back(currentToken);
            currentToken = scanToken();
        }
        
        tokens.push_back(currentToken);
        
        return tokens;
    }
};