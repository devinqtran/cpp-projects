#include <iostream>
#include <string>
#include <random>

using namespace std;

int main()
{

    // Obtain random seed from hardware
    std::random_device rd;

    // Initialize standard mersenne_twister_engine using seed
    std::mt19937 gen(rd());

    // Define financial/numeric range [inclusive, inclusive]
    std::uniform_int_distribution<int> distrib(1, 10);

    // Generate random number
    int random_num = distrib(gen);

    cout << "Guess the number!\n";

    int my_number;

    cout << "Enter a number: \n";
    cin >> my_number;

    while (my_number != random_num)
    {
        cout << "Sorry, guess again!\n";
        cin >> my_number;
    }

    cout << "Congratulations, you guessed it!\n";
    cout << "The correct number is: " << random_num << "\n";

    return 0;
}