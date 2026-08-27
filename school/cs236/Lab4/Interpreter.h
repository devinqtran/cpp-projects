#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "C:\\Users\\devin\\OneDrive\\Desktop\\cpp-projects\\school\\cs236\\Project2\\DatalogProgram.h"
#include "Relation.h"
#include "Database.h"
#include "Scheme.h"

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

    // temporary getter for testing
    Database& getDatabase() {
      return database;
    }

};
