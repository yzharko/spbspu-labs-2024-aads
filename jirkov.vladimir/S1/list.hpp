#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <iterator>
#include "node.hpp"
#include "iterator.hpp"

namespace jirkov {

  template<typename T>
  class List {
  private:
    Node<T>* head;
    Node<T>* tail;
    size_t size_;

  public:
    List() : head(nullptr), tail(nullptr), size_(0) {}

    ~List() {
      clear();
    }

    void push_back(const T& value) {
      Node<T>* newNode = new Node<T>(value);
      if (head == nullptr) {
        head = newNode;
        tail = newNode;
      }
      else
      {
        tail->next = newNode;
        tail = newNode;
      }
      size_++;
    }

    void pop_back() {
      if (head == nullptr) {
        return;
      }
      if (head == tail) {
        delete head;
        head = nullptr;
        tail = nullptr;
      }
      else
      {
        Node<T>* secondLastNode = head;
        while (secondLastNode->next != tail) {
          secondLastNode = secondLastNode->next;
        }
        delete tail;
        tail = secondLastNode;
        tail->next = nullptr;
      }
        size_--;
    }

    void clear() {
      Node<T>* currentNode = head;
      while (currentNode != nullptr) {
        Node<T>* nextNode = currentNode->next;
        delete currentNode;
        currentNode = nextNode;
      }
      head = nullptr;
      tail = nullptr;
      size_ = 0;
    }

    bool empty() const {
      return size_ == 0;
    }

    size_t size() const {
      return size_;
    }

    using iterator = ListIterator<T>;
    using const_iterator = ListIterator<const T>;

    iterator begin() {
      return iterator(head);
    }

    iterator end() {
      return iterator(nullptr);
    }

    const_iterator begin() const {
      return const_iterator(head);
    }

    const_iterator end() const {
      return const_iterator(nullptr);
    }

    void swap(List& other) {
      std::swap(head, other.head);
      std::swap(tail, other.tail);
      std::swap(size_, other.size_);
    }
  };
}

#endif
