#ifndef SORT_HPP
#define SORT_HPP

#include <algorithm>
#include <iterator>
#include <vector>
#include <stack>

namespace reznikova
{
  template< typename Iterator, typename Comparator >
  void qsort(Iterator first, Iterator last, Comparator cmp);
  template< typename Iterator, typename Compare >
  Iterator partition(Iterator left, Iterator right, Compare comparator);
  template< typename Iterator, typename Comparator >
  void shaker(Iterator first, Iterator last, Comparator cmp);
}

template<typename Iterator, typename Comparator>
void reznikova::qsort(Iterator first, Iterator last, Comparator cmp)
{
  if (first == last)
  {
    return;
  }
  Iterator pivot = first;
  Iterator left = first;
  Iterator right = std::next(first);
  while (right != last)
  {
    if (cmp(*right, *pivot))
    {
      std::swap(*left, *right);
      ++left;
    }
    ++right;
  }
  std::swap(*left, *pivot);
  qsort(first, left, cmp);
  qsort(std::next(left), last, cmp);
}

template< typename Iterator, typename Compare >
void reznikova::shaker(Iterator begin, Iterator end, Compare comp)
{
  if (std::next(begin) == end) {
    return;
  }
  bool isSwapped = false;
  do
  {
    for (Iterator i = begin; std::next(i, 1) != end; i++)
    {
      if (!comp(*i, *(std::next(i, 1))))
      {
        std::swap(*i, *(std::next(i, 1)));
        isSwapped = true;
      }
    }
    end--;
    if (!isSwapped)
    {
      break;
    }
    isSwapped = false;
    for (Iterator i = end; i != begin; i--)
    {
      if (comp(*i, *(std::next(i, -1))))
      {
        std::swap(*i, *(std::next(i, -1)));
        isSwapped = true;
      }
    }
    begin++;
  } while (isSwapped && begin != end);
}

#endif
