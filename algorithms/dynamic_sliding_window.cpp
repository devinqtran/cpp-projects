#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int lengthOfLongestSubstring(std::string s) {
    vector<int> charMap(256, 0); // track the frequency of characters
    int left = 0, maxLength = 0;

    for (int right = 0; right < s.length(); ++right) {
        char currentChar = s[right];
        charMap[currentChar]++;

        // If the character count is more than 1, shrink the window from the left
        while (charMap[currentChar] > 1) {
            charMap[s[left]]--;
            left++;
        }

        // Update the maximum length of substring found so far
        maxLength = max(maxLength, right - left + 1);
    }
    return maxLength;
}

int main() {
    std::string s = "abcabcbb";
    std::cout << "Length of longest substring without repeating characters: " << lengthOfLongestSubstring(s) << "\n";
    // Output: 3 (from substring "abc")
    return 0;
}