#include <iostream>
#include <queue>

int main() {
    // Creates a Max-Heap by default
    std::priority_queue<int> maxHeap;

    // Insert elements - O(log N)
    maxHeap.push(10);
    maxHeap.push(30);
    maxHeap.push(20);

    // Access top element (largest) - O(1)
    std::cout << "Top element: " << maxHeap.top() << std::endl; // Outputs 30

    // Remove top element - O(log N)
    maxHeap.pop(); 
    
    return 0;
}