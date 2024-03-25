#include <iostream>
#include <string>
#include "list.hpp"
#include "numbers.hpp"
#include "task.hpp"

int main()
{
  zheleznyakov::List<std::pair<std::string, zheleznyakov::List<unsigned long long>>> pairs;
  size_t pairsIndex = -1;
  std::string input;
  while (std::cin >> input)
  {
    if (zheleznyakov::isNumeric(input))
    {
      pairs[pairsIndex].second.pushBack(std::stoull(input));
    }
    else
    {
      pairs.pushBack({ input, {} });
      pairsIndex++;
    }
  }
  try
  {
    zheleznyakov::processTask(std::cout, pairs);
  }
  catch(const std::overflow_error& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}
