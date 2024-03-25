#ifndef DOUBLELIST_HPP
#define DOUBLELIST_HPP
#include <cstddef>
#include <utility>
#include <limits>
#include <cassert>
#include <memory>

namespace kovshikov
{
  template <typename T>
  class DoubleList
  {
  public:
    struct Node
    {
      friend class DoubleList<T>;
      Node(): data(0), prev(nullptr), next(nullptr) {};
      Node(T data_) :
      data(data_),
      prev(nullptr),
      next(nullptr)
      {};
      ~Node() = default;
    private:
      T data;
      Node* prev;
      Node* next;
    };

    struct Iterator
    {
      friend class DoubleList<T>;
      using this_t = Iterator;

      Iterator(): node(nullptr) {};
      Iterator(const this_t &) = default;
      Iterator(Node* ptr): node(ptr) {};
      ~Iterator() = default;

      this_t & operator=(const this_t &) = default;

      this_t & operator++();
      this_t operator++(int);

      this_t & operator--();
      this_t operator--(int);

      bool operator!=(const this_t & other) const;
      bool operator==(const this_t & other) const;

      T & operator*();
      T * operator->();
    private:
      Node* node;
    };

    DoubleList(): head_(nullptr), tail_(nullptr) {};
    DoubleList(const DoubleList& dl);
    DoubleList(DoubleList&& dl);
    DoubleList(size_t size, const T &value);
    ~DoubleList();

    DoubleList<T>& operator=(const DoubleList<T>& dl);
    DoubleList<T>& operator=(DoubleList&& dl);

    T& front() const;
    T& back() const;

    bool empty() const;

    void pushFront(const T &value);
    void pushBack(const T& value);
    void popFront();
    void popBack();
    void clear();
    void swap(DoubleList& dl);
    void remove(const T &value);
    template<class Predicate>
    void remove_if(Predicate pred);
    void assign(size_t size, const T &value);

    Iterator begin() const;
    Iterator end() const;
    const Iterator cbegin() const;
    const Iterator cend() const;

  private:
    Node* head_;
    Node* tail_;
  };
}

template<typename T>
kovshikov::DoubleList<T>::DoubleList(size_t size, const T &value)
{
  head_ = nullptr;
  tail_ = nullptr;
  for(size_t i = 0; i < size; i++)
  {
    this->pushBack(value);
  }
}

template <typename T>
kovshikov::DoubleList<T>::~DoubleList()
{
  clear();
}

template <typename T>
kovshikov::DoubleList<T>::DoubleList(const DoubleList& dl)
{
  this->head_ = nullptr;
  this->tail_ = nullptr;
  Node *temp = dl.head_;
  while(temp != nullptr)
  {
    this->pushBack(temp->data);
    temp = temp->next;
  }
}

template <typename T>
kovshikov::DoubleList<T>& kovshikov::DoubleList<T>::operator=(const DoubleList& dl)
{
  DoubleList<T> newDl(dl);
  this->swap(newDl);
  return *this;
}

template <typename T>
kovshikov::DoubleList<T>::DoubleList(DoubleList&& dl)
{
  this->head_ = nullptr;
  this->tail_ = nullptr;
  Node *temp = std::move(dl.head_);
  while(temp != nullptr)
  {
    this->pushBack(std::move(temp->data));
    temp = temp->next;
  }
}

template<typename T>
kovshikov::DoubleList<T>& kovshikov::DoubleList<T>::operator=(DoubleList&& dl)
{
  this->clear();
  Node *temp = std::move(dl.head_);
  while(temp != nullptr)
  {
    this->pushBack(std::move(temp->data));
    temp = temp->next;
  }
  return *this;
}

template <typename T>
T& kovshikov::DoubleList<T>::front() const
{
  return head_->data;
}

template <typename T>
T& kovshikov::DoubleList<T>::back() const
{
  return tail_->data;
}

template <typename T>
bool kovshikov::DoubleList<T>::empty() const
{
  if (head_ == nullptr && tail_ == nullptr)
  {
    return true;
  }
  else
  {
    return false;
  }
}

template <typename T>
void kovshikov::DoubleList<T>::pushFront(const T &value)
{
  Node* newNode = new Node(value);
  if (this->empty() == true)
  {
    head_ = newNode;
    tail_ = newNode;
  }
  else
  {
    newNode->next = head_;
    head_->prev = newNode;
    head_ = newNode;
  }
}

template <typename T>
void kovshikov::DoubleList<T>::pushBack(const T& value)
{
  Node* newNode = new Node(value);
  if (this->empty() == true)
  {
    head_ = newNode;
    tail_ = newNode;
  }
  else
  {
    newNode->prev = tail_;
    tail_->next = newNode;
    tail_ = newNode;
  }
}

template <typename T>
void kovshikov::DoubleList<T>::popFront()
{
  if(head_ != nullptr && tail_ != nullptr)
  {
    Node* temp = head_->next;
    delete head_;
    head_ = temp;
    if(head_ == nullptr)
    {
      tail_ = nullptr;
    }
    else
    {
      head_->prev = nullptr;
    }
  }
}

template <typename T>
void kovshikov::DoubleList<T>::popBack()
{
  if(head_ != nullptr && tail_ != nullptr)
  {
    Node* temp = tail_->prev;
    delete tail_;
    tail_ = temp;
    if(tail_ == nullptr)
    {
      head_ = nullptr;
    }
    else
    {
      tail_->next = nullptr;
    }
  }
}

template <typename T>
void kovshikov::DoubleList<T>::clear()
{
  while (head_ && tail_)
  {
    popFront();
  }
}

template <typename T>
void kovshikov::DoubleList<T>::swap(DoubleList& dl)
{
  Node* tempHead = dl.head_;
  Node* tempTail = dl.tail_;
  dl.head_ = this->head_;
  this->head_ = tempHead;
  dl.tail_ = this->tail_;
  this->tail_ = tempTail;
}

template<typename T>
void kovshikov::DoubleList<T>::remove(const T &value)
{
  Iterator iterator = this->begin();
  while(iterator != this->end())
  {
    if(iterator.node->data == value)
    {
      Node* tempPrev = iterator.node->prev;
      Node* tempNext = iterator.node->next;
      Iterator iteratorToDelete = iterator;
      if(head_ == tail_)
      {
        head_ = tail_ = nullptr;
      }
      else if(iterator.node == head_)
      {
        head_ = tempNext;
        tempNext->prev = nullptr;
      }
      else
      {
        tempPrev->next = tempNext;
        tempNext->prev = tempPrev;
      }
      delete iteratorToDelete.node;
    }
    iterator++;
   }
}

template<typename T>
template<class Predicate>
void kovshikov::DoubleList<T>::remove_if(Predicate pred)
{
  Iterator iterator = this->begin();
  while(iterator != this->end())
  {
    if(pred(iterator.node->data))
    {
      Node* tempPrev = iterator.node->prev;
      Node* tempNext = iterator.node->next;
      Iterator iteratorToDelete = iterator;
      if(head_ == tail_)
      {
        head_ = tail_ = nullptr;
      }
      else if(iterator.node == head_)
      {
        head_ = tempNext;
        tempNext->prev = nullptr;
      }
      else
      {
        tempPrev->next = tempNext;
        tempNext->prev = tempPrev;
      }
      delete iteratorToDelete.node;
    }
    iterator++;
   }
}

template<typename T>
void kovshikov::DoubleList<T>::assign(size_t size, const T &value)
{
  this->clear();
  for(size_t i = 0; i < size; i++)
  {
    this->pushBack(value);
  }
}

template<typename T>
typename kovshikov::DoubleList<T>::Iterator kovshikov::DoubleList<T>::begin() const
{
  return Iterator(head_);
}

template<typename T>
typename kovshikov::DoubleList<T>::Iterator kovshikov::DoubleList<T>::end() const
{
  if(this->empty())
  {
    return this->begin();
  }
  else
  {
    Node* pastTheEnd = tail_->next;
    return Iterator(pastTheEnd);
  }
}

template<typename T>
const typename kovshikov::DoubleList<T>::Iterator kovshikov::DoubleList<T>::cbegin() const
{
  return Iterator(head_);
}

template<typename T>
const typename kovshikov::DoubleList<T>::Iterator kovshikov::DoubleList<T>::cend() const
{
  if(this->empty)
  {
    return this->cbegin();
  }
  else
  {
    Node* pastTheEnd = tail_->next;
    return Iterator(pastTheEnd);
  }
}

template<typename T>
typename kovshikov::DoubleList<T>::Iterator::this_t & kovshikov::DoubleList<T>::Iterator::operator++()
{
  assert(node != nullptr);
  node = node->next;
  return *this;
}

template<typename T>
typename kovshikov::DoubleList<T>::Iterator::this_t kovshikov::DoubleList<T>::Iterator::operator++(int)
{
  assert(node != nullptr);
  this_t result(*this);
  ++(*this);
  return result;
}

template<typename T>
typename kovshikov::DoubleList<T>::Iterator::this_t & kovshikov::DoubleList<T>::Iterator::operator--()
{
  assert(node != nullptr);
  node = node->prev;
  return *this;
}

template<typename T>
typename kovshikov::DoubleList<T>::Iterator::this_t kovshikov::DoubleList<T>::Iterator::operator--(int)
{
  assert(node != nullptr);
  this_t result(*this);
  --(*this);
  return result;
}

template<typename T>
bool kovshikov::DoubleList<T>::Iterator::operator==(const this_t & other) const
{
  return node == other.node;
}

template<typename T>
bool kovshikov::DoubleList<T>::Iterator::operator!=(const this_t & other) const
{
  return !(other == *this);
}

template<typename T>
T & kovshikov::DoubleList<T>::Iterator::operator*()
{
  assert(node != nullptr);
  return node->data;
}

template<typename T>
T * kovshikov::DoubleList<T>::Iterator::operator->()
{
  assert(node != nullptr);
  return std::addressof(node->data);
}

#endif
