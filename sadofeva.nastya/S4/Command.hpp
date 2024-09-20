#ifndef COMMAND_HPP
#define COMMAND_HPP
#include "ABLtree.hpp"

namespace sadofeva
{
  void handleComplement(std::map<std::string, BinarySearchTree<int, std::string>> & dicts,
   const std::string & newDataset,
   const std::string & dataset1,
   const std::string & dataset2);
  void handleIntersect(std::map<std::string, BinarySearchTree<int, std::string>> & dicts,
   const std::string & newDataset,
   const std::string & dataset1,
   const std::string & dataset2);
  void handleUnion(std::map<std::string, BinarySearchTree<int, std::string>> & dicts,
   const std::string & newDataset,
   const std::string & dataset1,
   const std::string & dataset2);
  void handlePrint(std::map<std::string, BinarySearchTree<int, std::string>> & dicts, const std::string & dataset);
}
#endif
