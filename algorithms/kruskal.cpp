// Kruskal's Algorithm for Minimum Spanning Tree

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an edge
struct Edge {
    int u, v, weight;
    // Overload the < operator so we can easily sort edges by weight
    bool operator<(Edge const& other) {
        return weight < other.weight;
    }
};

// DSU (Disjoint Set Union) Structure
struct DSU {
    vector<int> parent;
    vector<int> rank; // Used to keep the tree flat for efficiency

    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        // Initially, every vertex is its own parent (its own set)
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    // Find the representative of the set that 'i' belongs to
    // Uses path compression for faster future lookups
    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]); 
    }

    // Unites the sets containing 'i' and 'j'
    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);

        if (root_i != root_j) {
            // Union by rank: attach the smaller tree to the root of the larger tree
            if (rank[root_i] < rank[root_j]) {
                parent[root_i] = root_j;
            } else if (rank[root_i] > rank[root_j]) {
                parent[root_j] = root_i;
            } else {
                parent[root_j] = root_i;
                rank[root_i]++;
            }
        }
    }
};

int main() {
    int n = 5; // Number of vertices (0 to 4)
    vector<Edge> edges = {
        {0, 1, 10}, {0, 2, 6}, {0, 3, 5}, 
        {1, 3, 15}, {2, 3, 4}
    };

    int cost = 0; // Total weight of the MST
    vector<Edge> result; // Edges included in the MST
    
    // Step 1: Sort edges by weight
    sort(edges.begin(), edges.end());

    // Initialize DSU for 'n' vertices
    DSU dsu(n);

    // Step 2 & 3: Iterate through sorted edges
    for (Edge e : edges) {
        // If u and v belong to different sets, adding the edge won't cause a cycle
        if (dsu.find(e.u) != dsu.find(e.v)) {
            cost += e.weight;      // Add to total cost
            result.push_back(e);   // Add edge to our result list
            dsu.unite(e.u, e.v);   // Merge the sets
        }
    }

    // Output the results
    cout << "Edges in the Minimum Spanning Tree:" << endl;
    for (Edge e : result) {
        cout << e.u << " - " << e.v << " : Weight " << e.weight << endl;
    }
    cout << "Total Cost: " << cost << endl;

    return 0;
}