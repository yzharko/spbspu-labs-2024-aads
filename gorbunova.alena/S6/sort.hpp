#ifndef SORTS_HPP
#define SORTS_HPP

#include <iterator>

namespace gorbunova
{
  template <typename Iterator, typename Comparator>
  void sortInsertion(Iterator begin, Iterator end, Comparator comp)
  {
    for (auto it = begin; it != end; ++it)
    {
      auto current = *it;
      auto pos = it;
      while (pos != begin && comp(current, *std::prev(pos)))
      {
        *pos = *std::prev(pos);
        if (pos != begin)
        {
          --pos;
        }
      }

      *pos = current;
    }
  }

  template <typename Iterator, typename Comparator>
  void sortBubble(Iterator begin, Iterator end, Comparator comp)
  {
    bool swapped;
    do
    {
      swapped = false;
      for (Iterator it = begin; it != std::prev(end); ++it)
      {
        if (comp(*std::next(it), *it))
        {
          std::iter_swap(it, std::next(it));
          swapped = true;
        }
      }
    } while (swapped);
  }
}

#endif
