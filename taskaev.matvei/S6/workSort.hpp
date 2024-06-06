#ifndef WORKSORT_HPP
#define WORKSORT_HPP
#include <iostream>
#include <deque>
#include <list>
#include <deque>
#include <iomanip>
#include <random>
#include "sortFunctions.hpp"
#include <List.hpp>

namespace taskaev
{
  template< typename It >
  void print(const It& it, std::ostream& out);

  template <typename T, typename Comparator>
  void generateData(size_t size, std::deque< T >& queue, List< T >& list);

  template< typename T, typename Comparator >
  void workSortings(std::ostream& out, size_t size);
}

#endif
