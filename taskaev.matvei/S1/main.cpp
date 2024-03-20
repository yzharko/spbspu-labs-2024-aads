#include <iostream>
#include <limits>
#include <utility>
#include <string>
#include "List.hpp"


int main()
{
  using namespace taskaev;
  List< std::pair< std::string, List < size_t > > > list;
  std::string name = "";
  std::cin >> name;
  while(std::cin)
  {
    list.pushFront({ name, List<size_t>()});
    while(std::cin >> name && !std::isalpha(name[0]))
    {
      list.front().second.pushBack(std::stoull(name));
    }
  }
  if(list.empty())
  {
    std::cout << "0\n";
    return 0;
  }
  list.reverse();
  typename List<std::pair<std::string, List<size_t>>>::ListIterator< std::pair< std::string, List<size_t>>> i = list.begin();
  while(i != list.end())
  {
    std::cout << i->first;
    if(++i != list.end())
    {
      std::cout << " ";
    }
  }
  List<size_t> sums;
  size_t maxNum = 1;
  i = list.begin();
  while (i != list.end())
  {
    size_t j = 0;
    auto it = i->second.begin();
    while (it != i->second.end())
    {
      j++;
      maxNum = (maxNum > j) ? maxNum : j;
      it++;
    }
    i++;
  }
  if (maxNum != 1)
  {
    std::cout << "\n";
  }
  bool bools = false;
  size_t sum;
  size_t j = 0;
  const size_t maxLimit = std::numeric_limits< size_t >::max();
  while (j < maxNum)
  {
    j++;
    sum = 0;
    i = list.begin();
    while (i != list.end())
    {
      if (!i->second.empty())
      {
        if (sum > 0 || bools)
        {
          std::cout << " ";
        }
        if (maxLimit - sum >= i->second.front())
        {
          sum += i->second.front();
        }
        else
        {
          bools = true;
        }
        std::cout << i->second.front();
        i->second.popFront();
      }
      i++;
    }
    std::cout << "\n";
    sums.pushFront(sum);
    if (bools)
    {
      std::cerr << " Stack Overflow error!\n";
      return 1;
    }
  }
  sums.reverse();
  typename List<size_t>::ListIterator<size_t> is = sums.begin();
  if(!sums.empty())
  {
    while(is != sums.end())
    {
      std::cout << *is;
      if(++is != sums.end())
      {
        std::cout << " ";
      }
    }
  }
  else
  {
    std::cout << "0\n";
  }
  std::cout << "\n";
  return 0;
}
