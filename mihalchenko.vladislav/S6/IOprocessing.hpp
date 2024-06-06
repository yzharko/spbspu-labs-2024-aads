#ifndef IO_PROCESSING_HPP
#define IO_PROCESSING_HPP
#include <iostream>
#include <iomanip>
#include <deque>
#include <list>
#include <list.hpp>
#include <algorithm>
#include "sorts.hpp"

namespace mihalchenko
{
  void fillContainerWithRandomNumbers(int size, std::deque<int> &deque, List<int> forward_list, std::list<int> &bidirect_list);
  void fillContainerWithRandomNumbers(int size, std::deque<double> &deque, List<double> forward_list, std::list<double> &bidirect_list);
  template <typename T>
  void printContainer(std::ostream &, const T &container);

  template <typename T, typename Compare>
  void makeSorted(std::ostream &out, size_t size, Compare compare);
}

void fillRandIntsContainer(int size, std::deque<int> &deque, List<int> forward_list, std::list<int> &bidirect_list)
{
  for (int i = 0; i < size; i++)
  {
    deque.push_back(rand() % 100);
  }
  std::copy(deque.begin(), deque.end(), std::back_inserter(forward_list));
  std::copy(deque.begin(), deque.end(), std::back_inserter(bidirect_list));
}

void fillRandDoublesContainer(int size, std::deque<double> &deque, List<double> forward_list, std::list<double> &bidirect_list)
{
  for (auto i = 0; i < size; i++)
  {
    deque.push_back(double(rand() % 1000) / double(rand() % 100));
  }
  std::copy(deque.begin(), deque.end(), std::back_inserter(forward_list));
  std::copy(deque.begin(), deque.end(), std::back_inserter(bidirect_list));
}

template <typename T>
void mihalchenko::printContainer(std::ostream &out, const T &container)
{
  for (auto iter = container.cbegin(); iter != container.cend(); iter++)
  {
    out << std::fixed << std::setprecision(1) << *iter;
    if (++iter == container.cend())
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
void mihalchenko::makeSorted(std::ostream &out, size_t size, Compare compare)
{
  List<T> forward_list;
  std::list<T> bidirect_list;
  std::deque<T> deque;

  fillRandDoublesContainer(size, deque, bidirect_list, forward_list);

  printContainer(out, bidirect_list);
  quickSort(bidirect_list.begin(), bidirect_list.end(), compare);
  printContainer(out, bidirect_list);

  quickSort(forward_list.begin(), forward_list.end(), compare);
  printContainer(out, forward_list);
  mergeSort(forward_list.begin(), forward_list.end(), compare);
  printContainer(out, forward_list);

  quickSort(deque.begin(), deque.end(), compare);
  printContainer(out, deque);
  mergeSort(deque.begin(), deque.end(), compare);
  printContainer(out, deque);
  std::sort(deque.begin(), deque.end(), compare);
  printContainer(out, deque);
}

#endif
