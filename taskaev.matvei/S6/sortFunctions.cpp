#include <iostream>
#include <algorithm>

#include "sortFunctions.hpp"

namespace taskaev
{
  template <typename Iterator, typename Comparator >
  void Shaker(Iterator begin, Iterator end, Comparator comp)
  {
    auto ends = std::prev(end);
    bool flag = true;
    while (flag)
    {
      flag = false;
      for (auto i = begin; i != ends; i++)
      {
	auto next = std::next(i);
	if (!comp(*i, next))
	{
	  std::swap(*i, *next);
	  flag = true;
        }
      }
      ends = std::prev(ends);
      for (auto i = ends; i != begin; i--)
      {
	auto prevs = std::prev(i);
	if (!comp(*i, next))
	{
          std::swap(*i, *next);
          flag = true;
	}
      }
      begin = std::next(begin);
    }
  }

  template <typename Iterator, typename Comparator >
  void Selection(Iterator begin, Iterator end, Comparator comp)
  {
    for (Iterator current = begin; curent != end; current++)
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
