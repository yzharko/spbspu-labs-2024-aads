#include "ExpressionCalculation.hpp"
#include <iostream>
#include <limits>
#include "stack.hpp"

namespace
{
  long long sum(long long a, long long b)
  {
    if (a > 0 && b > 0)
    {
      if (a > std::numeric_limits<long long>::max() - b)
      {
        throw std::overflow_error("overflow");
      }
    }
    else if (a < 0 && b < 0)
    {
      if (a < std::numeric_limits<long long>::min() - b)
      {
        throw std::overflow_error("overflow");
      }
    }
    return a + b;
  }
  long long mult(long long a, long long b)
  {
    const long long LLONG_MAX = std::numeric_limits<long long>::max();
    const long long LLONG_MIN = std::numeric_limits<long long>::min();

    if (a > 0 && b > 0 && a > LLONG_MAX / b)
    {
      throw std::overflow_error("overflow");
    }
    if (a < 0 && b < 0 && a < LLONG_MAX / b)
    {
      throw std::overflow_error("overflow");
    }
    if (a > 0 && b < 0 && b < LLONG_MIN / a)
    {
      throw std::overflow_error("overflow");
    }
    if (a < 0 && b > 0 && a < LLONG_MIN / b)
    {
      throw std::overflow_error("overflow");
    }

    return a * b;
  }
  long long divide(long long a, long long b)
  {
    if (b == 0)
    {
      throw std::logic_error("division by zero");
    }
    if (a == std::numeric_limits<long long>::min() && b == -1)
    {
      throw std::overflow_error("overflow");
    }
    return a / b;
  }
  long long calcRemainderOfDivision(long long a, long long b)
  {
    if (a < 0)
    {
      return a + b * (std::abs(a) / b + 1);
    }
    else
    {
      return a % b;
    }
  }
}

sadofeva::Queue<sadofeva::InfixExpression> sadofeva::readExpressions(std::istream & in)
{
  Queue<InfixExpression> expressions_queue;
  while (in && !in.eof())
  {
    auto ie = InfixExpression(in);
    if (!ie.empty())
    {
      expressions_queue.push(ie);
    }
    if ((in >> std::noskipws).peek() == '\n')
    {
      in >> std::skipws >> std::ws;
    }
  }
  return expressions_queue;
}

long long sadofeva::calculatePostfixExpression(PostfixExpression pexpression)
{
  Stack<long long> stack;
  while (!pexpression.empty())
  {
    ExpressionPart part = pexpression.getNextExpressionPart();
    pexpression.drop();
    if (part.isOperand())
    {
      stack.push(part.getOperand().num);
    }
    else if (part.getOperator().isMathOperation())
    {
      long long b = stack.top();
      stack.drop();
      long long a = stack.top();
      stack.drop();

      if (part.getOperator() == Operator('+'))
      {
        stack.push(sum(a, b));
      }
      else if (part.getOperator() == Operator('-'))
      {
        stack.push(sum(a, -b));
      }
      else if (part.getOperator() == Operator('/'))
      {
        stack.push(divide(a, b));
      }
      else if (part.getOperator() == Operator('*'))
      {
        stack.push(mult(a, b));
      }
      else if (part.getOperator() == Operator('%'))
      {
        stack.push(calcRemainderOfDivision(a, b));
      }
    }
  }
  long long result = stack.top();
  stack.drop();
  if (!stack.empty())
  {
    throw std::logic_error("expression calculation fail");
  }

  return result;
}
