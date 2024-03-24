#ifndef LIST_HPP
#define LIST_HPP
#define LIST_HPP

#include <iostream>
#include <initializer_list>
#include <vector>
#include <sstream>

namespace gorbunova
{
  template <typename T>
  struct Node
  {
    T data;
    Node<T> *next;
    Node(const T &value) : data(value), next(nullptr) {}
  };

  template <typename T>
  class List
  {
  private:
    Node<T> *head;

  public:
    class Iterator
    {
    private:
      Node<T> *current;
      friend class List<T>;

    public:
      Iterator(Node<T> *node) : current(node) {}
      T &operator*() const;
      Iterator &operator++();
      bool operator!=(const Iterator &other) const;
    };
    List();
    List(std::initializer_list<std::pair<std::string, std::vector<int>>> ilist);

    template <typename InputIterator>
    List(InputIterator first, InputIterator last);
    ~List();
    void push_back(const T &value);
    void clear();
    void assign(std::initializer_list<T> ilist);
    void splice(Iterator pos, List &other);
    void reverse();
    void insert(Iterator pos, const T& value);
    void erase(Iterator pos);

    friend std::ostream &operator<<(std::ostream &os, const List<T> &list)
    {
      std::vector<std::string> names;
      std::vector<std::vector<int>> values;
      for (auto it = list.begin(); it != list.end(); ++it)
      {
        names.push_back((*it).first);
        values.push_back((*it).second);
      }
      size_t max_size = 0;
      for (const auto &v : values)
      {
          max_size = std::max(max_size, v.size());
      }
      for (size_t i = 0; i < max_size; ++i)
      {
          for (size_t j = 0; j < names.size(); ++j)
          {
              if (i < values[j].size())
                  os << values[j][i] << " ";
          }
          os << std::endl;
      }
      return os;
    }
    Iterator begin() const;
    Iterator end() const;
  };
}

template <typename T>
T &gorbunova::List<T>::Iterator::operator*() const
{
  return current->data;
}

template <typename T>
typename gorbunova::List<T>::Iterator & gorbunova::List<T>::Iterator::operator++()
{
  current = current->next;
  return *this;
}

template <typename T>
bool gorbunova::List<T>::Iterator::operator!=(const Iterator &other) const
{
  return current != other.current;
}

template <typename T>
gorbunova::List<T>::List() : head(nullptr) {}

template <typename T>
gorbunova::List<T>::List(std::initializer_list<std::pair<std::string, std::vector<int>>> ilist) : head(nullptr)
{
  for (const auto &pair : ilist)
  {
    push_back(pair);
  }
}

template <typename T>
template <typename InputIterator>
gorbunova::List<T>::List(InputIterator first, InputIterator last) : head(nullptr)
{
  while(first != last)
  {
    push_back(*first);
    ++first;
  }
}

template <typename T>
gorbunova::List<T>::~List()
{
  clear();
}

template <typename T>
void gorbunova::List<T>::push_back(const T &value)
{
  Node<T> *tmp = new Node<T>(value);
  if (head == nullptr)
  {
    head = tmp;
  }
  else
  {
    Node<T> *curr = head;
    while (curr->next != nullptr)
    {
      curr = curr->next;
    }
    curr->next = tmp;
  }
}

template <typename T>
void gorbunova::List<T>::clear()
{
  while (head != nullptr)
  {
    Node<T> *tmp = head;
    head = head ->next;
    delete tmp;
  }
}

template <typename T>
void gorbunova::List<T>::assign(std::initializer_list<T> ilist)
{
  clear();
  for (const auto &value : ilist)
  {
    push_back(value);
  }
}

template <typename T>
void gorbunova::List<T>::splice(Iterator pos, List &other)
{
  if (other.head != nullptr)
  {
    Node<T> *otherTail = other.head;
    while (otherTail->next != nullptr)
    {
      otherTail = otherTail->next;
    }
    otherTail->next = pos.current;
    pos.current = other.head;
    other.head == nullptr;
  }
}

template <typename T>
void gorbunova::List<T>::reverse()
{
  Node<T> *prev = nullptr, *current = head, *next = nullptr;
  while (current != nullptr)
  {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }
  head = prev;
}

template <typename T>
void gorbunova::List<T>::insert(Iterator pos, const T &value)
{
  Node<T> *newNode = new Node<T>(value);
  newNode->next = pos.current->next;
  pos.current->next = newNode;
}

template <typename T>
void gorbunova::List<T>::erase(Iterator pos)
{
  Node<T> *toDelete = pos.current;
  pos.current = pos.current->next;
  delete toDelete;
}

template <typename T>
typename gorbunova::List<T>::Iterator gorbunova::List<T>::begin() const
{
  return Iterator(head);
}

template <typename T>
typename gorbunova::List<T>::Iterator gorbunova::List<T>::end() const
{
  return Iterator(nullptr);
}
#endif
