#ifndef STACK_HPP
#define STACK_HPP

#include "list.hpp"

namespace malanin
{
  template< typename T >
  class Stack
  {
  public:
    Stack();
    Stack(const T&);
    Stack(const Stack&);
    ~Stack() = default;

    Stack& operator=(const Stack&);

    bool empty() const noexcept;
    size_t size() const noexcept;

    T& top();
    const T& top() const;

    void push(const T&);
    void pop();
    template< class... Args >
    void emplace(Args&&... args);
    void swap(Stack&) noexcept;

    void print(std::ostream& = std::cout, char delimiter = ' ') const;
  private:
    List< T > container_;
  };
}

template< typename T >
malanin::Stack < T >::Stack():
  container_(List< T >())
{}

template< typename T >
malanin::Stack< T >::Stack(const T& value):
  container_(List< T >(value))
{}

template< typename T >
malanin::Stack< T >::Stack(const Stack< T >& rhs)
{
  container_ = rhs.container_;
}

template< typename T >
malanin::Stack< T >& malanin::Stack< T >::operator=(const Stack< T >& rhs)
{
  container_ = rhs.container_;
  return *this;
}

template< typename T >
bool malanin::Stack< T >::empty() const noexcept
{
  return container_.empty();
}

template< typename T >
size_t malanin::Stack< T >::size() const noexcept
{
  return container_.size();
}

template< typename T >
const T& malanin::Stack < T >::top() const
{
  return container_.front();
}

template< typename T >
T& malanin::Stack < T >::top()
{
  return container_.front();
}

template< typename T >
void malanin::Stack < T >::push(const T& value)
{
  container_.pushFront(value);
}

template< typename T >
void malanin::Stack < T >::pop()
{
  container_.popFront();
}

template< typename T >
template< class... Args >
void malanin::Stack< T >::emplace(Args&&... args)
{
  push(std::forward< Args > (args)...);
}

template< typename T >
void malanin::Stack < T >::swap(Stack< T >& rhs) noexcept
{
  container_.swap(rhs);
}

template< typename T >
void malanin::Stack< T >::print(std::ostream& out, char delimiter) const
{
  container_.print(out, delimiter);
}

#endif
