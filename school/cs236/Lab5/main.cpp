#include <iostream>
#include "Node.h"
#include "Graph.h"

using namespace std;

// test Node.h
// int main() {
//   Node node;
//   node.addEdge(4);
//   node.addEdge(8);
//   node.addEdge(2);
//   cout << node.toString() << endl;
// }

int main() {
  Graph graph(3);
  graph.addEdge(1,2);
  graph.addEdge(1,0);
  graph.addEdge(0,1);
  graph.addEdge(1,1);
  cout << graph.toString();
}