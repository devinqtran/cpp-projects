#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "DatalogProgram.h"
#include "Relation.h"
#include "Database.h"
#include "Scheme.h"
#include "Rule.h"
#include "Predicate.h"
#include "Graph.h"

using namespace std;

// Interpreter class holding a DatalogProgram and a Database
class Interpreter {
private:
    DatalogProgram program;
    Database database;

public:
    // Constructor that takes a parsed program
    Interpreter(const DatalogProgram& program) : program(program) { }

    void interpret() {
        evaluateSchemes();
        evaluateFacts();
        evaluateRules();
        evaluateQueries();
    }

    // evaluate schemes - create empty tables(relations)
    void evaluateSchemes() {
        // go through scheme predicates in the program
        // find name, headers, new empty relation using name and headers, add relation to the database
        for (auto predicate: program.getSchemes()) {
            // get name and headers
            string relationName = predicate.getName();
            vector<string> headers;
            for (auto parameter: predicate.getParameters()) {
                headers.push_back(parameter.toString());
            }

            // create new Scheme and Relation
            Scheme scheme(headers);
            Relation relation(relationName, scheme);

            // add the empty relation to the database
            database.addRelation(relationName, relation);
        }
    }

    // evaluate facts - add the tuples to the relations in the database
    void evaluateFacts() {
        for (auto fact : program.getFacts()) {
            string relationName = fact.getName();
            
            vector<string> tupleValues;
            for (auto parameter : fact.getParameters()) {
                tupleValues.push_back(parameter.toString());
            }
            
            Tuple newTuple(tupleValues);
            database.getRelation(relationName).addTuple(newTuple);
        }
    }

    // evaluate queries
    void evaluateQueries() {
        // print header
        cout << "Query Evaluation" << endl;

        // loop through each query in the DatalogProgram
        for (auto query : program.getQueries()) {
            
            // starting Relation is the relation from the database that matches the query name
            Relation result = database.getRelation(query.getName());

            // Trackers for our variables
            map<string, int> seenVariables; // map a variable name to its column index
            vector<int> projectIndices;     // column indicies to keep
            vector<string> renameHeaders;   // new headers for the renamed relation

            // select
            vector<Parameter> parameters = query.getParameters();
            for (size_t i = 0; i < parameters.size(); ++i) {
                // get the string value of the parameter at index i
                string paramValue = parameters.at(i).toString();

                if (paramValue.at(0) == '\'') {
                    // constant starts with a quote
                    result = result.select(i, paramValue);
                } 
                else {
                    // variable ID
                    if (seenVariables.find(paramValue) != seenVariables.end()) {
                        result = result.select(seenVariables[paramValue], i);
                    } 
                    else {
                        // remember this variable for future reference
                        seenVariables.insert({paramValue, i});
                        projectIndices.push_back(i);
                        renameHeaders.push_back(paramValue);
                    }
                }
            }
            // project
            result = result.project(projectIndices);

            // rename
            result = result.rename(renameHeaders);

            // print the result of the query
            cout << query.toString() << "? "; 

            if (result.getTuples().empty()) {
                cout << "No" << endl;
            } 
            else {
                cout << "Yes(" << result.getTuples().size() << ")" << endl;
                // prints only the result tuples
                if (!projectIndices.empty()) {
                    cout << result.toString(); 
                }
            }
        }
    }

    // helper method evaluatePredicate
    Relation evaluatePredicate(const Predicate& p) {
        Relation result = database.getRelation(p.getName());

        vector<int> projectIndices;
        vector<string> renameNames;
        map<string, int> seen;

        // select
        for (unsigned i = 0; i < p.getParameters().size(); i++) {
            string parameterValue = p.getParameters().at(i).toString();

            // check for a constant
            if (parameterValue.at(0) == '\'') {
                // select 1
                result = result.select(i, parameterValue);
            } else {
                // variable
                if (seen.find(parameterValue) != seen.end()) {
                    // select 2
                    result = result.select(seen[parameterValue], i);
                } else {
                    seen[parameterValue];
                    projectIndices.push_back(i);
                    renameNames.push_back(parameterValue);
                }
            }
        }
        // project
        result = result.project(projectIndices);
        
        // rename
        result = result.rename(renameNames);
        
        return result;
    }

    // evaluate Rule - evaluate predicates on right side and join them, project after matching variable results, rename, and then union, and add tuples
    bool evaluateRule(const Rule& rule) {
        // evaluate
        Relation result = evaluatePredicate(rule.getBodyPredicates().at(0));

        // join
        for (size_t i = 1; i < rule.getBodyPredicates().size(); i++) {
            Relation nextRelation = evaluatePredicate(rule.getBodyPredicates().at(i));
            result = result.join(nextRelation);
        }

        // project
        vector<int> projectIndices;
        const Predicate& headPredicate = rule.getHeadPredicate();
        
        for (unsigned i = 0; i < headPredicate.getParameters().size(); i++) {
            string headVariable = headPredicate.getParameters().at(i).toString();
            
            // find the variable within the joined Scheme
            for (unsigned j = 0; j < result.getScheme().size(); j++) {
                if (result.getScheme().at(j) == headVariable) {
                    projectIndices.push_back(j);
                    break;
                }
            }
        }
        result = result.project(projectIndices);

        // rename
        string targetName = headPredicate.getName();
        Relation& targetRelation = database.getRelation(targetName); // find the target relation
        
        // find the targetAttributes
        vector<string> targetAttributes;
        for (unsigned i = 0; i < targetRelation.getScheme().size(); i++) {
            targetAttributes.push_back(targetRelation.getScheme().at(i));
        }
        result = result.rename(targetAttributes);

        // union
        cout << rule.toString() << endl;

        // union the final result and print the tuplesAdded
        bool tuplesAdded = targetRelation.unionRelation(result);

        return tuplesAdded;
    }

    // Fixed-Point loop for evaluateRules
    void evaluateRules() {
        // print header
        cout << "Rule Evaluation" << endl;

        // track passes
        int passes = 0;
        bool changed = true;

        // loop
        while (changed) {
            passes++;

            // total tuples before pass
            int startTuples = database.getTotalTuples();

            // evaluate rules in order
            for (const Rule& rule : program.getRules()) {
                evaluateRule(rule);
            }

            // total tuples after pass
            int endTuples = database.getTotalTuples();

            // check for any new facts
            if (startTuples == endTuples) {
                changed = false;
            }
        }

        // print footer
        cout << "\nSchemes populated after " << passes << " passes through the Rules.\n" << endl;
    }

    // temporary getter for testing
    Database& getDatabase() {
      return database;
    }

    // makeGraph
    static Graph makeGraph(const vector<Rule>& rules) {

        Graph graph(rules.size());
        // code for adding edges to the graph using the rule dependencies

        // loop over the rule vector
        // print a line like this for each rule:
        // from rule R0: A() :- B()

        for (int i = 0; i < rules.size(); i++) {
            cout << "from rule R" << i << ": " << rules[i].toString() << "\n";

            for (const auto pred : rules[i].getBodyPredicates()) {
                cout << "from body predicate: " << pred.toString() << "\n";

                for (int j = 0; j < rules.size(); j++) {
                    cout << "to rule R" << j << ": " << rules[j].toString() << "\n";

                    // check if the current pred name is the same as rules[j], add edge if so
                    if (pred.getName() == rules[j].getHeadPredicate().getName()) {
                        graph.addEdge(i, j);
                        cout << "dependency found: (R" << i << ",R" << j << ")" << "\n"; 
                    }
                }
            }
        }

        

        return graph;
    }


};
