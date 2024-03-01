#ifndef LISTITERATOR_HPP
#define LISTITERATOR_HPP
#include "List.hpp"
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
    const T& operator*() const; // ! ! ! ! !
    const T* operator->() const; // ! ! ! ! !
    
    bool operator!=(const ListIterator< T >&) const;
    bool operator==(const ListIterator< T >&) const;
  };

  template< typename T >
  ListIterator< T >& ListIterator< T >::operator++() 
  {
    if (node == nullptr)
    {
      std::cout << "a"; // ! ! ! ! !
    }
    node = node->next_;
    return *this;
  }

  template< typename T >
  ListIterator< T > ListIterator< T >::operator++(int) 
  {
    if (node == nullptr)
    {
      std::cout << "a"; // ! ! ! ! !
    }
    ListIterator< T > result(*this);
    node = node->next_;
    return result;
  }

  template< typename T >
  ListIterator< T >& ListIterator< T >::operator--()
  {
    if (node == nullptr)
    {
      std::cout << "a"; // ! ! ! ! !
    }
    node = node->prev_;
    return *this;
  }

  template< typename T >
  ListIterator< T > ListIterator< T >::operator--(int) 
  {
    if (node == nullptr)
    {
      std::cout << "a"; // ! ! ! ! !
    }
    ListIterator< T > result(*this);
    node = node->prev_;
    return result;
  }

  template< typename T >
  bool ListIterator< T >::operator==(const ListIterator< T >& rhs) const 
  {
    return node == rhs.node;
  }

  template< typename T >
  bool ListIterator< T >::operator!=(const ListIterator< T >& rhs) const 
  {
    return !(rhs == *this);
  }

  template< typename T >
  T & ListIterator< T >::operator*() 
  {
    if (node == nullptr)
    {
      std::cout << "a"; // ! ! ! ! !
    }
    return node->data_;
  }

  template< typename T >
  T * ListIterator< T >::operator->() 
  {
    if (node == nullptr)
    {
      std::cout << "a"; // ! ! ! ! !
    }
    return std::addressof(node->data_);
  }

}
#endif
