#ifndef STACK_HPP
#define STACK_HPP

#include <stdexcept>
#include <vector>

namespace kaseev {

  template< typename T >
  class Stack {
  public:
    Stack() = default;

    ~Stack() = default;

    Stack(const Stack &other) noexcept;

    Stack(Stack &&other) noexcept;

    Stack &operator=(const Stack &other);

    Stack &operator=(Stack &&other) noexcept;

    bool empty() const noexcept;

    size_t size() const noexcept;

    void clear() noexcept;

    void push(const T &value) noexcept;

    void push_back(const T &value) noexcept;

    void pop();

    T &top();

    T &back();

  private:
    std::vector<T> list;
  };

  template< typename T >
  Stack<T>::Stack(const Stack &other) noexcept: list(other.list)
  {}

  template< typename T >
  Stack<T>::Stack(Stack &&other) noexcept : list(std::move(other.list))
  {}

  template< typename T >
  Stack<T> &Stack<T>::operator=(const Stack &other)
  {
    if (this != &other)
    {
      list = other.list;
    }
    return *this;
  }

  template< typename T >
  Stack<T> &Stack<T>::operator=(Stack &&other) noexcept
  {
    if (this != &other)
    {
      list = std::move(other.list);
    }
    return *this;
  }

  template< typename T >
  void Stack<T>::push(const T& value) noexcept
  {
    list.insert(list.begin(), value);
  }

  template< typename T >
  void Stack<T>::push_back(const T &value) noexcept
  {
    list.push_back(value);
  }

  template< typename T >
  void Stack<T>::pop()
  {
    if (list.empty())
    {
      throw std::out_of_range("Stack is empty");
    }
    list.erase(list.begin());
  }

  template< typename T >
  T &Stack<T>::top()
  {
    if (list.empty())
    {
      throw std::out_of_range("Stack is empty");
    }
    return list[0];
  }

  template< typename T >
  T &Stack<T>::back()
  {
    if (list.empty())
    {
      throw std::out_of_range("Stack is empty");
    }
    return list[list.size() - 1];
  }

  template< typename T >
  bool Stack<T>::empty() const noexcept
  {
    return list.empty();
  }

  template< typename T >
  void Stack<T>::clear() noexcept
  {
    list.clear();
  }

  template< typename T >
  size_t Stack<T>::size() const noexcept
  {
    return list.size();
  }
}

#endif
