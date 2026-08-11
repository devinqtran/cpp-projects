#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// Copy
string str = "Devin";
char *p = &str.at(0);

vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
vector<int> nums2(10, 0); // creates vector nums2 of size 10 with default val 0

extern float pow(float, int);

int pow(int, int);
double pow(double, double);

float pow(float x, int n)
{
    if (n < 0)
    {
        cout << "Sorry, negative exponent to pow()\n";
    }
    switch (n)
    {
    case 0:
        return 1;
    case 1:
        return x;
    default:
        return x * pow(x, n - 1);
    }
}

void swap(int *p, int *q)
{
    int t = *p;
    *p = *q;
    *q = t;
}

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

    float f;
    int i;
    cout << "Enter float: " << "\n";
    cin >> f;
    cout << "Enter int: " << "\n";
    cin >> i;

    cout << pow(f, i) << "\n";

    return 0;
}