#define LIST_HPP
#ifdef LIST_HPP
#include <cstddef>
#include "listIterator.hpp"

namespace maksimov
{
  template < typename T >
  class List
  {
  public:
    List(): head_(nullptr), size_(0) {};
    ~List();
    
    void pushBack(T);
    bool isEmpty();
  private:
    Node< T >* head_;
    size_t size_;
  };
}

template< typename T>
maksimov::List< T >::~List()
{
  for (size_t i = 0; i < size_; i++)
  {
    auto todel = head_;
    head_ = head_->next_;
    delete[] todel;
  }
}

template < typename T >
void maksimov::List< T >::pushBack(T data)
{
  Node< T >* ptr = new Node < T >(data);
  if (isEmpty())
  {
    head_ = ptr;
  }
  head_ = head_->next_;
  head_ = ptr;
  ++size_;
}

template < typename T >
bool maksimov::List< T >::isEmpty()
{
  return (head_ == nullptr);
}

#endif