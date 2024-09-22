#ifndef INPUTMAP_HPP
#define INPUTMAP_HPP
#include <iosfwd>
#include "AVLtree.hpp"

namespace sadofeva
{
  AVLTree< int, std::string > inputMap(std::istream&);
}

#endif

