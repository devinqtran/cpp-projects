#pragma once
#include <vector>
#include <string>
#include "Predicate.h" // string name, vector<Parameter> parameters
#include "Rule.h" // Predicate headPredicate, vector<Predicate> bodyPredicates

using namespace std;

/*
    datalogProgram	->	SCHEMES COLON scheme schemeList
                        FACTS COLON factList
                        RULES COLON ruleList
                        QUERIES COLON query queryList
                        END
*/

class DatalogProgram {
private:
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Rule> rules;
    vector<Predicate> queries;

public:
    void addScheme(Predicate s) { schemes.push_back(s); }
    void addFact(Predicate f) { facts.push_back(f); }
    void addRule(Rule r) { rules.push_back(r); }
    void addQuery(Predicate q) { queries.push_back(q); } 

    // toString method
    string toString() const {
        // print all vectors 

        // print schemes

        // print facts

        // print rules

        // print queries
    }
};