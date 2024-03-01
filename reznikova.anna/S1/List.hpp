#ifndef LIST_HPP
#define LIST_HPP
#include <iostream>
#include "ListIterator.hpp"
#include "Node.hpp"

namespace reznikova
{
  template< typename T >
  class List
  {
  public:
    List();
    ~List();
    List(const List & other) = default; // ?
    List(List && other) = default; // ?
    
    void pushFront(const T & val);
    void pushBack(const T & val);
    void popFront();
    void popBack();
    T & front();
    T & back();
    bool empty();
    void clear();
    void swap(List & other);
    ListIterator< T > begin();
    ListIterator< T > end();
//    ListIterator< T > cbegin();
//    ListIterator< T > cend();
    
  //private:
    size_t size_;
    Node< T > * head_;
    Node< T > * tail_;
  };

  template< typename T >
  List< T >::List():
    size_(0),
    head_(nullptr),
    tail_(nullptr)
  {}

  template< typename T >
  List<T>::~List()
  {
    clear();
  }

  template< typename T >
  void List<T>::pushFront(const T & val)
  {
    Node<T> * newNode = new Node<T>(val, nullptr, head_);
    if (empty())
    {
      tail_ = newNode;
      head_ = newNode;
    }
    else
    {
      head_->prev_ = newNode;
      head_ = newNode;
    }
    size_++;
  }

  template< typename T >
  void List<T>::pushBack(const T & val)
  {
    Node<T> * newNode = new Node<T>(val, tail_, nullptr);
    if (empty())
    {
      tail_ = newNode;
      head_ = newNode;
    }
    else
    {
      tail_->next_ = newNode;
      tail_ = newNode;
    }
    size_++;
  }

  template< typename T >
  void List<T>::popFront()
  {
    if (empty())
    {
      //    throw EmptyException
    }
    Node<T> * temp = head_;
    head_ = temp->next_;
    if (size_ == 1)
    {
      tail_ = nullptr;
    }
   // head_->prev_ = nullptr;
    delete temp;
    size_--;
  }

  template< typename T >
  void List<T>::popBack()
  {
    if (empty())
    {
      //    throw EmptyException
    }
    Node<T> * temp = tail_;
    tail_ = tail_->next_;
    if (size_ == 1)
    {
      head_ = nullptr;
    }
  //  tail_->prev_ = nullptr;
    delete temp;
    size_--;
  }

  template< typename T >
  T & List<T>::front()
  {
    return head_->data_;
  }

  template< typename T >
  T & List<T>::back()
  {
    return tail_->data_;
  }

  template< typename T >
  bool List<T>::empty()
  {
    return (size_ == 0);
  }

  template< typename T >
  void List<T>::clear()
  {
    while (!empty())
    {
      popFront();
    }
  }

  template< typename T >
  void List<T>::swap(List & other)
  {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.capasity_);
  }

  template< typename T >
  ListIterator< T > List<T>::begin()
  {
    return ListIterator< T >(head_);
  }

  template< typename T >
  ListIterator< T > List<T>::end()
  {
    return ListIterator< T >(tail_);
  }

}
#endif

