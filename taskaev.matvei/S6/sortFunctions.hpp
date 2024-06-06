#ifndef SORTFUNCTIONS_HPP
#define SORTFUNCTIONS_HPP
#include <iostream>
#include <algorithm>

namespace taskaev
{
  template <typename Iterator, typename Comparator >
  void Shaker(Iterator begin, Iterator end, Comparator comp)
  {
    Iterator left = begin;
    Iterator right = end;
    right--;
    bool sortFlag = true;

    while (sortFlag)
    {
      sortFlag = false;

      for (auto it = left; it != right; it++)
      {
        if (comp(*std::next(it), *it))
        {
          std::iter_swap(it, std::next(it));
          sortFlag = true;
        }
      }

      for (auto it = right; it != left; it--)
      {
        if (comp(*it, *std::prev(it)))
        {
          std::iter_swap(it, std::prev(it));
          sortFlag = true;
        }
      }

      left++;
      right--;
    }
  }

  template <typename Iterator, typename Comparator >
  void Selection(Iterator begin, Iterator end, Comparator comp)
  {
   for (Iterator current = begin; current != end; current++)
    {
      Iterator next = current;
      next++;
      if (next == end)
      {
        return;
      }
      Iterator min = current;
      for (; next != end; next++)
      {
        if (comp(*next, *min))
        {
          min = next;
        }
      }
      if (*min != *current)
      {
        std::swap(*min, *current);
      }
    }
  }
}

#endif
