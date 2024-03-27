#ifndef LIST_HPP
#define LIST_HPP
#include "node.hpp"
#include <cstddef>
#include <iterator>
#include <stdexcept>

template<typename T>
class List
{
private:
  struct Node
  {
    T value;
    Node* next;
    Node(T val, Node* next = nullptr) : value(val), next(next) {}
  };
  Node* head;
  Node* tail;
  size_t size;
public:
  List() : head(nullptr), tail(nullptr), size(0) {}
  List(const List& other) : head(nullptr), tail(nullptr), size(0)
  {
    List<T>::Node* current = other.head;
    while (current != nullptr)
    {
      push_back(current->value);
      current = current->next;
    }
  }
  List(List&& other) noexcept : head(other.head), tail(other.tail), size(other.size)
  {
    other.head = other.tail = nullptr;
    other.size = 0;
  }
  List& operator=(const List& other)
  {
    if (this != &other)
    {
      List tmp(other);
      swap(tmp);
    }
    return *this;
  }
  List& operator=(List&& other) noexcept
  {
    if (this != &other)
    {
      clear();
      head = other.head;
      tail = other.tail;
      size = other.size;
      other.head = other.tail = nullptr;
      other.size = 0;
    }
    return *this;
  }
  ~List() { clear(); }
  void push_back(T val)
  {
        List<T>::Node* newNode = new List<T>::Node(val);
        if (tail) tail->next = newNode;
        else head = newNode;
        tail = newNode;
        ++size;
  }
  bool empty() const { return size == 0; }
  void clear()
  {
    while (head)
    {
        List<T>::Node* temp = head;
        head = head->next;
        delete temp;
    }
    head = tail = nullptr;
    size = 0;
  }
  class iterator
  {
    List<T>::Node* ptr;
  public:
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::forward_iterator_tag;
    iterator(List<T>::Node* p = nullptr) : ptr(p) {}
    iterator& operator++()
    {
      if (ptr == nullptr) throw std::out_of_range("Iterator cannot be incremented past the end");
      ptr = ptr->next;
      return *this;
    }
    bool operator!=(const iterator& other) const
    {
      return ptr != other.ptr;
    }
    reference operator*()
    {
      if (ptr == nullptr) throw std::out_of_range("Iterator cannot be dereferenced");
      return ptr->value;
    }
  };
  iterator begin()
  {
    return iterator(head);
  }
  iterator end()
  {
    if (this == nullptr)
    {
      return nullptr;
    }
    else
    {
      return iterator(nullptr);
    }
  }
  class const_iterator
  {
    const List<T>::Node* ptr;
  public:
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = const T*;
    using reference = const T&;
    using iterator_category = std::forward_iterator_tag;
    const_iterator(const List<T>::Node* p = nullptr) : ptr(p) {}
    const_iterator& operator++()
    {
      if (ptr == nullptr) throw std::out_of_range("Const iterator cannot be incremented past the end");
      ptr = ptr->next; return *this;
    }
    bool operator!=(const const_iterator& other) const
    {
      return ptr != other.ptr;
    }
    reference operator*() const
    {
      if (ptr == nullptr) throw std::out_of_range("Const iterator cannot be dereferenced");
      return ptr->value;
    }
  };
  const_iterator begin() const
  {
    return const_iterator(head);
  }
  const_iterator end() const
  {
    return const_iterator(nullptr);
  }
};
#endif
