#ifndef LIST_HPP
#define LIST_HPP

#include "node.hpp"
#include "Iterator.hpp"
#include <iostream>
#include <limits>

namespace susidko
{
  template< typename T >
  class List
  {
    public:
      List():
        first_(nullptr),
        last_(nullptr),
        val_iter_(),
        size_(0)
      {}
      List(List< T > & p);
      List(List< T > && moved);
      List< T > & operator=(List< T > & p);
      List< T > & operator=(List< T > && moved);
      T & operator[](size_t index);
      void pushBack(T date_);
      void pushFront(T date_);
      void popBack();
      void popFront();
      void clear();
      bool empty();
      size_t size();
      ListIterator< T > begin();
      ListIterator< T > end();
      T front();
      T back();
      T getValue(size_t);
      T getSum();
      void print();
      void printpr();
      void printne();
      void swap(List< T > & other);
    private:
      Node< T > * first_;
      Node< T > * last_;
      ListIterator< T > val_iter_;
      size_t size_;
  };

  template< typename T >
  List< T >::List(List< T > & p)
  {
    first_ = nullptr;
    last_ = nullptr;
    ListIterator< T > val_iter_;
    size_ = 0;
    for (size_t i = 0; i < p.size_; i++)
    {
      auto temp = p.getValue(i);
      pushBack(temp);
    }
  }
  template< typename T >
  List< T >::List(List< T > && moved)
  {
    first_ = moved.first_;
    last_ = moved.last_;
    val_iter_ = moved.val_iter_;
    size_ = moved.size_;
    moved.first_ = nullptr;
    moved.last_ = nullptr;
    moved.val_iter_;
    moved.size_ = 0;
    }
  template< typename T >
  List< T > & List< T >::operator=(List< T > & p)
  {
    first_ = nullptr;
    last_ = nullptr;
    ListIterator< T > val_iter_;
    size_ = 0;
    for (size_t i = 0; i < p.size_; i++)
    {
      auto temp = p.getValue(i);
      pushBack(temp);
    }
    return *this;
  }
  template< typename T >
  List< T > & List< T >::operator=(List< T > && moved)
  {
    first_ = moved.first_;
    last_ = moved.last_;
    val_iter_ = moved.val_iter_;
    size_ = moved.size_;
    moved.first_ = nullptr;
    moved.last_ = nullptr;
    delete moved.val_iter_;
    moved.size_ = 0;
    return *this;
    }
  template< typename T >
  T & List< T >::operator[](size_t index)
  {
    if (index >= size_)
    {
      throw std::out_of_range("List index out of range");
    }
    ListIterator< T > temp_iter = begin();
    temp_iter = temp_iter + index;
    return temp_iter.node->data;
  }
  template< typename T >
  void List< T >::pushBack(T date_)
  {
    Node< T > * ptr = new Node < T >(date_);
    if (empty())
    {
      first_ = ptr;
      last_ = ptr;
    }
    else
    {
      last_->next = ptr;
      Node< T > * temp = last_;
      last_ = ptr;
      last_->prev = temp;
    }
    size_++;
  }
  template< typename T >
  void List< T >::pushFront(T date_)
  {
    Node< T > * ptr = new Node < T >(date_);
    if (empty())
    {
      first_ = ptr;
      last_ = ptr;
    }
    else
    {
      first_->prev = ptr;
      Node< T > * temp = first_;
      first_ = ptr;
      first_->next = temp;
    }
    size_++;
  }
  template< typename T >
  void List< T >::popBack()
  {
    if (empty())
    {
      throw std::logic_error("List is empty");
    }
    else
    {
      Node< T > * temp = new Node < T >(last_->prev->data, nullptr, last_->prev->prev);
      last_->prev->prev->next = temp;
      //delete last_->prev;
      delete last_;
      last_ = temp;
    }
    size_--;
  }
  template< typename T >
  void List< T >::popFront()
  {
    if (empty())
    {
      throw std::logic_error("List is empty");
    }
    else
    {
      Node< T > * temp = new Node < T >(first_->next->data, first_->next->next, nullptr);
      //delete last_->prev;
      delete first_;
      first_ = temp;
    }
    size_--;
  }
  template< typename T >
  void List< T >::clear()
  {
    while(first_)
    {
      Node< T > * temp = first_->next;
      delete first_;
      first_ = temp;
    }
  }
  template< typename T >
  bool List< T >::empty()
  {
    return first_ == nullptr;
  }
  template< typename T >
  size_t List< T >::size()
  {
    return size_;
  }
  template< typename T >
  ListIterator< T > List< T >::begin()
  {
    return ListIterator< T >(first_);
  }
  template< typename T >
  ListIterator< T > List< T >::end()
  {
    return ListIterator< T >(last_->next);
  }
  template< typename T >
  T List< T >::front()
  {
    return first_.date;
  }
  template< typename T >
  T List< T >::back()
  {
    return last_.date;
  }
  template< typename T >
  T List< T >::getValue(size_t index)
  {
    if (empty() or index >= size_)
    {
      return 0;
    }
    else
    {
      ListIterator< T > val_iter(begin());
      return (val_iter + index).node->data;
    }
  }
  template< typename T >
  T List< T >::getSum()
  {
    ListIterator< T > sum_iter(begin());
    T summ {};
    while (sum_iter.node != nullptr)
    {
      if (sum_iter.node->data > std::numeric_limits< unsigned long long >::max() - summ)
      {
        throw std::overflow_error("vjw");
      }
      summ += sum_iter.node->data;
      sum_iter++;
    }
    return summ;
  }
  template< typename T >
  void List< T >::print()
  {
    if (empty())
    {
      return;
    }
    ListIterator< T > printIter = begin();
    while (printIter.node->next != nullptr)
    {
      std::cout << printIter.node->data << ' ';
      printIter++;
    }
    std::cout << printIter.node->data << '\n';
  }
  template< typename T >
  void List< T >::printne()
  {
    ListIterator< T > printIter(begin());
    while (printIter.node->next->next != nullptr)
    {
      std::cout << printIter.node->next->data << ' ';
      printIter++;
    }
    std::cout << printIter.node->next->data << '\n';
    printIter.node = first_;
  }
  template< typename T >
  void List< T >::printpr()
  {
    ListIterator< T > printIter(begin() + 1);
    while (printIter.node->next != nullptr)
    {
      std::cout << printIter.node->prev->data << ' ';
      printIter++;
    }
    std::cout << printIter.node->prev->data << '\n';
    printIter.node = first_;
  }
  template< typename T >
  void List< T >::swap(List< T > & other)
  {
    std::swap(first_, other.first_);
    std::swap(last_, other.last_);
    std::swap(size_, other.size_);
  }
}

#endif
