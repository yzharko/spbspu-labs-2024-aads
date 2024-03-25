#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "node.hpp"

namespace jirkov {
  template<typename T>
  struct ListIterator {
    using value_type = T;
    using reference = value_type&;
    Node<value_type>* node;

    ListIterator(Node<value_type>* node) : node(node) {}

    reference operator*() const {
      return node->value;
    }

    ListIterator& operator++() {
      node = node->next;
      return *this;
    }

    bool operator==(const ListIterator& other) const {
      return node == other.node;
    }

    bool operator!=(const ListIterator& other) const {
      return !(*this == other);
    }
  };
}

#endif
