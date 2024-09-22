#ifndef TASK_HPP
#define TASK_HPP

#include "iter_print.hpp"
#include "list.hpp"

#include <iostream>
#include <random>

#include <forward_list>
#include <deque>

#include "bubble_sort.hpp"
#include "odd_even_sort.hpp"

namespace sadofeva
{
  template <typename T, typename Compare>
  void task(size_t N);

  template <typename SortFunc, typename Container, typename Compare>
  void check_sort(SortFunc func, Container cont, Compare comp, std::ostream & out);
}

template <typename T, typename Compare>
void sadofeva::task(size_t N)
{
  std::random_device dev;
  std::default_random_engine re(dev());
  using Distribution = typename std::
   conditional<std::is_same<T, int>::value, std::uniform_int_distribution<T>, std::uniform_real_distribution<T>>::type;

  Distribution gen(-100000, 100000);

  sadofeva::List<T> list;
  std::forward_list<T> flist;
  std::deque<T> deq;

  for (size_t i = 0; i < N; ++i)
  {
    auto val = gen(re);
    list.push_front(val);
    flist.push_front(val);
    deq.push_front(val);
  }

  print(deq.begin(), deq.end(), std::cout);

  Compare comp;

  check_sort(sadofeva::bubble_sort<typename std::deque<T>::iterator, Compare>, deq, comp, std::cout);
  check_sort(sadofeva::oddeven_sort<typename std::deque<T>::iterator, Compare>, deq, comp, std::cout);

  check_sort(sadofeva::bubble_sort<typename std::forward_list<T>::iterator, Compare>, flist, comp, std::cout);
  check_sort(sadofeva::oddeven_sort<typename std::forward_list<T>::iterator, Compare>, flist, comp, std::cout);

  check_sort(sadofeva::bubble_sort<typename sadofeva::List<T>::iterator, Compare>, list, comp, std::cout);
}

template <typename SortFunc, typename Container, typename Compare>
void sadofeva::check_sort(SortFunc func, Container cont, Compare comp, std::ostream & out)
{
  func(cont.begin(), cont.end(), comp);
  print(cont.begin(), cont.end(), out);
}

#endif
