#ifndef COMMAND_HPP
#define COMMAND_HPP
#include "ABLtree.hpp"

namespace sadofeva
{
  void handleComplement(std::map<std::string, BinarySearchTree<int, std::string>>& dicts, const std::string& newDataset, const std::string& dataset1,const std::string& dataset2);
}

#endif
