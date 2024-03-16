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
        len_(0)
      {}
      void pushBack(T date_);
      void free();
      bool empty();
      ListIterator< T > begin();
      ListIterator< T > end();
      T front();
      T back();
      T getValue();
      T getSum();
      void printFirst();
      void printNext();
      void print();
    private:
      ListIterator< T > left_iter_;
      ListIterator< T > right_iter_;
      Node< T > * first_;
      Node< T > * last_;
      size_t len_;
  };
  
  template< typename T >
  void List< T >::pushBack(T date_)
  {
    Node< T > * ptr = new Node < T >(date_);
    if (empty()) {
      first_ = ptr;
      last_ = ptr;
      left_iter_.node = ptr;
    }
    else
    {
      last_->next = ptr;
      last_ = ptr;
      right_iter_.node = last_->next;
    }
    len_ += 1;
  }
  template< typename T >
  void List< T >::free()
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
  ListIterator< T > List< T >::begin()
  {
    return left_iter_;
  }
  template< typename T >
  ListIterator< T > List< T >::end()
  {
    return right_iter_;
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
  T List< T >::getValue()
  {
    if (empty() or left_iter_.node == nullptr)
    {
      return 0;
    }
    else
    {
      T value = left_iter_.node->data;
      left_iter_++;
      return value;
    }
  }
  template< typename T >
  T List< T >::getSum()
  {
    T summ {};
    while (left_iter_.node != nullptr)
    {
      if (left_iter_.node->data > std::numeric_limits< unsigned long long >::max() - summ)
      {
        throw std::overflow_error("vjw");
      }
      summ += left_iter_.node->data;
      left_iter_++;
    }
    return summ;
  }
  template< typename T >
  void List< T >::printFirst()
  {
    if (left_iter_.node != nullptr)
    {
      std::cout << left_iter_.node->data;
      left_iter_++;
    }
  }
  template< typename T >
  void List< T >::printNext()
  {
    if (left_iter_.node != nullptr)
    {
      std::cout << ' ' << left_iter_.node->data;
      left_iter_++;
    }
  }
  template< typename T >
  void List< T >::print()
  {
    while (left_iter_.node->next != nullptr)
    {
      std::cout << left_iter_.node->data << ' ';
      left_iter_++;
    }
    std::cout << left_iter_.node->data << '\n';
    left_iter_.node = first_;
  }
}

#endif
