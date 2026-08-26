#include <iostream>
#include "Relation.h"
#include "Tuple.h"
#include "Scheme.h"

using namespace std;

// TEST
int main() {
    // 1. Set up the Student Relation
    Relation studentRelation("students", Scheme( {"ID", "Name", "Major"} ));
    vector<string> studentValues[] = {
        {"'42'", "'Ann'", "'CS'"},
        {"'64'", "'Ned'", "'EE'"},
    };
    for (auto& value : studentValues) {
        studentRelation.addTuple(Tuple(value));
    }

    // 2. Set up the Course Relation
    Relation courseRelation("courses", Scheme( {"ID", "Course"} ));
    vector<string> courseValues[] = {
        {"'42'", "'CS 100'"},
        {"'32'", "'CS 232'"},
    };
    for (auto& value : courseValues) {
        courseRelation.addTuple(Tuple(value));
    }

    // 3. Print original relations
    cout << "--- Student Relation ---" << endl;
    cout << studentRelation.toString() << endl;

    cout << "--- Course Relation ---" << endl;
    cout << courseRelation.toString() << endl;

    // 4. Perform the join and save the result
    Relation result = studentRelation.join(courseRelation);

    // 5. Print the resulting joined relation
    cout << "--- Joined Result ---" << endl;
    
    // Print the new scheme to verify joinSchemes worked
    cout << "Scheme: ";
    for (unsigned i = 0; i < result.getScheme().size(); i++) {
        cout << result.getScheme().at(i) << " ";
    }
    cout << "\n\nTuples:\n";
    
    // Print the tuples to verify joinTuples and joinable worked
    cout << result.toString() << endl;

    return 0;
}