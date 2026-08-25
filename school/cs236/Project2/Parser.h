#include <iostream>
#include <vector>
#include <string>
#include "Parameter.h"
#include "Predicate.h"
#include "Rule.h"
#include "DatalogProgram.h"
#include "..//Project1//Token.h"

class Parser
{
private:
    vector<Token> tokens; // a private vector of Token objects called token
    DatalogProgram program; // a private DatalogProgram object called program

public:
    // Constructor receives a reference to the tokens vector of Token objects
    Parser(const vector<Token> &tokens) : tokens(tokens) {}

    // Main parse function try...catch loop 
    void parse() {
        try {
            // parse top-level grammar rule
            program = datalogProgram();
            // std::cout << "Success!\n";
            // std::cout << program.toString(); // this prints the full AST
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
        if (tokenType() == t)
        {
            // cout << "match: " << t << endl;
            advanceToken();
        }
        else
        {
            throwError();
        }
    }

    // getter for the DatalogProgram object
    const DatalogProgram& getProgram() const {
        return program;
    }

    // ----- schemeList, factList, ruleList, queryList -----

    // schemeList -> scheme schemeList | lambda
    void schemeList(DatalogProgram& program) {
        if (tokenType() == ID) { 
            program.addScheme(scheme());
            schemeList(program);
        }
    }

    // factList	-> fact factList | lambda
    void factList(DatalogProgram& program) {
        if (tokenType() == ID) {
            program.addFact(fact());
            factList(program);
        }
    }
    
    // ruleList -> rule ruleList | lambda
    void ruleList(DatalogProgram& program) {
        if (tokenType() == ID) {
            program.addRule(rule());
            ruleList(program);
        }
    }
    
    // queryList ->	query queryList | lambda
    void queryList(DatalogProgram& program) {
        if (tokenType() == ID) {
            program.addQuery(query());
            queryList(program);
        }
    }

    // ----- idList, stringList, parameterList, predicateList -----

    // idList -> COMMA ID idList | lambda
    void idList(Predicate& currentPredicate) {
        if (tokenType() == COMMA) {
            match(COMMA);
            
            std::string paramValue = tokens.at(0).getValue();
            match(ID);
            currentPredicate.addParameter(Parameter(paramValue));
            
            idList(currentPredicate);
        }
    }


    // predicateList ->	COMMA predicate predicateList | lambda
    void predicateList(Rule& currentRule) {
        if (tokenType() == COMMA) {
            match(COMMA);
            
            Predicate bodyPred = predicate();
            currentRule.addBodyPredicate(bodyPred);
            
            predicateList(currentRule);
        }
    }

    // parameterList -> COMMA parameter parameterList | lambda
    void parameterList(Predicate& currentPredicate) {
        if (tokenType() == COMMA) {
            match(COMMA);
            currentPredicate.addParameter(parameter());
            parameterList(currentPredicate);
        }
    }

    // stringList -> COMMA STRING stringList | lambda
    void stringList(Predicate& currentPredicate) {
        if (tokenType() == COMMA) {
            match(COMMA);
            std::string strVal = tokens.at(0).getValue();
            match(STRING);
            currentPredicate.addParameter(Parameter(strVal));
            stringList(currentPredicate);
        }
    }

    // ----- scheme, fact, rule, query -----

    // scheme -> ID LEFT_PAREN ID idList RIGHT_PAREN
    Predicate scheme() {
        std::string name = tokens.at(0).getValue();
        match(ID);
        Predicate myScheme(name);

        match(LEFT_PAREN);
        
        std::string firstParam = tokens.at(0).getValue();
        match(ID);
        myScheme.addParameter(Parameter(firstParam));
        
        idList(myScheme);
        
        match(RIGHT_PAREN);
        return myScheme;
    }


    // fact -> ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
    Predicate fact() {
        std::string name = tokens.at(0).getValue();
        match(ID);
        Predicate myFact(name);

        match(LEFT_PAREN);
        std::string firstStr = tokens.at(0).getValue();
        match(STRING);
        myFact.addParameter(Parameter(firstStr));
        
        stringList(myFact);
        
        match(RIGHT_PAREN);
        match(PERIOD);
        return myFact;
    }

    // rule -> headPredicate COLON_DASH predicate predicateList PERIOD
    Rule rule() {
        Predicate head = headPredicate();
        Rule myRule(head);

        match(COLON_DASH);
        
        Predicate bodyPred = predicate();
        myRule.addBodyPredicate(bodyPred);
        
        predicateList(myRule);
        
        match(PERIOD);
        return myRule;
    }

    // query -> predicate Q_MARK
    Predicate query() {
        Predicate myQuery = predicate();
        match(Q_MARK);
        return myQuery;
    }

    // ----- parameter, predicate, headPredicate, datalogProgram -----

    // paramater ->	STRING | ID
    Parameter parameter() {
        string value = tokens.at(0).getValue(); // get the string value before matching and removing
        if (tokenType() == STRING) {
            match(STRING);
        } else if (tokenType() == ID) {
            match(ID);
        } else {
            throwError(); // no STRING/ID means syntax error
        }
        return Parameter(value);
    }

    // predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
    Predicate predicate() {
        std::string name = tokens.at(0).getValue();
        match(ID);
        Predicate myPred(name);

        match(LEFT_PAREN);
        myPred.addParameter(parameter());
        parameterList(myPred);
        match(RIGHT_PAREN);
        
        return myPred;
    }

    // headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN
    Predicate headPredicate() {
        std::string name = tokens.at(0).getValue();
        match(ID);
        Predicate head(name);

        match(LEFT_PAREN);
        std::string firstParam = tokens.at(0).getValue();
        match(ID);
        head.addParameter(Parameter(firstParam));
        
        idList(head);
        match(RIGHT_PAREN);
        
        return head;
    }

    /*
        datalogProgram	->	SCHEMES COLON scheme schemeList
                            FACTS COLON factList
                            RULES COLON ruleList
                            QUERIES COLON query queryList
                            END
    */
    DatalogProgram datalogProgram() {
        DatalogProgram program;

        match(SCHEMES);
        match(COLON);
        program.addScheme(scheme()); 
        schemeList(program);

        match(FACTS);
        match(COLON);
        factList(program);

        match(RULES);
        match(COLON);
        ruleList(program);

        match(QUERIES);
        match(COLON);
        program.addQuery(query());
        queryList(program);

        match(END);
        
        return program;
    }

    /*
        Remaining Tasks to finish Datalog Parser:
        1. Write parsing functions for the remaining grammar rules. (16 total)

        2. Fix error handling in the parser. (Throw an Exception in the 'throwError' function.) (Catch the Exception at the top of the parser and report the error.)

        3. Write classes for Parameter, Predicate, Rule, and Datalog Program. (4 classes containing rules from Parser.h grammars)

        4. Add code to the parser to create Parameter, Predicate, and Rule objects while parsing, and construct a Datalog Program object that contains lists of Schemes, Facts, Rules, and Queries.
    */
};