// Relation.h a Relation has a name, a Scheme, and a set of Tuples
#pragma once
#include <iostream>
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
            out << "  " <<tuple.toString(scheme) << "\n";
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
    Relation project(vector<int> indices) const {
        vector<string> newNames; // new Schneme (headers)
        for (size_t i = 0; i < indices.size(); ++i) {
            int targetIndex = indices.at(i);
            newNames.push_back(scheme.at(targetIndex));
        }
        Scheme newScheme(newNames);

        // new Relation using the new scheme
        Relation result(name, newScheme);

        // new Tuples (rows)
        for (const Tuple& tuple : tuples) {
            vector<string> newTupleValues;

            for (size_t i = 0; i < indices.size(); ++i) {
                int targetIndex  = indices.at(i);
                newTupleValues.push_back(tuple.at(targetIndex));
            }

            // new smaller Tuple
            Tuple newTuple(newTupleValues);

            // add new Tuple to result Relation
            result.addTuple(newTuple);
        }

        return result;
    }

    // Rename takes a vector<string> of new attribute names and replaces the relation's Scheme with these names (query variables)
    Relation rename(vector<string> newNames) {
        
        // create a new Scheme using the newNames
        Scheme newScheme(newNames);

        // Create a new Relation called result using the newScheme
        Relation result(name, newScheme);

        // copy tuples from current relation into the new one
        for (const Tuple& tuple : tuples) {
            result.addTuple(tuple);
        }

        // return new relation with newNames
        return result;
    }

    // Getter methods
    const Scheme& getScheme() const { return scheme; }
    const set<Tuple>& getTuples() const { return tuples; }

    // Lab 4

    // joinable function is given the scheme and tuple from the left relation of hte join and the scheme and tuple from the right relation of the join
    static bool joinable(const Scheme& leftScheme, const Scheme& rightScheme, const Tuple& leftTuple, const Tuple& rightTuple) {
        // test if tuples are joinable

        // for (unsigned leftIndex = 0; leftIndex < leftScheme.size(); leftIndex++) {
        //     const string& leftName = leftScheme.at(leftIndex);
        //     const string& leftValue = leftTuple.at(leftIndex);
        //     cout << "left name: " << leftName << " value: " << leftValue << endl;
        // }
        // for (unsigned rightIndex = 0; rightIndex < rightScheme.size(); rightIndex++) {
        //     const string& rightName = rightScheme.at(rightIndex);
        //     const string& rightValue = rightTuple.at(rightIndex);
        //     cout << "right name: " << rightName << " value: " << rightValue << endl;
        // }

        // Nested Loop
        for (unsigned leftIndex = 0; leftIndex < leftScheme.size(); leftIndex++) {
            const string& leftName = leftScheme.at(leftIndex);
            const string& leftValue = leftTuple.at(leftIndex);
            // cout << "left name: " << leftName << " value: " << leftValue << endl;

            for (unsigned rightIndex = 0; rightIndex < rightScheme.size(); rightIndex++) {
                const string& rightName = rightScheme.at(rightIndex);
                const string& rightValue = rightTuple.at(rightIndex);
                // cout << "right name: " << rightName << " value: " << rightValue << endl;

                if (leftName == rightName && leftValue != rightValue) {
                    return false;
                }
            }
        }

        return true;
    }
    
    // join function
    Relation join(const Relation& right) {
        const Relation& left = *this;

        // new joinScheme
        Scheme newScheme = joinSchemes(left.getScheme(), right.getScheme());

        Relation result(left.name + "_join_" + right.name, newScheme);

        // Nested loop
        for (const Tuple& leftTuple : left.getTuples()) {
            for (const Tuple& rightTuple : right.getTuples()) {
                if (joinable(left.getScheme(), right.getScheme(), leftTuple, rightTuple)) {
                    Tuple newTuple = joinTuples(left.getScheme(), right.getScheme(), leftTuple, rightTuple);
                    result.addTuple(newTuple);
                }
            }
        }

        return result;
    }

    // Result Scheme needs all attributes from leftScheme, and UNIQUE attributes from rightScheme
    Scheme joinSchemes(const Scheme& leftScheme, const Scheme& rightScheme) {
        vector<string> joinedNames; // new vector of strings to store all names

        // input left attributes
        for (unsigned leftIndex = 0; leftIndex < leftScheme.size(); leftIndex++) {
            joinedNames.push_back(leftScheme.at(leftIndex));
        }

        // loop through right and add UNIQUE attributes
        for (unsigned rightIndex = 0; rightIndex < rightScheme.size(); rightIndex++) {
            const string& rightName = rightScheme.at(rightIndex);
            bool unique = true;

            // check if rightName is in leftScheme already
            for (unsigned leftIndex = 0; leftIndex < leftScheme.size(); leftIndex++) {
                if (leftScheme.at(leftIndex) == rightName) {
                    unique = false;
                    break;
                }
            }

            // add the unique names to joinedNames
            if (unique) {
                joinedNames.push_back(rightName);
            }
        }

        // return the new scheme using the joinedNames
        return Scheme(joinedNames);
    }

    // Result Tuple must match newScheme from joinSchemes take all left values, only add values for UNIQUE right attributes
    Tuple joinTuples(const Scheme& leftScheme, const Scheme& rightScheme, const Tuple& leftTuple, const Tuple& rightTuple) {
        vector<string> joinedValues;

        // add all left attributes
        for (unsigned leftIndex = 0; leftIndex < leftTuple.size(); leftIndex++) {
            joinedValues.push_back(leftTuple.at(leftIndex));
        }

        // add all the UNIQUE right values (same as joinSchemes)
        for (unsigned rightIndex = 0; rightIndex < rightScheme.size(); rightIndex++) {
            const string& rightName = rightScheme.at(rightIndex);
            bool unique = true;

            for (unsigned leftIndex = 0; leftIndex < leftScheme.size(); leftIndex++) {
                if (leftScheme.at(leftIndex) == rightName) {
                    unique = false;
                    break;
                }
            }
            if (unique) {
                joinedValues.push_back(rightTuple.at(rightIndex));
            }
        }

        return Tuple(joinedValues);
    }

    // union - add tuples from right to this relation, return true if new tuples were added
    bool unionRelation(const Relation& right) {
        bool newTupleAdded = false;

        for (const Tuple& tuple : right.getTuples()) {
            if (tuples.insert(tuple).second) {
                newTupleAdded = true;

                cout << "  " << tuple.toString(scheme) << endl;
            }
        }
        return newTupleAdded;
    }

};

/*
    TODO: 
    1. Union operation bool unionRelation(const Relation& right) - take another relation and add all of the tuples to the current relation, 
    print only the new Tuples, return bool T/F for if Tuples were added

    2. Project operation - implement functionality to change the order of columns (indices = {2, 0} -> should output column 2 first and then 0)

    3. Rule evaluation - Evaluate, Join, Project, Rename, Union

    4. Loop for all rules and track number of passes, stop after ZERO Tuples are added to database
*/