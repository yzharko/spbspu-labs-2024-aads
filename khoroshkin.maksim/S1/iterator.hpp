#ifndef LISTITERATOR_HPP
#define LISTITERATOR_HPP

#include "node.hpp"
#include <memory>

namespace khoroshkin
{
  template < bool flag, class IsTrue, class IsFalse >
  struct choose;

  template< class IsTrue, class IsFalse >
  struct choose< true, IsTrue, IsFalse >
  {
    typedef IsTrue type;
  };

  template< class IsTrue, class IsFalse >
  struct choose< false, IsTrue, IsFalse >
  {
    typedef IsFalse type;
  };

  template< typename T, bool isConst >
  class ListIterator
  {
  public:
    typedef typename choose< isConst, const T &, T & >::type valueRef;
    typedef typename choose< isConst, const T *, T * >::type valuePointer;

    Node< T > * node;

    ListIterator(Node < T > * newNode = nullptr) :
      node(newNode)
    {}
    ~ListIterator() = default;
    ListIterator(const ListIterator< T, isConst > &) = default;
    ListIterator< T, isConst > & operator=(const ListIterator< T, isConst > &) = default;

    ListIterator< T, isConst > & operator++()
    {
      node = node->pNext;
      return *this;
    }

    ListIterator< T, isConst > operator++(int)
    {
      ListIterator< T, isConst > result(*this);
      ++(*this);
      return result;
    }

    valueRef operator*()
    {
      return node->data;
    }
    valuePointer operator->()
    {
      return std::addressof(node->data);
    }

    bool operator!=(const ListIterator< T, isConst > & rhs) const
    {
      return !(rhs == *this);
    }
    bool operator==(const ListIterator< T, isConst > & rhs) const
    {
      return node == rhs.node;
    }
  };
}

#endif
