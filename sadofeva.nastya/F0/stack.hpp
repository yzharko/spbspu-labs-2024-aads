#ifndef STACK_HPP
#define STACK_HPP

#include <stdexcept>
#include "list.hpp"

namespace sadofeva
{
  template <typename T>
  class Stack
  {
   public:
    Stack() = default;
    Stack(const Stack &);
    Stack(Stack &&);

    Stack & operator=(const Stack &);
    Stack & operator=(Stack &&);

    void swap(Stack &) noexcept;

    void push(const T &);
    void drop();
    const T & top() const;
    bool empty() const;
    T & front();

   private:
    List<T> list_;
  };
}

template <typename T>
sadofeva::Stack<T>::Stack(const Stack & s):
  list_(s.list_)
{}
template <typename T>
sadofeva::Stack<T>::Stack(Stack && s):
  list_{ std::move(s.list_) }
{}
template <typename T>
sadofeva::Stack<T> & sadofeva::Stack<T>::operator=(const Stack & s)
{
  if (this != &s)
  {
    Stack<T> tmp(s);
    swap(tmp);
  }
  return *this;
}
template <typename T>
T & sadofeva::Stack<T>::front()
{
  return list_.front();
}
template <typename T>
sadofeva::Stack<T> & sadofeva::Stack<T>::operator=(Stack && s)
{
  if (this != &s)
  {
    Stack<T> tmp(std::move(s));
    swap(tmp);
  }
  return *this;
}
template <typename T>
void sadofeva::Stack<T>::swap(Stack & s) noexcept
{
  std::swap(list_, s.list_);
}

template <typename T>
void sadofeva::Stack<T>::push(const T & value)
{
  list_.push_front(value);
}

template <typename T>
void sadofeva::Stack<T>::drop()
{
  if (empty())
  {
    throw std::logic_error("stack is empty");
  }
  list_.pop_front();
}

template <typename T>
const T & sadofeva::Stack<T>::top() const
{
  if (empty())
  {
    throw std::logic_error("stack is empty");
  }
  return list_.front();
}

template <typename T>
bool sadofeva::Stack<T>::empty() const
{
  return list_.empty();
}

#endif
