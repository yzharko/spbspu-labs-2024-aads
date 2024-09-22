#ifndef CMDS_HPP
#define CMDS_HPP
#include "AVLtree.hpp"

namespace sadofeva
{
  int traverseAscending(std::string& result, AVLtree< int, std::string >& tree);
  int traverseDescending(std::string& result, AVLtree< int, std::string >& tree);
  int TraverseBreadth(std::string& result, AVLtree< int, std::string >& tree);
}

#endif
