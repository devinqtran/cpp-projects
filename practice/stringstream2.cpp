#include <iostream>
#include <sstream>
#include <string>

/*

*/

using namespace std;

int main()
{

    string grades = "95,85,75,92,88,96,81";
    string grade;
    int totalGrade = 0;
    int numGrade = 0;

    stringstream ss;
    ss.str(grades); // pass the string called grades into the stringstream
    // cout << ss.str() << endl; // prints the entire string

    // getline(ss, grade, ','); // allows you to pass in another character that acts as a separator
    // cout << grade << endl; // returns just the first number because it stops at ','

    while (getline(ss, grade, ','))
    {
        // cout << grade << endl;
        totalGrade += stoi(grade); // stoi - string to int running total
        numGrade++;
    }

    // clear everything
    ss.str(""); // returns contents of the stream as standard string
    ss.clear();

    // put everything into the string stream
    ss << "Average: " << totalGrade / numGrade << endl
       << grades << endl;
    cout << ss.str() << endl;
}