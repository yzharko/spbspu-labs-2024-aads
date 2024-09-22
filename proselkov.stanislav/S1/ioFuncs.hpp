#ifndef IO_FUNCS
#define IO_FUNCS
#include <iostream>
#include <limits>
#include <utility>
#include <algorithm>
#include "List.hpp"
#include "divideFuncs.hpp"

using depot_t = proselkov::List< std::pair< std::string, proselkov::List< unsigned long long > > >;

namespace proselkov
{
  template< typename T >
  void inputData(depot_t& lines, size_t& maxDigits);

  template< typename T >
  void outOrds(depot_t& lines);

  template< typename T >
  List< T > outDigits(depot_t& lines, size_t& maxDigits, bool& isOverflow);

  template< typename T >
  void outSums(List< T >& sums);
}

template<typename T>
void proselkov::inputData(depot_t& lines, size_t& maxDigits)
{
  depot_t::Iterator iterLine;
  std::string line = "";

  while (std::getline(std::cin, line))
  {
    if (line.size() != 0)
    {
      std::string ord = proselkov::getOrd(line);
      std::pair< std::string, proselkov::List< unsigned long long > > pair = { ord, {} };
      lines.pushBack(pair);
      iterLine = lines.begin();
      for (size_t i = 0; i < (lines.getSize() - 1); i++)
      {
        iterLine++;
      }
      size_t cntDigits = 0;
      while (line.size() != 0)
      {
        unsigned long long digit = proselkov::getDigit(line);
        (*iterLine).second.pushBack(digit);
        cntDigits++;
      }
      maxDigits = std::max(maxDigits, cntDigits);
    }
  }
}

template< typename T >
void proselkov::outOrds(depot_t& lines)
{
  depot_t::Iterator iterLine = lines.begin();
  for (size_t i = 0; i < lines.getSize(); i++)
  {
    std::cout << (*iterLine).first;
    iterLine++;
    if (i < (lines.getSize() - 1))
    {
      std::cout << ' ';
    }
    else
    {
      std::cout << '\n';
    }
  }
}

template< typename T >
proselkov::List< T > proselkov::outDigits(depot_t& lines, size_t& maxDigits, bool& isOverflow)
{
  unsigned long long maxUll = std::numeric_limits< unsigned long long >::max();
  depot_t::Iterator iterLine = lines.begin();
  typename List< T >::Iterator iterDig;
  List< T > sums;
  T curSum = 0;
  for (size_t i = 0; i < maxDigits; i++)
  {
    curSum = 0;
    iterLine = lines.begin();
    for (iterLine = lines.begin(); iterLine != lines.end(); iterLine++)
    {
      iterDig = (*iterLine).second.begin();
      if ((*iterLine).second.getSize() > i)
      {
        iterDig = i != 0 ? (iterDig + i) : iterDig;
        curSum != 0 ? std::cout << ' ' << *iterDig : std::cout << *iterDig;
        *iterDig > (maxUll - curSum) ? isOverflow = true : curSum += *iterDig;
      }
    }
    sums.pushBack(curSum);
    std::cout << '\n';
  }
  return sums;
}

template< typename T >
void proselkov::outSums(List< T >& sums)
{
  if (sums.isEmpty())
  {
    std::cout << 0;
  }
  else
  {
    typename proselkov::List< T >::Iterator iterSums = sums.begin();
    for (size_t i = 0; i < sums.getSize(); i++)
    {
      if (i != 0)
      {
        std::cout << ' ';
      }
      std::cout << *iterSums;
      iterSums++;
    }
  }
  std::cout << '\n';
}

#endif
