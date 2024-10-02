#ifndef NODE_HPP
#define NODE_HPP
namespace smolyakov
{
  template<typename T>
  class Node final
  {
  public:
    Node(T value, Node<T>* next = nullptr, Node<T>* previous = nullptr);
    T value;
    Node<T> *next;
    Node<T> *previous;
  };
}

template<typename T>
smolyakov::Node<T>::Node(T value, Node<T>* next, Node<T>* previous)
  : value(value), next(next), previous(previous)
{}

#endif
