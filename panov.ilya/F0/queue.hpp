#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "list.hpp"
namespace panov
{
  template < typename T >
  class Queue
  {
  public:
    Queue() = default;
    Queue(const Queue< T >& other);
    Queue(Queue< T >&& other);
    ~Queue() = default;
    bool empty() const noexcept;
    size_t size() const noexcept;
    T& front() const;
    T& back() const;
    void push(const T& value);
    void pop();
    void swap(const List< T >& other);
  private:
    List< T > container_;
  };
}

template< typename T >
panov::Queue< T >::Queue(const Queue< T >& other) :
  container_(other.container_)
{}

template< typename T >
panov::Queue< T >::Queue(Queue< T >&& other) :
  container_(other.container_)
{
  other.container_ = nullptr;
}

template< typename T >
bool panov::Queue< T >::empty() const noexcept
{
  return container_.isEmpty();
}

template< typename T >
size_t panov::Queue< T >::size() const noexcept
{
  return container_.getSize();
}

template< typename T >
T& panov::Queue< T >::front() const
{
  return container_[0];
}

template< typename T >
T& panov::Queue< T >::back() const
{
  return container_[container_.getSize() - 1];
}

template< typename T >
void panov::Queue< T >::push(const T& value)
{
  container_.pushBack(value);
}

template< typename T >
void panov::Queue< T >::pop()
{
  container_.popFront();
}

template< typename T >
void panov::Queue< T >::swap(const List< T >& other)
{
  container_ = other;
}
#endif
