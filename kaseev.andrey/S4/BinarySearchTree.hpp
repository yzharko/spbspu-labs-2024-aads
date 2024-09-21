#ifndef BinarySearchTree_HPP
#define BinarySearchTree_HPP

#include <iostream>
#include <map>
#include <string>
#include <memory>
#include <iosfwd>

namespace kaseev {

  template< typename Key, typename Value, typename Compare >
  class BST {
  public:
    BST();
    BST(const BST &other);
    BST(const BST &&other) noexcept;
    BST &operator=(const BST &other);
    BST &operator=(BST &&other) noexcept;
    ~BST();

    class Iterator;
    class ConstIterator;

    void push(const Key &key, const Value &value);
    Value &operator[](const Key &key);
    const Value &operator[](const Key &key) const;
    void drop(const Key &key);
    bool empty() const noexcept;
    size_t size() const;
    void clear();
    void swap(BST &other) noexcept;
    ConstIterator begin() const;
    ConstIterator end() const;
    Iterator begin();
    Iterator end();
    ConstIterator find(const Key &key) const;
    std::pair< ConstIterator, ConstIterator > equalRange(const Key &key) const;
    size_t count(const Key &key) const;
    void insert(const std::pair< Key, Value > &pair);
    void erase(const Key &key);

  private:
    struct Node {
      std::pair< Key, Value > data;
      std::shared_ptr< Node > left;
      std::shared_ptr< Node > right;
      std::weak_ptr< Node > parent;
      int height;

      Node(std::shared_ptr< Node > &node);
      Node(const Key &key, const Value &value, std::shared_ptr< Node > parent = nullptr);
    };

    std::shared_ptr< Node > root;
    size_t nodeCount;
    Compare comp;

    std::shared_ptr< Node > insert(std::shared_ptr< Node > node, const Key &key, const Value &value, std::shared_ptr< Node > parent);
    std::shared_ptr< Node > erase(std::shared_ptr< Node > node, const Key &key);
    std::shared_ptr< Node > clone(const Node *node) const;
    std::shared_ptr< Node > balance(std::shared_ptr< Node > n);
    std::shared_ptr< Node > rotateRight(std::shared_ptr< Node > y);
    std::shared_ptr< Node > rotateLeft(std::shared_ptr< Node > x);

    Node *minValueNode(Node *node) const;
    Node *find(Node *node, const Key &key) const;

    int height(Node *n) const;
    int balanceFactor(Node *n) const;
    void updateHeight(Node *n);
  };
}

template< typename Key, typename Value, typename Compare >
kaseev::BST< Key, Value, Compare >::BST()
{
  root = nullptr;
  nodeCount = 0;
}

template< typename Key, typename Value, typename Compare >
kaseev::BST< Key, Value, Compare >::BST(const BST &other) :
    nodeCount(other.nodeCount),
    comp(other.comp)
{
  nodeCount = other.nodeCount;
  comp = other.comp;
  root = clone(other.root.get());
}

template< typename Key, typename Value, typename Compare >
kaseev::BST< Key, Value, Compare >::BST(const BST &&other) noexcept
{
  root = std::move(other.root);
  nodeCount = other.nodeCount;
  comp = std::move(other.comp);
  other.nodeCount = 0;
}

template< typename Key, typename Value, typename Compare >
kaseev::BST< Key, Value, Compare >::~BST()
{
  clear();
}

template< typename Key, typename Value, typename Compare >
kaseev::BST< Key, Value, Compare > &
kaseev::BST< Key, Value, Compare >::operator=(const BST &other)
{
  if (this == &other) {
    return *this;
  }
  root = clone(other.root.get());
  nodeCount = other.nodeCount;
  comp = other.comp;
  return *this;
}

template< typename Key, typename Value, typename Compare >
kaseev::BST< Key, Value, Compare > &
kaseev::BST< Key, Value, Compare >::operator=(BST &&other) noexcept
{
  if (this == &other) {
    return *this;
  }
  root = std::move(other.root);
  nodeCount = other.nodeCount;
  comp = std::move(other.comp);
  return *this;
}

template< typename Key, typename Value, typename Compare >
void kaseev::BST< Key, Value, Compare >::push(const Key &key, const Value &value)
{
  root = insert(std::move(root), key, value, nullptr);
}

template< typename Key, typename Value, typename Compare >
const Value &kaseev::BST< Key, Value, Compare >::operator[](const Key &key) const
{
  Node *node = find(root.get(), key);
  if (!node) {
    throw std::runtime_error("Key not found");
  }
  return node->data.second;
}

template< typename Key, typename Value, typename Compare >
Value &kaseev::BST< Key, Value, Compare >::operator[](const Key &key)
{
  Node *node = find(root.get(), key);
  if (!node) {
    root = insert(std::move(root), key, Value());
    node = find(root.get(), key);
  }
  return node->data.second;
}

template< typename Key, typename Value, typename Compare >
void kaseev::BST< Key, Value, Compare >::drop(const Key &key)
{
  root = erase(std::move(root), key);
}

template< typename Key, typename Value, typename Compare >
bool kaseev::BST< Key, Value, Compare >::empty() const noexcept
{
  return nodeCount == 0;
}

template< typename Key, typename Value, typename Compare >
size_t kaseev::BST< Key, Value, Compare >::size() const
{
  return nodeCount;
}

template< typename Key, typename Value, typename Compare >
void kaseev::BST< Key, Value, Compare >::clear()
{
  root.reset();
  nodeCount = 0;
}

template< typename Key, typename Value, typename Compare >
typename kaseev::BST< Key, Value, Compare >::ConstIterator
kaseev::BST< Key, Value, Compare >::begin() const
{
  if (!root) {
    return ConstIterator(Iterator());
  }
  return ConstIterator(Iterator(minValueNode(root.get())));
}

template< typename Key, typename Value, typename Compare >
typename kaseev::BST< Key, Value, Compare >::ConstIterator
kaseev::BST< Key, Value, Compare >::end() const
{
  return ConstIterator(Iterator());
}

template< typename Key, typename Value, typename Compare >
typename kaseev::BST< Key, Value, Compare >::Iterator
kaseev::BST< Key, Value, Compare >::begin()
{
  if (!root) {
    return Iterator();
  }
  return Iterator(minValueNode(root.get()));
}

template< typename Key, typename Value, typename Compare >
typename kaseev::BST< Key, Value, Compare >::Iterator
kaseev::BST< Key, Value, Compare >::end()
{
  return Iterator();
}

template< typename Key, typename Value, typename Compare >
typename kaseev::BST< Key, Value, Compare >::ConstIterator
kaseev::BST< Key, Value, Compare >::find(const Key &key) const
{
  Node *current = root.get();
  while (current) {
    if (comp(key, current->data.first)) {
      current = current->left.get();
    } else if (comp(current->data.first, key)) {
      current = current->right.get();
    } else {
      return ConstIterator(Iterator(current));
    }
  }
  return end();
}

template< typename Key, typename Value, typename Compare >
std::pair<
    typename kaseev::BST< Key, Value, Compare >::ConstIterator,
    typename kaseev::BST< Key, Value, Compare >::ConstIterator
> kaseev::BST< Key, Value, Compare >::equalRange(const Key &key) const
{
  auto node = root;
  while (node->left) {
    node = node->left;
  }

  auto lower = Iterator(node);
  while (lower != Iterator(nullptr) && comp(lower->first, key)) {
    ++lower;
  }
  Iterator upper = lower;
  while (upper != Iterator(nullptr) && !comp(key, upper->first)) {
    ++upper;
  }
  return std::make_pair(ConstIterator(lower), ConstIterator(upper));
}

template< typename Key, typename Value, typename Compare >
size_t kaseev::BST< Key, Value, Compare >::count(const Key &key) const
{
  return find(key) != end() ? 1 : 0;
}

template< typename Key, typename Value, typename Compare >
void kaseev::BST< Key, Value, Compare >::insert(const std::pair< Key, Value > &pair)
{
  push(pair.first, pair.second);
}

template< typename Key, typename Value, typename Compare >
void kaseev::BST< Key, Value, Compare >::erase(const Key &key)
{
  drop(key);
}

template< typename Key, typename Value, typename Compare >
int kaseev::BST< Key, Value, Compare >::height(BST::Node *n) const
{
  return n ? n->height : 0;
}

template< typename Key, typename Value, typename Compare >
int kaseev::BST< Key, Value, Compare >::balanceFactor(BST::Node *n) const
{
  return n ? height(n->left.get()) - height(n->right.get()) : 0;
}

template< typename Key, typename Value, typename Compare >
void kaseev::BST< Key, Value, Compare >::updateHeight(BST::Node *n)
{
  if (n) {
    n->height = 1 + std::max(height(n->left.get()), height(n->right.get()));
  }
}

template< typename Key, typename Value, typename Compare >
std::shared_ptr< typename kaseev::BST< Key, Value, Compare >::Node >
kaseev::BST< Key, Value, Compare >::rotateRight(std::shared_ptr< Node > y)
{
  std::shared_ptr< Node > x = std::move(y->left);
  y->left = std::move(x->right);
  if (y->left) {
    y->left->parent = y;
  }
  x->right = std::move(y);
  x->right->parent = x;
  updateHeight(x->right.get());
  updateHeight(x.get());
  x->parent = x->right->parent.lock();
  return x;
}

template< typename Key, typename Value, typename Compare >
std::shared_ptr< typename kaseev::BST< Key, Value, Compare >::Node >
kaseev::BST< Key, Value, Compare >::rotateLeft(std::shared_ptr< Node > x)
{
  std::shared_ptr< Node > y = std::move(x->right);
  x->right = std::move(y->left);
  if (x->right) {
    x->right->parent = x;
  }
  y->left = std::move(x);
  y->left->parent = y;
  updateHeight(y->left.get());
  updateHeight(y.get());
  y->parent = y->left->parent.lock();
  return y;
}

template< typename Key, typename Value, typename Compare >
std::shared_ptr< typename kaseev::BST< Key, Value, Compare >::Node >
kaseev::BST< Key, Value, Compare >::balance(std::shared_ptr< Node > n)
{
  updateHeight(n.get());
  if (balanceFactor(n.get()) > 1) {
    if (balanceFactor(n->left.get()) < 0) {
      n->left = rotateLeft(std::move(n->left));
    }
    auto newRoot = rotateRight(std::move(n));
    newRoot->parent.reset();
    return newRoot;
  }
  if (balanceFactor(n.get()) < -1) {
    if (balanceFactor(n->right.get()) > 0) {
      n->right = rotateRight(std::move(n->right));
    }
    auto newRoot = rotateLeft(std::move(n));
    newRoot->parent.reset();
    return newRoot;
  }
  return n;
}

template< typename Key, typename Value, typename Compare >
std::shared_ptr< typename kaseev::BST< Key, Value, Compare >::Node >
kaseev::BST< Key, Value, Compare >::insert(std::shared_ptr< Node > node, const Key &key, const Value &value, std::shared_ptr< Node > parent)
{
  if (!node) {
    ++nodeCount;
    return std::make_shared< Node >(key, value, parent);
  }
  if (comp(key, node->data.first)) {
    node->left = insert(node->left, key, value, node);
  } else if (comp(node->data.first, key)) {
    node->right = insert(node->right, key, value, node);
  } else {
    node->data.second = value;
  }
  return balance(node);
}

template< typename Key, typename Value, typename Compare >
std::shared_ptr< typename kaseev::BST< Key, Value, Compare >::Node >
kaseev::BST< Key, Value, Compare >::erase(std::shared_ptr< Node > node, const Key &key)
{
  if (!node) {
    return nullptr;
  }
  if (comp(key, node->data.first)) {
    node->left = erase(std::move(node->left), key);
  } else if (comp(node->data.first, key)) {
    node->right = erase(std::move(node->right), key);
  } else {
    if (!node->left) return std::move(node->right);
    if (!node->right) return std::move(node->left);
    Node *min = minValueNode(node->right.get());
    node->data.second = std::move(min->data.second);
    node->data.first = min->data.first;
    node->right = erase(std::move(node->right), min->data.first);
  }
  return balance(std::move(node));
}

template< typename Key, typename Value, typename Compare >
typename kaseev::BST< Key, Value, Compare >::Node *
kaseev::BST< Key, Value, Compare >::minValueNode(BST::Node *node) const
{
  while (node->left) {
    node = node->left.get();
  }
  return node;
}

template< typename Key, typename Value, typename Compare >
typename kaseev::BST< Key, Value, Compare >::Node *
kaseev::BST< Key, Value, Compare >::find(BST::Node *node, const Key &key) const
{
  if (!node) {
    return nullptr;
  }
  if (comp(key, node->data.first)) {
    return find(node->left.get(), key);
  }
  if (comp(node->data.first, key)) {
    return find(node->right.get(), key);
  }
  return node;
}

template< typename Key, typename Value, typename Compare >
std::shared_ptr< typename kaseev::BST< Key, Value, Compare >::Node >
kaseev::BST< Key, Value, Compare >::clone(const BST::Node *node) const
{
  if (!node) {
    return nullptr;
  }
  auto newNode = std::make_unique< Node >(node->data.first, node->data.second);
  newNode->left = clone(node->left.get());
  newNode->right = clone(node->right.get());
  return newNode;
}

#endif
