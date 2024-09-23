#include <iostream>
#include <string>
#include "commands.hpp"

namespace gorbunova
{
  void buildTree(std::istream& inputStream, MainTree& tree)
  {
    while (!inputStream.eof())
    {
      std::string line;
      std::getline(inputStream, line);
      if (!line.empty())
      {
        std::string temp = "";
        std::string name = "";
        size_t key = 0;
        std::string value = "";
        ChildTree subtree;
        bool isFirstWord = true;
        size_t index = 0;

        while (index < line.length())
        {
          if (line[index] != ' ')
          {
            temp += line[index];
          }
          else if (line[index] == ' ' && isFirstWord)
          {
            name = temp;
            temp.clear();
            isFirstWord = false;
          }
          else
          {
            if (std::isdigit(temp[0]))
            {
              key = std::stoll(temp);
              temp.clear();
            }
            else
            {
              value = temp;
              temp.clear();
              subtree.insert(key, value);
            }
          }
          index++;
        }

        if (key == 0)
        {
          name = temp;
        }

        if (!value.empty())
        {
          value = temp;
          subtree.insert(key, value);
        }

        tree.insert(name, subtree);
      }
    }
  }

  void displayTree(MainTree& tree)
  {
    std::string inputName;
    std::cin >> inputName;
    ChildTree subtree = tree.at(inputName);

    if (subtree.empty())
    {
      displayEmptyResult(std::cout);
      return;
    }

    auto it = subtree.cbegin();
    auto endIt = subtree.cend();
    std::cout << inputName << " ";

    while (it != endIt)
    {
      auto pair = *it;
      std::cout << pair.first << " " << pair.second;
      ++it;

      if (it != endIt)
      {
        std::cout << " ";
      }
      else
      {
        std::cout << "\n";
      }
    }
  }

  void computeComplement(MainTree& tree)
  {
    std::string resultName, firstName, secondName;
    std::cin >> resultName >> firstName >> secondName;
    ChildTree resultSubtree;

    if (firstName == secondName)
    {
      tree.insert(resultName, resultSubtree);
      return;
    }

    findComplement(tree.at(firstName), tree.at(secondName), resultSubtree);

    if (resultName != firstName && resultName != secondName)
    {
      tree.insert(resultName, resultSubtree);
    }
    else if (resultName == firstName)
    {
      tree.erase(firstName);
      tree.insert(resultName, resultSubtree);
    }
    else
    {
      tree.erase(secondName);
      tree.insert(resultName, resultSubtree);
    }
  }

  void findComplement(ChildTree& first, ChildTree& second, ChildTree& result)
  {
    for (auto it = first.begin(); it != first.end(); ++it)
    {
      bool existsInSecond = false;

      for (auto iter = second.begin(); iter != second.end(); ++iter)
      {
        if (it->first == iter->first)
        {
          existsInSecond = true;
          break;
        }
      }

      if (!existsInSecond)
      {
        result.insert(*it);
      }
    }
  }

  void computeIntersection(MainTree& tree)
  {
    std::string resultName, firstName, secondName;
    std::cin >> resultName >> firstName >> secondName;

    ChildTree intersectionSubtree;
    ChildTree firstSubtree = tree.at(firstName);
    ChildTree secondSubtree = tree.at(secondName);

    if (firstSubtree.empty() || secondSubtree.empty())
    {
      tree.erase(resultName);
      tree.insert(resultName, intersectionSubtree);
      return;
    }

    for (auto it = firstSubtree.begin(); it != firstSubtree.end(); ++it)
    {
      size_t key = it->first;

      if (secondSubtree.find(key) != secondSubtree.cend())
      {
        intersectionSubtree.insert(*it);
      }
    }

    if (resultName != firstName && resultName != secondName)
    {
      tree.insert(resultName, intersectionSubtree);
    }
    else if (resultName == firstName)
    {
      tree.erase(firstName);
      tree.insert(resultName, intersectionSubtree);
    }
    else
    {
      tree.erase(secondName);
      tree.insert(resultName, intersectionSubtree);
    }
  }

  ChildTree mergeSubtrees(ChildTree& firstTree, ChildTree& secondTree)
  {
    ChildTree mergedResult;
    auto itFirst = firstTree.begin();
    auto itSecond = secondTree.begin();

    while (itFirst != firstTree.end() || itSecond != secondTree.end())
    {
      if (itFirst != firstTree.end() && (itSecond == secondTree.end() || itFirst->first < itSecond->first))
      {
        mergedResult.insert(*itFirst);
        ++itFirst;
      }
      else if (itSecond != secondTree.end() && (itFirst == firstTree.end() || itSecond->first < itFirst->first))
      {
        mergedResult.insert(*itSecond);
        ++itSecond;
      }
      else
      {
        mergedResult.insert(*itFirst);
        ++itFirst;
        ++itSecond;
      }
    }

    return mergedResult;
  }

  void computeUnion(MainTree& tree)
  {
    std::string resultName, firstName, secondName;
    std::cin >> resultName >> firstName >> secondName;

    ChildTree unionedSubtree = mergeSubtrees(tree.at(firstName), tree.at(secondName));

    if (resultName != firstName && resultName != secondName)
    {
      tree.insert(resultName, unionedSubtree);
    }
    else if (resultName == firstName)
    {
      tree.erase(firstName);
      tree.insert(resultName, unionedSubtree);
    }
    else
    {
      tree.erase(secondName);
      tree.insert(resultName, unionedSubtree);
    }
  }

  void displayInvalidCommand(std::ostream& outputStream)
  {
    outputStream << "<INVALID COMMAND>\n";
  }

  void displayEmptyResult(std::ostream& outputStream)
  {
    outputStream << "<EMPTY>\n";
  }
}
