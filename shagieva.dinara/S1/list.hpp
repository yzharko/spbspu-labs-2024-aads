#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <utility>

namespace shagieva
{
  template<typename T>
  class List
  {
  private:
    struct Node
    {
      T data;
      Node * prev;
      Node * next;

      Node(T el):
        data(el)
      {}
    };

    Node * head;
    Node * tail;

  public:
    class ConstIterator
    {
    private:
      friend class List;

    public:
      const Node * curr;

      const Node * get() const
      {
        return curr;
      }

    public:
      ConstIterator(const Node * node):
        curr(node)
      {}

      T& operator*() const
      {
        return curr->data;
      }

      ConstIterator& operator++()
      {
        curr = curr->next;
        return *this;
      }

      ConstIterator operator++(int)
      {
        ConstIterator it = *this;
        curr = curr->next;
        return it;
      }

      ConstIterator& operator--()
      {
        curr = curr->prev;
        return *this;
      }

      ConstIterator operator--(int)
      {
        ConstIterator it = *this;
        curr = curr->prev;
        return it;
      }

      bool operator==(const ConstIterator& other) const
      {
        return curr == other.curr;
      }

      bool operator!=(const ConstIterator& other) const
      {
        return curr != other.curr;
      }
    };

    class Iterator: public ConstIterator
    {
    private:
      friend class List;

    public:
      Iterator(Node * node):
        ConstIterator(node)
      {}

      T& operator*() const
      {
        return const_cast<T&>(ConstIterator::operator*());
      }

      Iterator& operator++()
      {
        ConstIterator::operator++();
        return *this;
      }

      Iterator operator++(int)
      {
        auto res = ConstIterator::operator++(0);
        return Iterator(const_cast<Node *>(res.get()));
      }

      Iterator operator--()
      {
        ConstIterator::operator--();
        return *this;
      }

      Iterator operator--(int)
      {
        auto res = ConstIterator::operator--(0);
        return Iterator(const_cast<Node *>(res.get()));
      }
    };


  public:
    List();
    List(List const & l);
    List(List && l);
    ConstIterator begin() const;
    ConstIterator end() const;
    Iterator begin();
    Iterator end();
    T& front();
    T& back();
    bool empty() const;
    void push_back(const T& el);
    void push_front(const T& el);
    void erase(Iterator place);
    void pop_front();
    void pop_back();
    void clear();
    void swap(List & other);
    void fill(Iterator first, Iterator last, const T& el);
    Iterator find(const T& el) const;
    void remove(const T& el);
  };
}

template< typename T >
shagieva::List<T>::List():
  head(nullptr),
  tail(nullptr)
{}

template< typename T >
shagieva::List<T>::List(List const & l):
  head(l.head),
  tail(l.tail)
{}

template< typename T >
shagieva::List<T>::List(List && l):
  head(l.head),
  tail(l.tail)
{}

template< typename T >
typename shagieva::List<T>::ConstIterator shagieva::List<T>::begin() const
{
  return ConstIterator(head);
}

template< typename T >
typename shagieva::List<T>::ConstIterator shagieva::List<T>::end() const
{
  return ConstIterator(nullptr);
}

template< typename T >
typename shagieva::List<T>::Iterator shagieva::List<T>::begin()
{
  return Iterator(head);
}

template< typename T >
typename shagieva::List<T>::Iterator shagieva::List<T>::end()
{
  return Iterator(nullptr);
}

template< typename T >
T& shagieva::List<T>::front()
{
  return head->data;
}

template< typename T >
T& shagieva::List<T>::back()
{
  return tail->data;
}

template< typename T >
bool shagieva::List<T>::empty() const
{
  return head == nullptr;
}

template< typename T >
void shagieva::List<T>::push_back(const T& el)
{
  auto newNode = new Node(el);
  if (tail)
  {
    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
  }
  else
  {
    head = tail = newNode;
  }
}

template< typename T >
void shagieva::List<T>::push_front(const T& el)
{
  auto newNode = new Node(el);
  if (head)
  {
    head->prev = newNode;
    newNode->next = head;
    head = newNode;
  }
  else
  {
    head = tail = newNode;
  }
}

template< typename T >
void shagieva::List<T>::erase(Iterator place)
{

  auto ptr = place.curr;
  if (ptr->prev)
  {
    ptr->prev->next = ptr->next;
  }
  else
  {
    head = ptr->next;
  }

  if (ptr->next)
  {
    ptr->next->prev = ptr->prev;
  }
  else
  {
    tail = ptr->prev;
  }

  delete ptr;
}

template< typename T >
void shagieva::List<T>::pop_front()
{
  erase(begin());
}

template< typename T >
void shagieva::List<T>::pop_back()
{
  erase(--end());
}

template< typename T >
void shagieva::List<T>::clear()
{
  while (head)
  {
    delete std::exchange(head, head->next);
  }
}

template< typename T >
void shagieva::List<T>::swap(List & other)
{
  if (*this != other)
  {
    List<T> temp = *this;
    *this = other;
    other = temp;
  }
}

template< typename T >
void shagieva::List<T>::fill(Iterator first, Iterator last, const T& el)
{
  for (auto it = first; it == last; ++it)
  {
    *it = el;
  }
}

template< typename T >
typename shagieva::List<T>::Iterator shagieva::List<T>::find(const T& el) const
{
  for (auto it = begin(); it != end(); ++it)
  {
    if (*it == el)
    {
      return it;
    }
  }
  return Iterator(nullptr);
}

template< typename T >
void shagieva::List<T>::remove(const T& el)
{
  Iterator iteratorToRemove = find(el);
  erase(iteratorToRemove);
}
#endif
