#ifndef LIST_HPP
#define LIST_HPP

#include "node.hpp"
#include "iterator.hpp"
#include <memory>
#include <limits>
#include <stdexcept>

namespace anikanov {

  template<typename T>
  class List {
  public:
    List();
    List(const List &other);
    List(List &&other) noexcept;
    List(const T &value, size_t count);
    List(std::initializer_list< T > init);
    List(Iterator< T > first, Iterator< T > last);
    ~List();

    void push_back(const T &value);
    T pop(size_t n = std::numeric_limits< size_t >::max());
    bool empty();
    size_t size() const;
    void clear();
    void swap(List &other);
    void remove(const T &value);

    template<typename Predicate>
    void remove_if(Predicate pred);
    void reverse();
    void splice(Iterator< T > position, List< T > &other, Iterator< T > first, Iterator< T > last);
    Iterator< T > insert(Iterator< T > pos, const T &value);
    Iterator< T > erase(Iterator< T > pos);
    void assign(size_t count, const T &value);
    void assign(Iterator< T > first, Iterator< T > last);
    void assign(std::initializer_list< T > ilist);
    List< T > copy();

    T &operator[](size_t index);
    List< T > &operator=(List< T > &&other) noexcept;
    List< T > &operator=(List< T > other);

    Iterator< T > back();
    Iterator< T > begin() const;
    Iterator< T > end() const;

  private:
    std::shared_ptr< Node< T > > head, tail;
    size_t list_size;
  };

  template<typename T>
  List< T > &List< T >::operator=(List< T > other)
  {
    swap(other);
    return *this;
  }

  template<typename T>
  List< T > &List< T >::operator=(List< T > &&other) noexcept
  {
    if (this != &other) {
      clear(); // Освободим существующие ресурсы

      head = other.head;
      tail = other.tail;

      other.head = nullptr;
      other.tail = nullptr;
    }
    return *this;
  }

  template<typename T>
  List< T >::List() : head(nullptr), tail(nullptr), list_size(0)
  {
  }

  template<typename T>
  List< T >::List(const List &other): head(nullptr), tail(nullptr), list_size(0)
  {
    auto current = other.head;
    while (current != nullptr) {
      (*this).push_back(current->data);
      current = current->next;
    }
  }

  template<typename T>
  List< T >::List(List &&other) noexcept: head(std::move(other.head)), tail(std::move(other.tail)),
                                          list_size(other.list_size)
  {
    other.head = nullptr;
    other.tail = nullptr;
    other.list_size = 0;
  }

  template<typename T>
  List< T >::List(const T &value, size_t count): head(nullptr), tail(nullptr), list_size(0)
  {
    for (size_t i = 0; i < count; ++i) {
      push_back(value);
    }
  }

  template<typename T>
  List< T >::List(std::initializer_list< T > init): head(nullptr), tail(nullptr), list_size(0)
  {
    for (auto &element: init) {
      push_back(element);
    }
  }

  template<typename T>
  List< T >::List(Iterator< T > first, Iterator< T > last): head(nullptr), tail(nullptr), list_size(0)
  {
    for (; first != last; ++first) {
      push_back(*first);
    }
  }

  template<typename T>
  List< T >::~List()
  {
    this->clear();
  }

  template<typename T>
  void List< T >::push_back(const T &value)
  {
    auto newNode = std::make_shared< Node< T > >(value);
    if (head == nullptr) {
      head = newNode;
      tail = newNode;
    } else {
      tail->next = newNode;
      newNode->prev = tail;
      tail = newNode;
    }
    list_size++;
  }

  template<typename T>
  T List< T >::pop(size_t n)
  {
    if (list_size == 0) {
      throw std::out_of_range("List is empty");
    }

    if (n == std::numeric_limits< size_t >::max()) {
      n = list_size - 1;
    }

    if (n >= list_size) {
      throw std::out_of_range("Index out of range");
    }
    auto current = head;
    for (size_t i = 0; i < n; ++i) {
      current = current->next;
    }

    if (current->prev != nullptr) {
      current->prev->next = current->next;
    } else {
      head = current->next;
    }

    if (current->next != nullptr) {
      current->next->prev = current->prev;
    } else {
      tail = current->prev;
    }

    T value = current->data;
    --list_size;

    return value;
  }

  template<typename T>
  bool List< T >::empty()
  {
    if (head == nullptr) {
      return true;
    }
    return false;
  }

  template<typename T>
  size_t List< T >::size() const
  {
    return list_size;
  }

  template<typename T>
  void List< T >::clear()
  {
    auto current = tail;
    while (current != nullptr) {
      auto prev = current->prev;
      current->next = nullptr;
      current->prev = nullptr;
      current = prev;
      list_size--;
    }
    head = nullptr;
    tail = nullptr;
  }

  template<typename T>
  void List< T >::swap(List &other)
  {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
  }

  template<typename T>
  void List< T >::remove(const T &value)
  {
    remove_if([value](T &other) {
      return value == other;
    });
  }

  template<typename T>
  template<typename Predicate>
  void List< T >::remove_if(Predicate pred)
  {
    auto current = head;
    while (current != nullptr) {
      if (pred(current->data)) {
        auto toDelete = current;
        if (current->prev != nullptr) {
          current->prev->next = current->next;
        } else {
          head = current->next;
        }
        if (current->next != nullptr) {
          current->next->prev = current->prev;
        } else {
          tail = current->prev;
        }
        current = current->next;
        delete toDelete;
        --list_size;
      } else {
        current = current->next;
      }
    }
  }

  template<typename T>
  void List< T >::reverse()
  {
    List< T > new_list;
    for (int i = list_size - 1; i > -1; --i) {
      new_list.push_back((*this)[i]);
    }
    (*this).clear();
    for (int i = 0; i < new_list.size(); ++i) {
      (*this).push_back(new_list[i]);
    }
  }

  template<typename T>
  void List< T >::splice(Iterator< T > position, List< T > &other, Iterator< T > first, Iterator< T > last)
  {
    if (first == last || &other == this) {
      return;
    }

    auto current = first;
    bool extra = false;
    if (list_size == 0) {
      (*this).push_back(0);
      extra = true;
      position = (*this).begin();
    }

    while (current != last) {
      position = insert(position, *current);
      position++;
      current = other.erase(current);
    }
    if (extra) {
      (*this).pop();
    }
  }

  template<typename T>
  Iterator< T > List< T >::insert(Iterator< T > pos, const T &value)
  {
    auto newNode = std::make_shared< Node< T > >(value);
    auto posNode = pos.get_node();
    if (pos == (*this).begin()) {
      newNode->next = head;
      if (head) {
        head->prev = newNode;
      } else {
        tail = newNode;
      }
      head = newNode;
    } else {
      auto prevNode = posNode->prev;
      newNode->next = posNode;
      newNode->prev = prevNode;
      posNode->prev = newNode;
      if (prevNode) {
        prevNode->next = newNode;
      }
    }
    ++list_size;
    return Iterator< T >(newNode);
  }
  template<typename T>
  Iterator< T > List< T >::erase(Iterator< T > pos)
  {
    auto posNode = pos.get_node();
    if (posNode->prev) {
      posNode->prev->next = posNode->next;
    }
    if (posNode->next) {
      posNode->next->prev = posNode->prev;
    }
    return Iterator< T >(posNode->next);
  }

  template<typename T>
  void List< T >::assign(size_t count, const T &value)
  {
    clear();
    for (size_t i = 0; i < count; ++i) {
      push_back(value);
    }
  }

  template<typename T>
  void List< T >::assign(std::initializer_list< T > ilist)
  {
    for (auto &element: ilist) {
      push_back(element);
    }
  }

  template<typename T>
  void List< T >::assign(Iterator< T > first, Iterator< T > last)
  {
    (*this).clear();
    for (auto cur = first; cur != last; ++cur) {
      (*this).push_back(*cur);
    }
  }

  template<typename T>
  List< T > List< T >::copy()
  {
    List< T > newList;

    std::shared_ptr< Node< T>> current = head;
    while (current != nullptr) {
      newList.push_back(current->data);
      current = current->next;
    }

    return newList;
  }

  template<typename T>
  T &List< T >::operator[](size_t index)
  {
    if (index >= list_size) {
      throw std::out_of_range("Index out of range");
    }

    auto current = head;
    for (size_t i = 0; i < index; ++i) {
      current = current->next;
    }

    return current->data;
  }

  template<typename T>
  Iterator< T > List< T >::back()
  {
    return Iterator< T >(tail);
  }

  template<typename T>
  Iterator< T > List< T >::begin() const
  {
    return Iterator< T >(head);
  }

  template<typename T>
  Iterator< T > List< T >::end() const
  {
    return Iterator< T >(nullptr);
  }
}

#endif
