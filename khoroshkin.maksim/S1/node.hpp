#ifndef NODE_HPP
#define NODE_HPP

namespace khoroshkin
{
  template< typename T >
  class Node
  {
  public:
    Node(T data = T(), Node * pNext = nullptr);
    Node(const Node & obj);
    T data;
    Node< T >  * pNext;
  };
}

template< typename T >
khoroshkin::Node< T >::Node(T data, khoroshkin::Node< T > * pNext) :
  data(data), pNext(pNext)
{}

template< typename T>
khoroshkin::Node< T >::Node(const Node< T > & obj)
{
  data = obj.data;
  if (obj.pNext == nullptr)
  {
    pNext = nullptr;
  }
  else
  {
    pNext = new Node< T >(*obj.pNext);
  }
}

#endif
