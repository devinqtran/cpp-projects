#include <iostream>
#include <vector>

class Graph {
private:
    int numVertices;
    // An array of vectors to store the adjacency list
    std::vector<std::vector<int>> adjList;

public:
    // Constructor
    Graph(int vertices) {
        numVertices = vertices;
        adjList.resize(vertices);
    }

    // Add an undirected edge between vertex u and vertex v
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // Remove this line if the graph is Directed
    }

    // Print the graph representation
    void printGraph() {
        for (int i = 0; i < numVertices; ++i) {
            std::cout << "Vertex " << i << ":";
            for (int neighbor : adjList[i]) {
                std::cout << " -> " << neighbor;
            }
            std::cout << "\n";
        }
    }
};

int main() {
    // Create a graph with 5 vertices (0 to 4)
    Graph g(5);

    // Add edges
    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(3, 4);

    // Display the graph
    g.printGraph();

    return 0;
}
