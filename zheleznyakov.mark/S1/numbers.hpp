#ifndef NUMBERS_HPP
#define NUMBERS_HPP
#include <iostream>

namespace zheleznyakov
{
  bool isNumeric(std::string str);
}

bool zheleznyakov::isNumeric(std::string str)
{
  for (auto &chr : str)
  {
    if (!std::isdigit(chr))
    {
      return false;
    }
  }
  return true;
}
#endif
