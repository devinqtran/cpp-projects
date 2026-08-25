#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <random>
#include <algorithm>
#include <iomanip>
#include <limits>

// Plain Old Data (POD) representation of spatial points
struct Point {
    int64_t oid;
    double x;
    double y;
};

struct Facility {
    int id;
    double x;
    double y;
};

struct IterationRecord {
    int iteration;
    std::vector<Facility> facilities;
    double objective;
    std::vector<int> assignments;
    std::vector<size_t> cluster_sizes;
};

// Static geometry helper
class GeometryUtils {
public:
    static inline double euclidean_distance(double x1, double y1, double x2, double y2) noexcept {
        const double dx = x2 - x1;
        const double dy = y2 - y1;
        return std::sqrt(dx * dx + dy * dy);
    }
};

// High-performance Lloyd's algorithm engine
class LloydsAlgorithm {
private:
    int num_facilities;
    int max_iterations;
    double convergence_threshold;
    unsigned int random_seed;

public:
    LloydsAlgorithm(int num_facilities, int max_iterations, double convergence_threshold, unsigned int random_seed = 42)
        : num_facilities(num_facilities),
          max_iterations(max_iterations),
          convergence_threshold(convergence_threshold),
          random_seed(random_seed) {}

    std::vector<IterationRecord> run(const std::vector<Point>& points) {
        std::vector<IterationRecord> iteration_history;
        if (points.empty() || num_facilities <= 0 || static_cast<size_t>(num_facilities) > points.size()) {
            return iteration_history;
        }

        // Initialize pseudo-random number generator (mt19937)
        std::mt19937 rng(random_seed);
        std::vector<size_t> indices(points.size());
        std::iota(indices.begin(), indices.end(), 0);
        
        // Reservoir/Fisher-Yates sampling for initial facilities
        std::shuffle(indices.begin(), indices.end(), rng);

        std::vector<Facility> facilities;
        facilities.reserve(num_facilities);
        for (int i = 0; i < num_facilities; ++i) {
            facilities.push_back({i, points[indices[i]].x, points[indices[i]].y});
        }

        std::cout << std::left << std::setw(12) << "Iteration" 
                  << " | " << std::setw(35) << "Objective Function (Total Distance)" << "\n";
        std::cout << std::string(50, '-') << "\n";

        // Pre-allocate assignment buffers to avoid heap reallocations per iteration
        std::vector<int> assignments(points.size(), 0);

        for (int iter = 0; iter < max_iterations; ++iter) {
            double total_dist = 0.0;

            // 1. Assignment Step & Objective Calculation
            for (size_t i = 0; i < points.size(); ++i) {
                double min_dist = std::numeric_limits<double>::infinity();
                int best_facility = 0;

                for (int f = 0; f < num_facilities; ++f) {
                    double dist = GeometryUtils::euclidean_distance(points[i].x, points[i].y, facilities[f].x, facilities[f].y);
                    if (dist < min_dist) {
                        min_dist = dist;
                        best_facility = f;
                    }
                }
                assignments[i] = best_facility;
                total_dist += min_dist;
            }

            // Print iteration metrics
            std::cout << std::left << std::setw(12) << (iter + 1)
                      << " | " << std::fixed << std::setprecision(2) << std::setw(35) << total_dist << "\n";

            // Track cluster sizes
            std::vector<size_t> cluster_sizes(num_facilities, 0);
            for (int a : assignments) {
                cluster_sizes[a]++;
            }

            iteration_history.push_back({
                iter + 1,
                facilities,
                total_dist,
                assignments,
                cluster_sizes
            });

            // 2. Update Step (Centroid calculation)
            // Accumulator vectors for Single-Pass O(N) centroid updates
            std::vector<double> sum_x(num_facilities, 0.0);
            std::vector<double> sum_y(num_facilities, 0.0);
            std::vector<size_t> count(num_facilities, 0);

            for (size_t i = 0; i < points.size(); ++i) {
                int cluster = assignments[i];
                sum_x[cluster] += points[i].x;
                sum_y[cluster] += points[i].y;
                count[cluster]++;
            }

            double max_move = 0.0;
            std::vector<Facility> new_facilities = facilities;

            for (int f = 0; f < num_facilities; ++f) {
                if (count[f] > 0) {
                    double new_x = sum_x[f] / count[f];
                    double new_y = sum_y[f] / count[f];
                    double move = GeometryUtils::euclidean_distance(facilities[f].x, facilities[f].y, new_x, new_y);
                    max_move = std::max(max_move, move);
                    new_facilities[f] = {f, new_x, new_y};
                }
            }

            facilities = std::move(new_facilities);

            // Convergence check
            if (max_move < convergence_threshold) {
                std::cout << "\nConverged! Max movement (" << std::fixed << std::setprecision(4) 
                          << max_move << ") is below threshold.\n";
                break;
            }
        }

        return iteration_history;
    }
};

// Driver entry point
int main() {
    // Generate synthetic point dataset for verification
    constexpr size_t NUM_POINTS = 50000;
    std::vector<Point> points;
    points.reserve(NUM_POINTS);

    std::mt19937 gen(1337);
    std::uniform_real_distribution<double> dist_xy(0.0, 10000.0);

    for (size_t i = 0; i < NUM_POINTS; ++i) {
        points.push_back({static_cast<int64_t>(i + 1), dist_xy(gen), dist_xy(gen)});
    }

    // Parameters
    int num_facilities = 15;
    int max_iterations = 100;
    double convergence_threshold = 0.001;
    unsigned int random_seed = 42;

    LloydsAlgorithm engine(num_facilities, max_iterations, convergence_threshold, random_seed);
    std::vector<IterationRecord> history = engine.run(points);

    if (!history.empty()) {
        double initial_obj = history.front().objective;
        double final_obj = history.back().objective;
        double improvement = ((initial_obj - final_obj) / initial_obj) * 100.0;

        std::cout << std::string(50, '-') << "\n";
        std::cout << "SUMMARY STATISTICS\n";
        std::cout << "Initial Distance: " << std::fixed << std::setprecision(2) << initial_obj << "\n";
        std::cout << "Final Distance:   " << final_obj << "\n";
        std::cout << "Total Improvement: " << std::setprecision(2) << improvement << "%\n";
        std::cout << std::string(50, '-') << "\n";
    }

    return 0;
}