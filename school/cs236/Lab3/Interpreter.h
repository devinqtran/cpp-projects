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
        // Add evaluate functions below
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

    }

    // evaluate queries
    void evaluateQueries() {

    }

    // Temporary getter for testing
    Database& getDatabase() {
      return database;
    }

};
