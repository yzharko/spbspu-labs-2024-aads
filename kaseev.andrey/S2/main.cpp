#include <iostream>
#include <fstream>
#include "ExpressionEvaluator.hpp"

int main(int argc, char* argv[])
{
  kaseev::Queue< std::shared_ptr< kaseev::ExpressionItem > > expressionQueue;
  kaseev::Stack< long long > results;

  try
  {
    std::string line;
    if (argc > 1)
    {
      std::ifstream file(argv[1]);
      if (!file)
      {
        std::cerr << "Cannot open file: " << argv[1] << "\n";
        return 1;
      }
      while (std::getline(file, line))
      {
        if (!line.empty())
        {
          kaseev::ExpressionEvaluator::parseExpression(expressionQueue, line);
          kaseev::Queue< std::shared_ptr< kaseev::ExpressionItem > > postfixQueue = kaseev::ExpressionEvaluator::toPostfix(expressionQueue);
          results.push(kaseev::ExpressionEvaluator::evaluateExpression(postfixQueue));
          expressionQueue.clear();
        }
      }
    }
    else
    {
      while (std::getline(std::cin, line))
      {
        if (!line.empty())
        {
          kaseev::ExpressionEvaluator::parseExpression(expressionQueue, line);
          kaseev::Queue< std::shared_ptr< kaseev::ExpressionItem > > postfixQueue = kaseev::ExpressionEvaluator::toPostfix(expressionQueue);
          results.push(kaseev::ExpressionEvaluator::evaluateExpression(postfixQueue));
          expressionQueue.clear();
        }
      }
    }

    while (!results.empty())
    {
      std::cout << results.top() << (results.size() == 1 ? "" : " ");
      results.pop();
    }
    std::cout << "\n";
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
