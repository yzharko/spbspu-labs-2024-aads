#ifndef IO_PROCESSING_HPP
#define IO_PROCESSING_HPP
#include <iostream>
#include <iomanip>
#include <deque>
#include <list>
#include <list.hpp>
#include <algorithm>
// #include "sorts.hpp"
// #include "details.hpp"
#include "IOprocessing.hpp"

namespace mihalchenko
{
  void fillContainerWithRandomNumbers(int size, std::deque<int> &deque, std::list<int> &bidirect_list, List<int> forward_list);
  void fillContainerWithRandomNumbers(int size, std::deque<double> &deque, std::list<double> &bidirect_list, List<double> forward_list);
  template <typename T>
  void printContainer(std::ostream &, const T &container);
}

void fillRandIntsContainer(int size, std::deque<int> &deque, std::list<int> &bidirect_list, List<int> forward_list)
{
  for (int i = 0; i < size; i++)
  {
    deque.push_back(rand() % 100);
  }
  std::copy(deque.begin(), deque.end(), std::back_inserter(forward_list));
  std::copy(deque.begin(), deque.end(), std::back_inserter(bidirect_list));
}

void fillRandDoublesContainer(int size, std::deque<double> &deque, std::list<double> &bidirect_list, List<double> forward_list)
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

#endif
