#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Copy
string str = "Devin";
char *p = &str.at(0);
vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
vector<int> nums2(10, 0); // creates vector nums2 of size 10 with default val 0

int main()
{
    cout << p << "\n";

    for (int i = 0; i < 10; i++)
        nums2[i] = nums[i];
    cout << "Copied nums to nums2 " << nums2[0] << "\n";
    for (const auto &num : nums2)
    {
        cout << num << "\n";
    }

    return 0;
}