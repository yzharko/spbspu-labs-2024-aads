#include <functional>
#include <map>
#include <iostream>
#include "func.hpp"
#include "error.hpp"

int main(int argc, char** argv)
{
  if (argc != 4)
  {
    gorbunova::displayParameterError(std::cout);
    return 2;
  }

  int size = std::atoi(argv[3]);
  if (size <= 0)
  {
    gorbunova::displaySizeError(std::cout);
    return 1;
  }

  std::map<std::string, std::map<std::string, std::function<void(std::ostream&, int)>>> commandMap;
  {
    using namespace std::placeholders;
    commandMap["ints"]["ascending"] = std::bind(gorbunova::executeSorting<int, std::less<int>>, _1, _2, std::less<int>());
    commandMap["ints"]["descending"] = std::bind(gorbunova::executeSorting<int, std::greater<int>>, _1, _2, std::greater<int>());
    commandMap["floats"]["ascending"] = std::bind(gorbunova::executeSorting<double, std::less<double>>, _1, _2, std::less<double>());
    commandMap["floats"]["descending"] = std::bind(gorbunova::executeSorting<double, std::greater<double>>, _1, _2, std::greater<double>());
  }

  try
  {
    commandMap.at(argv[2]).at(argv[1])(std::cout, size);
  }
  catch (const std::out_of_range&)
  {
    gorbunova::displayParameterError(std::cout);
    return 1;
  }

  return 0;
}
