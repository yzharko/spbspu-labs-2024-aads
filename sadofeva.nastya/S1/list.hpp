#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>

namespace sadofeva
{
  template < typename T>
  class List
  {
  public:
    struct Node
    {
      Node(const Node& value) :
      value(value),
      next(0),
      prev(0)
      {}
      ~Node() {delete next;}
      Node* next;
      Node* prev;
    };
    class iterator
    {
      iterator() :
      current(0),
      next(0),
      prev(0)
      {}
      Node* next;
      Node* current;
      Node* prev;
      iterator begin() { return ++iterator(m_last); }
      iterator end() { return iterator(m_last);}
    };
    Node* head;
    Node* tail;
    List(); 
    ~List();
    void push_back(const T& value); 
    void push_front(const T& value); 
    void pop_front(); 
    void pop_back(); 
    void clearList(); 
    size_t siz;
    Node* m_last;
    };
}

template< typename T>
void sadofeva::List<T>::push_back(const T& value)
{
  Node* new_node = new done(value);
  new_node->prev = m_last->prev;
  new_node->next = m_last;
  m_last->prev->next = new_node;
  m_last->orev = new_node;
  ++siz;
}

template<typename T>
void sadofeva::List<T>::push_front(const T& value)
{
  Node* new_node = new Node(value);
  new_node->prev = m_last;
  new_node->next = m_last->next;
  m_last->next->prev = new_node;
  m_last->next = new_node;
  ++siz;
}
 
template<typename T>
void sadofeva::List<T>::pop_front()
{
  Node* node_to_del = m_last->next;
  m_last->next = node_to_del->next;
  node_to_del->next->prec = m_last;

  node_to_del->next = 0;
  delete node_to_del;
}

template<typename T>
void sadofeva::List<T>::pop_back()
{
  Node* node_to_del = m_last->prev;
  m_last->prev = node_to_del->prev;
  node_to_del->prev->next = m_last;
  node_to_del->next = 0;
  delete node_to_del;
}
template<typename T>
sadofeva::List<T>::~List()
{
  m_last->prev->next = 0;
  delete m_last;
}
 
template<typename T>
sadofeva::List<T>::List()
{
  m_last(new Node(value())), siz(0))
  m_last->prev = m_last->next = m_last;
}
template<typename T>
void sadofeva::List<T>::clearList()
{
  m_last->prev->next = 0;
  delte m_last->next;

  m_lat->prev = m_last->next = m_last;
  siz = 0;
}

#endif
