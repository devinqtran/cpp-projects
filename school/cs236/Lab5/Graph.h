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

    // method for clearing flags to false
    void clearFlags() {
        for (auto& pair : nodes) {
            pair.second.clearVisited();
        }
    }

    // getter method for getting the nodes map
    map<int, Node>& getNodes() {
        return nodes;
    }

    // R, nodeID, : , Node.toString() 

    // The 'toString' function prints each Node in the Graph on a separate line.
    // For each Node, print the node ID for the Node (print the letter R before the ID), 
    // followed by a colon (:) and the result of the 'toString' function on the Node.
    string toString() const {
        stringstream out;

        for (const auto& pair: nodes) {
            int nodeID = pair.first;
            Node node = pair.second;

            out << "R" << nodeID << ":" << node.toString() << endl;
        }
        return out.str();
    }

};

/*
    TO DO:
    1. Build the dependency graph and the reverse dependency graph
    2. Run DFS-Forest (in regular numeric order) on the reverse dependency graph to get the post-order
    3. Run DFS-Forest (in reverse post-order) on the forward dependency graph to find the strongly connected components
    4. Evaluate the rules in each component

    Suggestions:
    - Create a graph class
    - Adjacency list implementation (not adjacency matrix)
    - Graph stores all edges/adjacencies as a map<int,set<int>>
    - Also store a boolean 'visited' flag for each node
    - Make all of the functions dfs, dfsForest, etc. in the graph class
    - You should have a two different dfsForest functions: one for finding the post-order, and one for finding SCCs

*/