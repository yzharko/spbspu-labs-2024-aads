#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>
#include <assert.h>
#include <iterator>

namespace proselkov
{
  template< typename T >
  class List
  {
  public:
    class ConstIterator;
    class Iterator;
    using cIter = ConstIterator;
    using iter = Iterator;
    List();
    List(const List& other) = default;
    ~List();

    List< T >& operator=(const List& other) = default;

    void popFront();
    void popBack();

    void pushFront(T& data);
    void pushBack(T& data);
    void pushFront(const T& data);
    void pushBack(const T& data);
    void pushFront(T&& data);
    void pushBack(T&& data);

    T& getFront() const;
    T& getBack() const;

    void swap(List< T >& other) noexcept;
    void clear();

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;

    cIter cbegin() const noexcept;
    cIter cend() const noexcept;
    cIter begin() const;
    cIter end() const;
    iter begin();
    iter end();

  private:
    class Unit
    {
      friend class List< T >;
      T data;
      Unit* next;
      Unit* prev;
      Unit(T data, Unit* next = nullptr, Unit* prev = nullptr)
      {
        this->data = data;
        this->next = next;
        this->prev = prev;
      }
    };

    Unit* head;
    Unit* tail;
    size_t size;
  };
}

template< typename T >
class proselkov::List< T >::ConstIterator : public std::iterator< std::bidirectional_iterator_tag, T >
{
public:
  friend class List< T >;
  using this_t = ConstIterator;

  ConstIterator();
  ConstIterator(Unit* ptr);
  ConstIterator(const this_t&) = default;
  ~ConstIterator() = default;

  this_t& operator=(const this_t&) = default;

  this_t& operator++();
  this_t operator++(int);
  this_t& operator--();
  this_t operator--(int);
  this_t operator+(size_t index);

  const T& operator*() const;
  const T* operator->() const;

  bool operator==(const this_t&) const;
  bool operator!=(const this_t&) const;
  bool operator>=(const this_t&) const;

private:
  Unit* unit;
};

template< typename T >
proselkov::List< T >::ConstIterator::ConstIterator() :
  unit(nullptr)
{}

template< typename T >
proselkov::List< T >::ConstIterator::ConstIterator(Unit* ptr) :
  unit(ptr)
{}

template < typename T >
typename proselkov::List< T >::ConstIterator& proselkov::List< T >::ConstIterator::operator++()
{
  assert(unit != nullptr);
  unit = unit->next;
  return *this;
};

template < typename T >
typename proselkov::List< T >::ConstIterator proselkov::List< T >::ConstIterator::operator++(int)
{
  ConstIterator tempo(*this);
  ++(*this);
  return tempo;
}

template < typename T >
typename proselkov::List< T >::ConstIterator& proselkov::List< T >::ConstIterator::operator--()
{
  assert(unit != nullptr);
  unit = unit->prev;
  return *this;
}

template < typename T >
typename proselkov::List< T >::ConstIterator proselkov::List< T >::ConstIterator::operator--(int)
{
  ConstIterator tempo(*this);
  --(*this);
  return tempo;
}

template< typename T >
typename proselkov::List< T >::ConstIterator proselkov::List< T >::ConstIterator::operator+(size_t index)
{
  for (size_t i = 0; i < index; i++)
  {
    (*this)++;
  }
  return *this;
}

template< typename T >
const T& proselkov::List< T >::ConstIterator::operator*() const
{
  return unit->data;
}

template< typename T >
const T* proselkov::List< T >::ConstIterator::operator->() const
{
  return &(unit->data);
}

template< typename T >
bool proselkov::List< T >::ConstIterator::operator==(const this_t& that) const
{
  return unit == that.unit;
}

template< typename T >
bool proselkov::List< T >::ConstIterator::operator!=(const this_t& that) const
{
  return !(that == *this);
}

template< typename T >
bool proselkov::List< T >::ConstIterator::operator>=(const this_t& that) const
{
  Unit* cur = unit;
  while (cur) {
    if (cur == that.unit) {
      return true;
    }
    cur = cur->next;
  }
  return false;
}

template< typename T >
class proselkov::List< T >::Iterator : public std::iterator< std::bidirectional_iterator_tag, T >
{
public:
  friend class List< T >;
  using this_t = Iterator;
  Iterator();
  Iterator(Unit* ptr);
  Iterator(ConstIterator constIter);
  Iterator(const this_t&) = default;
  ~Iterator() = default;

  this_t& operator=(const this_t&) = default;
  this_t& operator++();
  this_t operator++(int);
  this_t& operator--();
  this_t operator--(int);
  this_t operator+(size_t index);

  T& operator*();
  T* operator->();
  const T& operator*() const;
  const T* operator->() const;

  bool operator==(const this_t&) const;
  bool operator!=(const this_t&) const;
  bool operator>=(const this_t&) const;

private:
  ConstIterator iter_;
};

template< typename T >
proselkov::List< T >::Iterator::Iterator() :
  iter_(ConstIterator())
{}

template< typename T >
proselkov::List< T >::Iterator::Iterator(Unit* ptr) :
  iter_(ConstIterator(ptr))
{}

template< typename T >
proselkov::List< T >::Iterator::Iterator(ConstIterator constIter) :
  iter_(constIter)
{}

template < typename T >
typename proselkov::List< T >::Iterator& proselkov::List< T >::Iterator::operator++()
{
  ++iter_;
  return *this;
};

template < typename T >
typename proselkov::List< T >::Iterator proselkov::List< T >::Iterator::operator++(int)
{
  this_t result = iter_;
  ++iter_;
  return result;
}

template < typename T >
typename proselkov::List< T >::Iterator& proselkov::List< T >::Iterator::operator--()
{
  --iter_;
  return *this;
}

template < typename T >
typename proselkov::List< T >::Iterator proselkov::List< T >::Iterator::operator--(int)
{
  --iter_;
  return iter_;
}

template< typename T >
typename proselkov::List< T >::Iterator proselkov::List< T >::Iterator::operator+(size_t index)
{
  for (size_t i = 0; i < index; i++)
  {
    (*this)++;
  }
  return *this;
}

template< typename T >
T& proselkov::List< T >::Iterator::operator*()
{
  return iter_.unit->data;
}

template< typename T >
T* proselkov::List< T >::Iterator::operator->()
{
  return &(iter_.unit->data);
}

template< typename T >
const T& proselkov::List< T >::Iterator::operator*() const
{
  return iter_.unit->data;
}

template< typename T >
const T* proselkov::List< T >::Iterator::operator->() const
{
  return &(iter_.unit->data);
}

template< typename T >
bool proselkov::List< T >::Iterator::operator==(const this_t& that) const
{
  return iter_ == that.iter_;
}

template< typename T >
bool proselkov::List< T >::Iterator::operator!=(const this_t& that) const
{
  return !(that == *this);
}

template< typename T >
bool proselkov::List< T >::Iterator::operator>=(const this_t& that) const
{
  return iter_ >= that.iter_;
}

template< typename T >
proselkov::List< T >::List()
{
  head = nullptr;
  tail = nullptr;
  size = 0;
}

template< typename T >
proselkov::List< T >::~List()
{
  clear();
}

template< typename T >
void proselkov::List< T >::popFront()
{
  Unit* tempo = head;
  head = head->next;
  delete tempo;
  size--;
}

template< typename T >
void proselkov::List< T >::popBack()
{
  Unit* delUnit = tail;
  tail = tail->prev;
  delete delUnit;
  size--;
}

template< typename T >
void proselkov::List< T >::pushFront(T& data)
{
  head = new Unit(data, head);
  if (size != 0)
  {
    head->next->prev = head;
  }
  size++;
}

template< typename T >
void proselkov::List< T >::pushBack(T& data)
{
  if (head == nullptr)
  {
    head = new Unit(data);
    tail = head;
  }
  else
  {
    Unit* adUnit = new Unit(data, nullptr, tail);
    tail->next = adUnit;
    tail = adUnit;
  }
  size++;
}

template< typename T >
void proselkov::List< T >::pushFront(const T& data)
{
  head = new Unit(data, head);
  if (size != 0)
  {
    head->next->prev = head;
  }
  size++;
}

template< typename T >
void proselkov::List< T >::pushBack(const T& data)
{
  if (head == nullptr)
  {
    head = new Unit(data);
    tail = head;
  }
  else
  {
    Unit* adUnit = new Unit(data, nullptr, tail);
    tail->next = adUnit;
    tail = adUnit;
  }
  size++;
}

template<typename T>
void proselkov::List<T>::pushFront(T&& data)
{
  head = new Unit(data, head);
  if (size != 0)
  {
    head->next->prev = head;
  }
  size++;
}

template<typename T>
void proselkov::List<T>::pushBack(T&& data)
{
  if (head == nullptr)
  {
    head = new Unit(data);
    tail = head;
  }
  else
  {
    Unit* adUnit = new Unit(data, nullptr, tail);
    tail->next = adUnit;
    tail = adUnit;
  }
  size++;
}

template< typename T >
T& proselkov::List< T >::getFront() const
{
  return head->data;
}

template< typename T >
T& proselkov::List< T >::getBack() const
{
  return tail->data;
}

template< typename T >
void proselkov::List< T >::swap(List< T >& targetList) noexcept
{
  Unit tempoH = targetList.head;
  targetList.head = head;
  head = tempoH;
  size_t tempoS = targetList.size;
  targetList.size = size;
  size = tempoS;
}

template< typename T >
void proselkov::List< T >::clear()
{
  while (size > 0)
  {
    popFront();
  }
}

template< typename T >
bool proselkov::List< T >::isEmpty() const noexcept
{
  return this->getSize() == 0;
}

template< typename T >
size_t proselkov::List< T >::getSize() const noexcept
{
  return size;
}

template < typename T >
typename proselkov::List< T >::ConstIterator proselkov::List< T >::cbegin() const noexcept
{
  return ConstIterator(head);
}

template< typename T >
typename proselkov::List< T >::ConstIterator proselkov::List< T >::cend() const noexcept
{
  return nullptr;
}

template < typename T >
typename proselkov::List< T >::ConstIterator proselkov::List< T >::begin() const
{
  return ConstIterator(head);
}

template< typename T >
typename proselkov::List< T >::ConstIterator proselkov::List< T >::end() const
{
  return nullptr;
}

template < typename T >
typename proselkov::List< T >::Iterator proselkov::List< T >::begin()
{
  return Iterator(head);
}

template< typename T >
typename proselkov::List< T >::Iterator proselkov::List< T >::end()
{
  return nullptr;
}

#endif
