#ifndef PARSER_HPP
#define PARSER_HPP
#include <fstream>
#include <string>
#include <climits>
#ifndef PARSER_HPP
#define PARSER_HPP
#include <fstream>
#include <string>
#include <climits>
#include <stdexcept>
#include "Queue.hpp"
#include "Stack.hpp"

namespace zasulsky
{
  class Parser
  {
  public:
    Parser(std::string  toparse);
    std::string operator ()();

  private:
    std::string parsable_;
    size_t current_;
  };

  int getPriority(std::string st);

  bool isOperand(std::string  st);

  Queue <std::string> convertToPostfix(Queue< std::string >& infix);

  long long solvePostfixExpr(Queue< std::string >& q);

  void outputResults(Stack< long long >& results);
}

#endif
