#include <iostream>
#include <fstream>
#include "InputProcessing.hpp"

int main(int argc, char ** argv)
{
  litsinger::Queue< litsinger::Element > infix;
  litsinger::Postfix postfix;
  long long int calculate_result = 0;
  litsinger::Stack< long long int > results;
  try
  {
    if (argc == 2)
    {
      std::ifstream input(argv[1]);
      if (!input)
      {
        std::cerr << "can't open file\n";
        return 1;
      }
      else
      {
        while (!input.eof())
        {
          litsinger::readLine(input, infix);
          litsinger::makePostfix(infix, postfix);
          if (!postfix.postfix_.empty())
          {
            calculate_result = litsinger::calculate(postfix);
            results.push(calculate_result);
          }
        }
      }
    }
    else if (argc == 1)
    {
      while (!std::cin.eof())
      {
        litsinger::readLine(std::cin, infix);
        litsinger::makePostfix(infix, postfix);
        if (!postfix.postfix_.empty())
        {
          calculate_result = litsinger::calculate(postfix);
          results.push(calculate_result);
        }
      }
    }
    else
    {
      std::cerr << "too much arguments\n";
      return 1;
    }
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what();
    return 1;
  }
  while (!results.empty())
  {
    std::cout << results.getValue();
    if (results.getSize() != 1)
    {
      std::cout << " ";
    }
    results.pop();
  }
  std::cout << "\n";
  return 0;
}
