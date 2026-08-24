// Relation.h a Relation has a name, a Scheme, and a set of Tuples
#pragma once
#include <vector>
#include <string>
#include <set>
#include <sstream>
#include "Scheme.h"
#include "Tuple.h"

using namespace std;

class Relation {
private:
    string name;
    Scheme scheme;
    set<Tuple> tuples;

public:

    // Constructor
    Relation(const string& name, const Scheme& scheme) : name(name), scheme(scheme) { }

    // method for adding a tuple to the set tuples
    void addTuple(const Tuple& tuple) {
        tuples.insert(tuple);
    }

    // toString
    string toString() const {
        stringstream out;

        // iterate through each tuple in set<Tuple>
        for (const Tuple& tuple: tuples) {
            out << tuple.toString(scheme) << "\n";
        }
        return out.str();
    }

    // Select 1 (Select by value) returns a new Relation containing only rows where index matches a constant value (column 1 == column 2)
    Relation select(int index, const string& value) const {
        Relation result(name, scheme);
        // add tuples to the result if they meet the condition
        for (const Tuple& tuple: tuples) {
            if (tuple.at(index) == value) {
                result.addTuple(tuple);
            }
        }

        return result;
    }

    // Select 2 (Select by variable) loops through two column index, keeps only the columns where the value at index1 matches the value at index2 (SK(X,X))
    Relation select(int index1, int index2) const {
        Relation result(name, scheme);
        for (const Tuple& tuple: tuples) {
            if (tuple.at(index1) == tuple.at(index2)) {
                result.addTuple(tuple);
            }
        }
        return result;
    }

    // Project takes a vector<int> of indexes, loops through each tuple, extracts the values at the specific index to create new smaller tuples, updates Scheme
    Relation project(vector<int> indices) {


    }

    // Rename takes a vector<string> of new attribute names and replaces the relation's Scheme with these names (query variables)
    Relation rename(vector<string> newNames) {
        // for Scheme scheme : schemes
        // replace name with newNames

        // return new relation with newNames
    }

};