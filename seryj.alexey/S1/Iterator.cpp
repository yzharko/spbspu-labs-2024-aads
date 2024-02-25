#include "Iterator.hpp"
#include <iostream>
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
  return !(rhs == *this);
}

template<class T>
bool Iterator<T>::operator==(const Iterator<T>& rhs) const
{
  return node == rhs.node;
}
