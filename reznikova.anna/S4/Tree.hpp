#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <stdexcept>
#include <utility>
#include <algorithm>

namespace reznikova
{
  template< typename Key, typename Value, typename Comparator = std::less< Key > >
  class Tree
  {
  public:
    class Node;
    class ConstIterator;
    class Iterator;
    using pair_type = std::pair< const Key, Value >;
    
    Tree();
    Tree(const Tree & otherTree);
    Tree(Tree && otherTree);
    ~Tree();
  private:
    
    Node * root_;
    Comparator cmp_;
    size_t size_;
  };
}

using namespace reznikova;

template< typename Key, typename Value, typename Comparator >
class Tree< Key, Value, Comparator >::Node
{
public:
  friend class Tree< Key, Value, Comparator >;
  explicit Node(Key key_, Value value_) :
    parent_(nullptr),
    left_(nullptr),
    right_(nullptr),
    value_pair_(std::make_pair(key_, value_)),
    height_(0)
  {}
private:
  Node * parent_;
  Node * left_;
  Node * right_;
  std::pair< const Key, Value > value_pair_;
  int height_;
};

template< typename Key, typename Value, typename Comparator >
class Tree< Key, Value, Comparator >::ConstIterator
{
  friend class Tree< Key, Value, Comparator >;
  using this_t = ConstIterator;
  using node_t = Node;
  using pair_type = std::pair< const Key, Value >;
  ConstIterator();
  ConstIterator(node_t * node, node_t * root);
  ConstIterator(const ConstIterator &) = default;
  ~ConstIterator() = default;
  this_t & operator=(const ConstIterator &) = default;
  this_t & operator++();
  this_t operator++(int);
  this_t & operator--();
  this_t operator--(int);
  const pair_type & operator*() const;
  const pair_type * operator->() const;
  bool operator!=(const this_t & rhs) const;
  bool operator==(const this_t & rhs) const;
private:
  node_t * node_;
  node_t * root_;
};

template< typename Key, typename Value, typename Comparator >
Tree< Key, Value, Comparator >::ConstIterator::ConstIterator():
  node_(nullptr),
  root_(nullptr)
{}

template< typename Key, typename Value, typename Comparator >
Tree< Key, Value, Comparator >::ConstIterator::ConstIterator(node_t * node, node_t * root):
  node_(node),
  root_(root)
{}

template< typename Key, typename Value, typename Comparator >
typename Tree< Key, Value, Comparator >::ConstIterator & Tree< Key, Value, Comparator >::ConstIterator::operator++()
{
  assert(node_ != nullptr);
  if (node_->right_)
  {
    node_ = node_->right_;
    while (node_->left_)
    {
      node_ = node_->left_;
    }
  }
  else
  {
    Node * temp = node_->parent_;
    while (temp and (node_ == temp->right_))
    {
      node_ = temp;
      temp = temp->parent_;
    }
    node_ = temp;
  }
  return *this;
}

template< typename Key, typename Value, typename Comparator >
typename Tree< Key, Value, Comparator >::ConstIterator Tree< Key, Value, Comparator >::ConstIterator::operator++(int)
{
  this_t result(*this);
  ++(*this);
  return result;
}

template< typename Key, typename Value, typename Comparator >
typename Tree< Key, Value, Comparator >::ConstIterator & Tree< Key, Value, Comparator >::ConstIterator::operator--()
{
  if (node_ == nullptr)
  {
    node_ = root_;
    while (node_->right)
    {
      node_ = node_->right;
    }
  }
  else
  {
    if (node_->left)
    {
      node_ = node_->left;
      while (node_->right)
      {
        node_ = node_->right;
      }
    }
    else
    {
      Node * temp = node_->parent;
      while (temp and (node_ == temp->left))
      {
        node_ = temp;
        temp = node_->parent;
      }
      node_ = temp;
    }
  }
  return *this;
}

template< typename Key, typename Value, typename Comparator >
typename Tree< Key, Value, Comparator >::ConstIterator Tree< Key, Value, Comparator >::ConstIterator::operator--(int)
{
  this_t result(*this);
  --(*this);
  return result;
}

template< typename Key, typename Value, typename Comparator >
const std::pair< const Key, Value > & Tree< Key, Value, Comparator >::ConstIterator::operator*() const
{
  assert(node_ != nullptr);
  return node_->value_pair_;
}

template< typename Key, typename Value, typename Comparator >
const std::pair< const Key, Value > * Tree< Key, Value, Comparator >::ConstIterator::operator->() const
{
  assert(node_ != nullptr);
  return std::addressof(node_->value_pair_);
}

template< typename Key, typename Value, typename Comparator >
bool Tree< Key, Value, Comparator >::ConstIterator::operator!=(const ConstIterator & rhs) const
{
  return !(*this == rhs);
}

template< typename Key, typename Value, typename Comparator >
bool Tree< Key, Value, Comparator >::ConstIterator::operator==(const ConstIterator & rhs) const
{
  return *this == rhs;
}
