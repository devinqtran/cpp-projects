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
    size_t pos = 0; // Tracks our current position in the string
    int line = 1;

    // Helper methods to make traversal clean and safe
    bool isAtEnd() const { return pos >= input.length(); }
    
    char advance() { return input[pos++]; }
    
    char peek() const { return isAtEnd() ? '\0' : input[pos]; }
    
    char peekNext() const { return (pos + 1 >= input.length()) ? '\0' : input[pos + 1]; }

public:
    Scanner(const string &input) : input(input) {}

    Token scanToken()
    {
        // Skip any white space and track new lines
        while (isspace(static_cast<unsigned char>(peek())))
        {
            if (peek() == '\n') line++;
            advance();
        }

        if (isAtEnd()) return Token(END, "", line);

        // Mark the start of our token
        size_t startPos = pos;
        char c = advance();

        // Case switch for handling symbols
        switch (c)
        {
            case ',': return Token(COMMA, ",", line);
            case '.': return Token(PERIOD, ".", line);
            case '?': return Token(Q_MARK, "?", line);
            case '(': return Token(LEFT_PAREN, "(", line);
            case ')': return Token(RIGHT_PAREN, ")", line);
            case '*': return Token(MULTIPLY, "*", line);
            case '+': return Token(ADD, "+", line);
            case ':':
                if (peek() == '-') {
                    advance(); // Consume the '-'
                    return Token(COLON_DASH, ":-", line);
                }
                return Token(COLON, ":", line);
        }

        // Check for keywords and identifiers
        if (isalpha(static_cast<unsigned char>(c)))
        {
            while (isalnum(static_cast<unsigned char>(peek()))) advance();
            
            // Extract the whole word at once
            string word = input.substr(startPos, pos - startPos);

            if (word == "Schemes") return Token(SCHEMES, word, line);
            if (word == "Facts") return Token(FACTS, word, line);
            if (word == "Rules") return Token(RULES, word, line);
            if (word == "Queries") return Token(QUERIES, word, line);

            return Token(ID, word, line);
        }

        // Checking for strings
        if (c == '\'') 
        {
            int startLine = line;
            while (true)
            {
                if (isAtEnd()) {
                    return Token(UNDEFINED, input.substr(startPos, pos - startPos), startLine);
                }

                if (peek() == '\'') {
                    advance(); // Consume closing quote
                    if (peek() == '\'') {
                        advance(); // Consume escaped quote and keep looping
                    } else {
                        // String terminated successfully
                        return Token(STRING, input.substr(startPos, pos - startPos), startLine);
                    }
                } else {
                    if (peek() == '\n') line++;
                    advance();
                }
            }
        }

        // Check for comments
        if (c == '#')
        {
            int startLine = line;

            // Block comment
            if (peek() == '|')
            {
                advance(); // consume '|'
                while (true)
                {
                    if (isAtEnd()) {
                        return Token(UNDEFINED, input.substr(startPos, pos - startPos), startLine);
                    }
                    if (peek() == '|' && peekNext() == '#') {
                        advance(); // consume '|'
                        advance(); // consume '#'
                        return Token(COMMENT, input.substr(startPos, pos - startPos), startLine);
                    }
                    if (peek() == '\n') line++;
                    advance();
                }
            }
            // Line comment
            else 
            {
                while (!isAtEnd() && peek() != '\n') {
                    advance();
                }
                return Token(COMMENT, input.substr(startPos, pos - startPos), startLine);
            }
        }

        // Undefined symbol
        return Token(UNDEFINED, string(1, c), line);
    }

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