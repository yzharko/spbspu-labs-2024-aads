#ifndef IO_PROCESSING_HPP
#define IO_PROCESSING_HPP
#include <iostream>
#include <iomanip>
#include <deque>
#include <list>
#include <list.hpp>
#include <algorithm>
// #include <random>
#include "sorts.hpp"

namespace mihalchenko
{
  void fillContainerWithRandomNumbers(size_t size, List<int> forward_list, std::list<int> &bidirect_list, std::deque<int> &deque);
  void fillContainerWithRandomNumbers(size_t size, List<double> forward_list, std::list<double> &bidirect_list, std::deque<double> &deque);
  template <typename T>
  void printContainer(std::ostream &, const T &container);

  template <typename T, typename Compare>
  void testSorts(std::ostream &out, size_t size, Compare compare);
}

void fillRandIntsContainer(size_t size, mihalchenko::List<int> forward_list, std::list<int> &bidirect_list, std::deque<int> &deque)
{
  for (size_t i = 0; i < size; i++)
  {
    forward_list.push_back(rand() % 100);
  }
  std::copy(forward_list.begin(), forward_list.end(), std::back_inserter(bidirect_list));
  std::copy(forward_list.begin(), forward_list.end(), std::back_inserter(deque));
}

void fillRandDoublesContainer(size_t size, mihalchenko::List<double> forward_list, std::list<double> &bidirect_list, std::deque<double> &deque)
{
  for (size_t i = 0; i < size; i++)
  {
    forward_list.push_back(double(rand() % 1000) / double(rand() % 100));
  }
  std::copy(forward_list.begin(), forward_list.end(), std::back_inserter(bidirect_list));
  std::copy(forward_list.begin(), forward_list.end(), std::back_inserter(deque));
}

template <typename T>
void mihalchenko::printContainer(std::ostream &out, const T &container)
{
  for (auto iter = container.begin(); iter != container.end(); iter++)
  {
    out << std::fixed << std::setprecision(1) << *iter;
    if (++iter == container.end())
    {
      out << "\n";
    }
    else
    {
      out << " ";
    }
  }
}

template <typename T, typename Compare>
void mihalchenko::testSorts(std::ostream &out, size_t size, Compare compare)
{
  List<T> forward_list;
  std::list<T> bidirect_list;
  std::deque<T> deque;

  fillRandDoublesContainer(size, forward_list, bidirect_list, deque);

  printContainer(out, forward_list);
  quickSort(forward_list.begin(), forward_list.end(), compare);
  printContainer(out, forward_list);

  quickSort(bidirect_list.begin(), bidirect_list.end(), compare);
  printContainer(out, bidirect_list);
  mergeSort(bidirect_list.begin(), bidirect_list.end(), compare);
  printContainer(out, bidirect_list);

  quickSort(deque.begin(), deque.end(), compare);
  printContainer(out, deque);
  mergeSort(deque.begin(), deque.end(), compare);
  printContainer(out, deque);
  std::sort(deque.begin(), deque.end(), compare);
  printContainer(out, deque);
}

#endif
