#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include "list.hpp"
#include <memory>

// мой итератор должен
// копироваться +
// иметь деструктор +
// оператор инкремент +
// оператор декремент +
// операция разыменовывания и проверки на равентсво/неравенство +
// конструктор по умолчанию +

namespace sobolevsky
{
  template< typename T >
  class Iterator
  {
  public:
    Node< T > * currNode = nullptr;

    Iterator(Node< T > * node);
    ~Iterator() = default;
    Iterator(const Iterator< T > &) = default;
    Iterator< T > & operator=(const Iterator< T > &) = default;

    Iterator& operator++();
    Iterator operator++(int);
    Iterator& operator--();
    Iterator operator--(int);

    bool operator!=(const Iterator& other) const;
    bool operator==(const Iterator& other) const;

    T & operator * ();
    T * operator->();

    std::string name();
  };
}

template< typename T >
sobolevsky::Iterator< T >::Iterator(Node< T > * node)
{
  currNode = node;
}

template< typename T >
sobolevsky::Iterator< T >& sobolevsky::Iterator< T >::operator++()
{
  if (currNode)
  {
    currNode = currNode->next;
  }
  return *this;
}

template<typename T>
sobolevsky::Iterator<T> sobolevsky::Iterator< T >::operator++(int)
{
  sobolevsky::Iterator< T > temp(*this);
  operator++();
  return temp;
}

template< typename T >
sobolevsky::Iterator< T >& sobolevsky::Iterator< T >::operator--()
{
  if (currNode)
  {
    currNode = currNode->prev;
  }
  return *this;
}

template<typename T>
sobolevsky::Iterator<T> sobolevsky::Iterator< T >::operator--(int)
{
  sobolevsky::Iterator< T > temp(*this);
  operator--();
  return temp;
}

template< typename T >
bool sobolevsky::Iterator< T >::operator!=(const Iterator& other) const
{
  return currNode != other.currNode;
}

template< typename T >
bool sobolevsky::Iterator< T >::operator==(const Iterator& other) const
{
  return currNode == other.currNode;
}

template< typename T >
T & sobolevsky::Iterator< T >::operator * ()
{
  return currNode->data;
}

template< typename T >
T * sobolevsky::Iterator< T >::operator->()
{
  return std::addressof(currNode->data);
}

template< typename T >
std::string sobolevsky::Iterator< T >::name()
{
  return currNode->name;
}

#endif
