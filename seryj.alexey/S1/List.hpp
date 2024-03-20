#ifndef LIST_HPP
#define LIST_HPP
#include "Iterator.hpp"
#include <exception>
template <class T>
class List
{
private:
  Node<T>* head;
  Iterator<T> begin;
  Iterator<T> end;
  size_t size = 0;
public:
  List<T>();
  List<T>(const List<T>& copy);
  List<T>(List<T>&& other);
  ~List<T>();

  T& operator[](size_t)const;
  List<T>& operator=(const List<T>& copy);
  List<T>& operator=(List<T>&& other);

  bool empty()const noexcept;
  void push(const T& value) noexcept;
  void pop();
  void clear() noexcept;
  void swap(List<T>& other) noexcept;
  size_t length() noexcept;
};
template<class T>
List<T>::List()
{
  head = new Node<T>();
  begin.node = head;
  end = begin;
}
template<class T>
List<T>::List(const List<T>& copy)
{
  head = new Node<T>;
  begin.node = head;
  end = begin;
  while (size < copy.size)
  {
    push(copy[size]);
  }
}
template<class T>
List<T>::List(List<T>&& other)
{
  head = other.head;
  begin.node = head;
  end = begin;
  while (size < other.size)
  {
    push(other[size]);
  }
}
template<class T>
List<T>::~List()
{
  clear();
}
template<class T>
T& List<T>::operator[](size_t value)const
{
  if (value >= size)
    throw std::logic_error("Index is out of boundaries");
  Iterator<T> iter;
  iter.node = head;
  for (size_t i = 0; i < value; i++)
  {
    iter++;
  }
  return *iter;
}
template<class T>
List<T>& List<T>::operator=(const List<T>& copy)
{
  clear();
  head = new Node<int>;
  begin.node = head;
  end = begin;
  while (size < copy.size)
  {
    push(copy[size]);
  }
  return *this;
}
template<class T>
List<T>& List<T>::operator=(List<T>&& other)
{
  clear();
  head = other.head;
  begin.node = head;
  end = begin;
  while (size < other.size)
  {
    push(other[size]);
  }
  return *this;
}
template<class T>
bool List<T>::empty() const noexcept
{
  return (size == 0);
}

template<class T>
void List<T>::push(const T& value) noexcept
{
  if (empty())
  {
    *end = value;
    size++;
  }
  else
  {
    end.node->next = new Node<T>;
    ++end;
    *end = value;
    size++;
  }
}

template<class T>
void List<T>::pop()
{
  if (empty())
    throw std::logic_error("No more elements to pop\n");
  Iterator<T> iter(begin);
  while (iter.node->next != end.node && size > 1)
  {
    iter++;
  }
  delete end.node;
  end = iter;
  size--;
}

template<class T>
void List<T>::clear() noexcept
{
  while (!empty())
  {
    pop();
  }
}

template<class T>
void List<T>::swap(List<T>& other) noexcept
{
  Node<T>* buffer_head = other.head;
  other.head = head;
  head = buffer_head;
  other.begin.node = other.head;
  begin.node = head;
  Iterator<T> buffer_end = other.end;
  other.end = end;
  end = buffer_end;
  size_t buffer_size = other.size;
  other.size = size;
  size = buffer_size;
}
template<class T>
size_t List<T>::length() noexcept
{
  return size;
}
#endif
