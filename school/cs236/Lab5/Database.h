#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Relation.h"

using namespace std;

class Database {
private:
    map<string, Relation> relations;

public:
    // Constructor
    Database() {}

    // method for adding relations to the map called relations
    void addRelation(const string& name, const Relation& relation) {
        relations.insert({name, relation});
    }

    // method for getting a relation
    Relation& getRelation(const string& name) {
        return relations.at(name);
    }

    // method for total tuples in database
    int getTotalTuples() const {
        int total = 0;
        for (auto const& [name, relation] : relations) {
            total += relation.getTuples().size();
        }
        return total;
    }

    void printDatabase() {
      cout << "--- Database Contents ---" << endl;
      for (auto const& [name, relation] : relations) {
          cout << "Table Name: " << name 
               << " | Columns: " << relation.getScheme().size() << endl;
      }
   }
};