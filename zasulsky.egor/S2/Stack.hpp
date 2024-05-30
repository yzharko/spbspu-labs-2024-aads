#ifndef STACK_HPP
#define STACK_HPP

#include <ForwardList.hpp>

namespace zasulsky
{
  template < class T >
  class Stack
  {
  public:

    void push(T data)
    {
      fl.insert_after(fl.cbeforeBegin(), data);
    }

    bool isEmpty()
    {
      return fl.empty();
    }

    void pop()
    {
      if (this->isEmpty())
      {
        throw std::logic_error("The list is empty!");
      }
      else
      {
        fl.erase_after(fl.cbeforeBegin());
      }
    }

    int getSize()
    {
      return fl.size()
    }

    T& top()
    {
      if (isEmpty())
      {
        throw std::logic_error("no elements!");
      }
      return fl.head()->data;
    }

  private:

    ForwardList< T > fl;

  };
}

#endif
