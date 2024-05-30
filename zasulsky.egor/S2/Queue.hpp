#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <ForwardList.hpp>

namespace zasulsky
{
  template < class T >
  class Queue
  {
  public:

    bool isEmpty()
    {
      return fl.empty();
    }

    void enqueue(T& data)
    {
      if (this->isEmpty())
      {
        fl.insert_after(fl.cbeforeBegin(), data);
      }
      else
      {
        detail::Node < T >* temp = fl.head();
        while (temp->next != nullptr)
        {
          temp = temp->next;
        }
        constIterator< T > it(temp);
        fl.insert_after(it, data);
      }
    }

    T peek()
    {
      if (this->isEmpty())
      {
        throw std::logic_error("no elements!");
      }
      return fl.head()->data;
    }

    void dequeue()
    {
      if (this->isEmpty())
      {
        throw std::logic_error("The list is empty!!");
      }
      else
      {
        fl.erase_after(fl.cbeforeBegin());
      }
    }

  private:

    ForwardList< T > fl;

  };
}

#endif
