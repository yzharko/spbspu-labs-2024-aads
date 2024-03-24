#ifndef NODE_HPP
#define NODE_HPP

namespace sukacheva {
  template <class T>
  struct Node
  {
    T data;
    Node<T>* next;
    Node(T data_) : data(data_), next(nullptr) {}
  };
}

#endif
