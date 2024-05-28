#ifndef BILATERALNODE_HPP
#define BILATERALNODE_HPP
#include <utility>
#include <stdexcept>
#include <memory>

namespace zasulsky
{
  namespace detail
  {
    template < class T >
    struct Node
    {
      Node(T data, Node < T >* prev = nullptr, Node < T >* next = nullptr)
      {
        this->data = data;
        this->next = next;
        this->prev = prev;
      }

      T data;

      Node < T >* prev;
      Node < T >* next;
    };

    template < class T >
    void deleteHead(Node < T >*& head)
    {
      Node < T >* temp = head->next;
      delete head;
      head = temp;
    }

    template < class T >
    void deleteTail(Node < T >* tail)
    {
      Node < T >* temp = tail->prev;
      delete tail;
      tail = temp;
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
    std::pair< std::unique_ptr< Node< T > >, std::unique_ptr<Node<T>>> copyList(Node<T>* other) {
      if (other)
      {
        std::unique_ptr< Node< T > > head = std::make_unique< Node< T > >(other->data);
        Node< T >* temp1 = other->next;
        Node< T >* temp2 = head.get();
        while (temp1 != nullptr) {
          temp2->next = std::make_unique< Node< T > >(temp1->data);
          temp2->next->prev = temp2;
          temp2 = temp2->next.get();
          temp1 = temp1->next;
        }
        return std::make_pair(std::move(head), std::unique_ptr<Node<T>>(temp2));
      }
      else
      {
        return std::make_pair(nullptr, nullptr);
      }
    }
  }

}
#endif
