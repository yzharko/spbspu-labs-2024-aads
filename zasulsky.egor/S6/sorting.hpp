#ifndef SORTING_HPP
#define SORTING_HPP

#include <iterator>


template <typename Container>
void reverseContainer(Container& container)
{
  Container dubl;
  for (auto it = container.begin(); it != container.end(); it++)
  {
    dubl.push_front(*it);
  }
  container = dubl;
}

template <class T>
void sortBubble(T& cont, bool ascending)
{
  bool swapped;
  do
  {
    swapped = false;
    for (auto it = cont.begin(); std::next(it) != cont.end(); ++it)
    {
      auto next_it = std::next(it);
      if (*it > *next_it)
      {
        std::iter_swap(it, next_it);
        swapped = true;
      }
    }
  } while (swapped);
  if (!ascending)
  {
    reverseContainer(cont);
  }
}

template <typename Container>
void shellSort(Container& arr, bool ascending) {
  using std::begin;
  using std::end;

  auto n = std::distance(begin(arr), end(arr));

  // Ќачинаем с большого интервала и уменьшаем его
  for (int gap = n / 2; gap > 0; gap /= 2) {
    // ¬ыполн€ем сортировку вставками дл€ текущего интервала
    for (int i = gap; i < n; i++) {
      auto temp = *std::next(begin(arr), i);
      int j;
      // —двигаем элементы arr[0..i-gap], которые больше temp, на одно место вперед
      for (j = i; j >= gap && *std::next(begin(arr), j - gap) > temp; j -= gap) {
        *std::next(begin(arr), j) = *std::next(begin(arr), j - gap);
      }
      *std::next(begin(arr), j) = temp;
    }
  }
  if (!ascending)
  {
    reverseContainer(arr);
  }
}


#endif
