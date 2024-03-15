#ifndef LIST_HPP
#define LIST_HPP

#include "node.hpp"
#include "iterator.hpp"
#include <cstddef>
#include <stdexcept>
#include <initializer_list>
#include <limits>

namespace khoroshkin
{
  template< typename T >
  using iterator = ListIterator< T, false >;
  template< typename T >
  using const_iterator = ListIterator< T, true >;

  template< typename T >
  class List
  {
  public:
    List();
    List(size_t count, const T & value);
    List(std::initializer_list< T > init);
    List(const List & obj);
    List(List && obj);
    ~List();

    List< T > & operator=(const List & obj);
    List< T > & operator=(List && obj);

    void push_back(T data);
    void pop_front();
    void clear();
    void swap(List< T > & other);
    void assign(size_t count, const T & value);
    void assign(const_iterator< T > first, const_iterator< T > last);
    void assign(std::initializer_list< T > ilist);
    iterator< T > insert_after(iterator< T > pos, const T & value);
    iterator< T > insert_after(iterator< T > pos, size_t count, const T & value);
    iterator< T > erase_after(iterator< T > pos);
    iterator< T > erase_after(iterator< T > first, iterator< T > last);
    template< class... Args >
    iterator< T > emplace_after(iterator< T > pos, Args &&... args);

    T & front();
    int getSize();
    bool isEmpty();
    T & operator[](const size_t index);
    void reverse();
    void splice_after(iterator< T > pos, List< T > & other);
    void remove(const T & value, bool onlyFirst = false);
    template< typename UnaryPredicate >
    void remove_if(UnaryPredicate p);
    void unique();
    void sort();
    void merge(List< T > & other);

    bool operator==(List< T > & rhs);
    bool operator!=(List< T > & rhs);
    bool operator<(List< T > & rhs);
    bool operator>(List< T > & rhs);
    bool operator<=(List< T > & rhs);
    bool operator>=(List< T > & rhs);

    iterator< T > begin();
    iterator< T > end();
    const_iterator< T > cbegin();
    const_iterator< T > cend();

    iterator< T > next(iterator< T > it);
  private:
    int size;
    Node< T > * head;
  };
}

template< typename T >
khoroshkin::List< T >::List() :
  size(0), head(nullptr)
{}

template< typename T >
khoroshkin::List< T >::List(size_t count, const T & value)
{
  for (size_t i = 0; i < count; ++i)
  {
    this->push_back(value);
  }
}

template< typename T >
khoroshkin::List< T >::List(std::initializer_list< T > init)
{
  for (auto it = init.begin(); it != init.end(); ++it)
  {
    this->push_back(*it);
  }
}

template< typename T >
khoroshkin::List< T >::List(const khoroshkin::List< T > & obj)
{
  if (obj.head == nullptr)
  {
    head = nullptr;
  }
  else
  {
    head = new Node< T >(*obj.head);
  }
  size = obj.size;
}

template< typename T >
khoroshkin::List< T > & khoroshkin::List< T >::operator=(const List & obj)
{
  if (this != &obj)
  {
    this->size = obj.size;
    clear();
    Node< T > * temp = obj.head;
    while (temp)
    {
      push_back(temp->data);
      temp = temp->pNext;
    }
  }
  return *this;
}

template< typename T >
khoroshkin::List< T >::List(khoroshkin::List< T > && obj) :
  size(obj.size), head(obj.head)
{
  obj.clear();
}

template< typename T >
khoroshkin::List< T > & khoroshkin::List< T >::operator=(List && obj)
{
  if (this != &obj)
  {
    clear();
    this->size = obj.size;
    while (obj.head)
    {
      push_back(obj.head->data);
      obj.head = obj.head->pNext;
    }
  }
  obj.clear();
  return *this;
}

template< typename T >
void khoroshkin::List< T >::assign(size_t count, const T & value)
{
  this->clear();
  for (size_t i = 0; i < count; ++i)
  {
    this->push_back(value);
  }
}

template< typename T >
void khoroshkin::List< T >::assign(const_iterator< T > first, const_iterator< T > last)
{
  this->clear();
  while (first != last)
  {
    this->push_back(*first);
    first++;
  }
}

template< typename T >
void khoroshkin::List< T >::assign(std::initializer_list< T > ilist)
{
  this->clear();
  for (auto it = ilist.begin(); it != ilist.end(); ++it)
  {
    this->push_back(*it);
  }
}

template< typename T >
void khoroshkin::List< T >::push_back(T data)
{
  if (head == nullptr)
  {
      head = new Node< T >(data);
  }
  else
  {
    Node< T > * current = this->head;
    while (current->pNext != nullptr)
    {
      current = current->pNext;
    }
    current->pNext = new Node< T >(data);
  }
  size++;
}

template< typename T >
khoroshkin::iterator< T > khoroshkin::List< T >::next(iterator< T > it)
{
  return ++it;
}

template< typename T >
T & khoroshkin::List< T >::operator[](const size_t index)
{
  size_t counter = 0;
  Node< T > * current = this->head;
  while (current != nullptr)
  {
    if (counter == index)
    {
      return current->data;
    }
    current = current->pNext;
    counter++;
  }
  throw std::out_of_range("Index out of range");
}

template< typename T >
void khoroshkin::List< T >::pop_front()
{
  Node< T > * temp = head;
  head = head->pNext;
  delete temp;
  size--;
}

template< typename T >
T & khoroshkin::List< T >::front()
{
  return head->data;
}

template< typename T >
void khoroshkin::List< T >::clear()
{
  while (size)
  {
    pop_front();
  }
}

template < typename T >
int khoroshkin::List< T >::getSize()
{
  return size;
}

template< typename T >
bool khoroshkin::List< T >::isEmpty()
{
  return !head;
}

template < typename T >
khoroshkin::List< T >::~List()
{
  clear();
}

template< typename T >
void khoroshkin::List< T >::swap(khoroshkin::List< T > & other)
{
  Node < T > * tempH = this->head;
  this->head = other.head;
  other.head = tempH;

  int tempS = this->size;
  this->size = other.size;
  other.size = tempS;
}

template< typename T >
khoroshkin::iterator< T > khoroshkin::List< T >::begin()
{
  if (isEmpty())
  {
    return end();
  }
  return this->head;
}

template< typename T >
khoroshkin::iterator< T > khoroshkin::List< T >::end()
{
  return nullptr;
}

template< typename T >
khoroshkin::const_iterator< T > khoroshkin::List< T >::cbegin()
{
  if (isEmpty())
  {
    return end();
  }
  return this->head;
}

template< typename T >
khoroshkin::const_iterator< T > khoroshkin::List< T >::cend()
{
  return nullptr;
}

template< typename T >
void khoroshkin::List< T >::remove(const T & value, bool onlyFirst)
{
  for (auto it = this->begin(); it != this->end(); ++it)
  {
    if (*it == value && *it == *this->begin())
    {
      this->pop_front();
      it = this->begin();
      if (onlyFirst)
      {
        break;
      }
    }
    else if (next(it) != this->end() && *next(it) == value)
    {
      Node< T > * subhead = it.node;
      Node< T > * todelete = subhead->pNext;
      subhead->pNext = todelete->pNext;
      delete todelete;
      this->size--;
      it = this->begin();
      if (onlyFirst)
      {
        break;
      }
    }
  }
}

template< typename T >
template< typename UnaryPredicate >
void khoroshkin::List< T >::remove_if(UnaryPredicate p)
{
  for (auto it = this->begin(); it != this->end(); ++it)
  {
    if (p(*it))
    {
      remove(*it);
      it = this->begin();
    }
  }
}

template< typename T >
khoroshkin::iterator< T > khoroshkin::List< T >::insert_after(iterator< T > pos, const T & value)
{
  Node< T > * subhead = pos.node;
  Node< T > * newNode = new Node< T >(value);
  newNode->pNext = subhead->pNext;
  subhead->pNext = newNode;
  size++;
  return newNode;
}

template< typename T >
khoroshkin::iterator< T > khoroshkin::List< T >::insert_after(iterator< T > pos, size_t count, const T & value)
{
  if (count == 0)
  {
    return pos;
  }
  for (size_t i = 0; i < count; ++i)
  {
    pos = insert_after(pos, value);
  }
  return pos;
}

template< typename T >
khoroshkin::iterator< T > khoroshkin::List< T >::erase_after(iterator< T > pos)
{
  if (pos.node->pNext)
  {
    Node< T > * todelete = pos.node->pNext;
    pos.node->pNext = pos.node->pNext->pNext;
    delete todelete;
    size--;
    return pos.node->pNext;
  }
  return this->end();
}

template< typename T >
khoroshkin::iterator< T > khoroshkin::List< T >::erase_after(iterator< T > first, iterator< T > last)
{
  while (next(first) != last)
  {
    erase_after(first);
  }
  return last;
}

template< typename T >
void khoroshkin::List< T >::reverse()
{
  List< T > temp;
  auto it = this->begin();
  while (it != this->end())
  {
    if (this->next(it) != this->end() && next(it).node->pNext == nullptr)
    {
      temp.push_back(*next(it));
      this->erase_after(it);
      if (this->getSize() != 1)
      {
        it = this->begin();
      }
    }
    if (this->getSize() == 1)
    {
      temp.push_back(*(this->begin()));
    }
    if (this->getSize() != 2)
    {
      it++;
    }
  }
  this->assign(temp.begin(), temp.end());
}

template< typename T >
void khoroshkin::List< T >::splice_after(iterator< T > pos, khoroshkin::List< T > & other)
{
  for (auto it = other.begin(); it != other.end(); ++it)
  {
    this->insert_after(pos, *it);
    pos++;
  }
}

template< typename T >
void khoroshkin::List< T >::unique()
{
  auto it = this->begin();
  while (it != this->end())
  {
    if (next(it) != this->end() && *next(it) == *it)
    {
      this->erase_after(it);
      it = this->begin();
    }
    it++;
  }
}

template< typename T >
bool khoroshkin::List< T >::operator==(khoroshkin::List< T > & rhs)
{
  if (this->getSize() != rhs.getSize())
  {
    return false;
  }
  auto it1 = this->begin();
  auto it2 = rhs.begin();
  while (it1 != this->end())
  {
    if (*it1 != *it2)
    {
      return false;
    }
    it1++;
    it2++;
  }
  return true;
}

template< typename T >
bool khoroshkin::List< T >::operator!=(khoroshkin::List< T > & rhs)
{
  return !(*this == rhs);
}

template< typename T >
bool khoroshkin::List< T >::operator<(khoroshkin::List< T > & rhs)
{
  auto it1 = this->begin();
  auto it2 = rhs.begin();
  while (it1 != this->end() && it2 != rhs.end())
  {
    if (*it1 < *it2)
    {
      return true;
    }
    it1++;
    it2++;
  }
  if (this->getSize() < rhs.getSize())
  {
    return true;
  }
  return false;
}

template< typename T >
bool khoroshkin::List< T >::operator>(khoroshkin::List< T > & rhs)
{
  auto it1 = this->begin();
  auto it2 = rhs.begin();
  while (it1 != this->end() && it2 != rhs.end())
  {
    if (*it1 > *it2)
    {
      return true;
    }
    it1++;
    it2++;
  }
  if (this->getSize() > rhs.getSize())
  {
    return true;
  }
  return false;
}

template< typename T >
bool khoroshkin::List< T >::operator>=(khoroshkin::List< T > & rhs)
{
  return !(*this < rhs);
}

template< typename T >
bool khoroshkin::List< T >::operator<=(khoroshkin::List< T > & rhs)
{
  return !(*this > rhs);
}

template< typename T >
void khoroshkin::List< T >::sort()
{
  List< T > temp;
  while (this->getSize())
  {
    T minValue = std::numeric_limits< T >::max();
    for (auto it = this->begin(); it != this->end(); ++it)
    {
      if (*it < minValue)
      {
        minValue = *it;
      }
    }
    temp.push_back(minValue);
    this->remove(minValue, true);
  }
  this->assign(temp.begin(), temp.end());
}

template< typename T >
void khoroshkin::List< T >::merge(khoroshkin::List< T > & other)
{
  if (*this == other)
  {
    return;
  }
  for (auto it = other.begin(); it != other.end(); ++it)
  {
    this->push_back(*it);
  }
  this->sort();
  other.clear();
}

template< typename T >
template< class... Args >
khoroshkin::iterator< T > khoroshkin::List< T >::emplace_after(iterator< T > pos, Args &&... args)
{
  return insert_after(pos, std::forward< Args >(args)...);
}

#endif
