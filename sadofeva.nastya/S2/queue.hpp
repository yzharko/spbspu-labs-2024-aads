#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <stdexcept>
#include "list.hpp"

namespace sadofeva
{
  template <typename T>
  class Queue
  {
   public:
    Queue() = default;
    Queue(const Queue &);
    Queue(Queue &&);

    Queue & operator=(const Queue &);
    Queue & operator=(Queue &&);

    void swap(Queue &) noexcept;

    void push(const T &);
    void drop();
    const T & next() const;
    bool empty() const;

   private:
    List<T> list_;
  };
}

template <typename T>
sadofeva::Queue<T>::Queue(const Queue & q):
  list_(q.list_)
{}
template <typename T>
sadofeva::Queue<T>::Queue(Queue && q):
  list_{ std::move(q.list_) }
{}
template <typename T>
sadofeva::Queue<T> & sadofeva::Queue<T>::operator=(const Queue & q)
{
  if (this != &q)
  {
    Queue<T> tmp(q);
    swap(tmp);
  }
  return *this;
}
template <typename T>
sadofeva::Queue<T> & sadofeva::Queue<T>::operator=(Queue && q)
{
  if (this != &q)
  {
    Queue<T> tmp(std::move(q));
    swap(tmp);
  }
  return *this;
}
template <typename T>
void sadofeva::Queue<T>::swap(Queue & q) noexcept
{
  std::swap(list_, q.list_);
}

template <typename T>
void sadofeva::Queue<T>::push(const T & value)
{
  list_.push_back(value);
}

template <typename T>
void sadofeva::Queue<T>::drop()
{
  if (empty())
  {
    throw std::logic_error("queue is empty");
  }
  list_.pop_front();
}

template <typename T>
const T & sadofeva::Queue<T>::next() const
{
  if (empty())
  {
    throw std::logic_error("queue is empty");
  }
  return list_.front();
}

template <typename T>
bool sadofeva::Queue<T>::empty() const
{
  return list_.empty();
}

#endif
