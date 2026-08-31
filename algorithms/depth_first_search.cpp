// Recursive implementation of a depth-first-search using a vector of vectors as an adjacency list
#include <iostream>
#include <vector>

class Graph {
    int numVertices; // total number of nodes(vertices) in the graph
    std::vector<std::vector<int>> adjList; // adjacency list represented as a vector of vectors

    // Helper function for recursion
    void dfsRecursive(int vertex, std::vector<bool>& visited) {
        // Mark the current node as visited and print it
        visited[vertex] = true; // mark current vertex as visited
        std::cout << vertex << " "; // print the current vertex to show traversal order

        // Recur for all the vertices adjacent to this vertex
        for (int neighbor : adjList[vertex]) { // loop through every neighbor connected to current vertex
            if (!visited[neighbor]) { // if the neighbor has not been visited it pauses and calls dfsRecursive on that neighbor
                dfsRecursive(neighbor, visited);
            }
        }
    }

public:
    // constructor for initializing the graph, sets total number of vertices 
    Graph(int vertices) {
        numVertices = vertices;
        adjList.resize(vertices);
    }

    // Function to add an undirected edge
    void addEdge(int src, int dest) {
        adjList[src].push_back(dest);
        adjList[dest].push_back(src); // Remove this line for a Directed Graph
    }

    // Main DFS function
    void DFS(int startVertex) {
        std::vector<bool> visited(numVertices, false);
        dfsRecursive(startVertex, visited);
    }
};

int main() {
    // creates a graph g with 5 vertices numbered 0-4
    Graph g(5); 
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);

    std::cout << "Recursive DFS starting from vertex 0:\n";
    g.DFS(0);

    return 0;
}