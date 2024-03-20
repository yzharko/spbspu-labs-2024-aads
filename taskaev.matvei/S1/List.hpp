#ifndef LIST_H
#define LIST_H
#include <cassert>
#include <memory>
#include "Node.hpp"

namespace taskaev
{
  template< typename T>
  class List
  {
  public:
    List();
    ~List();
    List(const List&) = default;
    List(List&&) = default;
    T& front() const;
    void pushFront(const T& data);
    void pushBack(const T& data);
    void popFront();
    void clear();
    bool empty();
    void swap(List<T>& other);
    void remove(const T& value);
    void reverse();
    Node<T>* head;
  public:
  template< typename U >
  class ListIterator
  {
  public:
    ListIterator() : node(nullptr) {}
    ListIterator(Node<T>* value) : node(value) {}
    ~ListIterator() = default;
    ListIterator<T>& operator++();
    ListIterator<T> operator++(int);
    T& operator*();
    T* operator->();
    bool operator==(const List<T>::ListIterator<T>& rhs) const;
    bool operator!=(const List<T>::ListIterator<T>& rhs) const;
    Node<T>* node;
  };
  public:
    ListIterator<T> begin() {return ListIterator<T>(head); };
    ListIterator<T> end() { return ListIterator<T>(); };
  };
  template <typename T>
  List<T>::List():head(nullptr){}

  template <typename T>
  List<T>::~List<T>()
  {
    clear();
  }
  template <typename T>
  T& List<T>::front() const
  {
    return head->data;
  }

  template <typename T>
  void List<T>::pushFront(const T& data)
  {
    Node<T>* node = new Node<T>(data);
    node -> next = head;
    head = node;
  }

  template <typename T>
  void List<T>::pushBack(const T& data)
  {
    Node<T>* node = new Node<T>(data);
    if(empty())
    {
      head = node;
    }
    else
    {
      Node<T>* temp = head;
      while(temp->next)
      {
        temp = temp->next;
      }
      temp->next = node;
    }
  }

  template <typename T>
  void List<T>::popFront()
  {
    Node<T>* newNode = head;
    head = head->next;
    delete newNode;
  }

  template <typename T>
  void List<T>::clear()
  {
    while (head) { popFront(); }
  }

  template <typename T>
  bool List<T>::empty() {
    return(head == nullptr);
  }

  template <typename T>
  void List<T>::swap(List<T>& other)
  {
    Node<T>* temp = head;
    head = other->head;
    other->temp = head;
    delete temp;
  }

  template <typename T>
  void List<T>::remove(const T& value)
  {
    Node<T>* node = head;
    Node<T>* temp = nullptr;
    while(node != nullptr)
    {
      if(node->data == value)
      {
        if(temp == value) {head = node->next;}
        else {temp->next = node->next;}
        delete node;
        node = (temp == nullptr)? head : temp->next;
      }
      else
      {
        temp = node;
        node = node->next;
      }
    }
  }

  template <typename T>
  void List<T>::reverse()
  {
    Node<T>* newNode = head;
    Node<T>* temp = head->next;
    newNode->next = nullptr;
    while(temp)
    {
      Node<T>* am = temp->next;
      temp->next = newNode;
      newNode = temp;
      temp = am;
    }
    head = newNode;
  }

  template<typename T>
  template<typename U>
  List<T>::ListIterator<T> &List<T>::ListIterator<U>::operator++()
  {
    assert(node != nullptr);
    node = node->next;
    return *this;
  }

  template<typename T>
  template<typename U>
  List<T>::ListIterator<T> List<T>::ListIterator<U>::operator++(int)
  {
    assert(node != nullptr);
    ListIterator<T> result(*this);
    ++(*this);
    return result;
  }

  template<typename T>
  template<typename U>
  T& List<T>::ListIterator<U>::operator*()
  {
    assert(node != nullptr);
    return node->data;
  }

  template<typename T>
  template<typename U>
  T* List<T>::ListIterator<U>::operator->()
  {
    assert(node != nullptr);
    return std::addressof(node->data);
  }

  template<typename T>
  template<typename U>
  bool List<T>::ListIterator<U>::operator==(const List<T>::ListIterator<T>& rhs) const
  {
    return node == rhs.node;
  }

  template<typename T>
  template<typename U>
  bool taskaev::List<T>::ListIterator<U>::operator!=(const taskaev::List<T>::ListIterator<T>& rhs) const
  {
    return !(rhs == *this);
  }
}
#endif
