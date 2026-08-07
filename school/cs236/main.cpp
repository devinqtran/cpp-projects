#include <iostream>
#include "Token.h"
#include "Scanner.h"

int main() {

  Scanner s = Scanner("'abc',");
  Token t = s.scanToken();
  while (t.getType() != END) {
      cout << t.toString() << endl;
      t = s.scanToken();
  }
  cout << t.toString() << endl;
}