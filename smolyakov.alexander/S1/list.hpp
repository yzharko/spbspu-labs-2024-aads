#ifndef LIST_HPP
#define LIST_HPP
#include <iterator>
#include "node.hpp"

namespace smolyakov
{
  template<typename T>
  class List
  {
  public:
    class Iterator;
    class ConstIterator;
  private:
    Node<T> head_;
    Node<T> tail_;
  };

  template<typename T>
  class List<T>::Iterator : public std::iterator<std::forward_iterator_tag, T>
  {
  public:
    Iterator();
    Iterator(const Iterator& other) = default;
    ~Iterator() = default;
  };

  template<typename T>
  class List<T>::ConstIterator : public std::iterator<std::forward_iterator_tag, T>
  {
  public:
    ConstIterator();
    ConstIterator(const ConstIterator& other) = default;
    ~ConstIterator() = default;
  };
}

#endif
