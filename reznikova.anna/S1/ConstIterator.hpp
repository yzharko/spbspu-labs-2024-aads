#ifndef CONSTITERATOR_HPP
#define CONSTITERATOR_HPP
#include "Iterator.hpp"
#include "Node.hpp"
namespace reznikova
{
  namespace details
  {
    template< typename T >
    class ConstIterator : public std::iterator< std::bidirectional_iterator_tag, T >
    {
    public:
      using this_t = ConstIterator;
      ConstIterator() : iter_(nullptr) {};
      ConstIterator(Iterator< T > iter) : iter_(iter) {};
      ConstIterator(const this_t&) = default;
      ~ConstIterator() = default;
      this_t & operator=(const this_t &) = default;
      this_t & operator++();
      this_t operator++(int);
      this_t & operator--();
      this_t operator--(int);
      const T & operator*() const;
      const T * operator->() const;
      bool operator!=(const this_t &) const;
      bool operator==(const this_t &) const;
    private:
      Iterator< T > iter_;
    };
  }
}

template< typename T >
typename reznikova::details::ConstIterator< T > & reznikova::details::ConstIterator< T >::operator++()
{
  assert(iter_.node_ != nullptr);
  iter_.node_ = iter_.node_->next_;
  return *this;
}

template< typename T >
typename reznikova::details::ConstIterator< T > reznikova::details::ConstIterator< T >::operator++(int)
{
  assert(iter_.node_ != nullptr);
  Iterator result(*this);
  iter_.node_ = iter_.node_->next_;
  return result;
}

template< typename T >
typename reznikova::details::ConstIterator< T > & reznikova::details::ConstIterator< T >::operator--()
{
  assert(iter_.node_ != nullptr);
  iter_.node_ = iter_.node_->prev_;
  return *this;
}

template< typename T >
typename reznikova::details::ConstIterator< T > reznikova::details::ConstIterator< T >::operator--(int)
{
  assert(iter_.node_ != nullptr);
  Iterator result(*this);
  iter_.node_ = iter_.node_->prev_;
  return result;
}

template< typename T >
bool reznikova::details::ConstIterator< T >::operator==(const ConstIterator & rhs) const
{
  return iter_.node_ == rhs.iter_.node_;
}

template< typename T >
bool reznikova::details::ConstIterator< T >::operator!=(const ConstIterator & rhs) const
{
  return !(rhs == *this);
}

template< typename T >
const T & reznikova::details::ConstIterator< T >::operator*() const
{
  assert(iter_.node_ != nullptr);
  return iter_.node_->data_;
}

template< typename T >
const T * reznikova::details::ConstIterator< T >::operator->() const
{
  assert(iter_.node_ != nullptr);
  return std::addressof(iter_.node_->data_);
}

#endif
