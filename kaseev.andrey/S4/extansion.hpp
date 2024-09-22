#ifndef AADS_EXTANSION_HPP
#define AADS_EXTANSION_HPP

#include <string>
#include "BinarySearchTree.hpp"

namespace kaseev {
  using tree = BST< int, std::string, std::less<> >;
  void print(std::ostream &os, const tree &dict);
  bool loadFromFile(const std::string &filename, std::map< std::string, tree > &dictionaries);
  void printInvalidUsage(std::ostream &os, char *argv[]);
  void printInvalidCommand(std::ostream &os);
  void printEmpty(std::ostream &os);
}

#endif
