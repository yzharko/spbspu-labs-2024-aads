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

