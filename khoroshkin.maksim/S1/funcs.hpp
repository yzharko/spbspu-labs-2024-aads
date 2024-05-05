#ifndef FUNCS_HPP
#define FUNCS_HPP

#include <iostream>
#include <limits>
#include <stdexcept>
#include "list.hpp"

namespace khoroshkin
{
  template < typename T >
  void printResult(std::ostream & out, List< std::pair< std::string, List< T > > > & allPairs, size_t maxLength);
  template < typename T >
  bool checkAllNext(size_t index, typename List< T >::iterator it, List< T > & allPairs);
}

using namespace khoroshkin;

template < typename T >
void khoroshkin::printResult(std::ostream & out, List< std::pair< std::string, List< T > > > & allPairs, size_t maxLength)
{
  using type = std::pair<std::string, khoroshkin::List< T > >;
  if (allPairs.getSize() == 0)
  {
    throw std::logic_error("Empty list");
  }

  for (auto it = allPairs.begin(); it != allPairs.end(); ++it)
  {
    out << (*it).first;
    allPairs.next(it) == allPairs.end() ? std::cout << "\n" : std::cout << " ";
  }

  if (allPairs[0].second.isEmpty())
  {
    throw std::logic_error("Empty list");
  }

  for (size_t i = 0; i < maxLength; i++)
  {
    for (auto it = allPairs.begin(); it != allPairs.end(); it++)
    {
      if ((*it).second.getSize() > i)
      {
        out << (*it).second[i];
        (allPairs.next(it) == allPairs.end() || !checkAllNext< type >(i, it, allPairs)) ? out << "\n" : out << " ";
      }
    }
  }

  List< unsigned long long > sumList;
  for (size_t i = 0; i < maxLength; i++)
  {
    unsigned long long sum = 0;
    for (auto it = allPairs.begin(); it != allPairs.end(); it++)
    {
      if ((*it).second.getSize() > i)
      {
        if (std::numeric_limits< unsigned long long >::max() - sum < (*it).second[i])
        {
          throw std::overflow_error("overflow!");
        }
        sum += (*it).second[i];
      }
    }
    sumList.push_back(sum);
  }
  for (auto it = sumList.begin(); it != sumList.end(); ++it)
  {
    out << *it;
    (sumList.next(it) == sumList.end()) ? out << "\n" : out << " ";
  }
}

template < typename T>
bool khoroshkin::checkAllNext(size_t index, typename List< T >::iterator it, List< T > & allPairs)
{
  while (allPairs.next(it) != allPairs.end())
  {
    if (static_cast< long long >((*allPairs.next(it)).second.getSize()) - 1 >= static_cast< long long>(index))
    {
      return true;
    }
    ++it;
  }
  return false;
}

#endif
