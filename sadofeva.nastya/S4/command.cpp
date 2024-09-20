#include "Command.hpp"

void sadofeva::handleComplement(std::map<std::string, BinarySearchTree<int, std::string>> & dicts,
 const std::string & newDataset,
 const std::string & dataset1,
 const std::string & dataset2)
{
  if (dicts.find(dataset1) == dicts.end() || dicts.find(dataset2) == dicts.end())
  {
    std::cout << "<INVALID COMMAND>"
              << "\n";
    return;
  }
  auto it1 = dicts.find(dataset1);
  auto it2 = dicts.find(dataset2);
  BinarySearchTree<int, std::string> result;

  for (auto it = it1->second.begin(); it != it1->second.end(); ++it)
  {
    int key = it->first;
    try
    {
      it2->second.get(key);
    }
    catch (const std::out_of_range &)
    {
      result.push(key, it->second);
    }
  }
  dicts[newDataset] = std::move(result);
}

void sadofeva::handleIntersect(std::map<std::string, BinarySearchTree<int, std::string>> & dicts,
 const std::string & newDataset,
 const std::string & dataset1,
 const std::string & dataset2)
{
  if (dicts.find(dataset1) == dicts.end() || dicts.find(dataset2) == dicts.end())
  {
    std::cout << "<INVALID COMMAND>"
              << "\n";
    return;
  }
  auto it1 = dicts.find(dataset1);
  auto it2 = dicts.find(dataset2);
  BinarySearchTree<int, std::string> result;
  for (auto it = it1->second.begin(); it != it1->second.end(); ++it)
  {
    int key = it->first;
    try
    {
      std::string value = it2->second.get(key);
      result.push(key, it->second);
    }
    catch (const std::out_of_range &)
    {
      continue;
    }
  }

  dicts[newDataset] = std::move(result);
}

void sadofeva::handleUnion(std::map<std::string, BinarySearchTree<int, std::string>> & dicts,
 const std::string & newDataset,
 const std::string & dataset1,
 const std::string & dataset2)
{
  if (dicts.find(dataset1) == dicts.end() || dicts.find(dataset2) == dicts.end())
  {
    std::cout << "<INVALID COMMAND>"
              << "\n";
    return;
  }
  auto it1 = dicts.find(dataset1);
  auto it2 = dicts.find(dataset2);
  BinarySearchTree<int, std::string> result;
  for (auto it = it1->second.begin(); it != it1->second.end(); ++it)
  {
    result.push(it->first, it->second);
  }

  for (auto it = it2->second.begin(); it != it2->second.end(); ++it)
  {
    try
    {
      result.get(it->first);
    }
    catch (const std::out_of_range &)
    {
      result.push(it->first, it->second);
    }
  }

  dicts[newDataset] = std::move(result);
}

void sadofeva::handlePrint(std::map<std::string, BinarySearchTree<int, std::string>> & dicts,
 const std::string & dataset)
{
  auto it = dicts.find(dataset);
  if (it == dicts.end())
  {
    std::cout << "<INVALID COMMAND>"
              << "\n";
    return;
  }

  BinarySearchTree<int, std::string> & tree = it->second;

  if (tree.empty())
  {
    std::cout << "<EMPTY>"
              << "\n";
    return;
  }

  for (auto it = tree.begin(); it != tree.end(); ++it)
  {
    std::cout << it->first << " " << it->second << " ";
  }
}
