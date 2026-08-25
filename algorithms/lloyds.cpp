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

    std::vector<int> assignments(n, -1); // create a new array assignments for n data points filled with -1

    // loop until convergence or max iterations
    for (int iter = 0; iter < maxIter; ++iter) {
        // 2. Assign each point to nearest centroid
        
        for (int i = 0; i < n; ++i) {
            double bestDist = std::numeric_limits<double>::max(); // set bestDist to the maximum number in C++ guarantees next num will be smaller
            int bestIdx = 0; // hold the index of the closest centroid for current point
            for (int j = 0; j < k; ++j) { // loop through all k centroids to find which is closest to current point i
                double d = distSq(points[i], centroids[j]); // calculate the squared distance between point i and centroid j
                if (d < bestDist) { // check if d is smaller than bestDist and update accordingly
                    bestDist = d;
                    bestIdx = j;
                }
            }
            assignments[i] = bestIdx;
        }

        // 3. Recompute centroids as the mean of each cluster
        std::vector<Point> newCentroids(k, {0.0, 0.0}); // temporary array for storing the newcentroids of count k and xy 0.0
        std::vector<int> counts(k, 0); // array to count how many points in each cluster

        for (int i = 0; i < n; ++i) { // adds the point's X and Y coordinates to running total for that cluster in newCentroids
            int c = assignments[i]; 
            newCentroids[c].x += points[i].x;
            newCentroids[c].y += points[i].y;
            counts[c]++;
        }
        for (int j = 0; j < k; ++j) { // loop through the k clusters
            if (counts[j] > 0) { // if a cluster has points in it
                newCentroids[j].x /= counts[j]; // divide sum of X + Y by number of points (counts[j])
                newCentroids[j].y /= counts[j];
            }
        }

        // 4. Check for convergence: did any centroid move beyond tolerance value?
        double maxShift = 0.0; // variable for tracking the maximum distance any single centroid moved
        for (int j = 0; j < k; ++j)
            maxShift = std::max(maxShift, distSq(centroids[j], newCentroids[j])); // calculates how far each centroid moved from centroids[j] to newCentroids[j]

        centroids = newCentroids; // overwrite old centroids with the newly calculated ones

        if (maxShift < tolerance * tolerance) { // check if the maximum distance any centroid moved is smaller than the tolerance squared
            std::cout << "Converged after " << iter + 1 << " iterations.\n"; // if it barely moved then the algorithm has found stable clusters
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