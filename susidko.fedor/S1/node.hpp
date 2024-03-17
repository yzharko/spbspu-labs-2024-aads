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
    Node(T data_, Node< T > * next_, Node< T > * prev_):
      data(data_),
      next(next_),
      prev(prev_)
    {}
    T data;
    Node< T > * next;
    Node< T > * prev;
  };
}

#endif
