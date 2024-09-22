#ifndef EXPRESSIONS_HPP
#define EXPRESSIONS_HPP
#include <climits>
#include "stack.hpp"
#include "queue.hpp"

std::string infixToPostfix(const std::string &infix)
{
  gorbunova::Stack<char> operators;
  gorbunova::Queue<std::string> postfixQueue;
  std::string numberBuffer;

  auto getPriority = [](char op) -> long long
  {
    if (op == '+' || op == '-')
      return 1;
    if (op == '*' || op == '/' || op == '%')
      return 2;
    return 0;
  };

  for (size_t i = 0; i < infix.size(); ++i)
  {
    char ch = infix[i];

    if (isdigit(ch))
    {
      numberBuffer += ch;
    }
    else
    {
      if (!numberBuffer.empty())
      {
        postfixQueue.push(numberBuffer);
        numberBuffer.clear();
      }

      if (ch == '(')
      {
        operators.push(ch);
      }
      else if (ch == ')')
      {
        while (!operators.isEmpty() && operators.top() != '(')
        {
          postfixQueue.push(std::string(1, operators.top()));
          operators.pop();
        }
        operators.pop();
      }
      else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%')
      {
        while (!operators.isEmpty() && getPriority(operators.top()) >= getPriority(ch))
        {
          postfixQueue.push(std::string(1, operators.top()));
          operators.pop();
        }
        operators.push(ch);
      }
    }
  }

  if (!numberBuffer.empty())
  {
    postfixQueue.push(numberBuffer);
  }

  while (!operators.isEmpty())
  {
    postfixQueue.push(std::string(1, operators.top()));
    operators.pop();
  }

  std::string result;
  while (!postfixQueue.isEmpty())
  {
    result += postfixQueue.front() + ' ';
    postfixQueue.pop();
  }

  return result;
}

long long calculatePostfix(const std::string &postfix)
{
  gorbunova::Stack<long long> stack;
  gorbunova::Queue<std::string> tokenQueue;

  size_t start = 0;
  size_t end = 0;

  while ((end = postfix.find(' ', start)) != std::string::npos)
  {
    std::string token = postfix.substr(start, end - start);
    tokenQueue.push(token);
    start = end + 1;
  }

  if (start < postfix.length())
  {
    tokenQueue.push(postfix.substr(start));
  }

  while (!tokenQueue.isEmpty())
  {
    std::string current = tokenQueue.front();
    tokenQueue.pop();

    if (isdigit(current[0]))
    {
      stack.push(std::stoll(current));
    }
    else
    {
      long long b = stack.pop();
      long long a = stack.pop();

      if (current == "+")
      {
        if ((b > 0 && a > LLONG_MAX - b) || (b < 0 && a < LLONG_MIN - b))
        {
          throw std::overflow_error("Addition overflow");
        }
        stack.push(a + b);
      }
      else if (current == "-")
        stack.push(a - b);
      else if (current == "*")
      {
        if ((a > 0 && b > 0 && a > LLONG_MAX / b) ||
          (a < 0 && b < 0 && a < LLONG_MIN / b) ||
          (a > 0 && b < 0 && a > LLONG_MIN / b) ||
          (a < 0 && b > 0 && a < LLONG_MAX / b))
        {
          throw std::overflow_error("Multiplication overflow");
        }
        stack.push(a * b);
      }
      else if (current == "/")
      {
        if (b == 0)
        {
          throw std::runtime_error("Division by zero");
        }
        stack.push(a / b);
      }
      else if (current == "%")
      {
        if (b == 0)
        {
          throw std::runtime_error("Modulo by zero");
        }
        long long result = a % b;
        if (result < 0)
        {
          result += std::abs(b);
        }
        stack.push(result);
      }
    }
  }

  return stack.pop();
}

#endif
