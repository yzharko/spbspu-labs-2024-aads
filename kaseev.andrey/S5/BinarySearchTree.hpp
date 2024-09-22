#ifndef BST_HPP
#define BST_HPP

#include <iostream>
#include <map>
#include <string>
#include <memory>
#include <iosfwd>
#include <stack>
#include <queue>

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
    size_t count(const Key &key) const;
    void erase(const Key &key);
    void insert(const std::pair< Key, Value > &pair);
    template< typename F >
    F traverse_lnr(F f) const;
    template< typename F >
    F traverse_rnl(F f) const;
    template< typename F >
    F traverse_breadth(F f) const;

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
    int height(Node *n) const;
    int balanceFactor(Node *n) const;
    void updateHeight(Node *n);
    std::shared_ptr< Node > rotateRight(std::shared_ptr< Node > y);
    std::shared_ptr< Node > rotateLeft(std::shared_ptr< Node > x);
    std::shared_ptr< Node > balance(std::shared_ptr< Node > n);
    std::shared_ptr< Node >
    insert(std::shared_ptr< Node > node, const Key &key, const Value &value, std::shared_ptr< Node > parent);
    std::shared_ptr< Node > erase(std::shared_ptr< Node > node, const Key &key);
    Node *minValueNode(Node *node) const;
    Node *find(Node *node, const Key &key) const;
    std::shared_ptr< Node > clone(const Node *node) const;
  };
}
template< typename Key, typename Value, typename Compare >
class kaseev::BST< Key, Value, Compare >::Iterator
    : public std::iterator< std::bidirectional_iterator_tag, std::pair< Key, Value > > {
private:
  Node *current;
  Node *findNext(Node *node) const;
  Node *findPrev(Node *node) const;
public:
  friend class BST;

  using kvPair = std::pair< Key, Value >;

  Iterator();
  explicit Iterator(Node *node);
  Iterator &operator++();
  Iterator operator++(int);
  Iterator &operator--();
  Iterator operator--(int);
  kvPair &operator*();
  kvPair *operator->();
  const kvPair &operator*() const;
  const kvPair *operator->() const;
  bool operator==(const Iterator &other) const;
  bool operator!=(const Iterator &other) const;
};

template< typename Key, typename Value, typename Compare >
class kaseev::BST< Key, Value, Compare >::ConstIterator
    : public std::iterator< std::bidirectional_iterator_tag, std::pair< Key, Value > > {
private:
  Iterator iter;
public:
  friend class BST;

  using kvPair = std::pair< Key, Value >;

  ConstIterator(Iterator it);
  ConstIterator &operator++();
  ConstIterator operator++(int);
  ConstIterator &operator--();
  ConstIterator operator--(int);
  const kvPair &operator*() const;
  const kvPair *operator->() const;
  bool operator==(const ConstIterator &other) const;
  bool operator!=(const ConstIterator &other) const;
};

template< typename Key, typename Value, typename Compare >
kaseev::BST< Key, Value, Compare >::ConstIterator::ConstIterator(
    kaseev::BST< Key, Value, Compare >::Iterator it)
{
  iter = it;
}

template< typename Key, typename Value, typename Compare >
kaseev::BST< Key, Value, Compare >::BST()
{
  root = nullptr;
  nodeCount = 0;
}

template< typename Key, typename Value, typename Compare >
kaseev::BST< Key, Value, Compare >::Node::Node(const Key &key, const Value &value,
                                               std::shared_ptr< Node > parent)
{
  data = std::pair< Key, Value >(key, value);
  left = nullptr;
  right = nullptr;
  this->parent = parent;
  height = 1;
}

template< typename Key, typename Value, typename Compare >
kaseev::BST< Key, Value, Compare >::Node::Node(std::shared_ptr< Node > &node)
{
  data = node->data;
  left = std::move(node->left);
  right = std::move(node->right);
  parent = node->parent.lock();
  height = node->height;
}

template< typename Key, typename Value, typename Compare >
kaseev::BST< Key, Value, Compare >::~BST()
{
  clear();
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
void kaseev::BST< Key, Value, Compare >::swap(BST &other) noexcept
{
  std::swap(root, other.root);
  std::swap(nodeCount, other.nodeCount);
  std::swap(comp, other.comp);
}

template< typename Key, typename Value, typename Compare >
kaseev::BST< Key, Value, Compare >::Iterator::Iterator()
{
  current = nullptr;
}

template< typename Key, typename Value, typename Compare >
kaseev::BST< Key, Value, Compare >::Iterator::Iterator(
    BST< Key, Value, Compare >::Node *node)
{
  current = node;
}

template< typename Key, typename Value, typename Compare >
std::pair< Key, Value > &kaseev::BST< Key, Value, Compare >::Iterator::operator*()
{
  return current->data;
}

template< typename Key, typename Value, typename Compare >
const std::pair< Key, Value > &kaseev::BST< Key, Value, Compare >::Iterator::operator*() const
{
  return current->data;
}

template< typename Key, typename Value, typename Compare >
std::pair< Key, Value > *kaseev::BST< Key, Value, Compare >::Iterator::operator->()
{
  return &current->data;
}

template< typename Key, typename Value, typename Compare >
const std::pair< Key, Value > *kaseev::BST< Key, Value, Compare >::Iterator::operator->() const
{
  return &current->data;
}

template< typename Key, typename Value, typename Compare >
typename kaseev::BST< Key, Value, Compare >::Iterator &
kaseev::BST< Key, Value, Compare >::Iterator::operator++()
{
  current = findNext(current);
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename kaseev::BST< Key, Value, Compare >::Iterator
kaseev::BST< Key, Value, Compare >::Iterator::operator++(int)
{
  Iterator temp = *this;
  ++(*this);
  return temp;
}

template< typename Key, typename Value, typename Compare >
typename kaseev::BST< Key, Value, Compare >::Iterator &
kaseev::BST< Key, Value, Compare >::Iterator::operator--()
{
  current = findPrev(current);
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename kaseev::BST< Key, Value, Compare >::Iterator
kaseev::BST< Key, Value, Compare >::Iterator::operator--(int)
{
  ConstIterator temp = *this;
  --(*this);
  return temp;
}

template< typename Key, typename Value, typename Compare >
bool
kaseev::BST< Key, Value, Compare >::Iterator::operator!=(const BST::Iterator &other) const
{
  return current != other.current;
}

template< typename Key, typename Value, typename Compare >
bool
kaseev::BST< Key, Value, Compare >::Iterator::operator==(const BST::Iterator &other) const
{
  return current == other.current;
}

template< typename Key, typename Value, typename Compare >
typename kaseev::BST< Key, Value, Compare >::Node *
kaseev::BST< Key, Value, Compare >::Iterator::findNext(Node *node) const
{
  if (node == nullptr) {
    return nullptr;
  }

  if (node->right) {
    node = node->right.get();
    while (node->left) {
      node = node->left.get();
    }
    return node;
  }

  while (node->parent.lock() && node->parent.lock()->right.get() == node) {
    node = node->parent.lock().get();
  }

  return node->parent.lock().get();
}

template< typename Key, typename Value, typename Compare >
typename kaseev::BST< Key, Value, Compare >::Node *
kaseev::BST< Key, Value, Compare >::Iterator::findPrev(Node *node) const
{
  if (node == nullptr) {
    return nullptr;
  }
  if (node->left) {
    node = node->left.get();
    while (node->right) {
      node = node->right.get();
    }
    return node;
  }
  while (node->parent.lock().get() && node->parent.lock().get()->left.get() == node) {
    node = node->parent.lock().get();
  }
  return node->parent.lock().get();
}

template< typename Key, typename Value, typename Compare >
const std::pair< Key, Value > &kaseev::BST< Key, Value, Compare >::ConstIterator::operator*() const
{
  return *iter;
}

template< typename Key, typename Value, typename Compare >
const std::pair< Key, Value > *kaseev::BST< Key, Value, Compare >::ConstIterator::operator->() const
{
  return &(*iter);
}

template< typename Key, typename Value, typename Compare >
typename kaseev::BST< Key, Value, Compare >::ConstIterator &
kaseev::BST< Key, Value, Compare >::ConstIterator::operator++()
{
  ++iter;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename kaseev::BST< Key, Value, Compare >::ConstIterator
kaseev::BST< Key, Value, Compare >::ConstIterator::operator++(int)
{
  ConstIterator tmp = *this;
  ++iter;
  return tmp;
}

template< typename Key, typename Value, typename Compare >
typename kaseev::BST< Key, Value, Compare >::ConstIterator &
kaseev::BST< Key, Value, Compare >::ConstIterator::operator--()
{
  --iter;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename kaseev::BST< Key, Value, Compare >::ConstIterator
kaseev::BST< Key, Value, Compare >::ConstIterator::operator--(int)
{
  ConstIterator tmp = *this;
  --iter;
  return tmp;
}

template< typename Key, typename Value, typename Compare >
bool kaseev::BST< Key, Value, Compare >::ConstIterator::operator==(
    const BST::ConstIterator &other) const
{
  return iter == other.iter;
}

template< typename Key, typename Value, typename Compare >
bool kaseev::BST< Key, Value, Compare >::ConstIterator::operator!=(
    const BST::ConstIterator &other) const
{
  return iter != other.iter;
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
size_t kaseev::BST< Key, Value, Compare >::count(const Key &key) const
{
  return find(key) != end() ? 1 : 0;
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
kaseev::BST< Key, Value, Compare >::insert(std::shared_ptr< Node > node, const Key &key,
                                           const Value &value, std::shared_ptr< Node > parent)
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

template< typename Key, typename Value, typename Compare >
void kaseev::BST< Key, Value, Compare >::insert(const std::pair< Key, Value > &pair)
{
  push(pair.first, pair.second);
}

template< typename Key, typename Value, typename Compare >
template< typename F >
F kaseev::BST< Key, Value, Compare >::traverse_lnr(F f) const
{
  if (!root) {
    return f;
  }

  std::stack < Node * > stack;
  Node *current = root.get();
  while (!stack.empty() || current != nullptr) {
    while (current != nullptr) {
      stack.push(current);
      current = current->left.get();
    }
    current = stack.top();
    stack.pop();
    f(current->data);
    current = current->right.get();
  }
  return f;
}

template< typename Key, typename Value, typename Compare >
template< typename F >
F kaseev::BST< Key, Value, Compare >::traverse_rnl(F f) const
{
  std::stack < Node * > stack;
  Node *current = root.get();
  while (!stack.empty() || current != nullptr) {
    while (current != nullptr) {
      stack.puch(current);
      current = current->right.get();
    }
    current = stack.top();
    stack.pop();
    f(current->data);
    current = current->left.get();
  }
  return f;
}

template< typename Key, typename Value, typename Compare >
template< typename F >
F kaseev::BST< Key, Value, Compare >::traverse_breadth(F f) const
{
  if (!root) {
    return f;
  }
  std::queue < Node * > queue;
  queue.push(root.get());
  while (!queue.empty()) {
    Node *current = queue.front();
    queue.pop();
    f(current->data);
    if (current->left) {
      queue.push(current->left.get());
    }
    if (current->right) {
      queue.push(current->right.get());
    }
  }
  return f;
}

#endif