#ifndef AVLtree_HPP
#define AVLtree_HPP
#include <iostream>
#include <memory>
#include <map>
#include <utility>
#include <iterator>
#include <stack>
#include <functional>
#include "stack.hpp"
#include "queue.hpp"

namespace sadofeva
{
  template <typename Key, typename Value, typename Compare = std::less<Key>>
  class BinarySearchTree {
  private:
    struct Node {
      std::pair<Key, Value> data;
      std::unique_ptr<Node> left, right;
      size_t height;
      Node(const Key& k, const Value& v) : data{ k, v }, left{ nullptr }, right{ nullptr } {}
    };

    std::unique_ptr<Node> root;
    size_t tree_size;
    Compare comp;

    Node* insert(Node* node, const Key& key, const Value& value);
    Node* find(Node* node, const Key& key) const;
    Node* remove(Node* node, const Key& key);
    Node* findMin(Node* node) const;
    Node* removeMin(Node* node);
    void inorder(Node* node, std::ostream& os) const;
    size_t height(Node* node);
    size_t getBalance(Node* node);
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);

  public:
    BinarySearchTree();
    void push(const Key& k, const Value& v);
    Value get(const Key& k) const;
    bool drop(const Key& k);
    size_t size() const;
    bool empty() const;
    void clear();
    void swap(BinarySearchTree& other);

    class Iterator;
    Iterator begin();
    Iterator end();

    class ConstIterator;
    ConstIterator cbegin() const;
    ConstIterator cend() const;

    template < typename F>
    F traverse_lnr(F f) const;

    template < typename F>
    F traverse_rnl(F f) const;

    template <typename F>
    F traverse_breadth(F f) const;

    void print(std::ostream& os) const;
  };

}

using namespace sadofeva;

template <typename Key, typename Value, typename Compare>
size_t BinarySearchTree<Key, Value, Compare>::height(Node* node)
{
  return node ? node->height : 0;
}

template <typename Key, typename Value, typename Compare>
size_t BinarySearchTree<Key, Value, Compare>::getBalance(Node* node)
{
  return node ? height(node->left.get()) - height(node->right.get()) : 0;
}

template <typename Key, typename Value, typename Compare>
typename BinarySearchTree<Key, Value, Compare>::Node* BinarySearchTree<Key, Value, Compare>::rotateRight(Node* y)
{
  Node* x = y->left.release();
  Node* T2 = x->right.release();
  x->right.reset(y);
  y->left.reset(T2);

  y->height = std::max(height(y->left.get()), height(y->right.get())) + 1;
  x->height = std::max(height(x->left.get()), height(x->right.get())) + 1;

  return x;
}

template <typename Key, typename Value, typename Compare>
typename BinarySearchTree<Key, Value, Compare>::Node* BinarySearchTree<Key, Value, Compare>::rotateLeft(Node* x)
{
  Node* y = x->right.release();
  Node* T2 = y->left.release();

  y->left.reset(x);
  x->right.reset(T2);

  x->height = std::max(height(x->left.get()), height(x->right.get())) + 1;
  y->height = std::max(height(y->left.get()), height(y->right.get())) + 1;

  return y;
}

template <typename Key, typename Value, typename Compare>
class BinarySearchTree<Key, Value, Compare>::Iterator
{
private:
  Node* current;
  std::stack<Node*> nodeStack;
  void pushLeft(Node* node);
public:
  friend class BinarySearchTree<Key, Value, Compare>;
  using iterator_category = std::forward_iterator_tag;
  using value_type = std::pair<Key, Value>;
  using difference_type = std::ptrdiff_t;
  using pointer = std::pair<Key, Value>*;
  using reference = std::pair<Key, Value>&;

  Iterator(Node* rootNode);
  Iterator operator++();
  Iterator operator++(int);

  reference operator*() const { return current->data; }
  pointer operator->() const { return &(current->data); }

  bool operator!=(const Iterator& other) const { return current != other.current; }
  bool operator==(const Iterator& other) const { return current == other.current; };
};


template <typename Key, typename Value, typename Compare>
void BinarySearchTree<Key, Value, Compare>::Iterator::pushLeft(Node* node)
{
  while (node)
  {
    nodeStack.push(node);
    node = node->left.get();
  }
}

template <typename Key, typename Value, typename Compare>
typename BinarySearchTree<Key, Value, Compare>::Iterator::Iterator BinarySearchTree<Key, Value, Compare>::Iterator::operator++(int)
{
  if (nodeStack.empty())
  {
    current = nullptr;
    return *this;
  }
  current = nodeStack.top();
  nodeStack.pop();
  if (current->right)
  {
    pushLeft(current->right.get());
  }
  return *this;
}

template <typename Key, typename Value, typename Compare>
typename BinarySearchTree<Key, Value, Compare>::Iterator::Iterator BinarySearchTree<Key, Value, Compare>::Iterator::operator++()
{
  Iterator tmp = *this;
  (*this)++;
  return tmp;
}

template <typename Key, typename Value, typename Compare>
BinarySearchTree<Key, Value, Compare>::Iterator::Iterator(Node* rootNode) : current(nullptr)
{
  pushLeft(rootNode);
  ++(*this);
}

template <typename Key, typename Value, typename Compare>
class BinarySearchTree<Key, Value, Compare>::ConstIterator
{
private:
  const Node* current;
  std::stack<const Node*> nodeStack;
  void pushLeft(const Node* node);

public:
  friend class BinarySearchTree<Key, Value, Compare>;
  using iterator_category = std::forward_iterator_tag;
  using value_type = const std::pair<Key, Value>;
  using difference_type = std::ptrdiff_t;
  using pointer = const std::pair<Key, Value>*;
  using reference = const std::pair<Key, Value>&;

  ConstIterator(const Node* rootNode);
  ConstIterator& operator++();
  ConstIterator operator++(int);

  reference operator*() const { return current->data; }
  pointer operator->() const { return &(current->data); }

  bool operator!=(const ConstIterator& other) const { return current != other.current; }
  bool operator==(const ConstIterator& other) const { return current == other.current; }
};

template <typename Key, typename Value, typename Compare>
void BinarySearchTree<Key, Value, Compare>::ConstIterator::pushLeft(const Node* node)
{
  while (node)
  {
    nodeStack.push(node);
    node = node->left.get();
  }
}

template <typename Key, typename Value, typename Compare>
BinarySearchTree<Key, Value, Compare>::ConstIterator::ConstIterator(const Node* rootNode) : current(nullptr)
{
  pushLeft(rootNode);
  ++(*this);
}

template <typename Key, typename Value, typename Compare>
typename BinarySearchTree<Key, Value, Compare>::ConstIterator::ConstIterator
BinarySearchTree<Key, Value, Compare>::ConstIterator::ConstIterator::operator++(int)
{
  ConstIterator tmp = *this;
  ++(*this);
  return tmp;
}

template <typename Key, typename Value, typename Compare>
typename BinarySearchTree<Key, Value, Compare>::ConstIterator::ConstIterator&
BinarySearchTree<Key, Value, Compare>::ConstIterator::operator++()
{
  if (nodeStack.empty()) {
    current = nullptr;
    return *this;
  }
  current = nodeStack.top();
  nodeStack.pop();
  if (current->right) {
    pushLeft(current->right.get());
  }
  return *this;
}

template <typename Key, typename Value, typename Compare>
BinarySearchTree<Key, Value, Compare>::BinarySearchTree() : root(nullptr), tree_size(0), comp(Compare()) {}

template <typename Key, typename Value, typename Compare>
typename BinarySearchTree<Key, Value, Compare>::Node*
BinarySearchTree<Key, Value, Compare>::insert(Node* node, const Key& key, const Value& value) {
  if (!node) {
    ++tree_size;
    return new Node(key, value);
  }
  if (comp(key, node->data.first)) {
    node->left.reset(insert(node->left.release(), key, value));
  }
  else if (comp(node->data.first, key)) {
    node->right.reset(insert(node->right.release(), key, value));
  }
  else 
  {
    node->data.second = value;
    return node;
  }
  node->height = 1 + std::max(height(node->left.get()), height(node->right.get()));

  int balance = getBalance(node);

  if (balance > 1 && comp(key, node->left->data.first)) {
    return rotateRight(node);
  }

  if (balance < -1 && comp(node->right->data.first, key)) {
    return rotateLeft(node);
  }

  if (balance > 1 && comp(node->left->data.first, key)) {
    node->left.reset(rotateLeft(node->left.release()));
    return rotateRight(node);
  }

  if (balance < -1 && comp(key, node->right->data.first)) {
    node->right.reset(rotateRight(node->right.release()));
    return rotateLeft(node);
  }

  return node;
}

template <typename Key, typename Value, typename Compare>
void BinarySearchTree<Key, Value, Compare>::push(const Key& k, const Value& v) {
    root.reset(insert(root.release(), k, v));
}

template <typename Key, typename Value, typename Compare>
typename BinarySearchTree<Key, Value, Compare>::Node*
BinarySearchTree<Key, Value, Compare>::find(Node* node, const Key& key) const {
  if (!node) return nullptr;
  if (comp(key, node->data.first)) {
    return find(node->left.get(), key);
  }
  else if (comp(node->data.first, key)) {
    return find(node->right.get(), key);
  }
  return node;
}

template <typename Key, typename Value, typename Compare>
Value BinarySearchTree<Key, Value, Compare>::get(const Key& k) const {
  Node* node = find(root.get(), k);
  if (node) return node->data.second;
  throw std::out_of_range("Key not found");
}

template <typename Key, typename Value, typename Compare>
bool BinarySearchTree<Key, Value, Compare>::drop(const Key& k) {
  if (find(root.get(), k)) {
    root.reset(remove(root.release(), k));
    --tree_size;
    return true;
  }
  return false;
}

template <typename Key, typename Value, typename Compare>
typename BinarySearchTree<Key, Value, Compare>::Node*
BinarySearchTree<Key, Value, Compare>::remove(Node* node, const Key& key) {
  if (!node) return nullptr;
  if (comp(key, node->data.first)) {
    node->left.reset(remove(node->left.release(), key));
  }
  else if (comp(node->data.first, key)) {
    node->right.reset(remove(node->right.release(), key));
  }
  else {
    if (!node->left) return node->right.release();
    if (!node->right) return node->left.release();
    Node* minNode = findMin(node->right.get());
    node->data = std::move(minNode->data);
    node->right.reset(removeMin(node->right.release()));
  }
  return node;
}

template <typename Key, typename Value, typename Compare>
typename BinarySearchTree<Key, Value, Compare>::Node*
BinarySearchTree<Key, Value, Compare>::findMin(Node* node) const {
  while (node->left) node = node->left.get();
  return node;
}

template <typename Key, typename Value, typename Compare>
typename BinarySearchTree<Key, Value, Compare>::Node* BinarySearchTree<Key, Value, Compare>::removeMin(Node* node) {
  if (!node->left) return node->right.release();
  node->left.reset(removeMin(node->left.release()));
  return node;
}

template <typename Key, typename Value, typename Compare>
size_t BinarySearchTree<Key, Value, Compare>::size() const {
  return tree_size;
}

template <typename Key, typename Value, typename Compare>
bool BinarySearchTree<Key, Value, Compare>::empty() const {
  return tree_size == 0;
}

template <typename Key, typename Value, typename Compare>
void BinarySearchTree<Key, Value, Compare>::clear() {
  root.reset();
  tree_size = 0;
}

template <typename Key, typename Value, typename Compare>
void BinarySearchTree<Key, Value, Compare>::swap(BinarySearchTree& other) {
  std::swap(root, other.root);
  std::swap(tree_size, other.tree_size);
  std::swap(comp, other.comp);
}

template <typename Key, typename Value, typename Compare>
typename BinarySearchTree<Key, Value, Compare>::Iterator BinarySearchTree<Key, Value, Compare>::begin() {
  return Iterator(root.get());
}

// End iterator
template <typename Key, typename Value, typename Compare>
typename BinarySearchTree<Key, Value, Compare>::Iterator BinarySearchTree<Key, Value, Compare>::end() {
  return Iterator(nullptr);
}

// Begin const iterator
template <typename Key, typename Value, typename Compare>
typename BinarySearchTree<Key, Value, Compare>::ConstIterator
BinarySearchTree<Key, Value, Compare>::cbegin() const {
  return ConstIterator(root.get());
}

// End const iterator
template <typename Key, typename Value, typename Compare>
typename BinarySearchTree<Key, Value, Compare>::ConstIterator
BinarySearchTree<Key, Value, Compare>::cend() const {
  return ConstIterator(nullptr);
}

// In-order traversal print
template <typename Key, typename Value, typename Compare>
void BinarySearchTree<Key, Value, Compare>::print(std::ostream& os) const {
  if (empty()) {
    os << "<EMPTY>\n";
  }
  else {
    std::function<void(Node*)> inorder_print = [&](Node* node) {
      if (!node) return;
      inorder_print(node->left.get());
      os << node->data.first << " " << node->data.second << " ";
      inorder_print(node->right.get());
      };
    inorder_print(root.get());
    os << "\n";
  }
}


template <typename Key, typename Value, typename Compare>
template <typename F>
F BinarySearchTree<Key, Value, Compare>::traverse_lnr(F f) const
{
  Stack< Node* > stack;
  stack.push(root.get());
  Node* current = root.get();
  while (!stack.empty())
  {
    while (current->left)
    {
      stack.push(current->left.get());
      current = current->left.get();
    }
    current = stack.top();
    stack.drop();
    f(current->data);
    if (current->right)
    {
      current = current->right.get();
      stack.push(current);
    }
  }
  return f;
}

template <typename Key, typename Value, typename Compare>
template <typename F>
F BinarySearchTree<Key, Value, Compare>::traverse_rnl(F f) const
{
  Stack< Node* > stack;
  stack.push(root.get());
  Node* current = root.get();
  while (!stack.empty())
  {
    while (current->right)
    {
      stack.push(current->right.get());
      current = current->right.get();
    }
    current = stack.front();
    stack.drop();
    f(current->data);
    if (current->left)
    {
      current = current->left.get();
      stack.push(current);
    }
  }
  return f;
}

template <typename Key, typename Value, typename Compare>
template <typename F>
F BinarySearchTree<Key, Value, Compare>::traverse_breadth(F f) const
{
  if (root == nullptr)
  {
    return f;
  }
  Queue< Node*>  queue;
  queue.push(root.get());
  while (!queue.empty())
  {
    Node* current = queue.next();
    queue.drop();

    f(current->data);

    if (current->left != nullptr)
    {
      queue.push(current->left.get());
    }
    if (current->right != nullptr)
    {
      queue.push(current->right.get());
    }
  }
  return f;
}

#endif
