// Relation.h a Relation has a name, a Scheme, and a set of Tuples
#pragma once
#include <vector>
#include <string>
#include <set>
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
};