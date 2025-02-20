#ifndef SORTOPERATION_HPP
#define SORTOPERATION_HPP

#include <iostream>
#include <list>
#include <forward_list>
#include <deque>
#include <functional>

namespace kaseev {
  template< typename T >
  void printList(const std::forward_list< T > &list, std::ostream &os);
  template< typename T >
  void printStdList(const std::list< T > &list, std::ostream &os);
  template< typename T >
  void printDeque(const std::deque< T > &deq, std::ostream &os);
  template< typename forwardIterator, typename Compare >
  void oddEvenSort(forwardIterator first, forwardIterator last, Compare comp);
  template< typename forwardIterator, typename Compare >
  void insertionSort(forwardIterator first, forwardIterator last, Compare comp);
  template< typename T, typename Compare >
  void stdSort(std::deque< T > &deq, Compare comp);
  template< typename T, typename Compare >
  void printSort(std::forward_list< T > &singleList, std::list< T > &doubleList, std::deque< T > &deq, Compare comp, std::ostream &os);
  template< typename T >
  void performSorts(std::forward_list< T > &singleList, std::list< T > &doubleList, std::deque< T > &deq, bool ascending, std::ostream &os);

}

#endif
