#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>
#include <stdexcept>
#include <memory>
#include <cassert>

namespace redko
{
  template< typename T >
  struct ListElem
  {
    ListElem():
      data(),
      next(nullptr)
    {}
    ListElem(T d):
      data(d),
      next(nullptr)
    {}

    T data;
    ListElem< T > * next;
  };

  template< typename T >
  class List
  {
  public:
    template < bool Const >
    class Iterator
    {
    private:
      friend class List;
      ListElem< T > * node;

    public:
      Iterator();
      ~Iterator() = default;
      Iterator(const Iterator &) = default;
      Iterator(ListElem< T > * ptr);
      Iterator< Const > & operator=(const Iterator &) = default;

      Iterator< Const > & operator++();
      Iterator< Const > operator++(int);

      template < bool Q = Const >
      typename std::enable_if< Q, const T * >::type operator->();
      template < bool Q = Const >
      typename std::enable_if< !Q, T * >::type operator->();

      template < bool Q = Const >
      typename std::enable_if< Q, const T & >::type operator*();
      template < bool Q = Const >
      typename std::enable_if< !Q, T & >::type operator*();

      bool operator!=(const Iterator< Const > &) const;
      bool operator==(const Iterator< Const > &) const;
    };
  public:
    using iterator = Iterator< false >;
    using const_iterator = Iterator< true >;

    List(): head_() {};
    List(size_t count, const T & value);
    List(size_t count);
    template< bool Const >
    List(Iterator< Const > first, Iterator< Const > last);
    List(const List & other);
    List(List && other) noexcept;
    List(std::initializer_list< T > ilist);
    ~List();

    List< T > & operator=(const List & other);
    List< T > & operator=(List && other);

    void assign(size_t count, const T & value);
    template< bool Const >
    void assign(Iterator< Const > first, Iterator< Const > last);
    void assign(std::initializer_list< T > ilist);

    T & front();

    iterator beforeBegin() noexcept;
    const_iterator beforeBegin() const noexcept;
    const_iterator cbeforeBegin() const noexcept;

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;

    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;

    bool isEmpty() const;

    void clear();
    iterator insertAfter(iterator pos, const T & value);
    iterator insertAfter(iterator pos, T && value);
    template< class... Args >
    iterator emplaceAfter(iterator pos, Args &&... args);
    iterator eraseAfter(iterator pos);
    void pushFront(const T & value);
    void pushFront(T && value);
    void pushBack(const T & value);
    void pushBack(T && value);
    void popFront();
    void swap(List & other);

    void merge(List & other);
    void merge(List && other);
    void spliceAfter(iterator pos, List & other);
    void spliceAfter(iterator pos, List && other);
    size_t remove(const T & value);
    template< typename UnaryPredicate >
    size_t removeIf(UnaryPredicate pred);
    void reverse() noexcept;
    size_t unique();
    void sort();

    bool operator==(const List & rhs);
    bool operator!=(const List & rhs);
    bool operator<(const List & rhs);
    bool operator<=(const List & rhs);
    bool operator>(const List & rhs);
    bool operator>=(const List & rhs);

  private:
    ListElem< T > head_;
  };
}
template< typename T >
using iterator = typename redko::List< T >::Iterator< false >;
template< typename T >
using const_iterator = typename redko::List< T >::Iterator< true >;

template< typename T >
template< bool Const >
redko::List< T >::Iterator< Const >::Iterator() :
  node(nullptr)
{}
template< typename T >
template< bool Const >
redko::List< T >::Iterator< Const >::Iterator(ListElem< T > * ptr) :
  node(ptr)
{}
template< typename T >
template< bool Const >
redko::List< T >::Iterator< Const > & redko::List< T >::Iterator< Const >::operator++()
{
  assert(node != nullptr);
  node = node->next;
  return *this;
}
template< typename T >
template< bool Const >
redko::List< T >::Iterator< Const > redko::List< T >::Iterator< Const >::operator++(int)
{
  assert(node != nullptr);
  Iterator result(*this);
  ++(*this);
  return result;
}

template< typename T >
template< bool Const >
template< bool Q >
typename std::enable_if< !Q, T & >::type
redko::List< T >::Iterator< Const >::operator*()
{
  assert(node != nullptr);
  return node->data;
}

template< typename T >
template< bool Const >
template< bool Q >
typename std::enable_if< Q, const T & >::type
redko::List< T >::Iterator< Const >::operator*()
{
  assert(node != nullptr);
  return node->data;
}

template< typename T >
template< bool Const >
template< bool Q >
typename std::enable_if< !Q, T * >::type
redko::List< T >::Iterator< Const >::operator->()
{
  assert(node != nullptr);
  return std::addressof(node->data);
}
template< typename T >
template< bool Const >
template< bool Q >
typename std::enable_if< Q, const T * >::type
redko::List< T >::Iterator< Const >::operator->()
{
  assert(node != nullptr);
  return std::addressof(node->data);
}

template< typename T >
template< bool Const >
bool redko::List< T >::Iterator< Const >::operator==(const Iterator & rhs) const
{
  return node == rhs.node;
}
template< typename T >
template< bool Const >
bool redko::List< T >::Iterator< Const >::operator!=(const Iterator & rhs) const
{
  return !(rhs == *this);
}

template< typename T >
redko::List< T >::List(size_t count, const T & value)
{
  for (int i = 0; i < count; i++)
  {
    pushBack(value);
  }
}
template< typename T >
redko::List< T >::List(size_t count)
{
  if (count < 1)
  {
    throw std::logic_error("non-positive number");
  }
  head_.next = new ListElem< T >();
  ListElem< T > * curr = head_.next->next;
  for (int i = 1; i < count; i++)
  {
    curr = new ListElem< T >();
    curr = curr->next;
  }
}
template< typename T >
template< bool Const >
redko::List< T >::List(Iterator< Const > first, Iterator< Const > last)
{
  while (first != last)
  {
    pushBack(*first);
    first++;
  }
}
template< typename T >
redko::List< T >::List(const List & other)
{
  ListElem< T > * othrElem = other.head_.next;
  while (othrElem != nullptr)
  {
    pushBack(othrElem->data);
    othrElem = othrElem->next;
  }
}
template< typename T >
redko::List< T >::List(List && other) noexcept
{
  head_.next = std::move(other.head_.next);
  other.head_.next = nullptr;
}
template< typename T >
redko::List< T >::~List()
{
  clear();
}
template< typename T >
redko::List< T >::List(std::initializer_list< T > ilist)
{
  for (auto value : ilist)
  {
    pushBack(value);
  }
}

template< typename T >
redko::List< T > & redko::List< T >::operator=(const List & other)
{
  if (&other != this)
  {
    clear();
    ListElem< T > * othrElem = other.head_.next;
    while (othrElem != nullptr)
    {
      pushBack(othrElem->data);
      othrElem = othrElem->next;
    }
  }
  return *this;
}
template< typename T >
redko::List< T > & redko::List< T >::operator=(List && other)
{
  if (&other != this)
  {
    clear();
    head_.next = std::move(other.head_.next);
    other.head_.next = nullptr;
  }
  return *this;
}

template< typename T >
void redko::List< T >::assign(size_t count, const T & value)
{
  clear();
  for (int i = 0; i < count; i++)
  {
    pushBack(value);
  }
}
template< typename T >
template< bool Const >
void redko::List< T >::assign(Iterator< Const > first, Iterator< Const > last)
{
  clear();
  while (first != last)
  {
    pushBack(*first);
    first++;
  }
}
template< typename T >
void redko::List< T >::assign(std::initializer_list< T > ilist)
{
  clear();
  for (auto value : ilist)
  {
    pushBack(value);
  }
}

template< typename T >
T & redko::List< T >::front()
{
  if (isEmpty())
  {
    throw std::logic_error("calling from empty list");
  }
  return head_.next->data;
}

template< typename T >
redko::List< T >::Iterator< false > redko::List< T >::beforeBegin() noexcept
{
  return Iterator< false >(&head_);
}
template< typename T >
redko::List< T >::Iterator< true > redko::List< T >::beforeBegin() const noexcept
{
  return Iterator< true >(&head_);
}
template< typename T >
redko::List< T >::Iterator< true > redko::List< T >::cbeforeBegin() const noexcept
{
  return Iterator< true >(& head_);
}

template< typename T >
redko::List< T >::Iterator< false > redko::List< T >::begin() noexcept
{
  return Iterator< false >(head_.next);
}
template< typename T >
redko::List< T >::Iterator< true > redko::List< T >::begin() const noexcept
{
  return Iterator< true >(head_.next);
}
template< typename T >
redko::List< T >::Iterator< true > redko::List< T >::cbegin() const noexcept
{
  return Iterator< true >(head_.next);
}

template< typename T >
redko::List< T >::Iterator< false > redko::List< T >::end() noexcept
{
  return Iterator< false >(nullptr);
}
template< typename T >
redko::List< T >::Iterator< true > redko::List< T >::end() const noexcept
{
  return Iterator< true >(nullptr);
}
template< typename T >
redko::List< T >::Iterator< true > redko::List< T >::cend() const noexcept
{
  return Iterator< true >(nullptr);
}

template< typename T >
bool redko::List< T >::isEmpty() const
{
  return head_.next == nullptr;
}

template< typename T >
void redko::List< T >::clear()
{
  while (begin() != end())
  {
    popFront();
  }
}
template< typename T >
redko::List< T >::Iterator< false > redko::List< T >::insertAfter(Iterator< false > pos, const T & value)
{
  ListElem< T > * newElem = new ListElem< T >(value);
  newElem->next = pos.node->next;
  pos.node->next = newElem;
  return pos++;
}
template< typename T >
redko::List< T >::Iterator< false > redko::List< T >::insertAfter(Iterator< false > pos, T && value)
{
  ListElem< T > * newElem = new ListElem< T >(std::move(value));
  newElem->next = pos.node->next;
  pos.node->next = newElem;
  return pos++;
}
template< typename T >
template< class... Args >
redko::List< T >::Iterator< false > redko::List< T >::emplaceAfter(Iterator< false > pos, Args &&... args)
{
  ListElem< T > * newElem = new ListElem< T >(std::forward< Args >(args)...);
  newElem->next = pos.node->next;
  pos.node->next = newElem;
  return pos++;
}
template< typename T >
redko::List< T >::Iterator< false > redko::List< T >::eraseAfter(Iterator< false > pos)
{
  ListElem< T > * p = pos.node->next;
  if (p != nullptr)
  {
    pos.node->next = p->next;
    delete p;
  }
  return pos++;
}
template< typename T >
void redko::List< T >::pushFront(const T & value)
{
  ListElem< T > * tmp = head_.next;
  head_.next = new ListElem< T >(value);
  head_.next->next = tmp;
}
template< typename T >
void redko::List< T >::pushFront(T && value)
{
  ListElem< T > * tmp = head_.next;
  head_.next = new ListElem< T >(value);
  head_.next->next = tmp;
}
template< typename T >
void redko::List< T >::pushBack(const T & value)
{
  ListElem< T > * tmp = new ListElem< T >(value);
  if (head_.next == nullptr)
  {
    head_.next = tmp;
  }
  else
  {
    Iterator< false > curr = begin();
    while (curr.node->next != nullptr)
    {
      curr++;
    }
    curr.node->next = tmp;
  }
}
template< typename T >
void redko::List< T >::pushBack(T && value)
{
  ListElem< T > * tmp = new ListElem< T >(std::move(value));
  if (head_.next == nullptr)
  {
    head_.next = tmp;
  }
  else
  {
    Iterator< false > curr = begin();
    while (curr.node->next != nullptr)
    {
      curr++;
    }
    curr.node->next = tmp;
  }
}
template< typename T >
void redko::List< T >::popFront()
{
  eraseAfter(beforeBegin());
}
template< typename T >
void redko::List< T >::swap(List & other)
{
  ListElem< T > tmp = other.head_;
  other.head_ = head_;
  head_ = tmp;
}

template< typename T >
void redko::List< T >::merge(List & other)
{
  if (&other != this)
  {
    ListElem< T > * thisElem = head_.next;
    if (thisElem != nullptr)
    {
      while (other.head_.next != nullptr)
      {
        if (thisElem->next != nullptr)
        {
          if (other.head_.next->data >= thisElem->data && other.head_.next->data < thisElem->next->data)
          {
            ListElem< T > * tmp = thisElem->next;
            thisElem->next = other.head_.next;
            other.head_.next = other.head_.next->next;
            thisElem->next->next = tmp;
          }
          thisElem = thisElem->next;
        }
        else
        {
          if (other.head_.next->data >= thisElem->data)
          {
            thisElem->next = other.head_.next;
            other.head_.next = other.head_.next->next;
            thisElem->next->next = nullptr;
            thisElem = thisElem->next;
          }
          else
          {
            ListElem< T >* tmp = head_.next;
            head_.next = other.head_.next;
            other.head_.next = other.head_.next->next;
            head_.next->next = tmp;
            thisElem = head_.next;
          }
        }
      }
    }
    else
    {
      *this = other;
    }
  }
}
template< typename T >
void redko::List< T >::merge(List && other)
{
  if (&other != this)
  {
    ListElem< T > * thisElem = head_.next;
    if (thisElem != nullptr)
    {
      while (other.head_.next != nullptr)
      {
        if (thisElem->next != nullptr)
        {
          if (other.head_.next->data >= thisElem->data && other.head_.next->data < thisElem->next->data)
          {
            ListElem< T > * tmp = thisElem->next;
            thisElem->next = other.head_.next;
            other.head_.next = other.head_.next->next;
            thisElem->next->next = tmp;
          }
          thisElem = thisElem->next;
        }
        else
        {
          if (other.head_.next->data >= thisElem->data)
          {
            thisElem->next = other.head_.next;
            other.head_.next = other.head_.next->next;
            thisElem->next->next = nullptr;
            thisElem = thisElem->next;
          }
          else
          {
            ListElem< T > * tmp = head_.next;
            head_.next = other.head_.next;
            other.head_.next = other.head_.next->next;
            head_.next->next = tmp;
            thisElem = head_.next;
          }
        }
      }
    }
    else
    {
      *this = other;
    }
  }
}
template< typename T >
void redko::List< T >::spliceAfter(Iterator< false > pos, List & other)
{
  if (!other.isEmpty())
  {
    Iterator< false > otherElem = other.begin();
    while (otherElem != other.end())
    {
      insertAfter(pos, *otherElem);
      pos++;
      otherElem++;
    }
    other.clear();
  }
}
template< typename T >
void redko::List< T >::spliceAfter(Iterator< false > pos, List && other)
{
  if (!other.isEmpty())
  {
    Iterator< false > otherElem = other.begin();
    while (otherElem != other.end())
    {
      insertAfter(pos, std::move(*otherElem));
      pos++;
      otherElem++;
    }
    other.clear();
  }
}
template< typename T >
size_t redko::List< T >::remove(const T & value)
{
  size_t count = 0;
  Iterator< false > prevIt = beforeBegin();
  Iterator< false > currIt = begin();
  while (currIt != end())
  {
    if (*currIt == value)
    {
      currIt = eraseAfter(prevIt);
      count++;
    }
    currIt++;
    prevIt++;
  }
  return count;
}
template< typename T >
template< typename UnaryPredicate >
size_t redko::List< T >::removeIf(UnaryPredicate pred)
{
  size_t count = 0;
  Iterator< false > prevIt = beforeBegin();
  Iterator< false > currIt = begin();
  while (currIt != end())
  {
    if (pred(*currIt))
    {
      currIt = eraseAfter(prevIt);
      count++;
    }
    currIt++;
    prevIt++;
  }
  return count;
}
template< typename T >
void redko::List< T >::reverse() noexcept
{
  if (!isEmpty() && head_.next->next != nullptr)
  {
    ListElem< T > * prevNode = head_.next;
    ListElem< T > * tmpNode = head_.next->next;
    while (tmpNode->next != nullptr)
    {
      tmpNode = tmpNode->next;
      prevNode = prevNode->next;
    }
    tmpNode->next = prevNode;
    ListElem< T > * currNode = prevNode;
    while (currNode != head_.next)
    {
      prevNode = head_.next;
      while (prevNode->next != currNode)
      {
        prevNode = prevNode->next;
      }
      currNode->next = prevNode;
      currNode = prevNode;
    }
    currNode->next = nullptr;
    head_.next = tmpNode;
  }
}
template< typename T >
size_t redko::List< T >::unique()
{
  size_t res = 0;
  if (!isEmpty() && head_.next->next != nullptr)
  {
    Iterator< false > nextElem(head_.next->next);
    Iterator< false > currElem(head_.next);
    while (nextElem != end())
    {
      if (*currElem == *nextElem)
      {
        res++;
        nextElem = eraseAfter((currElem));
        nextElem++;
      }
      else
      {
        currElem++;
        nextElem++;
      }
    }
  }
  return res;
}
template< typename T >
void redko::List< T >::sort()
{
  if (!isEmpty())
  {
    ListElem< T > * currElem = nullptr;
    ListElem< T > * nextElem = nullptr;
    bool wasEdited = true;
    while (wasEdited)
    {
      wasEdited = false;
      currElem = head_.next;
      nextElem = head_.next->next;
      while (nextElem != nullptr)
      {
        if (currElem->data > nextElem->data)
        {
          wasEdited = true;
          T tmp = currElem->data;
          currElem->data = nextElem->data;
          nextElem->data = tmp;
        }
        currElem = nextElem;
        nextElem = nextElem->next;
      }
    }
  }
}

template< typename T >
bool redko::List< T >::operator==(const List & rhs)
{
  if (this != &rhs)
  {
    ListElem< T > * lCurr = head_.next;
    ListElem< T > * rCurr = rhs.head_.next;
    while (lCurr != nullptr && rCurr != nullptr)
    {
      if (lCurr->data != rCurr->data)
      {
        return false;
      }
      lCurr = lCurr->next;
      rCurr = rCurr->next;
    }
    if (lCurr != nullptr || rCurr != nullptr)
    {
      return false;
    }
  }
  return true;
}
template< typename T >
bool redko::List< T >::operator!=(const List & rhs)
{
  return !(*this == rhs);
}
template< typename T >
bool redko::List< T >::operator<(const List & rhs)
{
  if (this != &rhs)
  {
    ListElem< T > * lCurr = head_.next;
    ListElem< T > * rCurr = rhs.head_.next;
    while (rCurr != nullptr)
    {
      if (lCurr == nullptr || lCurr->data < rCurr->data)
      {
        return true;
      }
      else if (lCurr->data > rCurr->data)
      {
        return false;
      }
      lCurr = lCurr->next;
      rCurr = rCurr->next;
    }
  }
  return false;
}
template< typename T >
bool redko::List< T >::operator<=(const List & rhs)
{
  return !(*this > rhs);
}
template< typename T >
bool redko::List< T >::operator>(const List & rhs)
{
  if (this != &rhs)
  {
    ListElem< T > * lCurr = head_.next;
    ListElem< T > * rCurr = rhs.head_.next;
    while (lCurr != nullptr)
    {
      if (rCurr == nullptr || lCurr->data > rCurr->data)
      {
        return true;
      }
      else if (lCurr->data < rCurr->data)
      {
        return false;
      }
      lCurr = lCurr->next;
      rCurr = rCurr->next;
    }
  }
  return false;
}
template< typename T >
bool redko::List< T >::operator>=(const List & rhs)
{
  return !(*this < rhs);
}

#endif
