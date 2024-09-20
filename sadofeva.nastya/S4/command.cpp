#include "Command.hpp"

void sadofeva::handleComplement(std::map<std::string, BinarySearchTree<int, std::string>>& dicts, const std::string& newDataset, const std::string& dataset1, const std::string& dataset2) {
  if (dicts.find(dataset1) == dicts.end() || dicts.find(dataset2) == dicts.end()) {
    std::cout << "<INVALID COMMAND>" << "\n";
    return 0;
  }

  BinarySearchTree<int, std::string> result;
  BinarySearchTree<int, std::string>& set1 = dicts[dataset1];
  BinarySearchTree<int, std::string>& set2 = dicts[dataset2];

  for (const auto& item : set1) {
    if (!set2.contains(item.first)) {
      result.push(item.first, item.second);
    }
  }
  dicts[newDataset] = result;
}
void handleIntersect(std::map<std::string, BinarySearchTree<int, std::string>>& dicts const std::string& newDataset, const std::string& dataset1, const std::string& dataset2)
{
  if (dicts.find(dataset1) == dicts.end() || dicts.find(dataset2) == dicts.end())
  {
    std::cout << "<INVALID COMMAND>" << "\n";
    return 0;
  }
  BinarySearchTree <int, std::string> result;
  BinarySearchTree<int, std::string>& set1 = dicts[dataset1];
  BinarySearchTree<int, std::string>& set2 = dicts[dataset2];

  for (const auto& item : set1) {
    if (set2.contains(item.first)) {
      result.push(item.first, item.second);
    }
  }

  dicts[newDataset] = result;
}

void handleUnion(std::map<std::string, BinarySearchTree<int, std::string>>& dicts const std::string& newDataset, const std::string& dataset1, const std::string& dataset2)
{
  if (dicts.find(dataset1) == dicts.end() || dicts.find(dataset2) == dicts.end()) {
    std::cout << "<INVALID COMMAND>" << "\n";
    return 0;
  }

  BinarySearchTree<int, std::string> result;
  BinarySearchTree<int, std::string>& set1 = dicts[dataset1];
  BinarySearchTree<int, std::string>& set2 = dicts[dataset2];

  for (const auto& item : set1) {
    result.push(item.first, item.second);
  }

  for (const auto& item : set2) {
    if (!set1.contains(item.first)) {
      result.push(item.first, item.second);
    }
  }

  dicts[newDataset] = result;
}

void handlePrint(std::map<std::string, BinarySearchTree<int, std::string>>& dicts, const std::string& dataset)
{
  auto it = dicts.find(dataset);
  if (if == dicts.end())
  {
    std::cout << "<INVALID COMMAND>" << "\n";
    return 0;
  }

  const BinarySearchTree<int, std::string>& tree = it->second;

  if (tree.empty())
  {
    std::cout << "<EMPTY>" << "\n";
    return 0;
  }

  for (auto it = tree.end(); it != tree.end(); ++it)
  {
    std::cout << it->first << " " << it->second << " ";
  }
}