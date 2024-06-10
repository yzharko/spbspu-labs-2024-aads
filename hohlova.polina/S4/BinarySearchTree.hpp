#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP
#include <iostream>
#include <stack>
#include <functional>

template < typename Key, typename Value, typename Compare = std::less< Key > >
class BinarySearchTree
{
public:
    class Node;
    class iterator;

    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree();
    void push(const Key& k, const Value& v);
    bool empty();
    Value get(const Key& k);
    bool contains(const Key& k)
    {
        Node* node = find(root, k);
        if (node)
        {
            return true;
        }
        return false;
    }

    Value drop(const Key& k)
    {
        Node* node = remove(root, k);
        if (node) {
            if (root == nullptr)
            {
                root = node;
            }
            Value val = node->value;
            return val;
        }
        throw std::out_of_range("Key not found");
    }

    iterator begin()
    {
        return iterator(root);
    }

    iterator end()
    {
        return iterator();
    }

private:
    Node* root;
    Compare comp;

    void clear(Node* node)
    {
        if (node)
        {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    Node* insert(Node* node, const Key& k, const Value& v)
    {
        if (!node)
        {
            return new Node(k, v);
        }

        if (comp(k, node->key))
        {
            node->left = insert(node->left, k, v);
        }
        else if (comp(node->key, k))
        {
            node->right = insert(node->right, k, v);
        }
        else
        {
            node->value = v;
        }
        return node;
    }

    Node* find(Node* node, const Key& k)
    {
        if (!node)
        {
            return nullptr;
        }

        if (comp(k, node->key))
        {
            return find(node->left, k);
        }
        else if (comp(node->key, k))
        {
            return find(node->right, k);
        }
        else
        {
            return node;
        }
    }

    Node* remove(Node*& node, const Key& k)
    {
        if (!node)
        {
            return nullptr;
        }

        if (comp(k, node->key))
        {
            node->left = remove(node->left, k);
        }
        else if (comp(node->key, k))
        {
            node->right = remove(node->right, k);
        }
        else
        {
            if (!node->left)
            {
                Node* temp = node->right;
                delete node;
                node = nullptr;
                return temp;
            }
            else if (!node->right)
            {
                Node* temp = node->left;
                delete node;
                node = nullptr;
                return temp;
            }

            Node* minRight = findMin(node->right);
            node->key = minRight->key;
            node->value = minRight->value;
            node->right = remove(node->right, minRight->key);
        }
        return node;
    }
    Node* findMin(Node* node)
    {
        while (node->left)
        {
            node = node->left;
        }
        return node;
    }
};

template< typename Key, typename Value, typename Compare >
class BinarySearchTree< Key, Value, Compare >::Node
{
public:
    friend class BinarySearchTree< Key, Value, Compare >;
    explicit Node(const Key& k, const Value& v) : key(k), value(v), left(nullptr), right(nullptr) {}
private:
    Key key;
    Value value;
    Node* left;
    Node* right;
};

template< typename Key, typename Value, typename Compare >
class BinarySearchTree< Key, Value, Compare >::iterator
{
public:
    friend class BinarySearchTree< Key, Value, Compare >;
    iterator() {}
    iterator(Node* node);

    bool operator!=(const iterator& other) const;
    iterator& operator++();
    std::pair<const Key&, const Value&> operator*() const;
private:
    void pushLeftBranch(Node* node);
    std::stack<Node*> stack;
};

template< typename Key, typename Value, typename Compare >
BinarySearchTree< Key, Value, Compare >::iterator::iterator(Node* node)
{
    if (node)
    {
        pushLeftBranch(node);
    }
}

template< typename Key, typename Value, typename Compare >
bool BinarySearchTree< Key, Value, Compare >::iterator::operator!=(const iterator& other) const
{
    return !stack.empty() || !other.stack.empty();
}

template< typename Key, typename Value, typename Compare >
typename BinarySearchTree< Key, Value, Compare >::iterator& BinarySearchTree< Key, Value, Compare >::iterator::operator++()
{
    Node* current = stack.top();
    stack.pop();
    pushLeftBranch(current->right);
    return *this;
}

template< typename Key, typename Value, typename Compare >
std::pair< const Key&, const Value& > BinarySearchTree< Key, Value, Compare >::iterator::operator*() const
{
    if (stack.empty())
    {
        throw std::runtime_error("Dereferencing end iterator");
    }
    return std::make_pair(std::cref(stack.top()->key), std::cref(stack.top()->value));
}

template< typename Key, typename Value, typename Compare >
void  BinarySearchTree< Key, Value, Compare >::iterator::pushLeftBranch(Node* node)
{
    while (node)
    {
        stack.push(node);
        node = node->left;
    }
}

template< typename Key, typename Value, typename Compare >
BinarySearchTree< Key, Value, Compare >::~BinarySearchTree()
{
    clear(root);
}

template< typename Key, typename Value, typename Compare >
void BinarySearchTree< Key, Value, Compare >::push(const Key& k, const Value& v)
{
    root = insert(root, k, v);
}

template< typename Key, typename Value, typename Compare >
bool BinarySearchTree< Key, Value, Compare >::empty()
{
    return root == nullptr ? true : false;
}

template< typename Key, typename Value, typename Compare >
Value BinarySearchTree< Key, Value, Compare >::get(const Key& k)
{
    Node* node = find(root, k);
    if (node)
    {
        return node->value;
    }
    return nullptr;
}

#endif
