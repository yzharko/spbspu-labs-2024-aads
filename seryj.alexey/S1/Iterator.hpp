#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include "Node.hpp"
#include <iostream>
template <class T>
struct Iterator
{
  Node<T>* node;

  Iterator() { node = nullptr; };
  ~Iterator() = default;
  Iterator(const Iterator<T>&) = default;
  Iterator<T>& operator=(const Iterator<T>&) = default;

  Iterator<T>& operator++();
  Iterator<T> operator++(int);

  T& operator*();
  T* operator->();

  bool operator!=(const Iterator<T>&) const;
  bool operator==(const Iterator<T>&) const;
};
template <class T>
Iterator<T>& Iterator<T>::operator++()
{
  node = node->next;
  return *this;
}
template <class T>
Iterator<T> Iterator<T>::operator++(int)
{
  Iterator<T> result(*this);
  ++(*this);
  return result;
}
template <class T>
T& Iterator<T>::operator*()
{
  return node->data;
}
template<class T>
T* Iterator<T>::operator->()
{
  return std::addressof(node->data);
}

template<class T>
bool Iterator<T>::operator!=(const Iterator<T>& rhs) const
{
  return !(rhs.node == node);
}

template<class T>
bool Iterator<T>::operator==(const Iterator<T>& rhs) const
{
  return node == rhs.node;
}

#endif
