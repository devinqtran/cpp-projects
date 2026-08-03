#include <iostream>

template <typename T>
T get_max(T a, T b)
{
    return (a > b) ? a : b;
}

template <typename T>
T get_min(T a, T b)
{
    return (a < b) ? a : b;
}
int main()
{
    std::cout << get_max(5, 10) << "\n";
    std::cout << get_max<double>(5.5, 2.1) << "\n";
    std::cout << get_max<char>('A', 'B') << "\n";
    std::cout << get_min(5, 10) << "\n";
    std::cout << get_min<double>(5.5, 2.1) << "\n";
    std::cout << get_min<char>('A', 'B') << "\n";

    return 0;
}