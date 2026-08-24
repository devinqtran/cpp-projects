// Tuple.h holds the values stored in one row of a Relation
#pragma once
#include <string>
#include <vector>

using namespace std;

class Tuple {
private:
    vector<string> values;

public:

    // Constructor - a Tuple object is initialized after passing a 'vector' of values to constructor
    Tuple (vector<string> values) : values(values) { }

    unsigned size() const {
        return values.size();
    }

    const string& at(int index) const {
        return values.at(index); 
    }

    bool operator<(const Tuple t) const {
        return values < t.values;
    }

    // TODO: add more delegation functions as needed


};