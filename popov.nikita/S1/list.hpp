#ifndef LIST_HPP
#define LIST_HPP

#include "node.hpp"

namespace popov
{
  template< typename T >
  struct List
  {
    Node< T > * head, * tail;
    List():
      head(nullptr),
      tail(nullptr)
    {}
    ~List()
    {
      while (head != nullptr)
      {
        pop_front();
      }
    }
    void pushBack(T data)
    {
      Node< T > * ptr = new Node< T >(data);
      ptr->prev = tail;
      if (tail != nullptr)
      {
        tail->next = ptr;
      }
      if (head == nullptr)
      {
        head = ptr;
      }
      tail = ptr;
    }
    void pop_front()
    {
      if (head == nullptr)
      {
        return;
      }
      Node<T> * ptr = head->next;
      if (ptr != nullptr)
      {
        ptr->prev = nullptr;
      }
      delete head;
      head = ptr;
    }
  };
}

#endif
