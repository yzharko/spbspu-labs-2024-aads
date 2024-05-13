#include "queue.hpp"
#include "stack.hpp"
#include <iostream>
//#include "function"
int main(int argc, char* argv[])
{
  using namespace jirkov;
  Queue< std::string > someQueue;
  Stack< long long > someStack;
  if (argc == 1)
  {
    std::string operation;
    while (!std::cin.eof())
    {
      std::getline(std::cin, operation);
      if (!operation.empty())
      {
        someQueue.push(operation);
      }
    }
  }
  else if (argc == 2)
  {
    std::ifstream std::cin(argv[]);
    std::string operation;
    while (!std::cin.eof())
    {
      std::getline(std::cin, operation);
      if (!operation.empty())
      {
        someQueue.push(operation);
      }
    }
  }
  else
  {
    std::cerr << "Wrong input" << "\n";
    return 1;
  }
  try
  {
    while (!someStack.empty())
    {
      std::cout << someStack.front();
      if (someStack.front() != someStack.back())
      {
        std::cout << ' ';
      }
      someStack.drop();
    }
    std::cout << '\n';
  }
  catch (std::exception & const e)
  {
    std::cout << e.what();
    return 1;
  }
  return 0;
}
