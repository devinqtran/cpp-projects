#include <iostream>
#include <vector>
#include <string>
#include "Relation.h"
#include "Tuple.h"
#include "Scheme.h"

using namespace std;

int main()
{

    vector<string> names = {"ID", "Name", "Major"};
    Scheme scheme(names);
    Relation relation("student", scheme);

    vector<string> values[] = {
        {"'42'", "'Ann'", "'CS'"},
        {"'32'", "'Bob'", "'CS'"},
        {"'64'", "'Ned'", "'EE'"},
        {"'16'", "'Jim'", "'EE'"},
        {"'99'", "'99'", "'CS'"} // Added to test Select 2 (ID == Name)
    };

    cout << "--- Adding Tuples ---" << endl;
    for (auto &value : values)
    {
        Tuple tuple(value);
        cout << tuple.toString(scheme) << endl;
        relation.addTuple(tuple);
    }

    // Original Relation
    cout << "\n--- Original Relation ---" << endl;
    cout << relation.toString();

    // Relation Select 1 (Constant Match)
    // Find all rows where Major (index 2) is 'CS'
    Relation select1Result = relation.select(2, "'CS'");
    cout << "\n--- Select 1: Major == 'CS' ---" << endl;
    cout << select1Result.toString();

    // Relation Select 2 (Variable Match)
    // Find all rows where ID (index 0) matches Name (index 1)
    Relation select2Result = relation.select(0, 1);
    cout << "\n--- Select 2: ID == Name ---" << endl;
    cout << select2Result.toString();

    // Relation Project
    // Keep only the Name and Major columns (indices 1 and 2) from Select 1 result
    vector<int> columnsToKeep = {1, 2};
    Relation projectResult = select1Result.project(columnsToKeep);
    cout << "\n--- Project: Keep Name and Major (from Select 1) ---" << endl;
    cout << projectResult.toString();

    // Relation Rename
    // Rename the headers of Project result
    vector<string> newHeaders = {"StudentName", "StudentField"};
    Relation renameResult = projectResult.rename(newHeaders);
    cout << "\n--- Rename: Headers to 'StudentName' and 'StudentField' ---" << endl;
    cout << renameResult.toString();

    return 0;
}