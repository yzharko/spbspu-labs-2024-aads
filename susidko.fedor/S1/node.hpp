#ifndef NODE_HPP
#define NODE_HPP

namespace susidko
{
  template< typename T >
  struct Node
  {
    Node(T data_):
      data(data_),
      next(nullptr),
      prev(nullptr)
    {}
    T data;
    Node< T > * next;
    Node< T > * prev;
  };
}

#endif
