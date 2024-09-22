#ifndef TREETRAVERSAL_HPP
#define TREETRAVERSAL_HPP

#include "BinarySearchTree.hpp"
#include "Sum.hpp"

namespace kaseev {
  void traverseAscending(const BST< long long, std::string, std::less<long long> > &tree);
  void traverseDescending(const BST< long long, std::string, std::less<long long> > &tree);
  void traverseBreadth(const BST< long long, std::string, std::less<long long> > &tree);
  void printResult(Sum &keySumCounter, std::ostream &os);
  void invalidCommandError(std::ostream &out);
  void emptyCommandWarning(std::ostream &out);
}

#endif
