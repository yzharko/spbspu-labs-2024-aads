#ifndef BINTREE_H
#define BINTREE_H
#include <iostream>
#include <string>
#include <vector>
template < class T, class V >
class AVLTree
{
public:
  AVLTree();
  AVLTree(const AVLTree< T, V > &other);
  AVLTree(AVLTree &&other) noexcept;
  ~AVLTree();
  AVLTree &operator=(const AVLTree< T, V > &other);
  AVLTree< T, V > &operator=(AVLTree< T, V > &&other) noexcept;
  bool contains(const T &key) const;
  V &get(const T &key);
  void insert(const T &key, const V &num);
  void deleteKey(const T &key);
  int getCount() const;
  void print(std::ostream &out);
private:
  struct Node
  {
    T key_;
    V value_;
    Node *left_;
    Node *right_;
    int height_;
    Node(const T &key, const V &value,
      Node *left = nullptr,
      Node *right = nullptr,
      int height = 1):
      key_(key),
      value_(value),
      left_(left),
      right_(right),
      height_(height)
    {
    }
  };
  Node *root_;
  Node *copyNodes(Node *node);
  void printNode(Node *node, std::ostream &out);
  void clear(Node *node);
  void fixHeight(Node *node);
  int getCount(Node *node) const;
  int getHeight(Node *root) const;
  int getBalance(Node *node);
  Node *deleteNode(Node *node, const T &key);
  Node *searchNode(const T &key) const;
  Node *insertNode(Node *node, const T &key, const V &num);
  Node *rotateLeft(Node *node);
  Node *rotateRight(Node *node);
  Node *balance(Node *node);
  Node *minValueNode(Node *node) const;
};
template < class T, class V >
typename AVLTree<T,V>::Node *AVLTree< T, V >::copyNodes(AVLTree::Node *node)
{
  if (node == nullptr) {
    return nullptr;
  }
  Node *newNode = new Node(node->key_, node->value_);
  newNode->left_ = copyNodes(node->left_);
  newNode->right_ = copyNodes(node->right_);
  return newNode;
}
template < class T, class V >
AVLTree< T, V >::AVLTree(const AVLTree< T, V > &other):
  root_(nullptr)
{
    root_ = copyNodes(other.root_);
}
template < class T, class V >
AVLTree< T, V > &AVLTree< T, V >::operator=(const AVLTree< T, V > &other)
{
  if (root_) {
    clear(root_);
  }
  root_ = copyNodes(other.root_);
  return *this;
}
template < class T, class V >
typename AVLTree< T, V >::Node *AVLTree< T, V >::searchNode(const T &key) const
{
  Node *temp_ = root_;
  while (temp_ != nullptr && temp_->key_ != key)
  {
    if (key < temp_->key_)
    {
      temp_ = temp_->left_;
    }
    else
    {
      temp_ = temp_->right_;
    }
  }
  return temp_;
}
template < class T, class V >
bool AVLTree< T, V >::contains(const T &key) const
{
  return searchNode(key) != nullptr;
}
template < class T, class V >
V &AVLTree< T, V >::get(const T &key)
{
  auto node = searchNode(key);
  if (node)
  {
    return node->value_;
  }
  else
  {
    throw std::logic_error("No data");
  }
}
template < class T, class V >
typename AVLTree< T, V >::Node *AVLTree< T, V >::insertNode(Node *node, const T &key, const V &num)
{
  if (node == nullptr)
  {
    Node *newNode = new Node(key, num);
    return newNode;
  }
  if (key < node->key_)
  {
    node->left_ = insertNode(node->left_, key, num);
  }
  else if (key > node->key_)
  {
    node->right_ = insertNode(node->right_, key, num);
  }
  return balance(node);
}
template < class T, class V >
void AVLTree< T, V >::clear(Node *node)
{
  if (node)
  {
    clear(node->left_);
    clear(node->right_);
    delete node;
  }
}
template < class T, class V >
void AVLTree< T, V >::printNode(AVLTree::Node *node, std::ostream &out)
{
  if (node->left_)
  {
    printNode(node->left_, out);
  }
  if (node->right_)
  {
    printNode(node->right_, out);
  }
  out << node->key_ << " " << node->value_ << "\n";
}
template < class T, class V >
int AVLTree< T, V >::getCount(AVLTree::Node *node) const
{
  if (node == nullptr)
  {
    return 0;
  }
  return (1 + getCount(node->left_) + getCount(node->right_));
}
template < class T, class V >
AVLTree< T, V > &AVLTree< T, V >::operator=(AVLTree< T, V > &&other) noexcept
{
  root_ = other.root_;
  other.root_ = nullptr;
  return *this;
}
template < class T, class V >
AVLTree< T, V >::AVLTree(AVLTree &&other) noexcept
{
  root_ = other.root_;
  other.root_ = nullptr;
}
template < class T, class V >
int AVLTree< T, V >::getHeight(AVLTree::Node *root) const
{
  if (root != nullptr)
  {
    return root->height_;
  }
  else
  {
    return 0;
  }
}
template < class T, class V >
void AVLTree< T, V >::insert(const T &key, const V &num)
{
  root_ = insertNode(root_, key, num);
}
template < class T, class V >
int AVLTree< T, V >::getBalance(AVLTree::Node *node)
{
  if (node == nullptr)
  {
    return 0;
  }
  return getHeight(node->left_) - getHeight(node->right_);
}
template < class T, class V >
void AVLTree< T, V >::fixHeight(AVLTree::Node *node)
{
  node->height_ = std::max(getHeight(node->left_),
                           getHeight(node->right_)) + 1;
}
template < class T, class V >
typename AVLTree< T, V >::Node *AVLTree< T, V >::rotateLeft(AVLTree::Node *node)
{
  Node *p = node->right_;
  node->right_ = p->left_;
  p->left_ = node;
  fixHeight(node);
  fixHeight(p);
  return p;
}
template < class T, class V >
typename AVLTree< T, V >::Node *AVLTree< T, V >::rotateRight(AVLTree::Node *node)
{
  Node *q = node->left_;
  node->left_ = q->right_;
  q->right_ = node;
  fixHeight(node);
  fixHeight(q);
  return q;
}
template < class T, class V >
typename AVLTree< T, V >::Node *AVLTree< T, V >::balance(AVLTree::Node *node)
{
  fixHeight(node);
  if (getBalance(node) == -2)
  {
    if (getBalance(node->right_) > 0)
    {
      node->right_ = rotateRight(node->right_);
    }
    return rotateLeft(node);
  }
  if (getBalance(node) == 2)
  {
    if (getBalance(node->left_) < 0)
    {
      node->left_ = rotateLeft(node->left_);
    }
    return rotateRight(node);
  }
  return node;
}
template < class T, class V >
typename AVLTree< T, V >::Node *AVLTree< T, V >::minValueNode(AVLTree::Node *node) const
{
  if (node->left_)
  {
    return minValueNode(node->left_);
  }
  return node;
}
template < class T, class V >
void AVLTree< T, V >::deleteKey(const T &key)
{
  root_ = deleteNode(root_, key);
}
template < class T, class V >
typename AVLTree< T, V >::Node *AVLTree< T, V >::deleteNode(AVLTree::Node *node, const T &key)
{
  if (!node)
  {
    return node;
  }
  if (key < node->key_)
  {
    node->left_ = deleteNode(node->left_, key);
  }
  else if (key > node->key_)
  {
    node->right_ = deleteNode(node->right_, key);
  }
  else
  {
    if (!node->left_)
    {
      Node *temp = node->right_;
      delete node;
      return temp;
    }
    else if (!node->right_)
    {
      Node *temp = node->left_;
      delete node;
      return temp;
    }
    Node *temp = minValueNode(node->right_);
    node->key_ = temp->key_;
    node->value_ = temp->value_;
    node->right_ = deleteNode(node->right_, temp->key_);
  }
  return balance(node);
}
template < class T, class V >
int AVLTree< T, V >::getCount() const
{
  return getCount(root_);
}
template < class T, class V >
void AVLTree< T, V >::print(std::ostream &out)
{
  printNode(root_, out);
}
template < class T, class V >
AVLTree< T, V >::~AVLTree()
{
  clear(root_);
}
template < class T, class V >
AVLTree< T, V >::AVLTree():
  root_(nullptr)
{
}
#endif
