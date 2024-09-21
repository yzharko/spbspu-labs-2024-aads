#define LIST_HPP
#ifdef LIST_HPP
#include <memory>
#include "node.hpp"

namespace maksimov
{
  template < typename T >
  class ListIterator
  {
    Node< T >* node_;
    using this_t = ListIterator< T >;

    ListIterator(): node_(nullptr) {}
    ~ListIterator() = default;
    ListIterator(const this_t &) = default;
    this_t & operator=(const this_t &) = default;

    this_t & operator++();
    this_t operator++(int);

    T& operator*();
    T* operator->();

    bool operator!=(const this_t&) const;
    bool operator==(const this_t&) const;
  };
}

template< typename T >
maksimov::ListIterator< T >& maksimov::ListIterator< T >::operator++()
{
  node_ = node_->next_;
  return *this;
}

template< typename T >
maksimov::ListIterator< T > maksimov::ListIterator< T >::operator++(int)
{
  this_t result(*this);
  ++(*this);
  return result;
}

template< typename T >
T& maksimov::ListIterator< T >::operator*()
{
  return node_->data_;
}

template< typename T >
T* maksimov::ListIterator< T >::operator->()
{
  return std::addressof(node_->data_);
}

template< typename T >
bool maksimov::ListIterator< T >::operator==(const this_t& rhs) const
{
  return node_ == rhs.node;
}

template< typename T >
bool maksimov::ListIterator< T >::operator!=(const this_t& rhs) const
{
  return !(rhs == *this);
}

#endif