#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include "node.hpp"
#include "listIterator.hpp"

namespace popov
{
  template< typename T >
  struct List
  {
    ListIterator< T > iter;
    Node< T > * head, * tail;
    size_t size;
    List():
      head(nullptr),
      tail(nullptr),
      size(0)
    {}
    ~List()
    {
      while (head != nullptr)
      {
        pop_front();
      }
    }
    void clear()
    {
      while (head)
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
    void swap(List< T > other)
    {
      std::swap(head, other.head);
      std::swap(tail, other.tail);
    }
    void pop_front()
    {
      if (head == nullptr)
      {
        return;
      }
      Node< T > * ptr = head->next;
      if (ptr != nullptr)
      {
        ptr->prev = nullptr;
      }
      delete head;
      head = ptr;
    }
    void iterBegin()
    {
      if (iter.node == nullptr)
      {
        iter.node = head;
      }
    }
  };
}

#endif
