#ifndef SORTS_HPP
#define SORTS_HPP

template <typename Iter, typename Compare>
void quickSort(Iter begin, Iter end, Compare compare)
{
  if (std::distance(begin, end) > 1)
  {
    Iter split = partOfQuickSort(begin, end, comp);
    quickSort(first, split, comp);
    if (split == first)
    {
      quickSort(++first, last, comp);
    }
    else
    {
      quickSort(split, last, comp);
    }
  }
}

template <typename Iter, typename Compare>
Iter partOfQuickSort(Iter begin, Iter end, Compare compare)
{
  --end;
  while (begin != end)
  {
    if (compare(*begin, *end))
    {
      --last;
    }
    else
    {
      if (std::next(begin) != end)
      {
        std::iter_swap(end, std::next(begin));
        std::iter_swap(begin, std::next(begin));
        ++begin;
      }
      else
      {
        std::iter_swap(begin, std::next(begin));
        return ++begin;
      }
    }
  }
  return begin;
}

#endif
