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
      return forwardList.empty();
    }

    void enqueue(T& data)
    {
      if (this->isEmpty())
      {
        forwardList.insert_after(forwardList.cbeforeBegin(), data);
      }
      else
      {
        detail::Node< T >* temp = forwardList.head();
        while (temp->next != nullptr)
        {
          temp = temp->next;
        }
        constIterator< T > it(temp);
        forwardList.insert_after(it, data);
      }
    }

    T peek()
    {
      return forwardList.getHead();
    }

    void dequeue()
    {
      if (this->isEmpty())
      {
        throw std::logic_error("The list is empty!!");
      }
      else
      {
        forwardList.erase_after(forwardList.cbeforeBegin());
      }
    }

  private:

    ForwardList< T > forwardList;

  };
}

#endif
