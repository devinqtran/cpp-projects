#include <iostream>
#include <future>
#include <thread>
#include <chrono>

// Imagine a game needs to calculate heavy AI movements or load a large 3D model but you do not want the loading screen to freeze
// Use async to perform the heavy math calculations in the background while the main program continues to run

// A "slow" function simulating heavy work (like loading a file or AI math)
int calculate_heavy_math() {
    std::cout << "[Background] Starting heavy math...\n";
    
    // Simulate taking 3 seconds to complete
    std::this_thread::sleep_for(std::chrono::seconds(3));
    
    std::cout << "[Background] Heavy math finished!\n";
    return 42; 
}

int main() {
    std::cout << "[Main] Program started.\n";

    // 1. START THE ASYNC TASK
    // We tell C++ to run 'calculate_heavy_math' in the background.
    // It returns a std::future, which is our "restaurant pager".
    std::future<int> math_result = std::async(std::launch::async, calculate_heavy_math);

    // 2. DO OTHER WORK
    // Because the math is running asynchronously, the main program doesn't stop.
    for (int i = 0; i < 3; i++) {
        std::cout << "[Main] Doing other work while waiting (frame " << i << ")...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // 3. GET THE RESULT
    // Now we actually need the answer. Calling .get() will block the main
    // thread ONLY IF the background task hasn't finished yet. 
    std::cout << "[Main] Waiting for the final result...\n";
    int answer = math_result.get(); 

    std::cout << "[Main] The answer is: " << answer << "\n";

    return 0;
}