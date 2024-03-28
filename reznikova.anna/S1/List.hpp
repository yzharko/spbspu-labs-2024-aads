#ifndef LIST_HPP
#define LIST_HPP
#include <iostream>
#include <cassert>
#include <cstddef>
#include <stdexcept>

namespace reznikova
{
  template< typename T >
  class List
  {
  public:
    class Iterator;
    class ConstIterator;
    List();
    List(const List & other);
    List(List && other);
    List(size_t count, const T & value);
    List(std::initializer_list<T> init);
    template < class InputIterator >
    List(InputIterator first, InputIterator last);
    ~List();

    List< T >& operator=(const List< T >& other);
    List< T >& operator=(List< T >&& other);

    void pushFront(const T & val);
    void pushBack(const T & val);
    void popFront();
    void popBack();
    T & getFront() noexcept;
    T & getBack() noexcept;
    bool empty() noexcept;
    void clear() noexcept;
    void swap(List & other);
    ConstIterator begin() const;
    ConstIterator end() const;
    Iterator begin();
    Iterator end();

    void remove(const T& value);
    template< class UnaryPredicate >
    void remove_if(UnaryPredicate p);
    void assign(size_t count, const T& value);
    template< class InputIt >
    void assign(InputIt first, InputIt last);
    void assign(std::initializer_list<T> ilist);
    Iterator insert(Iterator pos, const T& value);
    Iterator erase(Iterator pos);
    void reverse();
    void splice(Iterator position, List< T >& x);
    size_t getSize();

  private:
    struct Node
    {
      T data_;
      Node * prev_;
      Node * next_;
      Node() : data_(0), prev_(nullptr), next_(nullptr) {}
      Node(const T & data, Node * prev, Node * next) : data_(data), prev_(prev), next_(next) {}
    };
    size_t size_;
    Node * head_;
    Node * tail_;
  };
}

template< typename T >
class reznikova::List< T >::ConstIterator
{
  public:
    friend class List< T >;
    using this_t = ConstIterator;
    ConstIterator();
    ConstIterator(const this_t&) = default;
    ~ConstIterator() = default;
    this_t & operator=(const this_t &) = default;
    this_t & operator++();
    this_t operator++(int);
    this_t & operator--();
    this_t operator--(int);
    const T & operator*() const;
    const T * operator->() const;
    bool operator!=(const this_t &) const;
    bool operator==(const this_t &) const;
    this_t moveForward(size_t i);
    this_t moveBackward(size_t i);
    Node * getNode();
  private:
    Node * node_;
    ConstIterator(Node *, const List< T > *);
};

template< typename T >
typename reznikova::List< T >::ConstIterator & reznikova::List< T >::ConstIterator::operator++()
{
  assert(node_ == nullptr);
  node_ = node_->next_;
  return *this;
}

template< typename T >
typename reznikova::List< T >::ConstIterator reznikova::List< T >::ConstIterator::operator++(int)
{
  assert(node_ == nullptr);
  Iterator result(*this);
  node_ = node_->next_;
  return result;
}

template< typename T >
typename reznikova::List< T >::ConstIterator& reznikova::List< T >::ConstIterator::operator--()
{
  assert(node_ == nullptr);
  node_ = node_->prev_;
  return *this;
}

template< typename T >
typename reznikova::List< T >::ConstIterator reznikova::List< T >::ConstIterator::operator--(int)
{
  assert(node_ == nullptr);
  Iterator result(*this);
  node_ = node_->prev_;
  return result;
}

template< typename T >
bool reznikova::List< T >::ConstIterator::operator==(const ConstIterator & rhs) const
{
  return node_ == rhs.node_;
}

template< typename T >
bool reznikova::List< T >::ConstIterator::operator!=(const ConstIterator & rhs) const
{
  return !(rhs == *this);
}

template< typename T >
const T & reznikova::List< T >::ConstIterator::operator*() const
{
  assert(node_ == nullptr);
  return node_->data_;
}

template< typename T >
const T * reznikova::List< T >::ConstIterator::operator->() const
{
  assert(node_ == nullptr);
  return std::addressof(node_->data_);
}

//template< typename T >
//reznikova::List< T >::ConstIterator reznikova::List< T >::ConstIterator::moveForward(size_t i)
//{
//  for (size_t j = 0; j < i; j++)
//  {
//    assert(!node_);
//    node_ = node_->next_;
//  }
//  return node_;
//}
//
//template< typename T >
//reznikova::List< T >::ConstIterator reznikova::List< T >::ConstIterator::moveBackward(size_t i)
//{
//  for (size_t j = 0; j < i; j++)
//  {
//    assert(!node_);
//    node_ = node_->prev_;
//  }
//  return node_;
//}

template< typename T >
typename reznikova::List< T >::Node * reznikova::List< T >::ConstIterator::getNode()
{
  return node_;
}

template< typename T >
class reznikova::List< T >::Iterator
{
  public:
    friend class List< T >;
    using this_t = Iterator;
    Iterator();
    Iterator(ConstIterator);
    Iterator(const this_t &) = default;
    ~Iterator() = default;
    this_t & operator=(const this_t &) = default;
    this_t & operator++();
    this_t operator++(int);
    this_t & operator--();
    this_t operator--(int);
    T & operator*();
    T * operator->();
    const T & operator*() const;
    const T * operator->() const;
    bool operator!=(const Iterator &) const;
    bool operator==(const Iterator &) const;
    this_t moveForward(size_t i);
    this_t moveBackward(size_t i);
    Node * getNode();
  private:
    ConstIterator iter_;
};

template< typename T >
typename reznikova::List< T >::Iterator & reznikova::List< T >::Iterator::operator++()
{
  assert(iter_.node_ == nullptr);
  iter_.node_ = iter_.node_->next_;
  return *this;
}

template< typename T >
typename reznikova::List< T >::Iterator reznikova::List< T >::Iterator::operator++(int)
{
  assert(iter_.node_ == nullptr);
  Iterator result(*this);
  iter_.node_ = iter_.node_->next_;
  return result;
}

template< typename T >
typename reznikova::List< T >::Iterator & reznikova::List< T >::Iterator::operator--()
{
  assert(iter_.node_ == nullptr);
  iter_.node_ = iter_.node_->prev_;
  return *this;
}

template< typename T >
typename reznikova::List< T >::Iterator reznikova::List< T >::Iterator::operator--(int)
{
  assert(iter_.node_ == nullptr);
  Iterator result(*this);
  iter_.node_ = iter_.node_->prev_;
  return result;
}

template< typename T >
bool reznikova::List< T >::Iterator::operator==(const Iterator & rhs) const
{
  return iter_.node_ == rhs.node_;
}

template< typename T >
bool reznikova::List< T >::Iterator::operator!=(const Iterator & rhs) const
{
  return !(rhs == *this);
}

template< typename T >
T & reznikova::List< T >::Iterator::operator*()
{
  assert(iter_.node_ == nullptr);
  return iter_.node_->data_;
}

template< typename T >
T * reznikova::List< T >::Iterator::operator->()
{
  assert(iter_.node_ == nullptr);
  return std::addressof(iter_.node_->data_);
}

//template< typename T >
//reznikova::List< T >::Iterator reznikova::List< T >::Iterator::moveForward(size_t i)
//{
//  for (size_t j = 0; j < i; j++)
//  {
//    assert(!iter_.node_);
//    iter_.node_ = iter_.node_->next_;
//  }
//  return ConstIterator(iter_.node_);
//}
//
//template< typename T >
//reznikova::List< T >::Iterator reznikova::List< T >::Iterator::moveBackward(size_t i)
//{
//  for (size_t j = 0; j < i; j++)
//  {
//    assert(!iter_.node_);
//    iter_.node_ = iter_.node_->prev_;
//  }
//  return iter_.node_;
//}

template< typename T >
typename reznikova::List< T >::Node * reznikova::List< T >::Iterator::getNode()
{
  return iter_.node_;
}

template< typename T >
reznikova::List< T >::List():
  size_(0),
  head_(nullptr),
  tail_(nullptr)
{}

template< typename T >
reznikova::List<T>::List(const List & other):
  size_(0),
  head_(nullptr),
  tail_(nullptr)
{
  Node * temp = other.head_;
  while(temp)
  {
    pushBack(temp->data_);
    temp = temp->next_;
  }
}

template< typename T >
reznikova::List< T >::List(List && other):
  size_(other.size_),
  head_(other.head_),
  tail_(other.tail_)
{
  other.size_ = 0;
  other.head_ = nullptr;
  other.tail_ = nullptr;
}

template< typename T >
reznikova::List< T >::List(size_t count, const T & value):
List()
{
  for (size_t i; i < count; i++)
  {
    pushBack(value);
  }
}

template< typename T >
reznikova::List< T >::List(std::initializer_list<T> init):
List()
{
  const T * ptr = init.begin();
  while (ptr)
  {
    pushBack(*ptr);
    ptr++;
  }
}

template< typename T >
template < class InputIterator >
reznikova::List< T >::List(InputIterator first, InputIterator last):
List()
{
  while (first != last)
  {
    pushBack(*first);
    first++;
  }
}

template< typename T >
reznikova::List<T>::~List()
{
  clear();
  delete head_;
}

template< typename T >
reznikova::List< T >& reznikova::List< T >::operator=(const List< T >& other)
{
  List< T > temp(other);
  if (std::addressof(other) != this)
  {
    swap(temp);
  }
  return *this;
}

template< typename T >
reznikova::List< T >& reznikova::List< T >::operator=(List< T >&& other)
{
  List< T > temp(std::move(other));
  if (std::addressof(other) != this)
  {
    swap(temp);
  }
  return *this;
}

template< typename T >
void reznikova::List<T>::pushFront(const T & val)
{
  Node * newNode = new Node(val, nullptr, head_);
  if (empty())
  {
    tail_ = newNode;
    head_ = newNode;
  }
  else
  {
    head_->prev_ = newNode;
    head_ = newNode;
  }
  size_++;
}

template< typename T >
void reznikova::List<T>::pushBack(const T & val)
{
  Node * newNode = new Node(val, tail_, nullptr);
  if (empty())
  {
    tail_ = newNode;
    head_ = newNode;
  }
  else
  {
    tail_->next_ = newNode;
    tail_ = newNode;
  }
  size_++;
}

template< typename T >
void reznikova::List<T>::popFront()
{
  if (empty())
  {
    throw std::logic_error("can't delete element from empty list");
  }
  Node * temp = head_;
  head_ = head_->next_;
  if (temp->next_ == nullptr)
  {
    tail_ = nullptr;
  }
  delete temp;
  size_--;
}

template< typename T >
void reznikova::List<T>::popBack()
{
  if (empty())
  {
    throw std::logic_error("can't delete element from empty list");
  }
  Node * temp = tail_;
  tail_ = tail_->prev_;
  if (size_ == 1)
  {
    head_ = nullptr;
  }
  delete temp;
  size_--;
}

template< typename T >
T & reznikova::List<T>::getFront() noexcept
{
  return head_->data_;
}

template< typename T >
T & reznikova::List<T>::getBack() noexcept
{
  return tail_->data_;
}

template< typename T >
bool reznikova::List<T>::empty() noexcept
{
  return (size_ == 0);
}

template< typename T >
void reznikova::List<T>::clear() noexcept
{
  while (!empty())
  {
    popFront();
  }
}

template< typename T >
void reznikova::List<T>::swap(List & other)
{
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(size_, other.size_);
}

template< typename T >
typename reznikova::List< T >::ConstIterator reznikova::List< T >::begin() const
{
  return ConstIterator(this->head_, this);
}

template< typename T >
typename reznikova::List< T >::ConstIterator reznikova::List< T >::end() const
{
  return nullptr;
}

template< typename T >
typename reznikova::List< T >::Iterator reznikova::List< T >::begin()
{
  return ConstIterator(this->head_, this);
}

template< typename T >
typename reznikova::List< T >::Iterator reznikova::List< T >::end()
{
  return nullptr;
}


template< typename T >
void reznikova::List< T >::remove(const T& value)
{
  Node * temp = head_;
  while (temp)
  {
    if ((temp->data_ == value) && (temp == head_))
    {
      popFront();
    }
    else if ((temp->data_ == value) && (temp == tail_))
    {
      popBack();
    }
    else if ((temp->data_ == value) && (temp != tail_) && (temp != head_))
    {
      temp->next_->prev_ = temp->prev_;
      temp->prev_->next_ = temp->next_;
      delete temp;
      size_--;
    }
    temp = temp->next_;
  }
}

template< typename T >
template< class UnaryPredicate>
void reznikova::List< T >::remove_if(UnaryPredicate p)
{
  Node * temp = head_;
  while (temp)
  {
    if ((p(temp->data_)) && (temp == head_))
    {
      popFront();
    }
    else if ((p(temp->data_)) && (temp == tail_))
    {
      popBack();
    }
    else if ((p(temp->data_)) && (temp != tail_) && (temp != head_))
    {
      temp->next_->prev_ = temp->prev_;
      temp->prev_->next_ = temp->next_;
      delete temp;
      size_--;
    }
    temp = temp->next_;
  }
}

template< typename T >
void reznikova::List< T >::assign(size_t count, const T& value)
{
  clear();
  for (size_t i = 0; i < count; i++)
  {
    pushBack(value);
  }
}

template< typename T >
template< class InputIt >
void reznikova::List< T >::assign(InputIt first, InputIt last)
{
  clear();
  while (first != last)
  {
    pushBack(*first);
    first++;
  }
}

template< typename T >
void reznikova::List< T >::assign(std::initializer_list<T> ilist)
{
  clear();
  const T * ptr = ilist.begin();
  while (ptr)
  {
    pushBack(*ptr);
    ptr++;
  }
}

template< typename T >
typename reznikova::List< T >::Iterator reznikova::List< T >::insert(Iterator pos, const T& value)
{
  Iterator it;
  if (pos == head_)
  {
    pushFront(value);
    it = head_;
  }
  else
  {
    Node * node = new Node(value, pos->prev_, pos->prev_->next_);
    it = node;
    pos->prev_ = it;
    pos->prev_next_ = it;
  }
  return it;
}

template< typename T >
typename reznikova::List< T >::Iterator reznikova::List< T >::erase(Iterator pos)
{
  Iterator it;
  if (pos == head_)
  {
    popFront();
    it = head_;
  }
  else if (pos == tail_)
  {
    popBack();
    it = tail_;
  }
  else
  {
    pos->next_->prev_ = pos->prev_;
    pos->prev_->next_ = pos->next_;
    it = pos->next_;
    delete pos;
  }
  return it;
}

template< typename T >
void reznikova::List< T >::reverse()
{
  Node * temp = head_;
  while (head_->next_)
  {
    std::swap(head_->next_, head_->prev_);
    head_ = head_->prev_;
  }
  std::swap(tail_, temp);
  delete temp;
}

template< typename T >
void reznikova::List< T >::splice(Iterator position, List< T >& x)
{
  while (x.head_)
  {
    this->insert(position);
    position++;
    x.head_ = x.head_->next_;
  }
  delete x;
}

template< typename T >
size_t reznikova::List< T >::getSize()
{
  return size_;
}

#endif
