#ifndef LIST_HPP
#define LIST_HPP

#include "node.hpp"
#include "Iterator.hpp"
#include <iostream>

namespace susidko
{
  template< typename T >
  class List
  {
    public:
      List():
        first_(nullptr),
        last_(nullptr),
        endPrint(0)
      {}
      void pushBack(T date_)
      {
        Node< T > * ptr = new Node < T >(date_);
        if (isEmpty()) {
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
      }
      void free()
      {
        while(first_)
        {
          Node< T > * temp = first_->next;
          delete first_;
          first_ = temp;
        }
        std::cout << "ok";
      }
      bool isEmpty()
      {
        return first_ == nullptr;
      }
      ListIterator< T > begin()
      {
        return left_iter_;
      }
      ListIterator< T > end()
      {
        return right_iter_;
      }
      T front()
      {
        return first_.date;
      }
      T back()
      {
        return last_.date;
      }
      T getValue()
      {
        if (isEmpty() or left_iter_.node == nullptr)
        {
          return 0;
        }
        else
        {
          return left_iter_.node->data;
        }
      }
      void printNext(int flag)
      {
        if (left_iter_.node != nullptr)
        {
          std::cout << left_iter_.node->data;
          if (flag)
          {
            std::cout << ' ';
          }
          left_iter_++;
        }
      }
    private:
      ListIterator< T > left_iter_;
      ListIterator< T > right_iter_;
      Node< T > * first_;
      Node< T > * last_;
      bool endPrint;
  };
}
#endif
