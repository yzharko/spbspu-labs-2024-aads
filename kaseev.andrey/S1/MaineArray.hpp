#ifndef MAINEARRAY_HPP
#define MAINEARRAY_HPP

#include <iostream>
#include "Node.hpp"

namespace kaseev {
  template<class T>
  class List {
  public:
    List() : ArrSize(0), head(nullptr) {}
    ~List();
    void pushBack(const T& value);
    bool empty() const;
    int size() const;
    void pop_front();
    void clear();
    const T& operator[](int index) const;

  private:
    int ArrSize;
    Node<T>* head;
  };

  template<class T>
  List<T>::~List() {
    clear();
  }

  template<class T>
  void List<T>::pushBack(const T& value) {
    Node<T>* newNode = new Node<T>(value);

    if (head == nullptr) {
      head = newNode;
    } else {
      Node<T>* current = head;
      while (current->next != nullptr) {
        current = current->next;
      }
      current->next = newNode;
    }

    ArrSize++;
  }

  template<class T>
  bool List<T>::empty() const {
    return head == nullptr;
  }

  template<class T>
  int List<T>::size() const {
    return ArrSize;
  }

  template<class T>
  void List<T>::pop_front() {
    if (head == nullptr) {
      ArrSize = 0;
      throw std::logic_error("empty list");
    }

    Node<T>* temp = head;
    head = head->next;
    delete temp;
    ArrSize--;
  }

  template<class T>
  void List<T>::clear() {
    while (head != nullptr) {
      Node<T>* temp = head;
      head = head->next;
      delete temp;
      ArrSize--;
    }
  }

  template<class T>
  const T& List<T>::operator[](int index) const {
    if (index >= ArrSize) {
      throw std::out_of_range("Index out of range");
    }
    Node<T>* current = head;
    for (int i = 0; i < index; ++i) {
      current = current->next;
    }
    return current->data;
  }
}

#endif
