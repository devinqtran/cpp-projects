#include <random>
#include <iostream>
#include <string>
#include <vector>

int main() {
    // 1. Obtain a random seed from the hardware
    std::random_device rd;
    
    // 2. Initialize the Standard Mersenne Twister engine with the seed
    std::mt19937 gen(rd());
    
    // 3. Define the distributions (the "shape" of the randomness)
    std::uniform_int_distribution<int> d100(1, 100);       // Closed range [1, 100]
    std::uniform_real_distribution<double> percent(0.0, 1.0); // Open range [0.0, 1.0)

    std::cout << "Rolling a D100: " << d100(gen) << "\n";
    std::cout << "Random percentage: " << (percent(gen) * 100) << "%\n";

    return 0;
}