#ifndef LIST_HPP
#define LIST_HPP

#include "ListIterator.hpp"
#include <iostream>
#include <initializer_list>

namespace sukacheva {
  template <class T>
  struct List
  {
    Node< T >* head;
    Node< T >* tail;
    size_t listSize;

    using iterator = Iterator< T >;
    using const_iterator = Iterator< const T >;

    List() : head(nullptr), tail(nullptr), listSize(0){}
    List(size_t count, const T& value);
    List(std::initializer_list<T> init);
    template< class InputIt >
    List(InputIt first, InputIt last);
    ~List();
    List(const List&);
    List(List&& other);

    Node<T>* operator[](size_t index);

    void pushFront(const T& data);
    void pushBack(const T& data);
    void popFront();
    void clean();
    void swap(List& other);
    bool empty();
    T& front();
    void reverse();
    void remove(const T& value);
    template< class UnaryPredicate >
    void remove_if(UnaryPredicate p);

    iterator begin() { return iterator(head); }
    iterator end() { return iterator(nullptr); }

    const_iterator cbegin() const { return head; }
    const_iterator cend() const { return nullptr; }
  };

  template<class T>
  template<class UnaryPredicate>
  void List<T>::remove_if(UnaryPredicate p)
  {
    size_t index = 0;
    Iterator< T > it = begin();
    while (it.node)
    {
      if (p(it.node->data)) {
        if (it.node == head) {
          popFront();
        }
        else if (it.node == tail) {
          tail = this->operator[](index);
          this->operator[](index)->next = nullptr;
          it.node = this->operator[](index + 2);
          listSize--;
        }
        else {
          this->operator[](index)->next = this->operator[](index + 2);
          this->operator[](index + 1)->next = nullptr;
          it.node = this->operator[](index + 2);
          listSize--;
        }
      }
      else {
        index++;
        it.node = this->operator[](index + 1);
      }
    }
  }

  template<class T>
  void List<T>::remove(const T& value)
  {
    size_t index = 0;
    Iterator< T > it = begin();
    while (it.node)
    {
      if (it.node->data == value) {
        if (it.node == head) {
          popFront();
        }
        else if (it.node == tail) {
          tail = this->operator[](index);
          this->operator[](index)->next = nullptr;
          it.node = this->operator[](index + 2);
          listSize--;
        }
        else {
          this->operator[](index)->next = this->operator[](index + 2);
          this->operator[](index + 1)->next = nullptr;
          it.node = this->operator[](index + 2);
          listSize--;
        }
      }
      else {
        index++;
        it.node = this->operator[](index + 1);
      }
    }
  }

  template<class T>
  void List<T>::reverse()
  {
    size_t tempSize = listSize;
    for (size_t i = tempSize - 1; i != -1; i--)
    {
      pushBack(this->operator[](i)->data);
    }
    for (size_t i = 0; i != tempSize; i++)
    {
      popFront();
    }
  }

  template<class T>
  T& sukacheva::List<T>::front()
  {
    return head->data;
  }

  template<class T>
  Node<T>* List<T>::operator[](size_t index)
  {
    Iterator< T > it = begin();
    for (size_t i = 0; i != index; i++) {
      if (it == nullptr) {
        return nullptr;
      }
      it++;
    }
    return it.node;
  }

  template<class T>
  void List<T>::pushBack(const T& data)
  {
    Node< T >* newNode = new Node< T >(data);
    if (empty()) {
      head = newNode;
      tail = newNode;
    }
    else {
      tail->next = newNode;
      tail = newNode;
    }
    listSize++;
  }

  template< class T>
  void List<T>::pushFront(const T& data) {
    Node< T >* newNode = new Node< T >(data);
    if (empty()) {
      head = newNode;
      tail = newNode;
    }
    else {
      newNode->next = head;
      head = newNode;
    }
    listSize++;
  }

  template< class T>
  void List<T>::popFront() {
    Node< T >* front = head;
    if (front->next != nullptr) {
      head = front->next;
    }
    else {
      head = nullptr;
      tail = nullptr;
    }
    delete front;
    listSize--;
  }

  template< class T>
  bool List<T>::empty() {
    return (head == nullptr);
  }

  template< class T>
  void List<T>::clean() {
    while (head)
    {
      popFront();
    }
  }

  template< class T>
  void List<T>::swap(List& other) {
    Node< T >* temp_head = head;
    Node< T >* temp_tail = tail;
    size_t tempSize = other.listSize;
    other.listSize = listSize;
    listSize = tempSize;
    head = other.head;
    tail = other.tail;
    other.head = temp_head;
    other.tail = temp_tail;
    delete temp_head;
    delete temp_tail;
  }

  template< class T>
  List<T>::~List() {
    clean();
  }

  template<class T>
  List<T>::List(const List&) :
    head(nullptr),
    tail(nullptr),
    listSize(0)
  {
    Iterator< T > it = begin();
    while (it.node) {
      this->pushBack(it.node->data);
      ++it;
    }
  }

  template<class T>
  List<T>::List(List&& other) :
    head(other.head),
    tail(other.tail),
    listSize(other.listSize)
  {
    other.head = nullptr;
    other.tail = nullptr;
    other.listSize = 0;
  }

  template<class T>
  List<T>::List(size_t count, const T& value) : List()
  {
    for (size_t i = 0; i != count; ++i) {
      pushBack(value);
    }
  }

  template<class T>
  List<T>::List(std::initializer_list<T> init) : List()
  {
    Iterator< T > it = init.begin();
    while (it) {
      pushBack(it.node->data);
      it++;
    }
  }

  template<class T>
  template<class InputIt>
  List<T>::List(InputIt first, InputIt last) : List()
  {
    while (first != last) {
      pushBack(first);
      first++;
    }
  }
}

#endif
