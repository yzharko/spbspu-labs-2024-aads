#include "HelpFunc.hpp"
#include "List.hpp"
#include "Node.hpp"
#include "ListIterator.hpp"
#include <string>
#include <utility>
#include <stddef.h>
#include <limits>

sukacheva::List<std::pair<std::string, sukacheva::List<size_t>>> sukacheva::listInput(std::istream& in)
{
  std::string name = "";
  List< size_t > args;
  List< std::pair< std::string, List< size_t > > > resultList;
  in >> name;
  while (in) {
     resultList.pushBack({ name, args });
     while (in >> name && std::isdigit(name[0])) {
       resultList.tail->data.second.pushBack(std::stoul(name));
     }
  }
  return resultList;
}

size_t sukacheva::maxListSize(List< std::pair< std::string, List< size_t > > >& newList) {
  size_t size = 0;
  size_t maxSize = 0;
  Iterator<std::pair< std::string, List< size_t > >> it = newList.begin();
  while (it.node){
    size = it.node->data.second.listSize;
    maxSize = (maxSize < size ? size : maxSize);
    it++;
  }
  return maxSize;
}

void sukacheva::printNameList(List< std::pair< std::string, List< size_t > > >& newList)
{
  Iterator<std::pair< std::string, List< size_t > >> it = newList.begin();
  do {
    std::cout << it.node->data.first;
    if (it.node->next) {
      std::cout << " ";
    }
    it++;
  } while (it.node);
  std::cout << "\n";
}

void sukacheva::printArgs(List<std::pair<std::string, List<size_t>>>& newList)
{
  Iterator<std::pair< std::string, List< size_t > >> it = newList.begin();
  List<size_t> sumOfArgs;
  const size_t maxSum = std::numeric_limits< size_t >::max();
  bool overflowFlag = false;
  for (size_t i = 0; i < maxListSize(newList); i++) {
    it = newList.begin();
    size_t sum = 0;
    while (it.node) {
      if (it.node->data.second[i])
      {
        if (sum > 0) {
          std::cout << " ";
        }
        std::cout << it.node->data.second[i]->data;
        if (sum > maxSum - it.node->data.second[i]->data)
        {
          overflowFlag = true;
          std::cout << "\n";
          throw std::overflow_error("overflow!!");
        }
        else
        {
          sum += it.node->data.second[i]->data;
        }
      }
      it++;
    }
    std::cout << "\n";
    sumOfArgs.pushBack(sum);
  }
  if (!overflowFlag)
  {
    Iterator<size_t> itSum = sumOfArgs.begin();
    do {
      std::cout << itSum.node->data;
      if (itSum.node->next) {
        std::cout << " ";
      }
      itSum++;
    } while (itSum.node);
    std::cout << "\n";
  }
}
