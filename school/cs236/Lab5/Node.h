#pragma once
#include <set>
#include <string>
#include <sstream>

using namespace std;

class Node {
private:
    set<int> adjacentNodeIDs;

public:
    
    void addEdge(int adjacentNodeID) {
        adjacentNodeIDs.insert(adjacentNodeID);
    }

    // The 'toString' function prints the node IDs in the 'adjacent node IDs' set as a comma separated list. 
    // The letter R decoration is printed before each node ID. The node IDs are printed in sorted order. (Using a 'set' makes the sorting automatic.)
    string toString() const {
        stringstream out;
        bool isFirst = true;

        for (int id : adjacentNodeIDs) {
            if (!isFirst) {
                out << ",";
            }
            
            out << "R" << id;
            isFirst = false;
        }

        return out.str();
    }


};