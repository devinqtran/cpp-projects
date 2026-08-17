
// A graph plots a series of connections between nodes (vertices), these vertices are connected together by edges
// Purpose of a BST is to arrange/sort nodes into order
// Graph plots connections between nodes and direction to indicate pathways
// Graph edges can be assigned weight to indicate a length of time in units to get between nodes (a->b)
// Used for mapping and networking applications, shortest path (Djikstra's algorithm or A*)

// Store weightings for edges in an adjacency matrix

// Vertices stored within an array
// Edges stored in a two dimensional array
// Functions for adding edges and vertices
// Function to get a vertex's adjacent vertices
// Vertex is represented by the location class

#include <iostream>
#include <vector>

using namespace std;

// Adjacency Matrix Representation
int main() {
    int n, m;
    cin >> n >> m;

    // Initialize an (n+1) x (n+1) matrix with zeros
    vector<vector<int>> matrix(n + 1, vector<int>(n + 1, 0));

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        
        // For an Undirected Graph
        matrix[u][v] = 1;
        matrix[v][u] = 1;
    }

    return 0;
}
