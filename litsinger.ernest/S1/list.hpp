#ifndef LIST_HPP
#define LIST_HPP
#include <iostream>
#include "Iterator.hpp"
#include "node.hpp"

namespace litsinger
{
  template< typename T >
  class List
  {
  public:
    List();
    void pushBack(T value);
    void pushFront(T value);
    size_t getSize();
    void popFront();
    void popBack();
  private:
    head(nullptr);
    tail(nullptr);
    size_t size = 0;
  };
  template<typename T>
  inline void List<T>::pushBack(T value)
  {
    Node< T >* ptr = new Node< T >(data);
    size++;
    ptr->prev = tail;
    if (tail != nullptr)
    {
      tail->prev = ptr;
    }
    if (head == nullptr)
    {
      head = ptr;
    }
    tail = ptr;
  }
  template<typename T>
  inline void List<T>::pushFront(T value)
  {
    Node< T >* ptr = new Node< T >(data);
    size++;
    head = ptr->next;
    if (head != nullptr)
    {
      head->next = ptr;
    }
    if (head == nullptr)
    {
      head = ptr;
    }
    tail = ptr;
  }
  template<typename T>
  inline size_t List<T>::getSize()
  {
      return size_t();
  }
  template<typename T>
  inline void List<T>::popFront()
  {
    if (head == nullptr)
    {
      return;
    }
    Node<T>* ptr = head->next;
    if (ptr != nullptr)
    {
      ptr->prev = nullptr;
    }
    delete head;
    head = ptr;
    size--;
  }
  template<typename T>
  inline void List<T>::popBack()
  {
    if (tail == nullptr)
    {
      return;
    }
    Node<T> * ptr = tail->prev;
    if (ptr != nullptr)
    {
      ptr->next = nullptr;
    }
    delete tail;
    tail = ptr;
    size--;
  }
}

#endif
