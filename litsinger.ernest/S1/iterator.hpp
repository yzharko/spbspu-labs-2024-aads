#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include "Node.hpp"
#include <memory>

namespace litsinger
{
  template<typename T>
  class Iterator
  {
  public:
    Iterator(Node <T>* node = nullptr);
    ~Iterator() = default;
    Iterator(const Iterator< T >&) = default;
    Iterator<T>& operator=(const Iterator< T >&) = default;
    Iterator<T>& operator++();
    Iterator<T> operator++(int);

    T& operator*();
    T* operator->();

    bool operator==(const Iterator< T >&) const;
    bool operator!=(const Iterator< T >&) const;
  };
}

template <typename T>
litsinger::Iterator<T>& litsinger::Iterator<T>::operator++()
{
  node = node->next;
  return *this;
}

template <typename T>
litsinger::Iterator<T> litsinger::Iterator<T>::operator++(int)
{
  Iterator<T> result(*this);
  ++(*this);
  return result;
}

template<typename T>
T& litsinger::Iterator<T>::operator*()
{
  return node->data;
}

template<typename T>
T* litsinger::Iterator<T>::operator->()
{
  return std::addressof(node->data);
}

template<typename T>
inline bool litsinger::Iterator<T>::operator==(const Iterator<T>& that) const
{
  return node == that.node;
}

template<typename T>
bool litsinger::Iterator<T>::operator!=(const Iterator<T>& that) const
{
  return !(that == *this);

#endif
