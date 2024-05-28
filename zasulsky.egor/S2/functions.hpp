#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>
#include <climits>
#include "Queue.hpp"
#include "Stack.hpp"

namespace zasulsky
{
  int getPriority(std::string st);

  bool isOperand(std::string  st);

  Queue <std::string> convertToPostfix(Queue< std::string >& infix);

  long long solvePostfixExpr(Queue< std::string >& q);

  void outputResults(Stack< long long >& results);
}
#endif
