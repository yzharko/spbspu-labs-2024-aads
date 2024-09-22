#ifndef CMDS_HPP
#define CMDS_HPP
#include "AVLtree.hpp"

namespace sadofeva
{
  int traverseAscending(std::string& result, AVLTree< int, std::string >& tree);
  int traverseDescending(std::string& result, AVLTree< int, std::string >& tree);
  int TraverseBreadth(std::string& result, AVLTree< int, std::string >& tree);
}

#endif
