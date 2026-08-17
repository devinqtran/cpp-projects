#include <iostream>
#include <vector>
#include <iomanip>

// Define a large value to represent infinity for unconnected edges.
// We use 1e9 instead of INT_MAX to safely prevent integer overflow during addition.
const int INF = 1e9;

/**
 * Executes the Floyd-Warshall algorithm to find all-pairs shortest paths.
 * @param graph A 2D adjacency matrix representing edge weights.
 */

// input a 2d vector of ints named graph
void floydWarshall(std::vector<std::vector<int>> &graph)
{
    int V = graph.size();

    // Print the size of V
    std::cout << V << "\n";

    // Initialize the distance matrix with the input graph weights
    std::vector<std::vector<int>> dist = graph;

    // Outer loop selects the intermediate vertex 'k'
    for (int k = 0; k < V; ++k)
    {
        // Inner loops select the source vertex 'i' and destination vertex 'j'
        for (int i = 0; i < V; ++i)
        {
            for (int j = 0; j < V; ++j)
            {
                // If vertex k is on the shortest path from i to j, update the value of dist[i][j]
                if (dist[i][k] != INF && dist[k][j] != INF)
                {
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // Print the final calculated distance matrix
    std::cout << "Shortest distance matrix between every pair of vertices:\n";
    for (int i = 0; i < V; ++i)
    {
        for (int j = 0; j < V; ++j)
        {
            if (dist[i][j] == INF)
            {
                std::cout << std::setw(5) << "INF";
            }
            else
            {
                std::cout << std::setw(5) << dist[i][j];
            }
        }
        std::cout << "\n";
    }
}

int main()
{
    /*
    Example Weighted Graph:
         (4)  5      (1)
          0 -----> 1

          |      / |
      (2) |    /   | (3)
          v  v     v
          3 -----> 2
             1
    */
    int V = 4;
    std::vector<std::vector<int>> graph = {
        {0, 5, INF, 4},
        {INF, 0, 3, INF},
        {INF, INF, 0, INF},
        {INF, 1, 2, 0}};

    floydWarshall(graph);

    return 0;
}