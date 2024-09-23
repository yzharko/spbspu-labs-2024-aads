#ifndef STACK_HPP
#define STACK_HPP

#include "list.hpp"

namespace gorbunova
{
  template <typename T>
  class Stack
  {
  private:
    List<T> list;

  public:
    Stack() = default;
    Stack(const Stack& other);
    Stack& operator=(const Stack& other);
    ~Stack() = default;

    void push(const T& value);
    T pop();
    T top() const;
    bool isEmpty() const;
    size_t size() const;
  };

  template <typename T>
  Stack<T>::Stack(const Stack& other) : list(other.list) {}

  template <typename T>
  Stack<T>& Stack<T>::operator=(const Stack& other)
  {
    if (this != &other)
    {
      list = other.list;
    }
    return *this;
  }

  template <typename T>
  void Stack<T>::push(const T& value)
  {
    list.push_back(value);
  }

  template <typename T>
  T Stack<T>::pop()
  {
    if (list.getSize() == 0)
    {
      throw std::runtime_error("Stack is empty");
    }

    auto it = list.begin();
    for (size_t i = 0; i < list.getSize() - 1; ++i)
    {
      ++it;
    }

    T value = *it;
    list.erase(it);
    return value;
  }

  template <typename T>
  T Stack<T>::top() const
  {
    if (list.getSize() == 0)
    {
      throw std::runtime_error("Stack is empty");
    }

    auto it = list.begin();
    for (size_t i = 0; i < list.getSize() - 1; ++i)
    {
      ++it;
    }

    return *it;
  }

  template <typename T>
  bool Stack<T>::isEmpty() const
  {
    return list.getSize() == 0;
  }

  template <typename T>
  size_t Stack<T>::size() const
  {
    return list.getSize();
  }
}

#endif
