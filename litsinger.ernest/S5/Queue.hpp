#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "List.hpp"

namespace litsinger
{
  template< typename T >
  class Queue
  {
  public:
    Queue();
    Queue(const Queue & other);
    Queue(Queue && other);
    ~Queue() = default;
    void push(const T & value);
    void pop();
    bool empty() noexcept;
    T & getValue() const noexcept;
    size_t getSize() const noexcept;
    void reverse();
  private:
    List< T > data_;
  };
}

template< typename T >
litsinger::Queue< T >::Queue():
  data_(List< T >())
{}

template< typename T >
litsinger::Queue< T >::Queue(const Queue & other):
  data_(other.data_)
{}

template< typename T >
litsinger::Queue< T >::Queue(Queue && other):
  data_(other.data_)
{
    other.data_.clear();
}

template< typename T >
void litsinger::Queue< T >::push(const T & value)
{
  data_.pushBack(value);
}

template< typename T >
void litsinger::Queue< T >::pop()
{
  data_.popFront();
}

template< typename T >
bool litsinger::Queue< T >::empty() noexcept
{
  return data_.empty();
}

template< typename T >
T & litsinger::Queue< T >::getValue() const noexcept
{
  return data_.getFront();
}

template< typename T >
size_t litsinger::Queue< T >::getSize() const noexcept
{
  return data_.getSize();
}

template< typename T >
void litsinger::Queue< T >::reverse()
{
  return data_.reverse();
}

#endif
