#include "Operator.hpp"
#include <stdexcept>
#include <iostream>

sadofeva::Operator::Operator(char c):
  c{ c }
{
  if (!isBrackets() && !isMathOperation())
  {
    throw std::logic_error("not an operator");
  }
}

bool sadofeva::Operator::operator<(const Operator & o) const noexcept
{
  return getPriority_() < o.getPriority_();
}

bool sadofeva::Operator::operator==(const Operator & o) const noexcept
{
  return c == o.c;
}

bool sadofeva::Operator::operator<=(const Operator & o) const noexcept
{
  return *this < o || *this == o;
}

bool sadofeva::Operator::isBrackets() const noexcept
{
  return c == '(' || c == ')';
}

bool sadofeva::Operator::isMathOperation() const noexcept
{
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
}

int sadofeva::Operator::getPriority_() const noexcept
{
  if (c == '+' || c == '-')
  {
    return 1;
  }
  else if (c == '*' || c == '/' || c == '%')
  {
    return 2;
  }
  return 0;
}
