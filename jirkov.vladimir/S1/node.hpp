#ifndef NODE_HPP
#define NODE_HPP

namespace jirkov
{
  namespace details
  {
    template < typename T >
    struct Node
    {
      explicit Node(T value) : data(value), next(nullptr) {}
      T data;
      Node<T>* next;
    };
  }
}

#endif
