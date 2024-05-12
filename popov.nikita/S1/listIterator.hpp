#ifndef LISTITERATOR_HPP
#define LISTITERATOR_HPP
#include <iostream>
#include <cassert>
#include "node.hpp"

namespace popov
{
  template< typename T >
  struct ListIterator
  {
    Node< T > * node;
    using this_t = ListIterator< T >;
    ListIterator(): node(nullptr) {}
    ~ListIterator()= default;
    ListIterator(const this_t &) = default;
    this_t & operator=(const this_t &) = default;
    this_t & operator++()
    {
      assert(node != nullptr);
      node = node -> next;
      return *this;
    }
    this_t operator++(int)
    {
      assert(node != nullptr);
      this_t result(*this);
      ++(*this);
      return result;
    }
    bool operator==(const this_t & rhs) const
    {
      return node == rhs.node;
    }
    bool operator!=(const this_t & rhs) const
    {
      return !(rhs == *this);
    }
    T & operator*()
    {
      assert(node != nullptr);
      return node -> data;
    }
    T * operator->()
    {
      assrt(node != nullptr);
      return std::addressof(node->data);
    }
    this_t & operator--()
    {
      assert(node != nullptr);
      node = node -> prev;
      return *this;
    }
    this_t operator--(int)
    {
      assert(node != nullptr);
      this_t result(*this);
      --(*this);
      return result;
    }
  };
}

#endif
