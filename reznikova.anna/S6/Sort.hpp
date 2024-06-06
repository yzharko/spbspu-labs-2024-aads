#ifndef SORT_HPP
#define SORT_HPP

#include <algorithm>
#include <iterator>
#include <vector>

namespace reznikova
{
  template< typename Iterator, typename Comparator >
  void qsort(Iterator first, Iterator last, Comparator cmp);
  template< typename Iterator, typename Comparator >
  void shaker(Iterator first, Iterator last, Comparator cmp);
}


template<typename Iterator, typename Comparator>
void reznikova::qsort(Iterator first, Iterator last, Comparator cmp) {
  if (first == last || (first != last && ++Iterator(first) == last))
  {
    return;
  }
  auto pivot = *first;
  Iterator left = first;
  Iterator right = last;
  --right;
  while (left != right)
  {
    while (left != right && !cmp(*right, pivot))
    {
      --right;
      if (left != right)
      {
        std::iter_swap(left, right);
        ++left;
      }
    }
    while (left != right && cmp(*left, pivot))
    {
      ++left;
      if (left != right)
      {
        std::iter_swap(left, right);
        --right;
      }
    }
  }
  qsort(first, left, cmp);
  qsort(++left, last, cmp);
}



template<typename Iterator, typename Comparator>
void reznikova::shaker(Iterator first, Iterator last, Comparator cmp)
{
  bool swapped = true;
  while (swapped)
  {
    swapped = false;
    auto current = first;
    auto next = current;
    if (next != last)
    {
      ++next;
    }
    if (next == last)
    {
      return;
    }
    auto prev = current;
    ++current;
    while (next != last)
    {
      if (cmp(*next, *prev))
      {
        std::swap(*next, *prev);
        swapped = true;
      }
      ++prev;
      ++current;
      ++next;
    }
    if (!swapped)
    {
      break;
    }
    swapped = false;
    next = prev;
    current = first;
    prev = current;
    ++current;
    while (current != next) 
    {
      if (cmp(*current, *prev)) 
      {
        std::swap(*current, *prev);
        swapped = true;
      }
      ++prev;
      ++current;
    }
  }
}

#endif
