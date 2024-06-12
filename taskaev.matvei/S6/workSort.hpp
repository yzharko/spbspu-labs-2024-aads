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
  template < typename Iterators >
  void print(Iterators& iter, std::ostream& out)
  {
    out << *iter.begin();;
    ++iter.begin();
    while (iter.begin() != iter.end())
    {
      out << " " << *iter.begin();
      ++iter.begin();
    }
    out << "\n";
  }

  template <typename T >
  void generateData(size_t size, std::string types, List< T >& myList, std::forward_list< T >& list, std::deque< T >& queue)
  {
    std::random_device rd;
    std::mt19937 gen(rd());
    for (size_t i = 0; i < size; ++i)
    {
      if (types == "ints")
      {
        std::uniform_int_distribution< int > dis(-10000, 10000);
        int val = dis(gen);
        myList.pushBack(val);
        list.push_back(val);
        queue.push_back(val);
      }
      else if (types == "floats")
      {
        std::uniform_int_distribution< float > dis(0.0f, 99.9f);
        float val = dis(gen);
        myList.pushBack(val);
        list.push_back(val);
        queue.push_back(val);
      }
    }
  }

  template< typename T, typename Comparator >
  void workSortings(std::ostream& out, std::string types, size_t size, Comparator comp)
  {
    List< T > myList;
    std::forward_list< T > lits;
    std::deque< T > queue;
    generateData(size, types, myList, list, queue);
  }
}

#endif