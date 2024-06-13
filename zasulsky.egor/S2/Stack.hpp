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
      forwardList.insert_after(forwardList.cbeforeBegin(), data);
    }

    bool isEmpty() noexcept
    {
      return forwardList.empty();
    }

    void pop()
    {
      if (this->isEmpty())
      {
        throw std::logic_error("The list is empty!");
      }
      else
      {
        forwardList.erase_after(forwardList.cbeforeBegin());
      }
    }

    int getSize()
    {
      return forwardList.size();
    }

    T& top()
    {
      return forwardList.getHead();
    }

  private:

    ForwardList< T > forwardList;

  };
}

#endif
