#pragma once
#include <string>

using namespace std;

// parameter -> STRING | ID
class Parameter {
private:
    string value;

public:
    // Constructor
    Parameter(string value) : value(value) {}

    // toString for printing parsed data
    string toString() const {
        return value;
    }

};
