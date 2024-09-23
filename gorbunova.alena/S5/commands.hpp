#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "tree.hpp"
#include "queue.hpp"
#include <string>
#include <fstream>

namespace gorbunova
{
  void buildTree(std::istream& in, Tree<int, std::string>& tree);
  bool numbers(const std::string& str);
  void ascending(Tree<int, std::string>& tree);
  void descending(Tree<int, std::string>& tree);
  void breadth(Tree<int, std::string>& tree);
  void displayEmptyResult(std::ostream& out);
}

#endif
