#ifndef SORT_HPP
#define SORT_HPP

#include <algorithm>
#include <iterator>
#include <vector>

namespace reznikova
{
  template<typename Iterator, typename Comparator>
  Iterator partition(Iterator first, Iterator last, Comparator cmp);
  template< typename Iterator, typename Comparator >
  void qsort(Iterator first, Iterator last, Comparator cmp);
  template< typename Iterator, typename Comparator >
  void shaker(Iterator first, Iterator last, Comparator cmp);
}


template<typename Iterator, typename Comparator>
Iterator reznikova::partition(Iterator first, Iterator last, Comparator cmp)
{
  Iterator pivot = first;
  Iterator i = first;
  Iterator j = first;
  std::advance(j, 1);
  while (j != last)
  {
    if (cmp(*j, *pivot))
    {
      ++i;
      std::iter_swap(i, j);
    }
    ++j;
  }
  std::iter_swap(first, i);
  return i;
}

template<typename Iterator, typename Comparator>
void reznikova::qsort(Iterator first, Iterator last, Comparator cmp) {
  if (first == last)
  {
    return;
  }
  Iterator next_first = first;
  std::advance(next_first, 1);
  if (next_first == last)
  {
    return;
  }
  Iterator pivot = partition(first, last, cmp);
  qsort(first, pivot, cmp);
  std::advance(pivot, 1);
  qsort(pivot, last, cmp);
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
