#ifndef STACK_HPP
#define STACK_HPP
#include "List.hpp"

namespace proselkov
{
  template < typename T >
  class Stack
  {
  public:
    Stack() = default;
    Stack(const Stack& other);
    explicit Stack(const List< T >& dep);
    ~Stack() = default;

    Stack< T >& operator=(const Stack& other);

    T& getTop() const;

    void push(const T& data);
    void push(T&& data);
    void pop();

    size_t getSize() const noexcept;
    bool isEmpty() const noexcept;
  private:
    List< T > depot;
  };
}

template < typename T >
proselkov::Stack< T >::Stack(const Stack& other)
{
  depot = other.depot;
}

template < typename T >
proselkov::Stack< T >::Stack(const List< T >& dep)
{
  depot(dep);
}

template < typename T >
proselkov::Stack< T >& proselkov::Stack< T >::operator=(const Stack& other)
{
  depot = other.dep;
}

template < typename T >
T& proselkov::Stack< T >::getTop() const
{
  return depot.getFront();
}

template < typename T >
void proselkov::Stack< T >::push(const T& data)
{
  depot.pushFront(data);
}

template < typename T >
void proselkov::Stack< T >::push(T&& data)
{
  depot.pushFront(data);
}

template < typename T >
void proselkov::Stack< T >::pop()
{
  depot.popFront();
}

template<typename T>
size_t proselkov::Stack<T>::getSize() const noexcept
{
  return depot.getSize();
}

template < typename T >
bool proselkov::Stack< T >::isEmpty() const noexcept
{
  return depot.isEmpty();
}

#endif
