#include <iostream>
#include <string>
#include "InfixExpression.hpp"
sadofeva::InfixExpression::InfixExpression(std::istream & in):
  eparts_{}
{
  while (in && !in.eof() && (in >> std::noskipws).peek() != '\n' && in && !in.eof())
  {
    eparts_.push(ExpressionPart(in >> std::ws));
  }
}

const sadofeva::ExpressionPart & sadofeva::InfixExpression::getNextExpressionPart() const
{
  return eparts_.next();
}

void sadofeva::InfixExpression::drop()
{
  eparts_.drop();
}

bool sadofeva::InfixExpression::empty() const
{
  return eparts_.empty();
}
