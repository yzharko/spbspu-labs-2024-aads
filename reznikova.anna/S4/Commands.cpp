#include "Commands.hpp"
#include <sstream>

void reznikova::outputInvalidCommand(std::ostream & out)
{
  out << "< INVALID COMMAND >\n";
}

void reznikova::outputError(std::ostream & out)
{
  out << "< ERROR >\n";
}

std::string reznikova::getValue(std::string & input, size_t & i)
{
  std::string result = "";
  while (i < input.length() and input[i] != ' ')
  {
    result += input[i];
    i++;
  }
  i++;
  return result;
}

size_t reznikova::getKey(std::string & input, size_t & i)
{
  std::string result = "";
  while (i < input.length() and input[i] != ' ' and isdigit(input[i]))
  {
    result += input[i];
    i++;
  }
  i++;
  return std::stoul(result);
}

void reznikova::readFromFile(std::ifstream & is, Tree< std::string, Tree< size_t, std::string > > & treeMap)
{
  std::string input;
  while (getline(is, input))
  {
    size_t i = 0;
    std::string name = getValue(input, i);
    Tree< size_t, std::string > tree;
    while (i < input.length())
    {
      size_t key = getKey(input, i);
      std::string value = getValue(input, i);
      tree.insert(key, value);
    }
    treeMap.insert(name, tree);
  }
}

void reznikova::print(Tree< std::string, Tree< size_t, std::string > > & treeMap)
{
  std::string name;
  std::cin >> name;
  Tree< std::string, Tree< size_t, std::string > >::ConstIterator it = treeMap.find(name);
  if (it == treeMap.cend())
  {
    outputInvalidCommand(std::cout);
    return;
  }
  else if (it->second.isEmpty())
  {
    outputError(std::cout);
    return;
  }
  std::cout << name;
  Tree< size_t, std::string >::ConstIterator dictIt = it->second.cbegin();
  while (dictIt != it->second.cend())
  {
    std::cout <<  " " << dictIt->first << " " << dictIt->second;
    ++dictIt;
  }
  std::cout << "\n";
}

void reznikova::complement(Tree< std::string, Tree< size_t, std::string > > & treeMap)
{
  std::string newDict;
  std::string firstDict;
  std::string secondtDict;
  std::cin >> newDict >> firstDict >> secondtDict;
  Tree< std::string, Tree< size_t, std::string > >::ConstIterator firstIt = treeMap.find(firstDict);
  Tree< std::string, Tree< size_t, std::string > >::ConstIterator secondIt = treeMap.find(secondtDict);
  if (firstIt == treeMap.cend() or secondIt == treeMap.cend())
  {
    outputInvalidCommand(std::cout);
    return;
  }
  Tree< size_t, std::string > dictionary;
  Tree< size_t, std::string >::ConstIterator firstSubIter = firstIt->second.cbegin();
  while (firstSubIter != firstIt->second.cend())
  {
    if (secondIt->second.find(firstSubIter->first) == secondIt->second.cend())
    {
      dictionary.insert(firstSubIter->first, firstSubIter->second);
    }
    firstSubIter++;
  }
  Tree< size_t, std::string >::ConstIterator secondSubIter = secondIt->second.cbegin();
  while (secondSubIter != secondIt->second.cend())
  {
    if (firstIt->second.find(secondSubIter->first) == firstIt->second.cend())
    {
      dictionary.insert(secondSubIter->first, secondSubIter->second);
    }
    secondSubIter++;
  }
  treeMap.insert(newDict, dictionary);
}
