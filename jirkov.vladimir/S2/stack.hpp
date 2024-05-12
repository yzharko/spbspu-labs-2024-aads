#ifndef STACK_HPP
#define STACK_HPP
//#include "list.hpp"

namespace jirkov
{
  template< typename T >
  class Stack
  {
  public:
    Stack();
    Stack(const Stack < T > & newStack);
    Stack(Stack < T > && newStack);
    ~Stack();

    void push(const T& data);
    void drop();
    T& front();
    T& back();
    bool empty();
    size_t size();

  private:
    List< T > stack;
  };
}

template< typename T >
jirkov::Stack< T >::Stack(const Stack< T >& newStack)
{
  stack(newStack.stack);
}

template< typename T >
jirkov::Stack< T >::Stack(Stack< T >&& newStack)
{
  stack(std::move(newStack.stack));
}

template< typename T >
void jirkov::Stack< T >::push(const T& data)
{
  stack.pushFront(data);
}

template< typename T >
void jirkov::Stack< T >::drop()
{
  stack.popFront();
}

template< typename T >
T& jirkov::Stack< T >::front()
{
  stack.front();
}

template< typename T >
T& jirkov::Stack< T >::back()
{
  stack.back();
}

template< typename T >
bool jirkov::Stack< T >::empty()
{
  stack.empty();
}

template< typename T >
size_t jirkov::Stack< T >::size()
{
  stack.size();
}

#endif
