#ifndef LIST_HPP
#define LIST_HPP
#include <iterator>
#include <memory>
#include <stdexcept>
#include <utility>
#include "node.hpp"

namespace smolyakov
{
  template<typename T>
  class List
  {
  public:
    class Iterator;
    class ConstIterator;

    List();
    List(const List<T>& other);
    List(List<T>&& other);
    ~List();

    T operator [] (const size_t index);
    void pushFront(const T& value);
    void pushBack(const T& value);
    T popFront();
    T popBack();
    void clear();
    void swap(size_t value1Index, size_t value2Index);

    Iterator begin();
    Iterator end();
    ConstIterator constBegin();
    ConstIterator constEnd();

  private:
    size_t size_;
    Node<T>* head_;
    Node<T>* tail_;

    Node<T>* NodeByIndex(const size_t index);
  };

  template<typename T>
  class List<T>::Iterator : public std::iterator<std::forward_iterator_tag, T>
  {
  public:
    Iterator(Node<T>* node);
    Iterator(const Iterator& other) = default;
    ~Iterator() = default;

    Iterator& operator ++();
    Iterator operator ++(int);
    Iterator& operator --();
    Iterator operator --(int);

    T& operator *();
    T* operator ->();

    bool operator !=(const Iterator& rhs) const;
    bool operator ==(const Iterator& rhs) const;
  private:
    Node<T>* node_;
  };

  template<typename T>
  class List<T>::ConstIterator : public std::iterator<std::forward_iterator_tag, T>
  {
  public:
    ConstIterator(const Node<T>* node);
    ConstIterator(const ConstIterator& other) = default;
    ~ConstIterator() = default;

    ConstIterator& operator ++();
    ConstIterator operator ++(int);
    ConstIterator& operator --();
    ConstIterator operator --(int);

    T& operator *() const;
    T* operator ->() const;

    bool operator !=(const ConstIterator& rhs) const;
    bool operator ==(const ConstIterator& rhs) const;
  private:
    Node<T>* node_;
  };
}

template<typename T>
smolyakov::List<T>::Iterator::Iterator(Node<T>* node)
  : node_(node) {}

template<typename T>
typename smolyakov::List<T>::Iterator& smolyakov::List<T>::Iterator::operator ++()
{
  node_ = node_->next;
  return *this;
}

template<typename T>
typename smolyakov::List<T>::Iterator smolyakov::List<T>::Iterator::operator ++(int)
{
  List<T>::Iterator newIterator(*this);
  ++(*this);
  return newIterator;
}

template<typename T>
typename smolyakov::List<T>::Iterator& smolyakov::List<T>::Iterator::operator --()
{
  node_ = node_->previous;
  return *this;
}

template<typename T>
typename smolyakov::List<T>::Iterator smolyakov::List<T>::Iterator::operator --(int)
{
  List<T>::Iterator newIterator(*this);
  --(*this);
  return newIterator;
}

template<typename T>
T& smolyakov::List<T>::Iterator::operator *()
{
  return node_->value;
}

template<typename T>
T* smolyakov::List<T>::Iterator::operator ->()
{
  return std::addressof(node_->value);
}

template<typename T>
bool smolyakov::List<T>::Iterator::operator ==(const List<T>::Iterator& rhs) const
{
  return node_ == rhs.node_;
}

template<typename T>
bool smolyakov::List<T>::Iterator::operator !=(const List<T>::Iterator& rhs) const
{
  return node_ != rhs.node_;
}

template<typename T>
smolyakov::List<T>::ConstIterator::ConstIterator(const Node<T>* node)
  : node_(node) {}

template<typename T>
typename smolyakov::List<T>::ConstIterator& smolyakov::List<T>::ConstIterator::operator ++()
{
  node_ = node_->next;
  return *this;
}

template<typename T>
typename smolyakov::List<T>::ConstIterator smolyakov::List<T>::ConstIterator::operator ++(int)
{
  List<T>::ConstIterator newIterator(*this);
  ++(*this);
  return newIterator;
}

template<typename T>
typename smolyakov::List<T>::ConstIterator& smolyakov::List<T>::ConstIterator::operator --()
{
  node_ = node_->previous;
  return *this;
}

template<typename T>
typename smolyakov::List<T>::ConstIterator smolyakov::List<T>::ConstIterator::operator --(int)
{
  List<T>::Iterator newIterator(*this);
  --(*this);
  return newIterator;
}

template<typename T>
T& smolyakov::List<T>::ConstIterator::operator *() const
{
  return node_->value;
}

template<typename T>
T* smolyakov::List<T>::ConstIterator::operator ->() const
{
  return std::addressof(node_->value);
}

template<typename T>
bool smolyakov::List<T>::ConstIterator::operator ==(const List<T>::ConstIterator& rhs) const
{
  return node_ == rhs.node_;
}

template<typename T>
bool smolyakov::List<T>::ConstIterator::operator !=(const List<T>::ConstIterator& rhs) const
{
  return node_ != rhs.node_;
}

template<typename T>
smolyakov::List<T>::List()
  : size_(0), head_(nullptr), tail_(nullptr) {}

template<typename T>
smolyakov::List<T>::List(const List<T>& other)
  : size_(other.size_), head_(other.head_), tail_(other.tail_)
{
  if (size_ > 0)
  {
    head_ = new Node<T>(other.head_->value);
    Node<T>* tmpNode = other.head_;
    tail_ = head_;
    while(tmpNode->next != nullptr)
    {
      tail_->next = new Node<T>(tmpNode->next->value);
      tail_ = tail_->next;
      tmpNode = tmpNode->next;
    }
  }
}

template<typename T>
smolyakov::List<T>::List(List<T>&& other)
  : size_(other.size_), head_(other.head_), tail_(other.tail_)
{
  other.size_ = 0;
  other.head_ = nullptr;
  other.tail_ = nullptr;
}

template<typename T>
smolyakov::List<T>::~List<T>()
{
  clear();
}

template<typename T>
T smolyakov::List<T>::operator [] (const size_t index)
{
  return NodeByIndex(index)->value;
}

template<typename T>
void smolyakov::List<T>::pushBack(const T& value)
{
  Node<T> newTail = new Node<T>(value);

  if (size_ == 0)
  {
    head_ = newTail;
    tail_ = newTail;
  }
  else
  {
    newTail.previous = tail_;
    tail_->next = newTail;
    tail_ = newTail;
  }
  size_++;
}

template<typename T>
void smolyakov::List<T>::pushFront(const T& value)
{
  Node<T> newHead = new Node<T>(value);

  if (size_ == 0)
  {
    head_ = newHead;
    tail_ = newHead;
  }
  else
  {
    newHead.next = head_;
    head_->previous = newHead;
    head_ = newHead;
  }
  size_++;
}

template<typename T>
T smolyakov::List<T>::popFront()
{
  if (size_ == 0)
  {
    throw std::logic_error("Cannot pop a list with size 0");
  }
  else
  {
    Node<T> oldHead = head_;
    head_ = oldHead->next;
    T value = oldHead.value;
    delete oldHead;
    return value;
    size_--;
  }
}


template<typename T>
T smolyakov::List<T>::popBack()
{
  if (size_ == 0)
  {
    throw std::logic_error("Cannot pop a list with size 0");
  }
  else
  {
    Node<T> oldTail = tail_;
    tail_ = oldTail->previous;
    T value = oldTail.value;
    delete oldTail;
    return value;
    size_--;
  }
}

template<typename T>
void smolyakov::List<T>::clear()
{
  while (size_ > 0)
  {
    popFront();
  }
}

template <typename T>
smolyakov::Node<T>* smolyakov::List<T>::NodeByIndex(const size_t index)
{
  Node<T>* node = head_;
  size_t i = 0;
  while (node != nullptr)
  {
    if (i == index)
    {
      return node;
    }
    node = node->next;
    i++;
  }
  throw std::out_of_range("Given index was out of the list's range");
}

template<typename T>
void smolyakov::List<T>::swap(size_t value1Index, size_t value2Index)
{
  smolyakov::Node<T>* node1 = NodeByIndex(value1Index);
  smolyakov::Node<T>* node2 = NodeByIndex(value2Index);
  std::swap(node1, node2);
}



#endif
