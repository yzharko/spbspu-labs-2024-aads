#ifndef LIST_HPP
#define LIST_HPP
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "node.hpp"

namespace hohlova
{
  template <typename T>
  struct List
  {
  public:
    List();
    ~List();
    void pop_front();
    void push_back(const T &value);
    void clear();
    size_t size() const;

    void push_front(const T &value);
    void insert(const T &value, int index);
    void removeAt(int index);
    void pop_back();

    class Iterator
    {
    public:
      Iterator(Node<T> *ptr) : ptr(ptr) {}
      void operator++() { ptr = ptr->nextPoint; }
      T &operator*() { return ptr->data; }
      bool operator!=(const Iterator &other) { return ptr != other.ptr; }
      bool operator==(const Iterator &other) { return ptr == other.ptr; }

    private:
      Node<T> *ptr;
    };

    friend std::ostream &operator<<(std::ostream &os, const List<T> &list)
    {
      std::vector<std::string> names;
      std::vector<std::vector<unsigned long long>> values;

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
          {
            os << values[j][i];
          }
          if ((j + 1 < names.size()) && (i < values[j + 1].size()) && (i + 1 < max_size))
          {
            os << " ";
          }
        }
        os << std::endl;
      }
      return os;
    }

    Iterator begin() const { return Iterator(head); }
    Iterator end() const { return Iterator(nullptr); }

  private:
    Node<T> *head;
    int Size = 0;
  };
}

template <typename T>
hohlova::List<T>::List()
{
  Size = 0;
  head = nullptr;
}

template <typename T>
hohlova::List<T>::~List()
{
  clear();
}

template <typename T>
void hohlova::List<T>::pop_front()
{
  if (Size == 0)
    return;
  Node<T> *temp = head;
  head = head->nextPoint;
  delete temp;
  Size--;
}

template <typename T>
void hohlova::List<T>::push_back(const T &value)
{
  if (head == nullptr)
  {
    head = new Node<T>(value);
  }
  else
  {
    Node<T> *current = head;
    while (current->nextPoint != nullptr)
    {
      current = current->nextPoint;
    }
    current->nextPoint = new Node<T>(value);
  }
  Size++;
}

template <typename T>
void hohlova::List<T>::clear()
{
  while (Size)
  {
    pop_front();
  }
}

template <typename T>
size_t hohlova::List<T>::size() const
{
  return Size;
}

template <typename T>
void hohlova::List<T>::push_front(const T &value)
{
  head = new Node<T>(value, head);
  Size++;
}

template <typename T>
void hohlova::List<T>::insert(const T &value, int index)
{
  if (index == 0)
  {
    push_front(value);
  }
  else
  {
    Node<T> *prevPoint = this->head;
    for (int i = 0; i < index - 1; i++)
    {
      prevPoint = prevPoint->nextPoint;
    }
    Node<T> *newNode = new Node<T>(value, prevPoint->nextPoint);
    prevPoint->nextPoint = newNode;
    Size++;
  }
}

template <typename T>
void hohlova::List<T>::removeAt(int index)
{
  if (index == 0)
  {
    pop_front();
  }
  else
  {
    Node<T> *prevPoint = this->head;
    for (int i = 0; i < index - 1; i++)
    {
      prevPoint = prevPoint->nextPoint;
    }
    Node<T> *forDelete = prevPoint->nextPoint;
    prevPoint->nextPoint = forDelete->nextPoint;
    delete forDelete;
    Size--;
  }
}

template <typename T>
void hohlova::List<T>::pop_back()
{
  removeAt(Size - 1);
}

#endif
