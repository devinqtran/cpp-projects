#include <iostream>

struct student
{
    std::string name;
    char gender;
    int age;
    double gpa;
    bool enrolled;

public:
    void printStudent()
    {
    }
};

int main()
{

    student student1;
    student1.name = "Spongebob";
    student1.gpa = 3.2;
    student1.enrolled = true;
    student1.gender = 'M';
    student1.age = 21;

    student student2;
    student2.name = "Patrick";
    student2.gpa = 2.0;
    student2.enrolled = false;
    student2.gender = 'M';

    std::cout << student1.name << "\n";
    std::cout << student1.gpa << "\n";
    std::cout << student1.enrolled << "\n";
    std::cout << student1.gender << "\n";
    std::cout << student1.age << "\n";

    std::cout << student2.name << "\n";
    std::cout << student2.gpa << "\n";
    std::cout << student2.enrolled << "\n";
    std::cout << student2.gender << "\n";

    return 0;
}