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
  template< typename Iterator >
  void print(Iterator bagin, Iterator end, std::ostream& out)
  {
    out << *begin;
    begin++;
    while (begin != end)
    {
      out << " " << *begin;
      begin++;
    }
    out << "\n";
  }

  template <typename T, typename Comparator>
  void generateData(size_t size, std::deque< T >& queue, List< T >& list)
  {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-1000.0, 1000.0);

    for (size_t i = 0; i < size; ++i)
    {
      auto temp = static_cast<T>(dis(gen));
      queue.push_back(temp);
      list.pushFront(temp);
  }

  template< typename T, typename Comparator >
  void workSortings(std::ostream& out, size_t size)
  {
    std::deque < T > queue;
    List< T > list;

    generateData(size, queue, list);

    std::list< T > shakerSort(queue.begin(), queue.end());
    std::list< T > selectionSort(queue.begin(), queue.end());

    std::deque< T > sorts(queue.begin(), queue.end());
    std::deque< T > shakerS(queue.begin(), queue.end());
    std::deque< T > selectionS(queue.begin(), queue.end());

    print(queue.begin(), queue.end(), out);

    Shaker(shakerSort.begin(), shakerSort.end(), Comparator());
    print(shakerSort.begin(),shakerSort.end(), out);

    Selection(selectionSort.begin(), selectionSort.end(), Comparator());
    print(selectionSort.begin(),selectionSort.end(), out);

    std::sort(sorts.begin(), sorts.end(), Comparator());
    print(sorts.begin(),sorts.end(), out);

    Shaker(shakerS.begin(), shakerS.end(), Comparator());
    print(shakerS.begin(),shakerS.end(), out);

    Selection(selectionS.begin(), selectionS.end(), Comparator());
    print(selectionS.begin(), selectionS.end(), out);

    Shaker(list.begin(), list.end(), Comparator());
    print(list.begin(),list.end(), out);
  }
}

#endif
