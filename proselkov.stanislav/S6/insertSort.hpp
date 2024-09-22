#ifndef INSERT_SORT_HPP
#define INSERT_SORT_HPP
#include <iterator>
#include <cstddef>

namespace proselkov
{
  template< typename Iter, typename Compare >
  void sortInsert(Iter begin, Iter end, Compare compare);
}

template< typename Iter, typename Compare >
void proselkov::sortInsert(Iter begin, Iter end, Compare compare) {
  for (auto it = begin; it != end; ++it)
  {
    auto current = *it;
    auto pos = it;
    while (pos != begin && compare(current, *std::prev(pos)))
    {
      *pos = *std::prev(pos);
      if (pos != begin) {
        --pos;
      }
    }
    *pos = current;
  }
}

#endif
