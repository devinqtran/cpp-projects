// Scheme.h holds names of the columns of a Relation
#pragma once
#include <vector>
#include <string>

using namespace std;

// Inheritance, Scheme will inherit a 'vector' of names and functions like size() and at() from vector
class Scheme : public vector<string> {
private:

    vector<string> names;

public:
    // Constructor
    Scheme (vector<string> names) : names(names) { }

    unsigned size() const {
        return names.size();
    }

    const string& at(int index) const {
        return names.at(index);
    }

    // TODO: add more delegation functions as needed
};