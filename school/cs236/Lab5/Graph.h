#pragma once
#include <map>
#include "Node.h"
#include <string>
#include <sstream>

using namespace std;

// A Graph holds a map from node IDs (ints) to Nodes
class Graph {
private:
    map<int, Node> nodes;

public:

    // Constructor - passed a number of nodes to create in the graph
    Graph(int size) {
        for (int nodeID = 0; nodeID < size; nodeID++) {
            nodes[nodeID] = Node();
        }
    }

    // Takes the 'fromNode' in the map and calls 'addEdge' on that Node to add the 'toNodeID' to the set of adjacent node IDs in that Node object (edge)
    void addEdge(int fromNodeID, int toNodeID) {
        nodes[fromNodeID].addEdge(toNodeID);
    }

    // R, nodeID, : , Node.toString() 

    // The 'toString' function prints each Node in the Graph on a separate line.
    // For each Node, print the node ID for the Node (print the letter R before the ID), 
    // followed by a colon (:) and the result of the 'toString' function on the Node.
    string toString() const {
        stringstream out;

        for (auto& pair: nodes) {
            int nodeID = pair.first;
            Node node = pair.second;

            out << "R" << nodeID << ":" << node.toString() << endl;
        }
        return out.str();
    }

};