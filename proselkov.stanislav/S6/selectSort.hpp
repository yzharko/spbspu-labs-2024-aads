#ifndef SELECT_SORT_HPP
#define SELECT_SORT_HPP
#include <iterator>
#include <algorithm>

namespace proselkov
{
  template< typename Iter, typename Compare >
  void sortSelect(Iter begin, Iter end, Compare compare);
}

template< typename Iter, typename Compare >
void proselkov::sortSelect(Iter begin, Iter end, Compare compare) {
  while (begin != end)
  {
    Iter outer = begin;
    Iter current = begin;
    while (current != end)
    {
      if (compare(*current, *outer))
      {
        outer = current;
      }
      current++;
    }
    std::swap(*outer, *begin);
    begin++;
  }
}

#endif
