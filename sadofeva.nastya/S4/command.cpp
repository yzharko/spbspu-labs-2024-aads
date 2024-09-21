#include "Command.hpp"
#include <iostream>

void sadofeva::handleComplement(std::map<std::string, sadofeva::AVLTree<int, std::string>> & dicts,
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
  sadofeva::AVLTree<int, std::string> result;

  for (auto it = it1->second.begin(); it != it1->second.end(); ++it)
  {
    int key = it->first;
    try
    {
      it2->second.at(key);
    }
    catch (const std::out_of_range &)
    {
      result.insert(key, it->second);
    }
  }
  dicts[newDataset] = std::move(result);
}

void sadofeva::handleIntersect(std::map<std::string, sadofeva::AVLTree<int, std::string>> & dicts,
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
  sadofeva::AVLTree<int, std::string> result;
  for (auto it = it1->second.begin(); it != it1->second.end(); ++it)
  {
    int key = it->first;
    try
    {
      std::string value = (it2->second.at(key))->second;
      result.insert(key, it->second);
    }
    catch (const std::out_of_range &)
    {
      continue;
    }
  }

  dicts[newDataset] = std::move(result);
}

void sadofeva::handleUnion(std::map<std::string, sadofeva::AVLTree<int, std::string>> & dicts,
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
  sadofeva::AVLTree<int, std::string> result;
  for (auto it = it1->second.begin(); it != it1->second.end(); ++it)
  {
    result.insert(it->first, it->second);
  }

  for (auto it = it2->second.begin(); it != it2->second.end(); ++it)
  {
    try
    {
      result.at(it->first);
    }
    catch (const std::out_of_range &)
    {
      result.insert(it->first, it->second);
    }
  }

  dicts[newDataset] = std::move(result);
}

void sadofeva::handlePrint(std::map<std::string, sadofeva::AVLTree<int, std::string>> & dicts,
 const std::string & dataset)
{
  auto it = dicts.find(dataset);
  if (it == dicts.end())
  {
    std::cout << "<INVALID COMMAND>"
              << "\n";
    return;
  }

  sadofeva::AVLTree<int, std::string> & tree = it->second;

  if (tree.isEmpty())
  {
    std::cout << "<EMPTY>"
              << "\n";
    return;
  }

  std::cout << dataset;
  for (auto it = tree.begin(); it != tree.end(); ++it)
  {
    std::cout << ' ' << it->first << ' ' << it->second;
  }
  std::cout << "\n";
}
