#pragma once
#include <set>

using namespace std;

class Node {
private:
    set<int> adjacentNodeIDs;

public:
    
    void addEdge(int adjacentNodeID) {
        adjacentNodeIDs.insert(adjacentNodeID);
    }

};