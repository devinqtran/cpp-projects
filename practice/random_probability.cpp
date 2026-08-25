#include <iostream>
#include <random>
#include <map>
#include <iomanip>

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());

    // --- Bernoulli (Coin Flips / Procs) ---
    // 25% chance to score a critical hit
    std::bernoulli_distribution crit_chance(0.25);
    
    std::cout << "Attacking 5 times (25% crit chance):\n";
    for(int i = 0; i < 5; ++i) {
        if (crit_chance(gen)) {
            std::cout << "Hit " << i+1 << ": CRITICAL!\n";
        } else {
            std::cout << "Hit " << i+1 << ": Normal damage.\n";
        }
    }
    std::cout << "\n";

    // --- Normal (Gaussian / Bell Curve) ---
    // Mean of 50.0, Standard Deviation of 10.0
    std::normal_distribution<double> bell_curve(50.0, 10.0);
    
    std::map<int, int> histogram;
    for(int i = 0; i < 10000; ++i) {
        // Round the double to the nearest int to build our histogram buckets
        int val = std::round(bell_curve(gen));
        histogram[val]++;
    }

    std::cout << "Normal Distribution Histogram (Mean 50, StdDev 10):\n";
    // Print a slice of the bell curve (between 30 and 70)
    for(int i = 30; i <= 70; i += 5) {
        std::cout << std::setw(2) << i << "-" << (i+4) << ": ";
        // Scale the visual output
        std::cout << std::string(histogram[i] / 30, '*') << "\n";
    }

    return 0;
}