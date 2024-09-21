#ifndef STACK_HPP
#define STACK_HPP
#include "list.hpp"

namespace popov
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
popov::Stack< T >::Stack(const Stack< T >& otherStack)
{
  stack(otherStack.stack);
}

template< typename T >
popov::Stack< T >::Stack(Stack< T >&& otherStack)
{
  stack(std::move(otherStack.stack));
}

template< typename T >
void popov::Stack< T >::push(const T& data)
{
  stack.pushFront(data);
}

template< typename T >
void popov::Stack< T >::drop()
{
  stack.popFront();
}

template< typename T >
T& popov::Stack< T >::front()
{
  return stack.front();
}

template< typename T >
T& popov::Stack< T >::back()
{
  return stack.back();
}

template< typename T >
size_t popov::Stack< T >::getSize() const
{
  return stack.getSize();
}

template< typename T >
bool popov::Stack< T >::isEmpty() const noexcept
{
  return stack.isEmpty();
}

#endif
