#include <iostream>
#include <vector>
#include "..//Project1//Token.h"
#include "..\\Project1\\Scanner.h"
#include "Parser.h"

int main() {

  vector<Token> tokens = {
    Token(ID,"Ned",2),
    Token(LEFT_PAREN,"(",2),
    Token(ID,"Ted",2),
    Token(COMMA,",",2),
    Token(ID,"Zed",2),
    Token(RIGHT_PAREN,")",2),
  };

  Parser parser(tokens);
  parser.parse();

  return 0;

}