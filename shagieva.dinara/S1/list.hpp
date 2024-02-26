#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <utility>

namespace shagieva
{
  template< typename T >
  class List
  {
  private:
    struct Node
    {
      Node * prev = nullptr;
      Node * next = nullptr;
      T data;

      Node(T el):
        data { std::move(el) }
      {}
    };

    Node * head = nullptr;
    Node * tail = nullptr;

  public:
    List() = default;

    List(std::initializer_list<T> elements)
    {
      for (auto & el : elements)
      {
        push_back(el);
      }
    }

    ~List()
    {
      clear();
    }

  public:
    class iterator
    {
    private:
      Node * curr = nullptr;

    public:
      iterator(Node * p) :
        curr(p)
      {}

      Node * get()
      {
        return curr;
      }

      T operator*()
      {
        return curr->data;
      }

      iterator operator++()
      {
        curr = curr->next;
        return *this;
      }

      iterator operator++(int)
      {
        iterator it = *this;
        curr = curr->next;
        return it;
      }

      iterator operator--()
      {
        curr = curr->prev;
        return *this;
      }

      iterator operator--(int)
      {
        iterator it = *this;
        curr = curr->prev;
        return it;
      }

      bool operator==(const iterator & other) const
      {
        return curr == other.curr;
      }

      bool operator!=(const iterator & other) const
      {
        return curr != other.curr;
      }
    };

    iterator begin() const
    {
      return head;
    }

    iterator end() const
    {
      return nullptr;
    }

    void insert(iterator place, const T & el)
    {
      auto ptr = place.get();
      if(!ptr)
      {
        push_back(std::move(el));
        return;
      }

      auto newNode = new Node { std::move(el) };

      newNode->next = ptr;
      newNode->prev = ptr->prev;

      if (ptr->prev)
      {
        ptr->prev->next = newNode;
      }

      ptr->prev = newNode;
    }

    void erase(iterator place)
    {
      auto ptr = place.get();
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

    void push_back(const T& el)
    {
      auto newNode = new Node { std::move(el) };
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
      auto newNode = new Node { std::move(el) };
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

    void pop_front()
    {
      erase(begin());
    }

    void pop_back()
    {
      erase(--end());
    }

    void clear() noexcept
    {
      while (head)
      {
        delete std::exchange(head, head->next);
      }
      tail = nullptr;
    }
  };

  template< typename T  >
  void printList(const List<T> & list, std::ostream & out)
  {
    for (const auto & el: list)
    {
      out << el << " ";
    }
    out << "\n";
  }
}

#endif
