#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include "doublelist.hpp"
#include <iostream>
#include <string>

namespace kovshikov
{
  void inputPairs(DoubleList<std::pair<std::string, DoubleList<size_t>>> &allPairs, bool &isBigNumber);
  void outputListName(const DoubleList<std::pair<std::string, DoubleList<size_t>>> &allPairs);
  void outputResult(const DoubleList<std::pair<std::string, DoubleList<size_t>>> &allPairs, const  bool &isBigNumber);
}

#endif
