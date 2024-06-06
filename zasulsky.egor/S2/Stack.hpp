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
      fL.insert_after(fL.cbeforeBegin(), data);
    }

    bool isEmpty() noexcept
    {
      return fL.empty();
    }

    void pop()
    {
      if (this->isEmpty())
      {
        throw std::logic_error("The list is empty!");
      }
      else
      {
        fL.erase_after(fL.cbeforeBegin());
      }
    }

    int getSize()
    {
      return fL.size();
    }

    T& top()
    {
      if (isEmpty())
      {
        throw std::logic_error("no elements!");
      }
      return fL.head()->data;
    }

  private:

    ForwardList< T > fL;

  };
}

#endif
