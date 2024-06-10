#ifndef SORTS_HPP
#define SORTS_HPP

namespace mihalchenko
{
  template <typename Iter, typename Compare>
  void quickSort(Iter begin, Iter end, Compare compare);

  template <typename Iter, typename Compare>
  Iter partOfQuickSort(Iter begin, Iter end, Compare compare);

  template <typename Iter, typename Compare>
  void mergeSort(Iter begin, Iter end, Compare compare);
}

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

template <typename Iter, typename Compare>
void merge(Iter begin, Iter center, Iter end, Compare compare)
{
  std::list<typename Iter::typeOfValue> vector;
  Iter first = begin;
  Iter second = mid;

  while (first != center && second != end)
  {
    if (compare(*first, *second))
    {
      tempVec.push_back(*first);
      left++;
    }
    else
    {
      tempVec.push_back(*second);
      second++;
    }
  }
  vector.insert(vector.end(), first, center);
  vector.insert(vector.end(), second, end);
  std::copy(vector.begin(), vector.end(), begin);
}

template <typename Iter, typename Compare>
void mergeSort(Iter begin, Iter end, Compare compare)
{
  int size = std::distance(begin, end);

  if (size <= 1)
  {
    return;
  }
  Iter center = begin;
  for (int i = 0; i < (size / 2); i++)
  {
    mid++;
  }
  mergeSort(begin, center, compare);
  mergeSort(center, end, compare);
  merge(begin, center, end, compare);
}

#endif
