#ifndef LIST_HPP
#define LIST_HPP
#include <iostream>
#include <cstddef>
#include <stdexcept>
#include "ListIterator.hpp"
#include "Node.hpp"

namespace reznikova
{
  template< typename T >
  class List
  {
  public:
    List();
    List(size_t count, const T & value);
    List(std::initializer_list<T> init);
    ~List();
    List(const List & other);
    List(List && other);

    List< T >& operator=(const List< T >& other);
    List< T >& operator=(List< T >&& other);

    void pushFront(const T & val);
    void pushBack(const T & val);
    void popFront();
    void popBack();
    T & front();
    T & back();
    bool empty();
    void clear();
    void swap(List & other);
    ListIterator< T > begin() const;
    ListIterator< T > end() const;
    ListIterator< const T > cbegin() const;
    ListIterator< const T > cend() const;

    void remove(const T& value);
    template< class UnaryPredicate >
    void remove_if(UnaryPredicate p);
    void assign(size_t count, const T& value);
    template< class InputIt >
    void assign(InputIt first, InputIt last);
    void assign(std::initializer_list<T> ilist);
    ListIterator< T > insert(ListIterator< const T >  pos, const T& value);
    ListIterator< T > erase(ListIterator< T > pos);

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
  List< T >::List(size_t count, const T & value):
    List()
  {
    for (size_t i; i < count; i++)
    {
      pushBack(value);
    }
  }

  template< typename T >
  List< T >::List(std::initializer_list<T> init):
    List()
  {
    const T * ptr = init.begin();
    while (ptr)
    {
      pushBack(*ptr);
      ptr++;
    }
  }

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
  List< T >& List< T >::operator=(List< T >&& other)
  {
    List< T > temp(std::move(other));
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
  ListIterator< T > List< T >::begin() const
  {
    return ListIterator< T >(head_);
  }

  template< typename T >
  ListIterator< T > List< T >::end() const
  {
    return ListIterator< T >(tail_->next_);
  }

  template< typename T >
  ListIterator< const T > List< T >::cbegin() const
  {
    return ListIterator< T >(head_);
  }

  template< typename T >
  ListIterator< const T > List< T >::cend() const
  {
    return ListIterator< T >(tail_->next_);
  }

  template< typename T >
  void List< T >::remove(const T& value)
  {
    Node<T> * temp = head_;
    while (temp)
    {
      if ((temp->data_ == value) && (temp == head_))
      {
        popFront();
      }
      else if ((temp->data_ == value) && (temp == tail_))
      {
        popBack();
      }
      else if ((temp->data_ == value) && (temp != tail_) && (temp != head_))
      {
        temp->next_->prev_ = temp->prev_;
        temp->prev_->next_ = temp->next_;
        delete temp;
        size_--;
      }
      temp = temp->next_;
    }
  }

  template< typename T >
  template< class UnaryPredicate>
  void List< T >::remove_if(UnaryPredicate p)
  {
    Node<T> * temp = head_;
    while (temp)
    {
      if ((p(temp->data_)) && (temp == head_))
      {
        popFront();
      }
      else if ((p(temp->data_)) && (temp == tail_))
      {
        popBack();
      }
      else if ((p(temp->data_)) && (temp != tail_) && (temp != head_))
      {
        temp->next_->prev_ = temp->prev_;
        temp->prev_->next_ = temp->next_;
        delete temp;
        size_--;
      }
      temp = temp->next_;
    }
  }

  template< typename T >
  void List< T >::assign(size_t count, const T& value)
  {
    clear();
    for (size_t i = 0; i < count; i++)
    {
      pushBack(value);
    }
  }

  template< typename T >
  template< class InputIt >
  void List< T >::assign(InputIt first, InputIt last)
  {
    clear();
    while (first != last)
    {
      pushBack(*first);
      first++;
    }
  }

  template< typename T >
  void List< T >::assign(std::initializer_list<T> ilist)
  {
    clear();
    const T * ptr = ilist.begin();
    while (ptr)
    {
      pushBack(*ptr);
      ptr++;
    }
  }

  template< typename T >
  ListIterator< T > List< T >::insert(ListIterator< const T >  pos, const T& value)
  {
    ListIterator< T > it;
    if (pos == head_)
    {
      pushFront(value);
      it = head_;
    }
    else
    {
      Node< T > * node = new Node< T >(value, pos->prev_, pos->prev_->next_);
      it = node;
      pos->prev_ = it;
      pos->prev_next_ = it;
    }
    return it;
  }

  template< typename T >
  ListIterator< T > List< T >::erase(ListIterator< T > pos)
  {
    ListIterator< T > it;
    if (pos == head_)
    {
      popFront();
      it = head_;
    }
    else if (pos == tail_)
    {
      popBack();
      it = tail_;
    }
    else
    {
      pos->next_->prev_ = pos->prev_;
      pos->prev_->next_ = pos->next_;
      it = pos->next_;
      delete pos;
    }
    return it;
  }

#endif

