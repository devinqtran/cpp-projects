#include <iostream>
#include <utility>
#include "Node.h"
#include "Graph.h"
#include "Interpreter.h"

using namespace std;

int main() {

  // predicate names for fake rules
  // first is name for head predicate
  // second is names for body predicates
  pair<string,vector<string>> ruleNames[] = {
    { "A", { "B", "C" } },
    { "B", { "A", "D" } },
    { "B", { "B" } },
    { "E", { "F", "G" } },
    { "E", { "E", "F" } },
  };

  vector<Rule> rules;

  for (auto& rulePair : ruleNames) {
    string headName = rulePair.first;
    Rule rule = Rule(Predicate(headName));
    vector<string> bodyNames = rulePair.second;
    for (auto& bodyName : bodyNames)
      rule.addBodyPredicate(Predicate(bodyName));
    rules.push_back(rule);
  }

  // Call makeGraph using the local 'rules' vector and capture the pair
  pair<Graph, Graph> graphs = Interpreter::makeGraph(rules);
  
  // Extract the individual graphs from the pair
  Graph forwardGraph = graphs.first;
  Graph reverseGraph = graphs.second;

  // Print Forward Graph
  cout << "Dependency Graph\n";
  cout << forwardGraph.toString();

  // Print Reverse Graph
  cout << "\nReverse Dependency Graph\n";
  cout << reverseGraph.toString();

  return 0;
}