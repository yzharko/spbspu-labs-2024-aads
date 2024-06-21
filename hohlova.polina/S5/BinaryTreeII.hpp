#ifndef BINARYTREEII_HPP
#define BINARYTREEII_HPP
#include <string>
#include "BinarySearchTree.hpp"

namespace hohlova
{
  using Dictionary = BinarySearchTree< std::string, BinarySearchTree< int, std::string >* >;
  void readFile(const std::string& path, BinarySearchTree<int, std::string>& bst);
  void print(Dictionary& bst, const std::string& str);
  void ReadDataSet(const std::string& dataSet, BinarySearchTree<int, std::string>& bst);
  int ParseNum(const std::string& num);
  int sum(int a, int b);

  void warningEmpty(std::ostream& out);
  void warningInvCom(std::ostream& out);
}

#endif
