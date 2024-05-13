#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "list.hpp"
#include <utility>
#include <cstddef>

namespace jirkov
{
  template< typename T >
  class Queue
  {
  public:
    Queue() = default;
    Queue(const Queue < T > & newQueue);
    Queue(Queue < T > && newQueue);
    ~Queue() = default;

    void push(const T& data);
    void drop();
    T& front();
    T& back();
    size_t size();
    bool empty() const noexcept;

  private:
    List< T > queue;
  };
}

template< typename T >
jirkov::Queue< T >::Queue(const Queue < T > & newQueue)
{
  queue(newQueue.queue);
}

template< typename T >
jirkov::Queue< T >::Queue(Queue< T >&& newQueue)
{
  queue(std::move(newQueue.queue));
}

template< typename T >
void jirkov::Queue< T >::push(const T& data)
{
  queue.pushBack(data);
}

template< typename T >
void jirkov::Queue< T >::drop()
{
  queue.popFront();
}

template< typename T >
T& jirkov::Queue< T >::front()
{
  return queue.front();
}

template< typename T >
T& jirkov::Queue< T >::back()
{
  return queue.back();
}

template< typename T >
bool jirkov::Queue< T >::empty() const noexcept
{
  return queue.empty();
}

template< typename T >
size_t jirkov::Queue< T >::size()
{
  return queue.size();
}

#endif
