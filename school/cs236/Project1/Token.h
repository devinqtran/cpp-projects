#pragma once
#include <string>
#include <sstream>

using namespace std;

enum TokenType
{
    COMMA,          // 0
    PERIOD,         // 1
    Q_MARK,         // 2
    LEFT_PAREN,     // 3
    RIGHT_PAREN,    // 4
    COLON,          // 5
    COLON_DASH,     // 6
    MULTIPLY,       // 7
    ADD,            // 8
    SCHEMES,        // 9
    FACTS,          // 10
    RULES,          // 11
    QUERIES,        // 12
    ID,             // 13
    STRING,         // 14
    COMMENT,        // 15
    UNDEFINED,      // 16
    END,            // 17
};

class Token
{
private:
    TokenType type;
    string value;
    int line;

public:
    Token(TokenType type, string value, int line) : type(type), value(value), line(line) {}

    TokenType getType() const { return type; }

    string toString() const
    {
        stringstream out;
        out << "(" << typeName(type) << "," << "\"" << value << "\"" << "," << line << ")";
        return out.str();
    }

    // Function to return the correct string for each 'TokenType' value so toString will print the correct string
    string typeName(TokenType type) const
    {
        switch (type)
        {
        case COMMA:
            return "COMMA";
        case PERIOD:
            return "PERIOD";
        case Q_MARK:
            return "Q_MARK";
        case LEFT_PAREN:
            return "LEFT_PAREN";
        case RIGHT_PAREN:
            return "RIGHT_PAREN";
        case COLON:
            return "COLON";
        case COLON_DASH:
            return "COLON_DASH";
        case MULTIPLY:
            return "MULTIPLY";
        case ADD:
            return "ADD";
        case SCHEMES:
            return "SCHEMES";
        case FACTS:
            return "FACTS";
        case RULES:
            return "RULES";
        case QUERIES:
            return "QUERIES";
        case ID:
            return "ID";
        case STRING:
            return "STRING";
        case COMMENT:
            return "COMMENT";
        case UNDEFINED:
            return "UNDEFINED";
        case END:
            return "END";
        default:
            return "UNKNOWN";
        }
    }
};