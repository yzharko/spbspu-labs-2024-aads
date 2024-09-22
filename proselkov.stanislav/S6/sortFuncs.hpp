#ifndef SORT_FUNCS_HPP
#define SORT_FUNCS_HPP
#include <iomanip>
#include <deque>
#include <forward_list>
#include <List.hpp>
#include "insertSort.hpp"
#include "selectSort.hpp"

namespace proselkov
{
  void fillDepots(size_t size, List< int >& list, std::forward_list< int >& fList, std::deque< int >& deque);
  void fillDepots(size_t size, List< double >& list, std::forward_list< double >& fList, std::deque< double >& deque);

  template< typename T >
  std::ostream& outDepot(std::ostream& out, const T& depot);

  template< typename T, typename Compare >
  void makeSorted(std::ostream& out, size_t size, Compare compare);
}

void proselkov::fillDepots(size_t size, List< int >& list, std::forward_list< int >& fList, std::deque< int >& deque)
{
  for (size_t i = 0; i < size; ++i)
  {
    list.pushFront(rand() % 100);
  }

  std::copy(list.begin(), list.end(), std::front_inserter(fList));
  std::copy(list.begin(), list.end(), std::back_inserter(deque));
}

void proselkov::fillDepots(size_t size, List< double >& list, std::forward_list< double >& fList, std::deque< double >& deque)
{
  for (size_t i = 0; i < size; ++i)
  {
    list.pushFront(double(rand() % 1000) / double(rand() % 100));
  }

  std::copy(list.begin(), list.end(), std::front_inserter(fList));
  std::copy(list.begin(), list.end(), std::back_inserter(deque));
}

template< typename T >
std::ostream& proselkov::outDepot(std::ostream& out, const T& depot)
{
  for (auto iter = depot.begin(); iter != depot.end(); iter++)
  {
    out << std::fixed << std::setprecision(1) << *iter;
    if (std::next(iter) == depot.end())
    {
      out << "\n";
    }
    else
    {
      out << " ";
    }
  }
  return out;
}

template< typename T, typename Compare >
void proselkov::makeSorted(std::ostream& out, size_t size, Compare compare)
{
  List< T > list;
  std::forward_list< T > fList;
  std::deque< T > deque;

  fillDepots(size, list, fList, deque);

  outDepot(out, fList);
  sortSelect(fList.begin(), fList.end(), compare);
  outDepot(out, fList);

  sortSelect(list.begin(), list.end(), compare);
  outDepot(out, list);
  sortInsert(list.begin(), list.end(), compare);
  outDepot(out, list);

  sortSelect(deque.begin(), deque.end(), compare);
  outDepot(out, deque);
  sortInsert(deque.begin(), deque.end(), compare);
  outDepot(out, deque);
  std::sort(deque.begin(), deque.end(), compare);
  outDepot(out, deque);
}

#endif
