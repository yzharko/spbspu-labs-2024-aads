#ifndef ODD_EVEN_SORT_HPP
#define ODD_EVEN_SORT_HPP

#include <iterator>
#include <algorithm>

namespace sadofeva
{
  template <typename ForwardIterator, typename Compare>
  void oddeven_sort(ForwardIterator first, ForwardIterator last, Compare comp);
  template <typename ForwardIterator>
  void oddeven_sort(ForwardIterator first, ForwardIterator last);
}

template <typename ForwardIterator, typename Compare>
void sadofeva::oddeven_sort(ForwardIterator first, ForwardIterator last, Compare comp)
{
  bool sorted = false;
  while (!sorted)
  {
    sorted = true;
    for (ForwardIterator it = first; it != last; ++it)
    {
      ForwardIterator next = std::next(it);
      if (next == last)
      {
        break;
      }
      if (comp(*next, *it))
      {
        std::iter_swap(it, next);
        sorted = false;
      }
    }
    for (ForwardIterator it = first; it != last; ++it)
    {
      ForwardIterator next = std::next(it);
      if (next == last)
      {
        break;
      }
      if (comp(*next, *it))
      {
        std::iter_swap(it, next);
        sorted = false;
      }
    }
  }
}

template <typename ForwardIterator>
void sadofeva::oddeven_sort(ForwardIterator first, ForwardIterator last)
{
  oddeven_sort(first, last, std::less<typename std::iterator_traits<ForwardIterator>::value_type>{});
}

#endif
