#include "inputMap.hpp"
#include <iostream>
#include <stdexcept>

sadofeva::AVLTree< int, std::string > sadofeva::inputMap(std::istream& in)
{
  int key = 0;
  std::string value = "";
  AVLTree< int, std::string > tree;
  while (in)
  {
    while (in >> key >> value)
    {
      tree.insert(key, value);
    }
    if (!in.eof())
    {
      throw std::logic_error("Something is wrong with the input");
    }
  }
  return tree;
}
