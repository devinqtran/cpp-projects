#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "DatalogProgram.h"
#include "Relation.h"
#include "Database.h"
#include "Scheme.h"

using namespace std;

class Interpreter {
private:
    DatalogProgram program;
    Database database;

public:
    // Constructor that takes a parsed program
    Interpreter(const DatalogProgram& program) : program(program) { }

    void interpret() {
        // Add evaluate functions below
    }

    // evaluate schemes

    // evaluate facts

    // evaluate queries
};
