#ifndef SORTINGS_HPP
#define SORTINGS_HPP

#include <iterator>

namespace lisitsyna
{
  template < typename Iterator, typename Comparator >
  void sortInsertion(Iterator begin, Iterator end, Comparator comp)
  {
    for (auto it = begin; it != end; ++it)
    {
      auto current = *it;
      auto pos = it;
      while (pos != begin && comp(current, *std::prev(pos)))
      {
        *pos = *std::prev(pos);
        if (pos != begin) {
          --pos;
        }
      }

      *pos = current;
    }
  }

  template < class Iterator, class Compare >
  void bubblesort(Iterator begin, Iterator end, Compare cmp)
  {
    bool sorted_once = false;
    do
    {
      auto current_first = begin;
      auto current_second = std::next(begin);
      sorted_once = false;
      for (; current_second != end; current_first++, current_second++)
      {
        if (!cmp(*current_first, *current_second))
        {
          auto tmp = *current_first;
          *current_first = *current_second;
          *current_second = tmp;
          sorted_once = true;
        }
      }
    } while (sorted_once);
  }
}

#endif
