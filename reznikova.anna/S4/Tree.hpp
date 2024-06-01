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
    
    ConstIterator begin() const noexcept;
    ConstIterator end() const noexcept;
    Iterator begin() noexcept;
    Iterator end() noexcept;
    size_t getSize() const noexcept;
    bool isEmpty() const noexcept;
    void insert(const Key& key, const Value& value);
    void clear(Node * node);
    void swap(Tree & otherTree);
    Value & at(const Key & key);
    Iterator find(const Key & key);
    
  private:
    Node * LLrotation(Node * turnNode);
    Node * RRrotation(Node * turnNode);
    void updateHeight(Node * node);
    Node * balance(Node * node);
    Node * insert(Node * node, const Key & key, const Value & value);
    
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

template< typename Key, typename Value, typename Comparator >
class Tree< Key, Value, Comparator >::Iterator
{
  friend class Tree< Key, Value, Comparator >;
  using this_t = Iterator;
  using node_t = Node;
  using pair_type = std::pair< const Key, Value >;
  Iterator();
  Iterator(node_t * node, node_t * root);
  Iterator(const Iterator &) = default;
  ~Iterator() = default;
  this_t & operator=(const Iterator &) = default;
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
Tree< Key, Value, Comparator >::Iterator::Iterator():
  node_(nullptr),
  root_(nullptr)
{}

template< typename Key, typename Value, typename Comparator >
Tree< Key, Value, Comparator >::Iterator::Iterator(node_t * node, node_t * root):
  node_(node),
  root_(root)
{}

template< typename Key, typename Value, typename Comparator >
typename Tree< Key, Value, Comparator >::Iterator & Tree< Key, Value, Comparator >::Iterator::operator++()
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
typename Tree< Key, Value, Comparator >::Iterator Tree< Key, Value, Comparator >::Iterator::operator++(int)
{
  this_t result(*this);
  ++(*this);
  return result;
}

template< typename Key, typename Value, typename Comparator >
typename Tree< Key, Value, Comparator >::Iterator & Tree< Key, Value, Comparator >::Iterator::operator--()
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
typename Tree< Key, Value, Comparator >::Iterator Tree< Key, Value, Comparator >::Iterator::operator--(int)
{
  this_t result(*this);
  --(*this);
  return result;
}

template< typename Key, typename Value, typename Comparator >
const std::pair< const Key, Value > & Tree< Key, Value, Comparator >::Iterator::operator*() const
{
  assert(node_ != nullptr);
  return node_->value_pair_;
}

template< typename Key, typename Value, typename Comparator >
const std::pair< const Key, Value > * Tree< Key, Value, Comparator >::Iterator::operator->() const
{
  assert(node_ != nullptr);
  return std::addressof(node_->value_pair_);
}

template< typename Key, typename Value, typename Comparator >
bool Tree< Key, Value, Comparator >::Iterator::operator!=(const Iterator & rhs) const
{
  return !(*this == rhs);
}

template< typename Key, typename Value, typename Comparator >
bool Tree< Key, Value, Comparator >::Iterator::operator==(const Iterator & rhs) const
{
  return *this == rhs;
}

template< typename Key, typename Value, typename Comparator >
Tree< Key, Value, Comparator >::Tree() : root_(nullptr), cmp_(Comparator()), size_(0) {}

template< typename Key, typename Value, typename Comparator >
Tree< Key, Value, Comparator >::Tree(const Tree & otherTree) : root_(nullptr), cmp_(Comparator()), size_(0)
{
  root_ = nullptr;
  cmp_ = otherTree.cmp_;
  ConstIterator iter = otherTree.begin();
  while (iter != end())
  {
   insert(iter.node_->value_pair_.first, iter.node_->value_pair_.second);
   iter++;
  }
}

template< typename Key, typename Value, typename Comparator >
Tree< Key, Value, Comparator >::Tree(Tree && otherTree) : root_(otherTree.root_), cmp_(Comparator()), size_(otherTree.size_)
{
  otherTree.root_ = nullptr;
  otherTree.size_ = 0;
}

template< typename Key, typename Value, typename Comparator >
Tree< Key, Value, Comparator >::~Tree()
{
  clear(root_);
}

template< typename Key, typename Value, typename Comparator >
typename Tree< Key, Value, Comparator >::ConstIterator Tree< Key, Value, Comparator >::begin() const noexcept
{
  ConstIterator temp = ConstIterator(root_, root_);
  while (temp.node_->left_ != nullptr)
  {
    temp--;
  }
  return temp;
}

template< typename Key, typename Value, typename Comparator >
typename Tree< Key, Value, Comparator >::ConstIterator Tree< Key, Value, Comparator >::end() const noexcept
{
  ConstIterator temp = ConstIterator(root_, root_);
  while (temp.node_->right_ != nullptr)
  {
    temp++;
  }
  return temp;
}

template< typename Key, typename Value, typename Comparator >
typename Tree< Key, Value, Comparator >::Iterator Tree< Key, Value, Comparator >::begin() noexcept
{
  Iterator temp = Iterator(root_, root_);
  while (temp.node_->left_ != nullptr)
  {
    temp--;
  }
  return temp;
}

template< typename Key, typename Value, typename Comparator >
typename Tree< Key, Value, Comparator >::Iterator Tree< Key, Value, Comparator >::end() noexcept
{
  Iterator temp = Iterator(root_, root_);
  while (temp.node_->right_ != nullptr)
  {
    temp++;
  }
  return temp;
}

template< typename Key, typename Value, typename Comparator >
void Tree< Key, Value, Comparator >::clear(Node * node)
{
  if (node != nullptr)
  {
    clear(node->left_);
    clear(node->right_);
    delete node;
  }
}

template< typename Key, typename Value, typename Comparator >
void Tree< Key, Value, Comparator >::swap(Tree & otherTree)
{
  std::swap(otherTree.root_, root_);
  std::swap(otherTree.cmp_, cmp_);
  std::swap(otherTree.size_, size_);
}

template< typename Key, typename Value, typename Comparator >
size_t Tree< Key, Value, Comparator >::getSize() const noexcept
{
  return size_;
}

template< typename Key, typename Value, typename Comparator >
bool Tree< Key, Value, Comparator >::isEmpty() const noexcept
{
  return getSize() == 0 ? true : false;
}

template< typename Key, typename Value, typename Comparator >
typename Tree< Key, Value, Comparator >::Node * Tree< Key, Value, Comparator >::LLrotation(Node * prevRoot)
{
  Node * new_root = prevRoot->right_;
  Node * left_subTree = new_root->left_;
  new_root->left_ = prevRoot;
  prevRoot->right_ = left_subTree;
  updateHeight(prevRoot);
  updateHeight(new_root);
  return new_root;
}

template< typename Key, typename Value, typename Comparator >
typename Tree< Key, Value, Comparator >::Node * Tree< Key, Value, Comparator >::RRrotation(Node * prevRoot)
{
  Node * new_root = prevRoot->left_;
  Node * left_subTree = new_root->right_;
  new_root->right_ = prevRoot;
  prevRoot->left_ = left_subTree;
  updateHeight(prevRoot);
  updateHeight(new_root);
  return new_root;
}
template< typename Key, typename Value, typename Comparator >
void Tree< Key, Value, Comparator >::updateHeight(Node* node)
{
  if (node == nullptr)
  {
    throw std::logic_error("Node is null");
  }
  int leftHeight = (node->left_ != nullptr) ? node->left_->height_ : -1;
  int rightHeight = (node->right_ != nullptr) ? node->right_->height_ : -1;
  node->height_ = 1 + std::max(leftHeight, rightHeight);
}

template< typename Key, typename Value, typename Comparator >
typename Tree< Key, Value, Comparator >::Node * Tree< Key, Value, Comparator >::balance(Node* node)
{
  updateHeight(node);
  int balanceFactor = (node->left_ ? node->left_->height_ : -1) -
  (node->right_ ? node->right_->height_ : -1);
  if (balanceFactor > 1)
  {
    if ((node->left_->right_ ? node->left_->right_->height_ : -1) >
      (node->left_->left_ ? node->left_->left_->height_ : -1))
    {
      node->left_ = LLrotation(node->left_);
    }
    return RRrotation(node);
  }
  if (balanceFactor < -1)
  {
    if ((node->right_->left_ ? node->right_->left_->height_ : -1) >
      (node->right_->right_ ? node->right_->right_->height_ : -1))
    {
      node->right_ = RRrotation(node->right_);
    }
    return LLrotation(node);
  }
  
  return node;
}

template< typename Key, typename Value, typename Comparator >
typename Tree< Key, Value, Comparator >::Node * Tree< Key, Value, Comparator >::insert(Node* node, const Key& key, const Value& value)
{
  if (node == nullptr)
  {
    ++size_;
    return new Node(key, value);
  }
  
  if (cmp_(key, node->value_pair_.first))
  {
    node->left_ = insert(node->left_, key, value);
  }
  else if (cmp_(node->value_pair_.first, key))
  {
    node->right_ = insert(node->right_, key, value);
  }
  else
  {
    throw std::logic_error("Duplicate key");
  }
  return balance(node);
}

template< typename Key, typename Value, typename Comparator >
void Tree< Key, Value, Comparator >::insert(const Key& key, const Value& value)
{
  root_ = insert(root_, key, value);
}

template< typename Key, typename Value, typename Comparator >
Value & Tree< Key, Value, Comparator >::at(const Key & key)
{
  ConstIterator iter = begin();
  while (iter != end())
  {
   if (find(key).node_ != nullptr)
   {
     return find(key).node_->value_pair_.second;
   }
   iter++;
  }
  throw std::out_of_range("no such key");
}

template< typename Key, typename Value, typename Comparator >
typename Tree< Key, Value, Comparator >::Iterator Tree< Key, Value, Comparator >::find(const Key & key)
{
  Iterator iter = begin();
  while (iter != end())
  {
   if (iter.node_->value_pair_.first == key)
   {
     return iter;
   }
   iter++;
  }
  return Iterator(root_, nullptr);
}

#endif

