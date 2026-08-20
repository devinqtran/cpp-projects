#include <iostream>
#include <vector>

#include "..//Project1//Token.h"

class Parser
{
private:
    vector<Token> tokens; // a private vector of Token objects called token

public:
    // Constructor receives a reference to the tokens vector of Token objects
    Parser(const vector<Token> &tokens) : tokens(tokens) {}

    // Main parse function try...catch loop 
    void parse() {
        try {
            // TESTING REMOVE AFTER datalogProgram is finished
            scheme();

            // parse top-level grammar rule
            // datalogProgram(); // Need to implement

            // print success if it worked without exceptions
            std::cout << "Success!" << "\n";
        }    
        catch (const Token& errorToken) {
            // catch the thrown error token and report error
            std::cout << "Failure!" << "\n";
            std::cout << "  " << errorToken.toString() << "\n";
        }
    }

    // tokenType function returns the type of the current Token
    TokenType tokenType() const
    {
        return tokens.at(0).getType();
    }

    // advanceToken function moves to the next Token
    void advanceToken()
    {
        tokens.erase(tokens.begin());
    }

    // throwError function (INCOMPLETE)
    void throwError()
    {
        // Throw the current token as an error
        throw tokens.at(0);
    }

    // match function called when parsing a terminal symbol
    void match(TokenType t)
    {
        cout << "match: " << t << endl;

        if (tokenType() == t)
        {
            advanceToken();
        }
        else
        {
            throwError();
        }
    }

    // idList -> COMMA ID idList | lambda
    void idList()
    {
        if (tokenType() == COMMA)
        {
            match(COMMA);
            match(ID);
            idList();
        }
        else
        {
            // lambda
        }
    }

    // scheme -> ID LEFT_PAREN ID idList RIGHT_PAREN
    void scheme()
    {
        if (tokenType() == ID)
        {
            match(ID);
            match(LEFT_PAREN);
            match(ID);
            idList();
            match(RIGHT_PAREN);
        }
    }

    /*
        Remaining Tasks to finish Datalog Parser:
        1. Write parsing functions for the remaining grammar rules. (16 total)

        2. Fix error handling in the parser. (Throw an Exception in the 'throwError' function.) (Catch the Exception at the top of the parser and report the error.)

        3. Write classes for Parameter, Predicate, Rule, and Datalog Program. (4 classes containing rules from Parser.h grammars)

        4. Add code to the parser to create Parameter, Predicate, and Rule objects while parsing, and construct a Datalog Program object that contains lists of Schemes, Facts, Rules, and Queries.
    */
};