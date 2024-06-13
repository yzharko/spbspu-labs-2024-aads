#ifndef STACK_HPP
#define STACK_HPP

#include <ForwardList.hpp>

namespace zasulsky
{
  template < class T >
  class Stack
  {
  public:

    Queue() :
      forwardList(ForwardList< T >())
    {}

    Stack(const Stack& other) :
      forwardList(other.forwardList)
    {}

    Stack(Stack&& other) :
      forwardList(std::move(other.forwardList))
    {}

    ~Stack() = default;

    Stack& operator=(const Stack& rhs)
    {
      if (this == std::addressof(rhs))
      {
        return *this;
      }
      forwardList = rhs.forwardList;
      return *this;
    }

    Stack& operator=(Stack&& rhs)
    {
      if (this == std::addressof(rhs))
      {
        return *this;
      }
      forwardList = std::move(rhs.forwardList);
      return *this;
    }

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