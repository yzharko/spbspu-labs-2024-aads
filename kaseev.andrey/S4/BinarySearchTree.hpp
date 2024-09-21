#ifndef BinarySearchTree_HPP
#define BinarySearchTree_HPP

#include <iostream>
#include <map>
#include <string>
#include <memory>
#include <iosfwd>
#include <iterator>

namespace kaseev {

  template< typename Key, typename Value, typename Compare = std::less<Key> >
  class BST {
  public:
    BST();
    BST(const BST &other);
    BST(BST &&other) noexcept;
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
    std::pair<ConstIterator, ConstIterator> equalRange(const Key &key) const;
    size_t count(const Key &key) const;
    void insert(const std::pair<Key, Value> &pair);
    void erase(const Key &key);

  private:
    struct Node {
      std::pair<Key, Value> data;
      std::shared_ptr<Node> left;
      std::shared_ptr<Node> right;
      std::weak_ptr<Node> parent;
      int height;

      Node(const Key &key, const Value &value, std::shared_ptr<Node> parent = nullptr);
    };

    std::shared_ptr<Node> root;
    size_t nodeCount;
    Compare comp;

    std::shared_ptr<Node> insert(std::shared_ptr<Node> node, const Key &key, const Value &value, std::shared_ptr<Node> parent);
    std::shared_ptr<Node> erase(std::shared_ptr<Node> node, const Key &key);
    std::shared_ptr<Node> clone(const Node *node) const;
    std::shared_ptr<Node> balance(std::shared_ptr<Node> n);
    std::shared_ptr<Node> rotateRight(std::shared_ptr<Node> y);
    std::shared_ptr<Node> rotateLeft(std::shared_ptr<Node> x);

    Node *minValueNode(Node *node) const;
    Node *find(Node *node, const Key &key) const;

    int height(Node *n) const;
    int balanceFactor(Node *n) const;
    void updateHeight(Node *n);
  };

  template<typename Key, typename Value, typename Compare>
  class BST<Key, Value, Compare>::Iterator : public std::iterator<std::bidirectional_iterator_tag, std::pair<Key, Value>> {
  private:
    Node *current;

  public:
    Iterator();
    explicit Iterator(Node *node);
    Iterator &operator++();
    Iterator operator++(int);
    std::pair<Key, Value> &operator*();
    std::pair<Key, Value> *operator->();
    bool operator==(const Iterator &other) const;
    bool operator!=(const Iterator &other) const;

    Node *findNext(Node *node) const;
  };

  template<typename Key, typename Value, typename Compare>
  class BST<Key, Value, Compare>::ConstIterator : public std::iterator<std::bidirectional_iterator_tag, std::pair<Key, Value>> {
  private:
    Iterator iter;

  public:
    ConstIterator() = default;
    ConstIterator(Iterator it) : iter(it) {}
    ConstIterator &operator++() { ++iter; return *this; }
    ConstIterator operator++(int) { ConstIterator tmp = *this; ++iter; return tmp; }
    const std::pair<Key, Value> &operator*() const { return *iter; }
    const std::pair<Key, Value> *operator->() const { return &(*iter); }
    bool operator==(const ConstIterator &other) const { return iter == other.iter; }
    bool operator!=(const ConstIterator &other) const { return iter != other.iter; }
  };

  template<typename Key, typename Value, typename Compare>
  BST<Key, Value, Compare>::Node::Node(const Key &key, const Value &value, std::shared_ptr<Node> parent)
      : data(key, value), parent(parent), left(nullptr), right(nullptr), height(1) {}

  template<typename Key, typename Value, typename Compare>
  BST<Key, Value, Compare>::BST() : root(nullptr), nodeCount(0), comp(Compare()) {}

  template<typename Key, typename Value, typename Compare>
  BST<Key, Value, Compare>::BST(const BST &other) : comp(other.comp), nodeCount(other.nodeCount) {
    root = clone(other.root.get());
  }

  template<typename Key, typename Value, typename Compare>
  BST<Key, Value, Compare>::BST(BST &&other) noexcept : root(std::move(other.root)), nodeCount(other.nodeCount), comp(std::move(other.comp)) {
    other.nodeCount = 0;
  }

  template<typename Key, typename Value, typename Compare>
  BST<Key, Value, Compare> &BST<Key, Value, Compare>::operator=(const BST &other) {
    if (this == &other) {
      return *this;
    }
    root = clone(other.root.get());
    nodeCount = other.nodeCount;
    comp = other.comp;
    return *this;
  }

  template<typename Key, typename Value, typename Compare>
  BST<Key, Value, Compare> &BST<Key, Value, Compare>::operator=(BST &&other) noexcept {
    if (this == &other) {
      return *this;
    }
    root = std::move(other.root);
    nodeCount = other.nodeCount;
    comp = std::move(other.comp);
    other.nodeCount = 0;
    return *this;
  }

  template<typename Key, typename Value, typename Compare>
  BST<Key, Value, Compare>::~BST() {
    clear();
  }

  template<typename Key, typename Value, typename Compare>
  void BST<Key, Value, Compare>::push(const Key &key, const Value &value) {
    root = insert(root, key, value, nullptr);
  }

  template<typename Key, typename Value, typename Compare>
  Value &BST<Key, Value, Compare>::operator[](const Key &key) {
    Node *node = find(root.get(), key);
    if (!node) {
      root = insert(root, key, Value(), nullptr);
      node = find(root.get(), key);
    }
    return node->data.second;
  }

  template<typename Key, typename Value, typename Compare>
  const Value &BST<Key, Value, Compare>::operator[](const Key &key) const {
    Node *node = find(root.get(), key);
    if (!node) {
      throw std::runtime_error("Key not found");
    }
    return node->data.second;
  }

  template<typename Key, typename Value, typename Compare>
  void BST<Key, Value, Compare>::drop(const Key &key) {
    root = erase(root, key);
  }

  template<typename Key, typename Value, typename Compare>
  bool BST<Key, Value, Compare>::empty() const noexcept {
    return nodeCount == 0;
  }

  template<typename Key, typename Value, typename Compare>
  size_t BST<Key, Value, Compare>::size() const {
    return nodeCount;
  }

  template<typename Key, typename Value, typename Compare>
  void BST<Key, Value, Compare>::clear() {
    root.reset();
    nodeCount = 0;
  }

  template<typename Key, typename Value, typename Compare>
  void BST<Key, Value, Compare>::swap(BST &other) noexcept {
    std::swap(root, other.root);
    std::swap(nodeCount, other.nodeCount);
    std::swap(comp, other.comp);
  }

  template<typename Key, typename Value, typename Compare>
  typename BST<Key, Value, Compare>::ConstIterator BST<Key, Value, Compare>::find(const Key &key) const {
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

  template<typename Key, typename Value, typename Compare>
  size_t BST<Key, Value, Compare>::count(const Key &key) const {
    return find(root.get(), key) != nullptr ? 1 : 0;
  }

  template<typename Key, typename Value, typename Compare>
  typename BST<Key, Value, Compare>::Iterator BST<Key, Value, Compare>::begin() {
    if (!root) {
      return Iterator(nullptr);
    }
    Node *min = minValueNode(root.get());
    return Iterator(min);
  }

  template<typename Key, typename Value, typename Compare>
  typename BST<Key, Value, Compare>::Iterator BST<Key, Value, Compare>::end() {
    return Iterator(nullptr);
  }

  template<typename Key, typename Value, typename Compare>
  typename BST<Key, Value, Compare>::ConstIterator BST<Key, Value, Compare>::begin() const {
    if (!root) {
      return ConstIterator(Iterator(nullptr));
    }
    Node *min = minValueNode(root.get());
    return ConstIterator(Iterator(min));
  }

  template<typename Key, typename Value, typename Compare>
  typename BST<Key, Value, Compare>::ConstIterator BST<Key, Value, Compare>::end() const {
    return ConstIterator(Iterator(nullptr));
  }

  template<typename Key, typename Value, typename Compare>
  std::shared_ptr<typename BST<Key, Value, Compare>::Node>
  BST<Key, Value, Compare>::insert(std::shared_ptr<Node> node, const Key &key, const Value &value, std::shared_ptr<Node> parent) {
    if (!node) {
      ++nodeCount;
      return std::make_shared<Node>(key, value, parent);
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

  template<typename Key, typename Value, typename Compare>
  std::shared_ptr<typename BST<Key, Value, Compare>::Node>
  BST<Key, Value, Compare>::erase(std::shared_ptr<Node> node, const Key &key) {
    if (!node) {
      return nullptr;
    }
    if (comp(key, node->data.first)) {
      node->left = erase(node->left, key);
    } else if (comp(node->data.first, key)) {
      node->right = erase(node->right, key);
    } else {
      if (!node->left) {
        return node->right;
      }
      if (!node->right) {
        return node->left;
      }
      Node *min = minValueNode(node->right.get());
      node->data.first = min->data.first;
      node->data.second = min->data.second;
      node->right = erase(node->right, min->data.first);
    }
    return balance(node);
  }

  template<typename Key, typename Value, typename Compare>
  std::shared_ptr<typename BST<Key, Value, Compare>::Node>
  BST<Key, Value, Compare>::balance(std::shared_ptr<Node> n) {
    updateHeight(n.get());
    if (balanceFactor(n.get()) > 1) {
      if (balanceFactor(n->left.get()) < 0) {
        n->left = rotateLeft(n->left);
      }
      return rotateRight(n);
    }
    if (balanceFactor(n.get()) < -1) {
      if (balanceFactor(n->right.get()) > 0) {
        n->right = rotateRight(n->right);
      }
      return rotateLeft(n);
    }
    return n;
  }

  template<typename Key, typename Value, typename Compare>
  std::shared_ptr<typename BST<Key, Value, Compare>::Node>
  BST<Key, Value, Compare>::rotateRight(std::shared_ptr<Node> y) {
    std::shared_ptr<Node> x = y->left;
    y->left = x->right;
    if (y->left) {
      y->left->parent = y;
    }
    x->right = y;
    x->parent = y->parent;
    y->parent = x;
    updateHeight(y.get());
    updateHeight(x.get());
    return x;
  }

  template<typename Key, typename Value, typename Compare>
  std::shared_ptr<typename BST<Key, Value, Compare>::Node>
  BST<Key, Value, Compare>::rotateLeft(std::shared_ptr<Node> x) {
    std::shared_ptr<Node> y = x->right;
    x->right = y->left;
    if (x->right) {
      x->right->parent = x;
    }
    y->left = x;
    y->parent = x->parent;
    x->parent = y;
    updateHeight(x.get());
    updateHeight(y.get());
    return y;
  }

  template<typename Key, typename Value, typename Compare>
  int BST<Key, Value, Compare>::height(Node *n) const {
    return n ? n->height : 0;
  }

  template<typename Key, typename Value, typename Compare>
  int BST<Key, Value, Compare>::balanceFactor(Node *n) const {
    return n ? height(n->left.get()) - height(n->right.get()) : 0;
  }

  template<typename Key, typename Value, typename Compare>
  void BST<Key, Value, Compare>::updateHeight(Node *n) {
    if (n) {
      n->height = 1 + std::max(height(n->left.get()), height(n->right.get()));
    }
  }

  template<typename Key, typename Value, typename Compare>
  std::shared_ptr<typename BST<Key, Value, Compare>::Node>
  BST<Key, Value, Compare>::clone(const Node *node) const {
    if (!node) {
      return nullptr;
    }
    auto newNode = std::make_shared<Node>(node->data.first, node->data.second);
    newNode->left = clone(node->left.get());
    newNode->right = clone(node->right.get());
    if (newNode->left) {
      newNode->left->parent = newNode;
    }
    if (newNode->right) {
      newNode->right->parent = newNode;
    }
    return newNode;
  }

  template<typename Key, typename Value, typename Compare>
  typename BST<Key, Value, Compare>::Node *BST<Key, Value, Compare>::minValueNode(Node *node) const {
    while (node && node->left) {
      node = node->left.get();
    }
    return node;
  }

  template<typename Key, typename Value, typename Compare>
  typename BST<Key, Value, Compare>::Node *BST<Key, Value, Compare>::find(Node *node, const Key &key) const {
    if (!node) {
      return nullptr;
    }
    if (comp(key, node->data.first)) {
      return find(node->left.get(), key);
    } else if (comp(node->data.first, key)) {
      return find(node->right.get(), key);
    }
    return node;
  }

  template<typename Key, typename Value, typename Compare>
  BST<Key, Value, Compare>::Iterator::Iterator() : current(nullptr) {}

  template<typename Key, typename Value, typename Compare>
  BST<Key, Value, Compare>::Iterator::Iterator(Node *node) : current(node) {}

  template<typename Key, typename Value, typename Compare>
  typename BST<Key, Value, Compare>::Iterator &BST<Key, Value, Compare>::Iterator::operator++() {
    current = findNext(current);
    return *this;
  }

  template<typename Key, typename Value, typename Compare>
  typename BST<Key, Value, Compare>::Iterator BST<Key, Value, Compare>::Iterator::operator++(int) {
    Iterator temp = *this;
    ++(*this);
    return temp;
  }

  template<typename Key, typename Value, typename Compare>
  std::pair<Key, Value> &BST<Key, Value, Compare>::Iterator::operator*() {
    return current->data;
  }

  template<typename Key, typename Value, typename Compare>
  std::pair<Key, Value> *BST<Key, Value, Compare>::Iterator::operator->() {
    return &(current->data);
  }

  template<typename Key, typename Value, typename Compare>
  bool BST<Key, Value, Compare>::Iterator::operator==(const Iterator &other) const {
    return current == other.current;
  }

  template<typename Key, typename Value, typename Compare>
  bool BST<Key, Value, Compare>::Iterator::operator!=(const Iterator &other) const {
    return current != other.current;
  }

  template<typename Key, typename Value, typename Compare>
  typename BST<Key, Value, Compare>::Node *BST<Key, Value, Compare>::Iterator::findNext(Node *node) const {
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
}

#endif
