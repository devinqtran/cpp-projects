#pragma once
#include <vector>
#include <string>
#include "Predicate.h"

using namespace std;

// rule ->headPredicate COLON_DASH predicate predicateList PERIOD
class Rule {
private:
    Predicate headPredicate;
    vector<Predicate> bodyPredicates;


public:
    // Constructor
    Rule(Predicate head) : headPredicate(head) {}

    // method for adding a predicate to the vector bodyPredicates
    void addBodyPredicate(Predicate p) {
        bodyPredicates.push_back(p);
    }

    // toString method for printing the values
    string toString() const {
        string result = headPredicate.toString() + " :- "; // create a string result and initialize it to the value of headPredicate.toString(), then concatenate " :- "
        for (size_t i = 0; i < bodyPredicates.size(); ++i) {
            result += bodyPredicates[i].toString();
            if (i < bodyPredicates.size() - 1) {
                result += ",";
            }
        }
        result += ".";
        return result;
    }
};