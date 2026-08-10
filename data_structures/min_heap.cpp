#include <iostream>
#include <queue>
#include <vector>

int main()
{
    // Syntax: priority_queue<Type, UnderlyingContainer, Comparator>
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

    minHeap.push(10);
    minHeap.push(30);
    minHeap.push(20);

    std::cout << "Top element: " << minHeap.top() << std::endl; // Outputs 10
    return 0;
}