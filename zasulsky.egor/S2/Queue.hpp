#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <ForwardList.hpp>

namespace zasulsky
{
  template < class T >
  class Queue
  {
  public:

    bool isEmpty() noexcept
    {
      return fL.empty();
    }

    void enqueue(T& data)
    {
      if (this->isEmpty())
      {
        fL.insert_after(fL.cbeforeBegin(), data);
      }
      else
      {
        detail::Node< T >* temp = fL.head();
        while (temp->next != nullptr)
        {
          temp = temp->next;
        }
        constIterator< T > it(temp);
        fL.insert_after(it, data);
      }
    }

    T peek()
    {
      if (this->isEmpty())
      {
        throw std::logic_error("no elements!");
      }
      return fL.head()->data;
    }

    void dequeue()
    {
      if (this->isEmpty())
      {
        throw std::logic_error("The list is empty!!");
      }
      else
      {
        fL.erase_after(fL.cbeforeBegin());
      }
    }

  private:

    ForwardList< T > fL;

  };
}

#endif
