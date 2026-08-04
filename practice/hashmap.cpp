#include <iostream>
#include <unordered_map>
#include <string>

int main()
{
    // 1. Declaration (Key: string, Value: int)
    std::unordered_map<std::string, int> inventory;

    // 2. Insertion
    inventory["apples"] = 50;          // Using square brackets
    inventory.insert({"bananas", 30}); // Using insert() with a pair

    // 3. Accessing Values
    std::cout << "Apples: " << inventory["apples"] << std::endl;

    // 4. Checking if a key exists
    std::string search_key = "oranges";
    if (inventory.find(search_key) != inventory.end())
    {
        std::cout << "Found " << search_key << std::endl;
    }
    else
    {
        std::cout << search_key << " not found!" << std::endl;
    }

    // 5. Deletion
    inventory.erase("bananas");

    // 6. Iterating through the map
    for (const auto &pair : inventory)
    {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    return 0;
}