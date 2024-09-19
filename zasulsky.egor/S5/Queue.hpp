#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <list.hpp>

namespace zasulsky
{
  template < typename T >
  class Queue
  {
  public:
    Queue() = default;
    Queue(const Queue& other);
    explicit Queue(const List< T >& dep);
    ~Queue() = default;

    Queue< T >& operator=(const Queue& other);

    T& getFront() const;
    T& getBack() const;

    void push(const T& data);
    void push(T&& data);
    void pop();

    size_t getSize() const noexcept;
    bool isEmpty() const noexcept;

  private:
    List< T > depot;
  };
}

template < typename T >
zasulsky::Queue< T >::Queue(const Queue& other)
{
  depot = other.depot;
}

template < typename T >
zasulsky::Queue< T >::Queue(const zasulsky::List< T >& dep)
{
  depot(dep);
}

template < typename T >
zasulsky::Queue< T >& zasulsky::Queue< T >::operator=(const Queue& other)
{
  depot = other.dep;
}

template < typename T >
T& zasulsky::Queue< T >::getFront() const
{
  return depot.getFront();
}

template < typename T >
T& zasulsky::Queue< T >::getBack() const
{
  return depot.getBack();
}

template < typename T >
void zasulsky::Queue< T >::push(const T& data)
{
  depot.pushBack(data);
}

template < typename T >
void zasulsky::Queue< T >::push(T&& data)
{
  depot.pushBack(data);
}

template < typename T >
void zasulsky::Queue< T >::pop()
{
  depot.popFront();
}

template<typename T>
size_t zasulsky::Queue<T>::getSize() const noexcept
{
  return depot.getSize();
}

template < typename T >
bool zasulsky::Queue< T >::isEmpty() const noexcept
{
  return depot.empty();
}

#endif
