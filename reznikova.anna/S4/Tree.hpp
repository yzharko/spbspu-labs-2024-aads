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

