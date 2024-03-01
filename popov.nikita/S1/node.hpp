#ifndef NODE_HPP
#define NODE_HPP

namespace popov
{
  template < typename T >
  struct Node
  {
    T data;
    Node< T > * next;
    Node< T > * prev;
    Node( T data)
    {
      this->data = data;
      this->next = this->prev = nullptr;
    }
  };
}

#endif
