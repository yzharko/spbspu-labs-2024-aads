#ifndef BINARYTREEII_HPP
#define BINARYTREEII_HPP
#include <string>
#include "BinarySearchTree.hpp"

void ReadFile(const std::string& path, BinarySearchTree<int, std::string>& bst);
void ReadDataSet(const std::string& dataSet, BinarySearchTree<int, std::string>& bst);
int sum(int a, int b);
#endif
