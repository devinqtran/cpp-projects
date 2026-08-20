#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
    int numStudents = 6;
    int totalGrade = 0;

    ifstream myFile("C:\\Users\\devin\\OneDrive\\Desktop\\cpp-projects\\practice\\student-grades.csv");
    if (myFile.is_open())
    {
        string line;
        while(getline(myFile, line)) {
            // cout << line << endl; // print each line from the csv

            stringstream ss(line); // create a new stringstream ss using the line

            // parse student
            string student;
            getline(ss, student, ','); 
            cout << student << " ";

            // parse grade
            string grade;
            getline(ss, grade, ',');
            cout << grade << endl;
            totalGrade += stoi(grade);
        }
        cout << totalGrade/numStudents << "\n";
    }

    myFile.close();
}