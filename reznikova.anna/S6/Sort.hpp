#ifndef SORT_HPP
#define SORT_HPP

#include <algorithm>
#include <vector>
#include <iterator>

namespace reznikova
{
  template< typename Iterator, typename Comparator >
  void qsort(Iterator first, Iterator last, Comparator cmp);
  template< typename Iterator, typename Comparator >
  void shaker(Iterator first, Iterator last, Comparator cmp);
}

template< typename Iterator, typename Comparator >
void reznikova::qsort(Iterator first, Iterator last, Comparator cmp)
{
  if (first == last || std::next(first) == last)
  {
    return;
  }
  auto pivot = *first;
  std::vector<typename std::iterator_traits<Iterator>::value_type> less;
  std::vector<typename std::iterator_traits<Iterator>::value_type> greater;
  for (Iterator it = std::next(first); it != last; ++it)
  {
    if (cmp(*it, pivot))
    {
      less.push_back(*it);
    }
    else
    {
      greater.push_back(*it);
    }
  }
  Iterator it = first;
  for (const auto & elem : less)
  {
    *it = elem;
    ++it;
  }
  *it = pivot;
  ++it;
  for (const auto & elem : greater)
  {
    *it = elem;
    ++it;
  }
  qsort(first, std::next(first, less.size()), cmp);
  qsort(std::next(first, less.size() + 1), last, cmp);
}

template<typename Iterator, typename Comparator>
void shaker(Iterator first, Iterator last, Comparator cmp)
{
  if (first == last)
  {
    return;
  }
  bool swapped = true;
  while (swapped)
  {
    swapped = false;
    for (Iterator it = first; it != std::prev(last); ++it)
    {
      Iterator next_it = std::next(it);
      if (!cmp(*it, *next_it))
      {
        std::iter_swap(it, next_it);
        swapped = true;
      }
    }
    if (!swapped)
    {
      break;
    }
    swapped = false;
    last = std::prev(last);
    for (Iterator it = std::prev(last); it != first; --it)
    {
      Iterator prev_it = std::prev(it);
      if (cmp(*it, *prev_it))
      {
        std::iter_swap(it, prev_it);
        swapped = true;
      }
    }
    first = std::next(first);
  }
}

#endif

