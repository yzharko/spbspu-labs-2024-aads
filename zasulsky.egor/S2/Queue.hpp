#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "bilateralNode.hpp"

namespace zasulsky
{
  template < class T >
  class Queue
  {
  public:

    Queue() :
      head_(nullptr),
      tail_(nullptr)
    {}

    Queue(T& data) :
      head_(new detail::bilateralNode < T >(data)),
      tail_(head_)
    {}

    Queue(Queue < T >& other) :
      head_(nullptr),
      tail_(nullptr)
    {
      head_ = detail::copyList(other.head_).first;
      tail_ = detail::copyList(other.tail_).second;
    }

    Queue(Queue < T >&& other) :
      head_(other.head_),
      tail_(other.tail_)
    {
      other.head_ = nullptr;
      other.tail_ = nullptr;
    }

    ~Queue()
    {
      detail::freeList(head_);
    }

    Queue < T >& operator = (Queue < T >& other)
    {
      if (!isEmpty())
      {
        detail::freeList(head_);
      }
      head_ = detail::copyList(other.head_).first;
      tail_ = detail::copyList(other.tail_).second;
      return   *this;
    }

    Queue < T >& operator = (Queue < T >&& other)
    {
      if (!isEmpty())
      {
        detail::freeList(head_);
      }
      head_ = other.head_;
      tail_ = other.tail_;
      other.head_ = nullptr;
      other.tail_ = nullptr;
      return  *this;
    }

    bool isEmpty()
    {
      return head_ == nullptr;
    }
    void enqueue(T  data)
    {
      if (this->isEmpty())
      {
        tail_ = new detail::bilateralNode < T >(data);
        head_ = tail_;
      }
      else
      {
        tail_ = new detail::bilateralNode < T >(data, tail_);
        tail_->prev->next = tail_;
      }
    }

    T peek()
    {
      if (this->isEmpty())
      {
        throw std::logic_error("no elements!");
      }
      return head_->data;
    }

    void dequeue()
    {
      if (this->isEmpty())
      {
        throw std::logic_error("The list is empty!!");
      }
      else
      {
        detail::bilateralNode < T >* temp = head_->next;
        delete head_;
        head_ = temp;
      }
    }

  private:

    detail::bilateralNode < T >* head_;
    detail::bilateralNode < T >* tail_;
  };
}

#endif
