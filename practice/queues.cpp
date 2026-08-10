#include <iostream>
#include <queue> // Required header

int main()
{
    // Create a queue that stores integers
    std::queue<int> taskQueue;

    // Add elements to the back
    taskQueue.push(10);
    taskQueue.push(20);
    taskQueue.push(30);

    // Check size and state
    std::cout << "Queue size: " << taskQueue.size() << "\n"; // Outputs 3

    // Access front and back elements
    std::cout << "Front element: " << taskQueue.front() << "\n"; // Outputs 10
    std::cout << "Back element: " << taskQueue.back() << "\n";   // Outputs 30

    // Process and remove the front element
    taskQueue.pop();

    // Look at the new front element
    std::cout << "New front element: " << taskQueue.front() << "\n"; // Outputs 20

    // Safely empty the queue using a loop
    while (!taskQueue.empty())
    {
        std::cout << "Removing: " << taskQueue.front() << "\n";
        taskQueue.pop();
    }

    return 0;
}