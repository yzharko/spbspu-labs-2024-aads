#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>
#include <stdexcept>
#include <cassert>

namespace sadofeva
{
  template < typename T>
  class List
  {
  public:
    struct Node
    {
      Node(const T & value);
      T value;
      ~Node() = default;
      Node* next;
      Node* prev;
    };
    class iterator;
    class const_iterator;
    List();
    ~List();
    List(const List & list);
    List(List && list);
    void push_back(const T & value);
    void push_front(const T & value);
    void pop_front();
    void pop_back();
    void clear();
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    T & front();
    T & back();
    List & operator=(const List & list);
    List & operator=(List && list) noexcept;
    void swap(List & list) noexcept;
    bool empty() const;
  private:
    Node * head_;
    Node * tail_;
  };
}

template< typename T>
void sadofeva::List<T>::push_back(const T & value)
{
  Node * new_node = new Node(value);
  if (tail_)
  {
    tail_->next = new_node;
    new_node->prev = tail_;
  }
  else
  {
    head_ = new_node;
  }
  tail_ = new_node;
}

template<typename T>
void sadofeva::List<T>::push_front(const T & value)
{
  Node * new_node = new Node(value);
  new_node->next = head_;
  if (head_)
  {
    head_->prev = new_node;
  }
  else
  {
    tail_ = new_node;
  }
  head_ = new_node;
}

template<typename T>
void sadofeva::List<T>::pop_front()
{
  if (empty())
  {
    throw std::logic_error("List is empty");
  }
  Node * node_to_del = head_;
  if (head_ == tail_)
  {
    head_ = nullptr;
    tail_ = nullptr;
  }
  else
  {
    head_ = head_->next;
    head_->prev = nullptr;
  }
  delete node_to_del;
}

template<typename T>
void sadofeva::List<T>::pop_back()
{
  if (empty())
  {
    throw std::logic_error("List is empty");
  }
  Node * node_to_del = tail_;
  if (head_ == tail_)
  {
    head_ = nullptr;
    tail_ = nullptr;
  }
  else
  {
    tail_ = tail_->prev;
    tail_->next = nullptr;
  }
  delete node_to_del;
}


template<typename T>
sadofeva::List<T>::~List()
{
  clear();
}

template<typename T>
sadofeva::List<T>::List():
  head_(nullptr),
  tail_(nullptr)
{}

template<typename T>
void sadofeva::List<T>::clear()
{
  while ( head_ != nullptr)
  {
    Node * node_to_del = head_;
    head_ = head_->next;
    delete node_to_del;
  }
  head_ = nullptr;
  tail_ = nullptr;
}

template < typename T>
sadofeva::List<T>::Node::Node(const T & value):
  value(value),
  next(nullptr),
  prev(nullptr)
{}

template <typename T>
sadofeva::List<T>::List(const List & list):
  List()
{
  if (list.empty())
  {
    return;
  }
  try
  {
    Node * list_node = list.head_->next;
    head_ = new Node(list.head_->value);
    Node * this_node = head_;
    while (list_node)
    {
      this_node->next = new Node(list_node->value);
      this_node->next->prev = this_node;
      this_node = this_node->next;
      this_node = list_node->next;
    }
    tail_ = this_node;
  }
  catch (...)
  {
    clear();
    throw;
  }
}

template <typename T>
bool sadofeva::List<T>::empty() const
{
  return !head_;
}

template <typename T>
sadofeva::List<T>::List(List && list):
  head_(list.head_),
  tail_(list.tail_)
{
  list.head_ = nullptr;
  list.tail_ = nullptr;
}

template <typename T>
typename sadofeva::List<T>::List & sadofeva::List<T>::operator=(const List & list)
{
  if (this != & list)
  {
    List<T> tmp(list);
    swap(tmp);
  }
  return *this;
}

template <typename T>
typename sadofeva::List<T>::List & sadofeva::List<T>::operator=(List && list) noexcept
{
  if (this != &list)
  {
    swap(list);
  }
  return *this;
}

template <typename T>
void sadofeva::List<T>::swap(List & list) noexcept
{
  std::swap(head_,list.head_);
  std::swap(tail_,list.tail_);
}

template <typename T>
T & sadofeva::List<T>::front()
{
  if (empty())
  {
    throw std::logic_error("list is empty");
  }
  return *head_;
}

template <typename T>
class sadofeva::List<T>::iterator
{
  public:
    friend class List<T>;
    iterator();
    iterator(const iterator &) = default;
    ~iterator() = default;
    iterator & operator = (const iterator &) = default;
    iterator & operator++();
    iterator operator++(int);
    iterator & operator--();
    iterator operator--(int);
    T & operator*();
    T * operator ->();
    const T & operator*() const;
    const T * operator->() const;
    bool operator != (const iterator &) const;
    bool operator==(const iterator &) const;
  private:
    using Node = typename List<T>::Node;
    Node * node_;
    const List<T> * list_;
    iterator(Node * node, const List<T> * list);
};

template <typename T>
sadofeva::List<T>::iterator::iterator():
  node_(nullptr),
  list_(nullptr)
{}

template <typename T>
sadofeva::List<T>::iterator::iterator(Node * node, const List<T> * list):
  node_(node),
  list_(list)
{}

template <typename T>
typename sadofeva::List<T>::iterator & sadofeva::List<T>::iterator::operator++()
{
  assert(node_);
  node_ = node_->next;
  return *this;
}

template<typename T>
typename sadofeva::List<T>::iterator sadofeva::List<T>::iterator::operator++(int)
{
  assert(node_);
  iterator result(*this);
  ++(*this);
  return result;
}

template<typename T>
typename sadofeva::List<T>::iterator & sadofeva::List<T>::iterator::operator--()
{
  asset(node_);
  iterator result(*this);
  --(*this);
  return result;
}

template<typename T>
bool sadofeva::List<T>::iterator::operator==(const iterator & it) const
{
  return nose_ = it.node_ && list_ == it.list_;
}

template<typename T>
bool sadofeva::List<T>::iterator::operator!=(const iterator & it) const
{
  return !(it == *this);
}

template<typename T>
T & sadofeva::List<T>::iterator::operator*()
{
  assert(node_);
  return node_->value;
}

template <typename T>
T * sadofeva::List<T>::iterator::operator->()
{
  assert(node_);
  return std::addressof(node_->value);
}

template<typename T>
const T & sadofeva::List<T>::iterator::operator*() const
{
  assert(node_);
  return & node_->value;
}

template<typename T>
const T * sadofeva::List<T>::iterator::operator->() const
{
  assert(node_);
  return & node_->value;
}

template <typename T>
class sadofeva::List<T>::const_iterator
{
  public:
    friend class List<T>;
    const_iterator();
    const_iterator(const const_iterator &) = default;
    const_iterator(iterator);
    ~const_iterator() = default;
    const_iterator & operator = (const const_iterator &) = default;
    const_iterator & operator++();
    const_iterator operator++(int);
    const_iterator & operator --();
    const_iterator operator--(int);
    const T & operator*() const;
    const T * operator->() const;
    bool operator !=(const const_iterator &) const;
    bool operator ==(const const_iterator &) const;
  private:
    iterator iterator_;
};

template<typename T>
void sadofeva::List<T>::const_iterator::const_iterator():
  iterator_()
{}

template<typename T>
sadofeva::List<T>::const_iterator::const_iterator(iterator iter):
  iterator_(iter)
{}

template<typename T>
typename sadofeva::List<T>::const_iterator & sadofeva::List<T>::const_iterator::operator++()
{
  ++iterator_;
  return *this;
}

template<typename T>
typename sadofeva::List<T>::const_iterator sadofeva::List<T>::const_iterator::operator++(int)
{
  return const_iterator(iterator_++);
}

template<typename T>
typename sadofeva::List<T>::const_iterator sadofeva::List<T>::const_iterator::operator--()
{
  --iterator;
  return *this;
}

template<typename T>
typename sadofeva::List<T>::const_iterator sadofeva::List<T>::const_iterator::operator--(int)
{
  return iterator(iterator_--);
}

template<typename T>
bool sadofeva::List<T>::const_iterator::operator==(const const_iterator & it) const
{
  return iterator_ == it.iterator_;
}

template<typename T>
bool sadofeva::List<T>::const_iterator::operator!=(const const_iterator & it) const
{
  return !(it == *this);
}

template<typename T>
const T & sadofeva::List<T>::const_iterator::operator*() const
{
  return *iterator_;
}

template<typename T>
const T * sadofeva::List<T>::const_iterator::operator->() const
{
  return &(*iterator_);
}

template <typename T>
typename sadofeva::List<T>::iterator sadofeva::List<T>::begin()
{
  return iterator(head_,this);
}

template<typename T>
typename sadofeva::List<T>::iterator sadofeva::List<T>::end()
{
  return iterator(nullptr,this);
}

template <typename T>
typename sadofeva::List<T>::const_iterator sadofeva::List<T>::begin() const
{
  return const_iterator(iterator(head_,this));
}

template <typename T>
typename sadofeva::List<T>::const_iterator sadofeva::List<T>::end() const
{
  return const_iterator(iterator(nullptr,this));
}
#endif
