#ifndef SORTFUNCTIONS_HPP
#define SORTFUNCTIONS_HPP
#include <iostream>
#include <algorithm>

namespace taskaev
{
  template <typename Iterator, typename Comparator >
  void Shaker(Iterator begin, Iterator end, Comparator comp)
  {
    if (begin == end || std::next(begin) == end)
    {
      return;
    }
    Iterator one = begin;
    Iterator two = begin;
    while (std::next(two) != end)
    {
      ++two;
    }
    while (true)
    {
      bool flag = false;
      Iterator iter = begin;
      while (iter != two)
      {
        Iterator next = std::next(iter);
        if (comp(*next, *iter))
        {
          std::iter_swap(iter, next);
          flag = true;
        }
        iter++;
      }
      if (!flag)
      {
        break;
      }
      if (one == two)
      {
        break;
      }
      --two;
      flag = false;
      Iterator iter = end;
      while (iter != begin)
      {
        Iterator prev = std::prev(iter);
        if (comp(*iter, *prev))
        {
          std::iter_swap(iter, prev);
          flag = true;
        }
        iter--;
      }
      if (!flag)
      {
        break;
      }
      if (one == two)
      {
        break;
      }
      ++one;
    }
  }

  template <typename Iterator, typename Comparator >
  void Selection(Iterator begin, Iterator end, Comparator comp)
  {
    while (begin != end)
    {
      Iterator one = begin;
      Iterator two = begin;
      while (two != end)
      {
        if(comp(*two, *one))
        {
          one = two;
        }
        two++;
      }
      std::swap(*one, *begin);
      begin++;
    }
  }
}

#endif
