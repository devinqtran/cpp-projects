#include <iostream>
#include <random>
#include <vector>
#include <string>

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());

    // Item pool we want to draw from
    std::vector<std::string> loot_table = {
        "Common Sword",   // Index 0
        "Uncommon Shield",// Index 1
        "Rare Helmet",    // Index 2
        "Epic Armor"      // Index 3
    };

    // The weights map directly to the indices of the loot_table above.
    // 70% Common, 20% Uncommon, 9% Rare, 1% Epic
    std::discrete_distribution<int> loot_dist({70.0, 20.0, 9.0, 1.0});

    std::cout << "Opening 10 loot crates:\n";
    for(int i = 0; i < 10; ++i) {
        int drawn_index = loot_dist(gen);
        std::cout << "Crate " << i+1 << ": " << loot_table[drawn_index] << "\n";
    }

    return 0;
}