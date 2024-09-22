#include <fstream>
#include "expressions.hpp"
#include "queue.hpp"

int main(int argc, char *argv[])
{
  std::ifstream file;
  gorbunova::Queue<std::string> expressions;
  gorbunova::Stack<long long> results;

  if (argc == 2)
  {
    file.open(argv[1]);
    if (!file.is_open())
    {
      std::cerr << "Cant open file: " << argv[1] << std::endl;
      return 1;
    }
  }
  else
  {
    std::string expression;
    while (std::getline(std::cin, expression))
    {
      if (expression.empty())
        break;
      expressions.push(expression);
    }
  }

  if (argc == 2)
  {
    std::string expression;
    while (std::getline(file, expression))
    {
      if (!expression.empty())
      {
        expressions.push(expression);
      }
    }
  }

  while (!expressions.isEmpty())
  {
    std::string expression = expressions.front();
    expressions.pop();
    try
    {
      std::string postfix = infixToPostfix(expression);
      long long result = calculatePostfix(postfix);
      results.push(result);
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << expression << std::endl;
      return 1;
    }
  }

  while (!results.isEmpty())
  {
    std::cout << results.pop();
    if (!results.isEmpty())
    {
      std::cout << ' ';
    }
  }
  std::cout << std::endl;

  return 0;
}
