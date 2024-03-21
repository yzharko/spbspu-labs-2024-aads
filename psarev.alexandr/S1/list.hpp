#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>
#include <assert.h>

namespace psarev
{
  template< typename T >
  class List
  {
  public:
    class ConstIterator;
   /* class Iterator;*/

    List();
    ~List();

    void popFront();
    void popBack();
    void pushFront(T data);
    void pushBack(T data);
    void insert(T data, size_t index);
    void remove(const T& value);

    T& front();
    T& back();

    void swap(List< T >& other);
    void clear();

    bool empty();
    size_t getSize();

    ConstIterator begin();
    /*Iterator end();*/

  private:
    class Unit
    {
    public:
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
    size_t size;
  };
}

//ConstIterator-------------------------------------------
template< typename T >
class psarev::List< T >::ConstIterator
{
public:
  friend class List< T >;
  using this_t = ConstIterator;

  ConstIterator();
  ConstIterator(Unit* unit);
  ConstIterator(const this_t&) = default;
  ~ConstIterator() = default;

  this_t& operator=(const this_t&) = default;

  this_t& operator++();
  this_t operator++(int);
  this_t& operator--();
  this_t operator--(int);

  const T& operator*() const;
  const T* operator->() const;

  bool operator==(const this_t&) const;
  bool operator!=(const this_t&) const;

private:
  Unit* unit;
  ConstIterator(Unit*, const List< T >*);
};

template<typename T>
psarev::List<T>::ConstIterator::ConstIterator() :
  unit(nullptr)
{}

template<typename T>
psarev::List<T>::ConstIterator::ConstIterator(Unit* pointer)
{
  unit = pointer;
}

template <typename T>
psarev::List<T>::ConstIterator& psarev::List<T>::ConstIterator::operator++()
{
  assert(unit != nullptr);
  unit = unit->next;
  return *this;
};

template <typename T>
psarev::List<T>::ConstIterator psarev::List<T>::ConstIterator::operator++(int)
{
  Iterator tempo(*this);
  ++(*this);
  return tempo;
}

template <typename T>
psarev::List<T>::ConstIterator& psarev::List<T>::ConstIterator::operator--()
{
  assert(unit != nullptr);
  unit = unit->prev;
  return *this;
}

template <typename T>
psarev::List<T>::ConstIterator psarev::List<T>::ConstIterator::operator--(int)
{
  Iterator tempo(*this);
  --(*this);
  return tempo;
}

template<typename T>
const T& psarev::List<T>::ConstIterator::operator*() const
{
  return unit->data;
}

template<typename T>
const T* psarev::List<T>::ConstIterator::operator->() const
{
  return &(unit->data);
}

template<typename T>
bool psarev::List<T>::ConstIterator::operator==(const this_t& that) const
{
  return unit == that.unit;
}

template<typename T>
bool psarev::List<T>::ConstIterator::operator!=(const this_t& that) const
{
  return !(that == *this);
}
//Iterator--------------------------------------------------
//template< typename T >
//class psarev::List< T >::Iterator
//{
//public:
//  friend class List< T >;
//  using this_t = Iterator;
//  Iterator();
//  Iterator(ConstIterator);
//  Iterator(const this_t&) = default;
//  ~Iterator() = default;
//
//  this_t& operator=(const this_t&) = default;
//  this_t& operator++();
//  this_t operator++(int);
//  this_t& operator--();
//  this_t operator--(int);
//
//  T& operator*();
//  T* operator->();
//  const T& operator*() const;
//  const T* operator->() const;
//
//  bool operator==(const this_t&) const;
//  bool operator!=(const this_t&) const;
//
//private:
//  ConstIterator iter_;
//};

//List--------------------------------------------------

template<typename T>
psarev::List<T>::List()
{
  head = nullptr;
  size = 0;
}

template<typename T>
psarev::List<T>::~List()
{
  clear();
}

template<typename T>
void psarev::List<T>::popFront()
{
  Unit* tempo = head;
  head = head->next;
  delete tempo;

  size--;
}

template<typename T>
void psarev::List<T>::popBack()
{
  remove(size - 1);
}

template<typename T>
void psarev::List<T>::pushFront(T data)
{
  head = new Unit(data, head);
  if (size != 0)
  {
    head->next->prev = head;
  }
  size++;
}

template<typename T>
void psarev::List<T>::pushBack(T data)
{
  if (head == nullptr)
  {
    head = new Unit(data);
  }
  else
  {
    Unit* curr = this->head;
    while (curr->next != nullptr)
    {
      curr = curr->next;
    }
    curr->next = new Unit(data, nullptr, curr);
  }
  size++;
}

template<typename T>
void psarev::List<T>::insert(T data, size_t index)
{
  if (index == 0)
  {
    pushFront(data);
  }
  else
  {
    Unit* previous = this->head;
    for (size_t i = 0; i < (index - 1); i++)
    {
      previous = previous->next;
    }

    previous->next = new Unit(data, previous->next, previous);
    previous = previous->next;
    previous->next->previous = previous;
    size++;
  }
}

template<typename T>
void psarev::List<T>::remove(const T& value)
{
  Unit* tempo = this->head;
  for (size_t i = 0; i < size; i++)
  {
    if (tempo->data == value)
    {
      Unit* removable = tempo;
      tempo = tempo->prev;
      tempo->next = removable->next;
      removable->next->prev = tempo;
      delete removable;
      i--;
      --size;
    }
    tempo = tempo->next;
  }
}

template<typename T>
T& psarev::List<T>::front()
{
  return head->data;
}

template<typename T>
T& psarev::List<T>::back()
{
  Unit* tempo = this->head;
  for (size_t i = 0; i < (size - 1); i++)
  {
    tempo = tempo->next;
  }
  return tempo->data;
}

template<typename T>
void psarev::List<T>::swap(List<T>& targetList)
{
  Unit tempoH = targetList.head;
  targetList.head = head;
  head = tempoH;
  size_t tempoS = targetList.size;
  targetList.size = size;
  size = tempoS;
}

template<typename T>
void psarev::List<T>::clear()
{
  while (size > 0)
  {
    popFront();
  }
}

template<typename T>
bool psarev::List<T>::empty()
{
  return this->getSize() == 0;
}

template<typename T>
size_t psarev::List<T>::getSize()
{
  return size;
}

//--------------------------------------------------------

template <typename T>
psarev::List<T>::ConstIterator psarev::List<T>::begin()
{
  return Iterator(head);
}

//template<typename T>
//psarev::List<T>::Iterator psarev::List<T>::end()
//{
//  Iterator point = begin();
//  while (point.unit != nullptr)
//  {
//    point++;
//  }
//  return point;
//}

#endif
