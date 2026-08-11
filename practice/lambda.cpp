#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> numbers = {5, 2, 9, 1, 5, 6};

    // Sorting in descending order using an inline custom comparator
    std::sort(numbers.begin(), numbers.end(), [](int a, int b)
              { return a > b; });

    // Counting numbers greater than a threshold using a captured variable
    int threshold = 4;
    auto matches = std::count_if(numbers.begin(), numbers.end(), [threshold](int n)
                                 { return n > threshold; });

    std::cout << "Count above " << threshold << ": " << matches << "\n";

    std::vector<int> numbers1 = {1, 4, 6, 7, 2, 3, 5, 9, 8};
    

}