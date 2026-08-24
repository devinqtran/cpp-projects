#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Tuple.h"
#include "Scheme.h"
#include "Relation.h"

int main() {

  vector<string> names = { "ID", "Name", "Major" };

  Scheme scheme(names);

  Relation relation("student", scheme);

  vector<string> values[] = {
    {"'42'", "'Ann'", "'CS'"},
    {"'32'", "'Bob'", "'CS'"},
    {"'64'", "'Ned'", "'EE'"},
    {"'16'", "'Jim'", "'EE'"},
  };

  for (auto& value : values) {
    Tuple tuple(value);
    cout << tuple.toString(scheme) << endl;
    relation.addTuple(tuple);
  }

  cout << "relation:" << endl;
  cout << relation.toString();

}