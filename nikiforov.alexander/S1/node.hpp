#ifndef NODE_HPP
#define NODE_HPP

namespace nikiforov
{
  template <typename T>
  struct Node
  {
    T data;
    Node* pNext;
    Node(T data, Node* pNext = nullptr);
  };
}
template<typename T>
nikiforov::Node<T>::Node(T data, Node* pNext)
{
  this->data = data;
  this->pNext = pNext;
}
#endif
