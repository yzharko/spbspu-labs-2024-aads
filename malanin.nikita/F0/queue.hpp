#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "list.hpp"

namespace malanin
{
  template< typename T >
  class Queue
  {
  public:
    Queue();
    Queue(const T& value);
    Queue(const Queue& rhs);
    ~Queue() = default;

    Queue& operator=(const Queue& rhs);

    bool empty() const noexcept;
    size_t size() const noexcept;
    T& front();
    T& front() const;

    T& back();
    const T& back() const;

    void push(const T&);
    void pop();
    template< class... Args >
    void emplace(Args&&... args);
    void swap(Queue&) noexcept;

    void print() const;
  private:
    List< T > container_;
  };
}

template< typename T >
malanin::Queue< T >::Queue():
  container_(List< T >())
{}

template< typename T >
malanin::Queue< T >::Queue(const T& value):
  container_(List< T >(value))
{}

template< typename T >
malanin::Queue< T >::Queue(const Queue< T >& rhs)
{
  container_ = rhs.container_;
}

template< typename T >
malanin::Queue< T >& malanin::Queue< T >::operator=(const malanin::Queue< T >& rhs)
{
  container_ = rhs.container_;
  return *this;
}

template< typename T >
bool malanin::Queue< T >::empty() const noexcept
{
  return container_.empty();
}

template< typename T >
size_t malanin::Queue< T >::size() const noexcept
{
  return container_.size();
}

template< typename T >
T& malanin::Queue< T >::front()
{
  return container_.front();
}

template< typename T >
T& malanin::Queue< T >::front() const
{
  return container_.front();
}

template< typename T >
T& malanin::Queue< T >::back()
{
  typename List< T >::Iterator iter(container_.begin());
  for (size_t i = 1; i < container_.size(); i++)
  {
    iter++;
  }
  return *iter;
}

template< typename T >
const T& malanin::Queue< T >::back() const
{
  typename List< T >::Iterator iter(container_.begin());
  for (size_t i = 1; i < container_.size(); i++)
  {
    iter++;
  }
  return *iter;
}

template< typename T >
void malanin::Queue< T > ::push(const T& value)
{
  container_.pushBack(value);
}

template< typename T >
void malanin::Queue< T >::pop()
{
  container_.popFront();
}

template< typename T >
template< class... Args >
void malanin::Queue< T >::emplace(Args&&... args)
{
  push(std::forward< Args > (args)...);
}

template< typename T >
void malanin::Queue< T >::swap(Queue& rhs) noexcept
{
  container_.swap(rhs);
}

template< typename T >
void malanin::Queue< T >::print() const
{
  container_.print();
}

#endif
