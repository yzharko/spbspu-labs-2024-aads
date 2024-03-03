#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <utility>

namespace shagieva
{
  template<typename T>
  class List
  {
  private:
    struct Node
    {
      T data;
      Node * prev;
      Node * next;

      Node(T el):
        data(el)
      {}
    };

    Node * head;
    Node * tail;

  public:
    List() = default;

    class ConstIterator
    {
    private:
      friend class List;

    protected:
      const Node * curr;

      const Node * get() const
      {
        return curr;
      }

    public:
      ConstIterator(const Node * node):
        curr(node)
      {}

      T& operator*() const
      {
        return curr->data;
      }

      ConstIterator& operator++()
      {
        curr = curr->next;
        return *this;
      }

      ConstIterator operator++(int)
      {
        ConstIterator it = *this;
        curr = curr->next;
        return it;
      }

      ConstIterator& operator--()
      {
        curr = curr->prev;
        return *this;
      }

      ConstIterator operator--(int)
      {
        ConstIterator it = *this;
        curr = curr->prev;
        return it;
      }

      bool operator==(ConstIterator& other) const
      {
        return curr == other.curr;
      }

      bool operator!=(ConstIterator& other) const
      {
        return curr != other.curr;
      }
    };

    class Iterator: public ConstIterator
    {
    private:
      friend class List;

    public:
      Iterator(Node * node):
        ConstIterator(node)
      {}

      T& operator*() const
      {
        return const_cast<T&>(ConstIterator::operator*());
      }

      Iterator& operator++()
      {
        ConstIterator::operator++();
        return *this;
      }

      Iterator operator++(int)
      {
        auto res = ConstIterator::operator++(0);
        return Iterator(const_cast<Node *>(res.get()));
      }

      Iterator operator--()
      {
        ConstIterator::operator--();
        return *this;
      }

      Iterator operator--(int)
      {
        auto res = ConstIterator::operator--(0);
        return Iterator(const_cast<Node *>(res.get()));
      }
    };

    ConstIterator begin() const
    {
      return ConstIterator(head);
    }

    ConstIterator end() const
    {
      return ConstIterator(nullptr);
    }

    Iterator begin()
    {
      return Iterator(head);
    }

    Iterator end()
    {
      return Iterator(nullptr);
    }

    T& front()
    {
      return head->data;
    }

    T& back()
    {
      return tail->data;
    }

    bool empty() const
    {
      return head == nullptr;
    }

    void push_back(const T& el)
    {
      auto newNode = new Node(el);
      if (tail)
      {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
      }
      else
      {
        head = tail = newNode;
      }
    }

    void push_front(const T& el)
    {
      auto newNode = new Node(el);
      if (head)
      {
        head->prev = newNode;
        newNode->next = head;
        head = newNode;
      }
      else
      {
        head = tail = newNode;
      }
    }

    void erase(Iterator place)
    {
      auto ptr = place.curr;
      if (ptr->prev)
      {
        ptr->prev->next = ptr->next;
      }
      else
      {
        head = ptr->next;
      }

      if (ptr->next)
      {
        ptr->next->prev = ptr->prev;
      }
      else
      {
        tail = ptr->prev;
      }

      delete ptr;
    }

    void pop_front()
    {
      erase(begin());
    }

    void pop_back()
    {
      erase(--end());
    }

    void clear()
    {
      while (head)
      {
        delete std::exchange(head, head->next);
      }
    }

    void swap(List & other)
    {
      if (*this != other)
      {
        List<T> temp = *this;
        *this = other;
        other = temp;
      }
    }
  };
}
#endif


