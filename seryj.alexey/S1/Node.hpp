#ifndef NODE_HPP
#define NODE_HPP
template <class T>
struct Node
{
  T data;
  Node<T>* next;
};
#endif
