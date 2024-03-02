#ifndef LIST_HPP
#define LIST_HPP

#include "node.hpp"
#include "listIterator.hpp"

namespace popov
{
  template< typename T >
  struct List
  {
    ListIterator<T> iter;
    Node< T > * head, * tail;
    size_t size;
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
        iter.node = head;
      }
      tail = ptr;
      ++size;
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
    void iterBegin()
    {
      if (iter.node == tail)
      {
        iter.node = head;
      }
    }
  };
}

#endif
