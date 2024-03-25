#ifndef NODE_HPP
#define NODE_HPP

namespace jirkov {

  template<typename T>
  struct Node {
    T value;
    Node* next;

    Node(const T& value) : value(value), next(nullptr) {}
  };
}

#endif
