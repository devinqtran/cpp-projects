#pragma once
#include <set>
#include <string>
#include <sstream>

using namespace std;

class Node {
private:
    set<int> adjacentNodeIDs;
    bool visited;

public:

    // Constructor
    Node() {
        visited = false;
    }
    
    void addEdge(int adjacentNodeID) {
        adjacentNodeIDs.insert(adjacentNodeID);
    }

    // method for marking if it has been visited
    void markVisited() {
        visited = true;
    }

    // method for checking if it was visited
    bool isVisited() const {
        return visited;
    }

    // method for clearing visited
    void clearVisited() {
        visited = false;
    }

    // method for getting the adjacency list
    const set<int>& getAdjacentNodes() const {
        return adjacentNodeIDs;
    }

    // toString function, prints the node IDs in the 'adjacent node IDs' set as a comma separated list. 
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