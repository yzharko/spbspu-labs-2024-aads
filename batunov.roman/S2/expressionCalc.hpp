#ifndef EXPRESSION_CALC_HPP
#define EXPRESSION_CALC_HPP
#include <iostream>
#include <string>
#include "stack.hpp"
#include "queue.hpp"

namespace batunov
{
  void readInfixForm(std::istream& input, Queue< std::string >& result);
  void strToQueue(std::string expression, Queue< std::string >& result);
  bool isOperand(std::string symbol);
  bool isOperator(std::string c);
  int precendence(std::string c);
  void infixToPostfix(Queue< std::string >& expression, Queue< std::string >& result);
  long long countOperation(long long fval, long long sval, std::string operation);
  long long calculateExpr(Queue< std::string >& expression);
  void formResultStack(Queue< std::string >& expressions, Stack< long long >& resultStack);
}

#endif
