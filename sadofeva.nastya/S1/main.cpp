#inlude <iostream>
#include <cstring>
#include "lish.hpp"

int main()
{
  using namespace sadofeva;
  std::string input_str;
  using pair = std::pair<std::string, List<int>>;
  size number = 0;
  while (std::cin)
  {
    std::cin >> input_str;
    if (!std::cin)
    {
      break;
    }
    if (std::cin.eof())
    {
      break;
    }
    if (isdigit(input_str[0]))
    {
      pair.push_back(input_str[0]));
    }
  }
}
