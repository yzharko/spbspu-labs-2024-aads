#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <tuple>
#include <string>
#include "bintree.hpp"

namespace lisitsyna
{
  std::pair< int, std::string > ascend(AVLTree< int, std::string > & data);
  std::pair< int, std::string > descend(AVLTree< int, std::string > & data);
  std::pair< int, std::string > breadth(AVLTree< int, std::string > & data);
}

#endif
