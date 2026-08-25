#pragma once
#include <vector>
#include <string>
#include <set>         // for domain
#include "Predicate.h" // string name, vector<Parameter> parameters
#include "Rule.h"      // Predicate headPredicate, vector<Predicate> bodyPredicates
#include <sstream>

using namespace std;

/*
    datalogProgram	->	SCHEMES COLON scheme schemeList
                        FACTS COLON factList
                        RULES COLON ruleList
                        QUERIES COLON query queryList
                        END
*/

class DatalogProgram
{
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
    string toString() const
    {
        // print all vectors
        ostringstream out; // create a new output stringstream object called out

        // print schemes
        out << "Schemes(" << schemes.size() << "):\n";
        for (const Predicate &scheme : schemes)
        {
            out << " " << scheme.toString() << "\n";
        }

        // print facts
        out << "Facts(" << facts.size() << "):\n";
        for (const Predicate &fact : facts)
        {
            out << " " << fact.toString() << ".\n";
        }

        // print rules
        out << "Rules(" << rules.size() << "):\n";
        for (const Rule &rule : rules)
        {
            out << " " << rule.toString() << "\n";
        }

        // print queries
        out << "Queries(" << queries.size() << "):\n";
        for (const Predicate &query : queries)
        {
            out << " " << query.toString() << "?\n";
        }

        // calculate domain
        set<std::string> domain;
        for (const Predicate &fact : facts)
        {
            for (const Parameter &param : fact.getParameters())
            {
                domain.insert(param.toString());
            }
        }

        // print domain
        out << "Domain(" << domain.size() << "):\n";
        for (const std::string &domainString : domain)
        {
            out << "  " << domainString << "\n";
        }

        return out.str(); // returns the output stringstream called out converted to a string
    }

    // Getter methods for the vectors
    const vector<Predicate> &getSchemes() const { return schemes; }
    const vector<Predicate> &getFacts() const { return facts; }
    const vector<Rule> &getRules() const { return rules; }
    const vector<Predicate> &getQueries() const { return queries; }

};