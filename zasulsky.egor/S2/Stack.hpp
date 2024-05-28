##ifndef STACK_HPP
#define STACK_HPP
#include "bilateralNode.hpp"

namespace zasulsky
{
  template < class T >
  class Stack
  {
  public:
    Stack() :
      vertex_(nullptr)
    {}



    Stack(T data) :
      vertex_(new detail::Node < T >(data))
    {}

    Stack(const Stack < T >& other) :
      vertex_(nullptr)
    {
      vertex_ = detail::copyList(other.vertex_);
    }

    Stack(Stack < T >&& other) :
      vertex_(other.vertex)
    {
      other.vertex_ = nullptr;
    }

    Stack < T >& operator = (Stack < T >& other)
    {
      if (!isEmpty())
      {
        detail::freeList(vertex_);
      }
      vertex_ = detail::copyList(other.vertex_).first;
      return  *this;
    }

    Stack < T >& operator = (Stack < T >&& other)
    {
      if (!isEmpty())
      {
        detail::freeList(vertex_);
      }
      vertex_ = other.vertex_;
      other.vertex_ = nullptr;
      return  *this;
    }

    ~Stack()
    {
      if (vertex_)
      {
        detail::freeList(vertex_);
      }
    }

    void push(T data)
    {
      vertex_ = new detail::Node < T >(data, vertex_);
    }

    bool isEmpty()
    {
      return vertex_ == nullptr;
    }

    void pop()
    {
      if (this->isEmpty())
      {
        throw std::logic_error("The list is empty!");
      }
      else
      {
        detail::Node < T >* temp = vertex_->prev;
        delete vertex_;
        vertex_ = temp;
      }
    }

    size_t getSize()
    {
      size_t count = 0;
      detail::Node < T >* temp = vertex_;
      while (temp)
      {
        count++;
        temp = temp->next;
      }
      return count;
    }

    T& top()
    {
      if (isEmpty())
      {
        throw std::logic_error("no elements!");
      }
      return vertex_->data;
    }

  private:


    detail::Node< T >* vertex_;
  };
}

#endif
