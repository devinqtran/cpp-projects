#include <iostream>
#include <vector>

#include "..//Project1//Token.h"

class Parser {
private:
    vector<Token> tokens; // a private vector of Token objects called token

public:
    // Constructor receives a reference to the tokens vector of Token objects
    Parser(const vector<Token>& tokens) : tokens(tokens) {}

    // tokenType function returns the type of the current Token
    TokenType tokenType() const {
        return tokens.at(0).getType();
    }

    // advanceToken function moves to the next Token
    void advanceToken() {
        tokens.erase(tokens.begin()); 
    }
    
    // throwError function (INCOMPLETE)
    void throwError() {
        std::cout << "error" << std::endl;
    }

    // match function called when parsing a terminal symbol
    void match(TokenType t) {
        cout << "match: " << t << endl;

        if (tokenType() == t) {
            advanceToken();
        }
        else {
            throwError();
        }
    }

    // idList -> COMMA ID idList | lambda
    void idList() {
        if (tokenType() == COMMA) {
            match(COMMA);
            match(ID);
            idList();
        } else {
            // lambda
        }
    }

    // scheme -> ID LEFT_PAREN ID idList RIGHT_PAREN
    void scheme() {
        if (tokenType() == ID) {
            match(ID);
            match(LEFT_PAREN);
            match(ID);
            idList();
            match(RIGHT_PAREN);
        }
    }

};