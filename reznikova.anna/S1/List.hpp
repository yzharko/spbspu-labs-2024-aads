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
    List(const List & other);
    List(List && other);

    List< T >& operator=(const List< T >& other);
  //  List< T >& operator=(List< T >&& other);

    void pushFront(const T & val);
    void pushBack(const T & val);
    void popFront();
    void popBack();
    T & front();
    T & back();
    bool empty();
    void clear();
    void swap(List & other);
    reznikova::ListIterator< T > begin();
    reznikova::ListIterator< T > end();
//    ListIterator< T > cbegin();
//    ListIterator< T > cend();

    Node<T>* operator[](const size_t index);

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
    delete head_;
  }

  template< typename T >
  List<T>::List(const List & other):
  size_(0),
  head_(nullptr),
  tail_(nullptr)
  {
    Node< T > * temp = other.head_;
    while(temp)
    {
      pushBack(temp->data_);
      temp = temp->next_;
    }
  }

  template< typename T >
  List< T >::List(List && other):
  size_(other.size_),
  head_(other.head_),
  tail_(other.tail_)
  {
    other.size_ = 0;
    other.head_ = nullptr;
    other.tail_ = nullptr;
  }

  template< typename T >
  List< T >& List< T >::operator=(const List< T >& other)
  {
    List< T > temp(other);
    if (std::addressof(other) != this)
     {
       swap(temp);
     }
     return *this;
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
      throw std::logic_error("can't delete element from empty list");
    }
    Node<T> * temp = head_;
    head_ = head_->next_;
    if (temp->next_ == nullptr)
    {
      tail_ = nullptr;
    }
    delete temp;
    size_--;
  }

  template< typename T >
  void List<T>::popBack()
  {
    if (empty())
    {
      throw std::logic_error("can't delete element from empty list");
    }
    Node<T> * temp = tail_;
    tail_ = tail_->prev_;
    if (size_ == 1)
    {
      head_ = nullptr;
    }
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
    std::swap(size_, other.size_);
  }

  template< typename T >
  reznikova::ListIterator< T > List<T>::begin()
  {
    return ListIterator< T >(head_);
  }

  template< typename T >
  reznikova::ListIterator< T > List<T>::end()
  {
    return ListIterator< T >(tail_);
  }

  template< typename T >
  reznikova::Node<T>* List<T>::operator[](const size_t index)
  {
    if (empty())
    {
      throw std::logic_error("list is empty");
    }
    Node<T>* temp = head_;
    for (size_t i = 0; i < index; i++)
    {
      temp = temp->next_;
      if (!temp)
      {
        return nullptr;
      }
    }
    return temp;
  }
}
#endif
