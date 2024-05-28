#ifndef BILATERALNODE_HPP
#define BILATERALNODE_HPP
#include <utility>
#include <stdexcept>

namespace detail
{
  template < class T >
  struct bilateralNode
  {
    bilateralNode(T data, bilateralNode < T >* prev = nullptr, bilateralNode < T >* next = nullptr)
    {
      this->data = data;
      this->next = next;
      this->prev = prev;
    }

    T data;

    bilateralNode < T >* prev;
    bilateralNode < T >* next;
  };

  template < class T >
  void deleteHead(bilateralNode < T >*& head)
  {
    bilateralNode < T >* temp = head->next;
    delete head;
    head = temp;
  }

  template < class T >
  void deleteTail(bilateralNode < T >* tail)
  {
    bilateralNode < T >* temp = tail->prev;
    delete tail;
    tail = temp;
  }

  template < class T >
  void freeList(bilateralNode < T >* head)
  {
    while (head)
    {
      deleteHead(head);
    }
  }

  template < class T >
  std::pair< bilateralNode < T >*, bilateralNode < T >* > copyList(bilateralNode < T >* other)
  {
    if (other)
    {
      bilateralNode < T >* head = new bilateralNode< T >(other->data);
      bilateralNode < T >* temp1 = other;
      bilateralNode < T >* temp2 = head;
      while (temp1->next != nullptr)
      {
        temp2->next = new bilateralNode< T >((temp1->next)->data);
        temp2 = temp2->next;
        temp1 = temp1->next;
      }
      return std::make_pair(head, temp2);
    }
    else
    {
      throw std::logic_error("List is empty!\n");
    }
  }
}

#endif
