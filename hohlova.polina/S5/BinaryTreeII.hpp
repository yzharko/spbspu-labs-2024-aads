#ifndef BINARYTREEII_HPP
#define BINARYTREE_HPP
#include <string>
#include "BinarySearchTree.hpp"

namespace hohlova
{
  void ReadFile(const std::string& path, BinarySearchTree<int, std::string>& bst);
  void ReadDataSet(const std::string& dataSet, BinarySearchTree<int, std::string>& bst);
  int ParseNum(const std::string& num);
  int sum(int a, int b);
}

#endif
