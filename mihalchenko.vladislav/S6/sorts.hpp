#ifndef SORTS_HPP
#define SORTS_HPP

#include <algorithm>
#include <list.hpp>
#include <iterator>
#include <forward_list>

namespace mihalchenko
{
  template < typename Iter, typename Compare >
  void quickSort(Iter begin, Iter end, Compare compare);

  template < typename Iter, typename Compare >
  Iter partOfQuickSort(Iter begin, Iter end, Compare compare);

  template < typename Iter, typename Compare >
  void mergeSort(Iter begin, Iter end, Compare compare);

  template < typename Iter, typename Compare >
  void merge(Iter begin, Iter center, Iter end, Compare compare);
}

template < typename Iter, typename Compare >
void mihalchenko::quickSort(Iter begin, Iter end, Compare compare)
{
  if (std::distance(begin, end) <= 1)
  {
    return;
  }
  Iter temp_pos = partOfQuickSort(begin, end, compare);
  quickSort(begin, temp_pos, compare);
  quickSort(std::next(temp_pos), end, compare);
}

template < typename Iter, typename Compare >
Iter mihalchenko::partOfQuickSort(Iter begin, Iter end, Compare compare)
{
  auto temp = *begin;
  Iter temp_pos = begin;
  ++begin;
  Iter part_iter = temp_pos;
  for (Iter iter = begin; iter != end; ++iter)
  {
    if (compare(*iter, temp))
    {
      ++part_iter;
      std::iter_swap(part_iter, iter);
    }
  }
  std::iter_swap(temp_pos, part_iter);
  return part_iter;
}

template < typename Iter, typename Compare >
void mihalchenko::mergeSort(Iter begin, Iter end, Compare compare)
{
  long long size = std::distance(begin, end);
  if (size < 2)
  {
    return;
  }
  Iter center = begin;
  for (long long i = 0; i < (size / 2); i++)
  {
    center++;
  }
  mergeSort(begin, center, compare);
  mergeSort(center, end, compare);
  merge(begin, center, end, compare);
}

template < typename Iter, typename Compare >
void mihalchenko::merge(Iter begin, Iter center, Iter end, Compare compare)
{
  mihalchenko::List< typename std::iterator_traits< Iter >::value_type > vector;
  Iter first = begin;
  Iter second = center;
  while (first != center && second != end)
  {
    if (compare(*first, *second))
    {
      vector.push_front(std::move(*first));
      first = std::next(first);
    }
    else
    {
      vector.push_front(std::move(*second));
      second = std::next(second);
    }
  }
  while (first != center)
  {
    vector.push_front(std::move(*first));
    first = std::next(first);
  }
  while (second != end)
  {
    vector.push_front(std::move(*second));
    second = std::next(second);
  }
  vector.reverse();
  auto temp_iter = vector.begin();
  for (auto it = begin; it != end; ++it)
  {
    *it = std::move(*temp_iter);
    temp_iter = std::next(temp_iter);
  }
}

#endif
