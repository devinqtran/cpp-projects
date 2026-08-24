// Tuple.h holds the values stored in one row of a Relation
#pragma once
#include <string>
#include <vector>
#include <sstream>
#include "Scheme.h"

using namespace std;

// Class created using Delegation, meaning all methods and helpers need to be defined as needed
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

    // operator<() function allows Tuple objects to be stored in a set (set data type uses less-than operator to organize into a BST)
    bool operator<(const Tuple t) const {
        return values < t.values;
    }

    // TODO: add more delegation functions as needed

    // toString method using Tuple.h and Scheme.h
    string toString (const Scheme& scheme) const { // toString method that takes a reference to the Scheme scheme
        const Tuple& tuple = *this;
        stringstream out; // create a new stringstream called out
        
        // print "name=value" pairs
        for (size_t i = 0; i < scheme.size(); ++i) {
            out << scheme.at(i) << "='" << tuple.at(i) << "'";
        
            // print comma and space if not last element
            if (i < scheme.size()- 1) {
                out << ", ";
            }
        }
        return out.str();
    }
};