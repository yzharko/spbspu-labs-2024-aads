#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <memory>
#include "node.hpp"

namespace anikanov {

  template<typename T>
  class Iterator {
  public:
    using node_t = Node< T >;
    using this_t = Iterator< T >;

    Iterator();

    explicit Iterator(std::shared_ptr< node_t > node_ptr) : node(node_ptr)
    {
    }

    ~Iterator() = default;

    Iterator(const this_t &other) : node(other.node)
    {
    }

    std::shared_ptr< Node< T > > get_node() const;

    this_t &operator=(const this_t &);

    Iterator< T > operator+(int n) const;

    Iterator< T > operator-(int n) const;

    Iterator< T > &operator+=(int n);

    // Оператор -= для смещения назад
    Iterator< T > &operator-=(int n);

    this_t &operator++();
    this_t operator++(int);
    this_t &operator--();
    this_t operator--(int);

    T &operator*();
    const T &operator*() const;
    T *operator->();
    const T *operator->() const;

    bool operator!=(const this_t &other) const;
    bool operator==(const this_t &other) const;

  private:
    std::shared_ptr< node_t > node;
  };

  template<typename T>
  Iterator< T >::Iterator()
  {
    node = nullptr;
  }

  template<typename T>
  std::shared_ptr< Node< T>> Iterator< T >::get_node() const
  {
    return node;
  }

  template<typename T>
  typename Iterator< T >::this_t &Iterator< T >::operator=(const typename Iterator< T >::this_t &other)
  {
    node = other.node;
    return *this;
  }

  template<typename T>
  Iterator< T > Iterator< T >::operator+(int n) const
  {
    Iterator< T > tmp = *this;
    for (int i = 0; i < n && tmp.node != nullptr; ++i) {
      ++tmp;
    }
    return tmp;
  }

  template<typename T>
  Iterator< T > Iterator< T >::operator-(int n) const
  {
    Iterator< T > tmp = *this;
    for (int i = 0; i < n && tmp.node != nullptr; ++i) {
      --tmp;
    }
    return tmp;
  }

  template<typename T>
  Iterator< T > &Iterator< T >::operator+=(int n)
  {
    for (int i = 0; i < n && this->node != nullptr; ++i) {
      ++(*this);
    }
    return *this;
  }

  template<typename T>
  Iterator< T > &Iterator< T >::operator-=(int n)
  {
    for (int i = 0; i < n && this->node != nullptr; ++i) {
      --(*this);
    }
    return *this;
  }

  template<typename T>
  typename Iterator< T >::this_t &Iterator< T >::operator++()
  {
    if (node) {
      node = node->next;
    }
    return *this;
  }


  template<typename T>
  typename Iterator< T >::this_t Iterator< T >::operator++(int)
  {
    this_t tmp = *this;
    ++(*this);
    return tmp;
  }

  template<typename T>
  typename Iterator< T >::this_t &Iterator< T >::operator--()
  {
    if (node) {
      node = node->prev;
    }
    return *this;
  }

  template<typename T>
  typename Iterator< T >::this_t Iterator< T >::operator--(int)
  {
    this_t tmp = *this;
    --(*this);
    return tmp;
  }

  template<typename T>
  T &Iterator< T >::operator*()
  {
    return node->data;
  }

  template<typename T>
  const T &Iterator< T >::operator*() const
  {
    return node->data;
  }

  template<typename T>
  T *Iterator< T >::operator->()
  {
    return &(node->data);
  }

  template<typename T>
  const T *Iterator< T >::operator->() const
  {
    return &(node->data);
  }

  template<typename T>
  bool Iterator< T >::operator!=(const this_t &other) const
  {
    return node != other.node;
  }

  template<typename T>
  bool Iterator< T >::operator==(const this_t &other) const
  {
    return node == other.node;
  }
}

#endif
