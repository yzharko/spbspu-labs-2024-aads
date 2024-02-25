#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include "List.hpp"
template <class T>
struct Iterator
{
  List<T>* node;

  Iterator() : node(nullptr) {};
  ~Iterator() = default;
  Iterator(const Iterator<T>&) = default;
  Iterator<T>& operator=(const Iterator<T>&) = default;

  Iterator<T> & operator++();
  Iterator<T> operator++(int);

  T & operator*();
  T * operator->();

  bool operator!=(const Iterator<T>&) const;
  bool operator==(const Iterator<T>&) const;
};
#endif