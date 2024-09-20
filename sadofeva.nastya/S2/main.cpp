#include <iostream>
#include <string>
#include <fstream>
#include "stack.hpp"
#include "ExpressionCalculation.hpp"

int main(int argc, char ** argv)
{
  sadofeva::Queue<sadofeva::InfixExpression> expressions;

  if (argc == 2)
  {
    std::string fileName = argv[1];
    std::ifstream fin(fileName);
    if (!fin.is_open())
    {
      std::cerr << "Bad file or filename\n";
      return 1;
    }

    try
    {
      expressions = sadofeva::readExpressions(fin);
    }
    catch (const std::exception & e)
    {
      fin.close();
      std::cerr << e.what() << '\n';
      return 2;
    }
    fin.close();
  }
  else if (argc == 1)
  {
    try
    {
      expressions = sadofeva::readExpressions(std::cin);
    }
    catch (const std::exception & e)
    {
      std::cerr << e.what() << '\n';
      return 2;
    }

    if (std::cin.fail())
    {
      std::cerr << "Incorrect input\n";
      return 1;
    }
  }
  else
  {
    std::cerr << "Bad args\n";
    return 1;
  }

  if (!expressions.empty())
  {
    sadofeva::Stack<long long> answers;
    while (!expressions.empty())
    {
      sadofeva::PostfixExpression postfix_expression_next(expressions.next());
      expressions.drop();
      try
      {
        answers.push(sadofeva::calculatePostfixExpression(postfix_expression_next));
      }
      catch (const std::exception & e)
      {
        std::cerr << e.what() << '\n';
        return 2;
      }
    }

    while (!answers.empty())
    {
      std::cout << answers.top();
      answers.drop();
      if (!answers.empty())
      {
        std::cout << ' ';
      }
    }
  }
  std::cout << '\n';

  return 0;
}

