#pragma once
#include <string>
#include <vector>
#include "Parameter.h"

using namespace std;

// predicate -> ID LEFT_PAREN parameter parameterList RIGHT_PAREN
class Predicate {
private:
    string name;
    vector<Parameter> parameters;

public:
    // Constructor
    Predicate(string name) : name(name) {}

    // Method for adding a parameter to the parameters vector
    void addParameter(Parameter p) {
        parameters.push_back(p);
    }

    // Getter method for parameters
    const vector<Parameter>& getParameters() const {
        return parameters;
    }

    // Getter method for name
    string getName() const {
        return name;
    }

    // toString method for printing the values
    string toString() const {
        string result = name + "(";
        for (size_t i = 0; i < parameters.size(); ++i) {
            result += parameters[i].toString();
            if (i < parameters.size() - 1) {
                result += ",";
            }
        }
        result += ")";
        return result;
    }
};