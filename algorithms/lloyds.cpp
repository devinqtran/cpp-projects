/*
    Lloyd's algorithm implementation in C++17
    This implementation is designed for high performance and clarity, leveraging modern C++ features.
    1. Place k seed points (initial centroids) randomly in the space represented by the points.
    2. Assign each point to the nearest seed point (forming Voronoi cells).
    3. Move each centroid to the mean of all points assigned to it.
    4. Repeat steps 2 and 3 until convergence (centroids do not move significantly) or a maximum number of iterations is reached.

    Complexity:
    Each iteration is O(n*k)
    Worst case O(n) iterations needed
    Overall: O(n^2*k)
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <cstdlib>
#include <ctime>

// Data types

struct Point {
    double x, y;
};

// Squared Euclidean distance function (avoids unnecessary square root calculations)
double distSq(const Point& a, const Point& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;;
    return dx * dx + dy * dy;
}

// Algorithm

std::vector<Point> lloyds(
    const std::vector<Point>& points,
    int k,
    int maxIter = 100,
    double tolerance = 1e-6
) {
    int n = points.size();

    // 1. Initialize: choose k random points as the starting centroids
    std::vector<Point> centroids(k); // create a vector of k Point objects called centroids
    std::vector<int> used(n, 0); // create a vector of n points called 'used' and set the initial values to 0 

    // loop exactly k times
    for (int i = 0; i < k; ++i) {
        int idx; // create int idx
        do { idx = rand() % n; } while (used[idx]); // do-while loop that will randomly pick a number and % n ensures that it is between 0 and n-1
        centroids[i] = points[idx]; // after a random index is found, copy data point from original points array at idx in the centroids array
        used[idx] = 1; // mark this index in the used array as 1 so it will not be used again
    }

    std::vector<int> assignments(n, -1);

    for (int iter = 0; iter < maxIter; ++iter) {
        // 2. Assign each point to nearest centroid
        
        for (int i = 0; i < n; ++i) {
            double bestDist = std::numeric_limits<double>::max();
            int bestIdx = 0;
            for (int j = 0; j < k; ++j) {
                double d = distSq(points[i], centroids[j]);
                if (d < bestDist) {
                    bestDist = d;
                    bestIdx = j;
                }
            }
            assignments[i] = bestIdx;
        }

        // 3. Recompute centroids as the mean of each cluster
        std::vector<Point> newCentroids(k, {0.0, 0.0});
        std::vector<int> counts(k, 0);

        for (int i = 0; i < n; ++i) {
            int c = assignments[i];
            newCentroids[c].x += points[i].x;
            newCentroids[c].y += points[i].y;
            counts[c]++;
        }
        for (int j = 0; j < k; ++j) {
            if (counts[j] > 0) {
                newCentroids[j].x /= counts[j];
                newCentroids[j].y /= counts[j];
            }
            // If a cluster is empty, keep the old centroid in place
            // (or re-initialize — see note below)
        }

        // 4. Check for convergence: did any centroid move beyond tolerance value?
        double maxShift = 0.0;
        for (int j = 0; j < k; ++j)
            maxShift = std::max(maxShift, distSq(centroids[j], newCentroids[j]));

        centroids = newCentroids;

        if (maxShift < tolerance * tolerance) {
            std::cout << "Converged after " << iter + 1 << " iterations.\n";
            break;
        }
    }
    return centroids;
}

// Usage

int main() {
    srand(42);

    // Fake dataset: two loose blobs
    std::vector<Point> points = {
        {1.0,1.1},{1.2,0.9},{0.8,1.3},{1.1,1.0},{1.3,1.2},
        {5.0,5.1},{5.2,4.9},{4.8,5.3},{5.1,5.0},{5.3,5.2},
    };

    int k = 2;
    auto centroids = lloyds(points, k);

    std::cout << "Final centroids:\n";
    for (int j = 0; j < k; ++j)
        std::cout << "  Cluster " << j << ": ("
                  << centroids[j].x << ", " << centroids[j].y << ")\n";

    return 0;
}