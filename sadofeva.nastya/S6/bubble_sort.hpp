#ifndef BUBBLE_SORT_HPP
#define BUBBLE_SORT_HPP

#include <iterator>
#include <algorithm>

namespace sadofeva
{
  template <typename ForwardIterator, typename Compare>
  void bubble_sort(ForwardIterator first, ForwardIterator last, Compare comp);
  template <typename ForwardIterator>
  void bubble_sort(ForwardIterator first, ForwardIterator last);
}

template <typename ForwardIterator, typename Compare>
void sadofeva::bubble_sort(ForwardIterator first, ForwardIterator last, Compare comp)
{
  for (ForwardIterator sorted = first; first != last; last = sorted)
  {
    sorted = first;
    for (ForwardIterator current = first, prev = first; ++current != last; ++prev)
    {
      if (comp(*current, *prev))
      {
        std::iter_swap(current, prev);
        sorted = current;
      }
    }
  }
}

template <typename ForwardIterator>
void sadofeva::bubble_sort(ForwardIterator first, ForwardIterator last)
{
  bubble_sort(first, last, std::less<typename std::iterator_traits<ForwardIterator>::value_type>{});
}

#endif
