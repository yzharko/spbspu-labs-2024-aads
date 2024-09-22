#ifndef STACK_HPP
#define STACK_HPP
#include "list.hpp"

namespace malanin
{
  template< typename T >
  class Stack
  {
  public:
    Stack() = default;
    Stack(const Stack< T >& otherStack);
    Stack(Stack< T >&& otherStack);
    ~Stack() = default;

    void push(const T& data);
    void drop();
    T& front();
    T& back();
    size_t getSize() const;
    bool isEmpty() const noexcept;

  private:
    List< T > stack;
  };
}

template< typename T >
malanin::Stack< T >::Stack(const Stack< T >& otherStack)
{
  stack(otherStack.stack);
}

template< typename T >
malanin::Stack< T >::Stack(Stack< T >&& otherStack)
{
  stack(std::move(otherStack.stack));
}

template< typename T >
void malanin::Stack< T >::push(const T& data)
{
  stack.pushFront(data);
}

template< typename T >
void malanin::Stack< T >::drop()
{
  stack.popFront();
}

template< typename T >
T& malanin::Stack< T >::front()
{
  return stack.front();
}

template< typename T >
T& malanin::Stack< T >::back()
{
  return stack.back();
}

template< typename T >
size_t malanin::Stack< T >::getSize() const
{
  return stack.getSize();
}

template< typename T >
bool malanin::Stack< T >::isEmpty() const noexcept
{
  return stack.isEmpty();
}

#endif
