k#ifndef SORT_HPP
#define SORT_HPP

#include <algorithm>
#include <iterator>
#include <vector>
#include <stack>
#include <pair>

namespace reznikova
{
  template< typename Iterator, typename Comparator >
  void qsort(Iterator first, Iterator last, Comparator cmp);
  template< typename Iterator, typename Comparator >
  void shaker(Iterator first, Iterator last, Comparator cmp);
}

template<typename Iterator, typename Comparator>
void reznikova::qsort(Iterator first, Iterator last, Comparator cmp)
{
  if (first == last || Iterator(++first) == last)
  {
    return;
  }
  std::stack<std::pair<Iterator, Iterator>> stack;
  stack.push({first, last});
  while (!stack.empty())
  {
    Iterator left = stack.top().first;
    Iterator right = stack.top().second;
    stack.pop();
    Iterator pivot = Iterator(right--);
    Iterator i = left;
    Iterator j = left;
    while (j != pivot)
    {
      if (cmp(*j, *pivot))
      {
        std::iter_swap(i, j);
        ++i;
      }
      ++j;
    }
    std::iter_swap(i, pivot);
    if (i != left)
      stack.push({left, i});
    if (Iterator(i++) != right)
      stack.push({Iterator(i++), right});
  }
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

