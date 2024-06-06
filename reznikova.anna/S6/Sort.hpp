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
void reznikova::qsort(Iterator first, Iterator last, Comparator cmp)
{
  if (first == last)
  {
    return;
  }
  auto pivot = *first;
  Iterator left = first;
  Iterator right = last;
  --right;
  while (true)
  {
    while (left != right && cmp(*left, pivot))
    {
      ++left;
    }
    while (left != right && !cmp(*right, pivot))
    {
      --right;
    }
    if (left == right)
    {
      break;
    }
    auto temp = *left;
    *left = *right;
    *right = temp;
  }
  Iterator mid = left;
  if (!cmp(*first, pivot))
  {
    auto temp = *first;
    *first = *mid;
    *mid = temp;
  }
  Iterator mid_next = mid;
  ++mid_next;
  qsort(first, mid, cmp);
  qsort(mid_next, last, cmp);
}

template<typename Iterator, typename Comparator>
void reznikova::shaker(Iterator first, Iterator last, Comparator cmp)
{
  if (first == last)
  {
    return;
  }
  bool swapped = true;
  while (swapped)
  {
    swapped = false;
    for (Iterator it = first; it != last; ++it)
    {
      Iterator next_it = it;
      ++next_it;
      if (next_it == last)
      {
        break;
      }
      if (!cmp(*it, *next_it))
      {
        auto temp = *it;
        *it = *next_it;
        *next_it = temp;
        swapped = true;
      }
    }
    if (!swapped)
    {
      break;
    }
    swapped = false;
    Iterator last_it = last;
    --last_it;
    for (Iterator it = last_it; it != first; --it)
    {
      Iterator prev_it = it;
      --prev_it;
      if (cmp(*it, *prev_it))
      {
        auto temp = *it;
        *it = *prev_it;
        *prev_it = temp;
        swapped = true;
      }
    }
    ++first;
    --last;
  }
}

#endif
