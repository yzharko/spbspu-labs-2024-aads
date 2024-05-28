#ifndef Node_HPP
#define Node_HPP
#include <stdexcept>

namespace detail
{
  template < class T >
  struct Node
  {
    Node(T data, Node < T >* next = nullptr)
    {
      this->data = data;
      this->next = next;
    }

    T data;
    Node< T >* next;
  };

  template < class T >
  void deleteHead(Node < T >*& head)
  {
    Node < T >* temp = head->next;
    delete head;
    head = temp;
  }
  template < class T >

  void freeList(Node < T >* head)
  {
    while (head)
    {
      deleteHead(head);
    }
  }

  template < class T >
  Node < T >* copyList(Node < T >* other)
  {
    if (other)
    {
      Node < T >* head = new Node< T >(other->data);
      Node< T >* temp1 = other;
      Node< T >* temp2 = head;
      while (temp1->next != nullptr)
      {
        temp2->next = new Node< T >((temp1->next)->data);
        temp2 = temp2->next;
        temp1 = temp1->next;
      }
      return head;
    }
    else
    {
      throw std::logic_error("List is empty!\n");
    }
  }
}

#endif
