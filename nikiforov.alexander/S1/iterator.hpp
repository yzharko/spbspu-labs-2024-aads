#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include "node.hpp"

namespace nikiforov
{
  template < typename T >
  class Iterator
  {
  public:
    Iterator(Node< T >* pNode);
    ~Iterator() = default;
    Iterator(const Iterator< T >&) = default;

    T& operator*();
    T* operator->();
    const T& operator*() const;
    const T* operator->() const;

    bool operator!=(const Iterator& lhs) const;
    bool operator==(const Iterator& lhs) const;

    Iterator< T >& operator++();
    Iterator< T > operator++(int);

  private:
    Node< T >* pNode;
  };
}
template< typename T >
nikiforov::Iterator< T >::Iterator(Node< T >* pNode)
{
  this->pNode = pNode;
}

template< typename T >
T& nikiforov::Iterator< T >::operator*()
{
  return pNode->data;
}

template< typename T >
const T& nikiforov::Iterator< T >::operator*() const
{
  return pNode->data;
}

template< typename T >
T* nikiforov::Iterator< T >::operator->()
{
  return &(pNode->data);
}

template< typename T >
const T* nikiforov::Iterator< T >::operator->() const
{
  return &(pNode->data);
}

template< typename T >
bool nikiforov::Iterator< T >::operator!=(const Iterator& lhs) const
{
  return !(*this == lhs);
}

template< typename T >
bool nikiforov::Iterator< T >::operator==(const Iterator& lhs) const
{
  return pNode == lhs.pNode;
}


template< typename T >
nikiforov::Iterator< T >& nikiforov::Iterator< T >::operator++()
{
  pNode = pNode->pNext;
  return *this;
}

template< typename T >
nikiforov::Iterator< T > nikiforov::Iterator< T >::operator++(int)
{
  Iterator< T > iter = *this;
  ++(*this);
  return iter;
}

#endif
