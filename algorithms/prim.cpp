// Prim's Algorithm for Minimum Spanning Tree

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Structure to represent a destination vertex and the edge weight
struct Edge
{
    int to, weight;
};

// Structure for the Priority Queue
struct QueueNode
{
    int weight, current_vertex, parent_vertex;

    // C++ priority_queue is a Max-Heap by default.
    // By inverting the < operator, we force it to act as a Min-Heap.
    bool operator<(const QueueNode &other) const
    {
        return weight > other.weight;
    }
};

int main()
{
    int V = 5; // Number of vertices (0 to 4)

    // Adjacency list representation of the graph
    vector<vector<Edge>> adj(V);

    // Helper lambda function to add undirected edges
    auto addEdge = [&](int u, int v, int weight)
    {
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});
    };

    // Recreating the same graph used in the Kruskal's example
    addEdge(0, 1, 10);
    addEdge(0, 2, 6);
    addEdge(0, 3, 5);
    addEdge(1, 3, 15);
    addEdge(2, 3, 4);

    // Setup for Prim's Algorithm
    priority_queue<QueueNode> pq;
    vector<bool> inMST(V, false); // Keeps track of vertices already in the tree
    int total_cost = 0;

    // Start the algorithm from vertex 0
    // weight = 0, current = 0, parent = -1 (no parent)
    pq.push({0, 0, -1});

    cout << "Edges in the Minimum Spanning Tree:" << endl;

    while (!pq.empty())
    {
        // 1. Get the cheapest edge connected to our tree
        QueueNode curr = pq.top();
        pq.pop();

        int u = curr.current_vertex;

        // 2. Check for cycles: if the vertex is already in the MST, skip it
        if (inMST[u])
            continue;

        // 3. Mark the vertex as part of the MST
        inMST[u] = true;
        total_cost += curr.weight;

        // If it's not the starting node, print the edge that got us here
        if (curr.parent_vertex != -1)
        {
            cout << curr.parent_vertex << " - " << u << " : Weight " << curr.weight << endl;
        }

        // 4. Look at all neighbors of the newly added vertex
        for (Edge e : adj[u])
        {
            // If the neighbor isn't in the MST yet, throw the potential edge into the queue
            if (!inMST[e.to])
            {
                pq.push({e.weight, e.to, u});
            }
        }
    }

    cout << "Total Cost: " << total_cost << endl;

    return 0;
}