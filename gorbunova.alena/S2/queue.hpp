#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "list.hpp"

namespace gorbunova
{
  template <typename T>
  class Queue
  {
  private:
    List<T> list;

  public:
    Queue() = default;
    Queue(const Queue &other);
    Queue &operator=(const Queue &other);
    void push(const T &value);
    void pop();
    T &front() const;
    T &back() const;
    bool isEmpty() const;
    size_t size() const;
    ~Queue() = default;
  };

  template <typename T>
  Queue<T>::Queue(const Queue &other) : list(other.list) {}

  template <typename T>
  Queue<T> &Queue<T>::operator=(const Queue &other)
  {
    if (this != &other)
    {
      list = other.list;
    }
    return *this;
  }

  template <typename T>
  void Queue<T>::push(const T &value)
  {
    list.push_back(value);
  }

  template <typename T>
  void Queue<T>::pop()
  {
    if (list.getSize() == 0)
    {
      throw std::out_of_range("Queue is empty");
    }
    list.erase(list.begin());
  }

  template <typename T>
  T &Queue<T>::front() const
  {
    if (list.getSize() == 0)
    {
      throw std::out_of_range("Queue is empty");
    }
    return *list.begin();
  }

  template <typename T>
  T &Queue<T>::back() const
  {
    if (list.getSize() == 0)
    {
      throw std::out_of_range("Queue is empty");
    }
    auto it = list.begin();
    for (size_t i = 0; i < list.getSize() - 1; ++i)
    {
      ++it;
    }
    return *it;
  }

  template <typename T>
  bool Queue<T>::isEmpty() const
  {
    return list.getSize() == 0;
  }

  template <typename T>
  size_t Queue<T>::size() const
  {
    return list.getSize();
  }
}

#endif
