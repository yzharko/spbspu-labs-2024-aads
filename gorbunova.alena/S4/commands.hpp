#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "tree.hpp"
#include <iostream>
#include <fstream>
#include <string>

namespace gorbunova
{
  using MainTree = Tree<std::string, Tree<size_t, std::string>>;
  using ChildTree = Tree<size_t, std::string>;

  void buildTree(std::istream& inputStream, MainTree& tree);
  void displayTree(MainTree& tree);
  void computeComplement(MainTree& tree);
  void findComplement(ChildTree& firstSubtree, ChildTree& secondSubtree, ChildTree& resultSubtree);
  void computeIntersection(MainTree& tree);
  void computeUnion(MainTree& tree);
  void displayInvalidCommand(std::ostream& outputStream);
  void displayEmptyResult(std::ostream& outputStream);
  ChildTree mergeSubtrees(ChildTree& firstTree, ChildTree& secondTree);
}

#endif
