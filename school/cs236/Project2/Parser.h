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
            // parse top-level grammar rule
            datalogProgram();

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

    // ----- schemeList, factList, ruleList, queryList -----

    // schemeList -> scheme schemeList | lambda
    void schemeList() {
        if (tokenType() == ID) { // check for ID because first token of a scheme is an ID
            scheme();
            schemeList();
        } else {
            // lambda
        }
    }

    // factList	-> fact factList | lambda
    void factList() {
        if (tokenType() == ID) {
            fact();
            factList();
        } else {
            // lambda
        }
    }
    
    // ruleList -> rule ruleList | lambda
    void ruleList() {
        if (tokenType() == ID) { // first token of a rule is a headPredicate, first token of a headPredicate is an ID
            rule();
            ruleList();
        } else {
            // lambda
        }
    }
    
    // queryList ->	query queryList | lambda
    void queryList() {
        if (tokenType() == ID) {
            query();
            queryList();
        } else {
            // lambda
        }
    }

    // ----- idList, stringList, parameterList, predicateList -----

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


    // predicateList ->	COMMA predicate predicateList | lambda
    void predicateList() {
        if (tokenType() == COMMA) {
            match(COMMA);
            // predicate();
            // predicateList();
        } else {
            // lambda
        }
    }

    // parameterList -> COMMA parameter parameterList | lambda
    void parameterList() {
        if (tokenType() == COMMA) {
            match(COMMA);
            // parameter();
            // parameterList();
        } else {
            // lambda
        }
    }

    // stringList -> COMMA STRING stringList | lambda
    void stringList() {
        if (tokenType() == COMMA) {
            match(COMMA);
            match(ID);
            idList();
        } else {
            // lambda
        }
    }

    // ----- scheme, fact, rule, query -----

    // scheme -> ID LEFT_PAREN ID idList RIGHT_PAREN
    void scheme()
    {
        match(ID);
        match(LEFT_PAREN);
        match(ID);
        idList();
        match(RIGHT_PAREN);
    }

    // fact -> ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
    void fact() {
        match(ID);
        match(LEFT_PAREN);
        match(STRING);
        stringList();
        match(RIGHT_PAREN);
        match(PERIOD);
    }

    // rule -> headPredicate COLON_DASH predicate predicateList PERIOD
    void rule() {
        // headPredicate();
        match(COLON_DASH);
        // predicate();
        // predicateList();
        match(PERIOD);
    }

    // query -> predicate Q_MARK
    void query() {
        // predicate();
        match(Q_MARK);
    }

    // ----- parameter, predicate, headPredicate, datalogProgram -----

    // paramater ->	STRING | ID
    void parameter() {
        if (tokenType() == STRING) {
            match(STRING);
        } else if (tokenType() == ID) {
            match(ID);
        } else {
            throwError(); // no STRING/ID means syntax error
        }
    }

    // predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
    void predicate() {
        match(ID);
        match(LEFT_PAREN);
        parameter();
        parameterList();
        match(RIGHT_PAREN);
    }

    // headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN
    void headPredicate() {
        match(ID);
        match(LEFT_PAREN);
        match(ID);
        idList();
        match(RIGHT_PAREN);
    }

    /*
        datalogProgram	->	SCHEMES COLON scheme schemeList
                            FACTS COLON factList
                            RULES COLON ruleList
                            QUERIES COLON query queryList
                            END
    */
    void datalogProgram() {
        match(SCHEMES);
        match(COLON);
        scheme();
        schemeList();

        match(FACTS);
        match(COLON);
        factList();

        match(RULES);
        match(COLON);
        ruleList();

        match(QUERIES);
        match(COLON);
        query();
        queryList();

        match(END);
    }

    /*
        Remaining Tasks to finish Datalog Parser:
        1. Write parsing functions for the remaining grammar rules. (16 total)

        2. Fix error handling in the parser. (Throw an Exception in the 'throwError' function.) (Catch the Exception at the top of the parser and report the error.)

        3. Write classes for Parameter, Predicate, Rule, and Datalog Program. (4 classes containing rules from Parser.h grammars)

        4. Add code to the parser to create Parameter, Predicate, and Rule objects while parsing, and construct a Datalog Program object that contains lists of Schemes, Facts, Rules, and Queries.
    */
};