#include <iostream>
#include <string>
#include <memory>
#include <limits>
#include "list.hpp"
#include "funcs.hpp"

int main()
{
  using namespace khoroshkin;
  List< std::pair< std::string, List< unsigned long long > > > allPairs;
  std::string input;
  size_t count = 0;
  size_t maxLength = 0;
  while (std::cin >> input)
  {
    if (isdigit(input[0]))
    {
      allPairs[count].second.push_back(std::stoull(input));
    }
    else
    {
      allPairs.push_back({input,{}});
      allPairs.getSize() == 1 ? 0 : count++;
    }
    if (maxLength < allPairs[count].second.getSize())
    {
      maxLength = allPairs[count].second.getSize();
    }
  }
  try
  {
    printResult(std::cout, allPairs, maxLength);
  }
  catch(const std::overflow_error & e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  catch(const std::logic_error & e)
  {
    std::cout << 0 << '\n';
    return 0;
  }
  return 0;
}

