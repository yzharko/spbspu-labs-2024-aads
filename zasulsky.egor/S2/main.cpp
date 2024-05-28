#include <iostream>
#include <fstream>
#include "functions.hpp"
#include "parser.hpp"
#include "Stack.hpp"
#include "Queue.hpp"

int main(int argc, char* argv[])
{
  if (argc != 1 && argc != 2)
  {
    std::cerr << "invalid number of argument passed\n";
  }
  std::ifstream file;
  if (argc == 2)
  {
    file.open(argv[1]);
    if (!file.is_open())
    {
      std::cout << "file isn't open!\n";
      return 2;
    }
  }
  auto& input = argc == 2 ? file : std::cin;
  zasulsky::Stack < long long > results;
  std::string str;
  zasulsky::Queue < std::string > expr;
  try
  {
    if (input.peek() == std::ifstream::traits_type::eof())
    {
      std::cout << '\n';
      return 0;
    }
    while (getline(input, str))
    {
      if (str.find_first_not_of(" ") == std::string::npos || str.empty())
      {
        continue;
      }
      zasulsky::Parser pars(str);
      for (auto i = pars(); !i.empty(); i = pars())
      {
        expr.enqueue(i);
      }
      zasulsky::Queue <std::string > postfix = convertToPostfix(expr);
      long long answer = solvePostfixExpr(postfix);
      results.push(answer);
    }
    outputResults(results);
  }

  catch (std::runtime_error& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  catch (...)
  {
    std::cerr << "An invalid infisk expression was passed\n";
    return 1;
  }
}