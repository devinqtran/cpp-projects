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

    // Relation select function returns a new Relation that contains a subset of Tuplesw from an existing Relation that meet a select condition
    // a given position in that Tuple must have a given value
    Relation select(int index, const string& value) const {
        Relation result(name, scheme);
        // add tuples to the result if they meet the condition

        /*
            for each tuple in the relation
                if the value at the given index equals the given value
                    add the tuple to the result
        */
        for (const Tuple& tuple: tuples) {
            if (tuple.at(index) == value) {
                result.addTuple(tuple);
            }
        }

        return result;
    }

};