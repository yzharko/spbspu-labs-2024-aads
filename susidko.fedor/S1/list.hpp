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
      List(size_t count);
      List(size_t count, const T & value);
      List(List< T > & p);
      List(List< T > && moved);
      List< T > & operator=(List< T > & p);
      List< T > & operator=(List< T > && moved);
      T & operator[](size_t index);
      void assign(T data_);
      void pushBack(T data_);
      void pushFront(T data_);
      void popBack();
      void popFront();
      void remove(const T & value);
      void remove_if(bool (*p)(T));
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
  List< T >::List(size_t count)
  {
    first_ = nullptr;
    size_ = 0;
    for (size_t i = 0; i < count; i++)
    {
      pushBack(T{});
    }
  }
  template< typename T >
  List< T >::List(size_t count, const T & value)
  {
    first_ = nullptr;
    size_ = 0;
    for (size_t i = 0; i < count; i++)
    {
      pushBack(value);
    }
  }
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
  void List< T >::assign(T data_)
  {
    ListIterator< T > temp_iter = begin();
    for (size_t i = 0; i < size_; i++)
    {
      temp_iter.node->data = data_;
      temp_iter++;
    }
  }
  template< typename T >
  void List< T >::pushBack(T data_)
  {
    Node< T > * ptr = new Node < T >(data_);
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
  void List< T >::pushFront(T data_)
  {
    Node< T > * ptr = new Node < T >(data_);
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
  void List< T >::remove(const T & value)
  {
    if (empty())
    {
      return;
    }
    else
    {
      ListIterator< T > temp_iter = begin();
      while (temp_iter.node->data == value)
      {
        Node< T > * temp_node = temp_iter.node;
        temp_iter++;
        first_ = temp_iter.node;
        delete temp_node;
        size_--;
      }
      size_t temp_size = size_;
      temp_iter++;
      for (size_t i = 1; i < temp_size - 1; i++)
      {
        if (temp_iter.node->data == value)
        {
          Node< T > * temp_node = temp_iter.node;
          temp_iter.node->prev->next = temp_iter.node->next;
          temp_iter.node->next->prev = temp_iter.node->prev;
          temp_iter++;
          delete temp_node;
          size_--;
        }
        else
        {
          temp_iter++;
        }
      }
      if (temp_iter.node->data == value)
      {
        Node< T > * temp_node = temp_iter.node;
        temp_iter.node->prev->next = nullptr;
        last_ = temp_iter.node->prev;
        delete temp_node;
        size_--;
      }
    }
  }
  template< typename T >
  void List< T >::remove_if(bool (*p)(T))
  {
    if (empty())
    {
      return;
    }
    else
    {
      ListIterator< T > temp_iter = begin();
      while (p(temp_iter.node->data))
      {
        Node< T > * temp_node = temp_iter.node;
        temp_iter++;
        first_ = temp_iter.node;
        delete temp_node;
        size_--;
      }
      size_t temp_size = size_;
      temp_iter++;
      for (size_t i = 1; i < temp_size - 1; i++)
      {
        if (p(temp_iter.node->data))
        {
          Node< T > * temp_node = temp_iter.node;
          temp_iter.node->prev->next = temp_iter.node->next;
          temp_iter.node->next->prev = temp_iter.node->prev;
          temp_iter++;
          delete temp_node;
          size_--;
        }
        else
        {
          temp_iter++;
        }
      }
      if (p(temp_iter.node->data))
      {
        Node< T > * temp_node = temp_iter.node;
        temp_iter.node->prev->next = nullptr;
        last_ = temp_iter.node->prev;
        delete temp_node;
        size_--;
      }
    }
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
    return first_.data;
  }
  template< typename T >
  T List< T >::back()
  {
    return last_.data;
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
    while (printIter.node->next)
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
