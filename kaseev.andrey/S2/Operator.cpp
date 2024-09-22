#include "Operator.hpp"

kaseev::Operator::Operator(char op) : operator_(op)
{
  if (!isOperator(op))
  {
    throw std::invalid_argument("Unsupported operator");
  }
}

bool kaseev::Operator::isLeftParenthesis() const
{
  return operator_ == '(';
}

bool kaseev::Operator::isRightParenthesis() const
{
  return operator_ == ')';
}

char kaseev::Operator::getOperator() const
{
  return operator_;
}

int kaseev::Operator::precedence() const
{
  if (operator_ == '+' || operator_ == '-')
  {
    return 1;
  }
  else if (operator_ == '*' || operator_ == '/' || operator_ == '%')
  {
    return 2;
  }
  else if (operator_ == '(' || operator_ == ')')
  {
    return 0;
  }
  else
  {
    throw std::runtime_error("Unsupported operator");
  }
}

long long kaseev::Operator::applyOp(long long a, long long b) const
{
  if (operator_ == '+')
  {
    return a + b;
  }
  else if (operator_ == '-')
  {
    return a - b;
  }
  else if (operator_ == '*')
  {
    return a * b;
  }
  else if (operator_ == '/')
  {
    if (b == 0)
    {
      throw std::runtime_error("Division by zero");
    }
    return a / b;
  }
  else if (operator_ == '%')
  {
    if (b == 0)
    {
      throw std::runtime_error("Modulo by zero");
    }
    if (a < 0)
    {
      return a % b + abs(b);
    }
    return a % b;
  }
  else
  {
    throw std::invalid_argument("Invalid operation");
  }
}

bool kaseev::Operator::isOperator()
{
  return true;
}

bool kaseev::Operator::isOperand()
{
  return false;
}

bool kaseev::Operator::isOperator(char c)
{
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '(' || c == ')';
}
