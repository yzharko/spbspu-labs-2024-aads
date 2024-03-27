#ifndef NODE_HPP
#define NODE_HPP
#include <cstddef>

template <typename T>
struct Node
{
  T data;
  Node* Next;
  Node(T data = T(), Node* Next = nullptr)
  {
    this->data = data;
    this->Next = NULL;
  }
};

#endif
