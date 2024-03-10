#ifndef LISTITERATOR_HPP
#define LISTITERATOR_HPP
#include <cstddef>
#include <stdexcept>
#include <memory>
#include "Node.hpp"

namespace reznikova
{
  template< typename T >
  struct ListIterator
  {
    Node< T > * node;
    ListIterator(): node(nullptr) {}
    ListIterator(Node< T > * ptr): node(ptr) {}
    ~ListIterator() = default;
    ListIterator(const ListIterator< T >&) = default;
    ListIterator< T > & operator=(const ListIterator< T >&) = default;
    ListIterator< T > & operator++();
    ListIterator< T > operator++(int);
    ListIterator< T > & operator--();
    ListIterator< T > operator--(int);

    T & operator*();
    T * operator->();
    const T& operator*() const;
    const T* operator->() const;

    bool operator!=(const ListIterator< T >&) const;
    bool operator==(const ListIterator< T >&) const;

    ListIterator< T > moveForward(size_t i);
    ListIterator< T > moveBackward(size_t i);
  };
}

template< typename T >
reznikova::ListIterator< T >& reznikova::ListIterator< T >::operator++()
{
  if (node == nullptr)
  {
    throw std::logic_error("iterator is null");
  }
  node = node->next_;
  return *this;
}

template< typename T >
reznikova::ListIterator< T > reznikova::ListIterator< T >::operator++(int)
{
  if (node == nullptr)
  {
    throw std::logic_error("iterator is null");
  }
  ListIterator< T > result(*this);
  node = node->next_;
  return result;
}

template< typename T >
reznikova::ListIterator< T >& reznikova::ListIterator< T >::operator--()
{
  if (node == nullptr)
  {
    throw std::logic_error("iterator is null");
  }
  node = node->prev_;
  return *this;
}

template< typename T >
reznikova::ListIterator< T > reznikova::ListIterator< T >::operator--(int)
{
  if (node == nullptr)
  {
    throw std::logic_error("iterator is null");
  }
  ListIterator< T > result(*this);
  node = node->prev_;
  return result;
}

template< typename T >
bool reznikova::ListIterator< T >::operator==(const ListIterator< T >& rhs) const
{
  return node == rhs.node;
}

template< typename T >
bool reznikova::ListIterator< T >::operator!=(const ListIterator< T >& rhs) const
{
  return !(rhs == *this);
}

template< typename T >
T & reznikova::ListIterator< T >::operator*()
{
  if (node == nullptr)
  {
    throw std::logic_error("iterator is null");
  }
  return node->data_;
}

template< typename T >
T * reznikova::ListIterator< T >::operator->()
{
  if (node == nullptr)
  {
    throw std::logic_error("iterator is null");
  }
  return std::addressof(node->data_);
}

template< typename T >
reznikova::ListIterator< T > reznikova::ListIterator< T >::moveForward(size_t i)
{
  for (size_t j = 0; j < i; j++)
  {
    if (!node)
    {
      throw std::logic_error("index out of range");
    }
    node = node->next_;
  }
  return node;
}

template< typename T >
reznikova::ListIterator< T > reznikova::ListIterator< T >::moveBackward(size_t i)
{
  for (size_t j = 0; j < i; j++)
  {
    if (!node)
    {
      throw std::logic_error("index out of range");
    }
    node = node->prev_;
  }
  return node;
}


#endif
