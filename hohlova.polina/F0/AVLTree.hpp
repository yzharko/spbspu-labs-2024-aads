#ifndef AVLTREE_HPP
#define AVLTREE_HPP
#include <iostream>
#include <utility>

using namespace std;

template< typename Key, typename Value >
struct Node
{
    pair< Key, Value > data;
    Node* left;
    Node* right;
    Node* parent;

    Node(const pair< Key, Value >& data) : data(data), left(nullptr), right(nullptr), parent(nullptr) {}
};

template< typename Key, typename Value >
class BinarySearchTree
{
private:
    Node< Key, Value >* root;

    Node< Key, Value >* insert(Node< Key, Value >* node, const pair< Key, Value >& data)
    {
        if (node == nullptr)
        {
            return new Node< Key, Value >(data);
        }

        if (data.first < node->data.first)
        {
            node->left = insert(node->left, data);
            node->left->parent = node;
        }
        else
        {
            node->right = insert(node->right, data);
            node->right->parent = node;
        }

        return node;
    }

    Node< Key, Value >* search(Node< Key, Value >* node, const Key& key)
    {
        if (node == nullptr || node->data.first == key)
        {
            return node;
        }

        if (key < node->data.first)
        {
            return search(node->left, key);
        }
        else
        {
            return search(node->right, key);
        }
    }

    Node< Key, Value >* remove(Node< Key, Value >* node, const Key& key)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        if (key < node->data.first)
        {
            node->left = remove(node->left, key);
        }
        else if (key > node->data.first)
        {
            node->right = remove(node->right, key);
        }
        else
        {
            if (node->left == nullptr)
            {
                Node< Key, Value >* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr)
            {
                Node< Key, Value >* temp = node->left;
                delete node;
                return temp;
            }

            Node< Key, Value >* temp = minNode(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data.first);
        }

        return node;
    }

    Node< Key, Value >* minNode(Node<Key, Value>* node)
    {
        while (node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(const Key& key, const Value& value)
    {
        root = insert(root, make_pair(key, value));
    }

    void insert(const std::pair< Key, Value >& pair)
    {
        root = insert(root, make_pair(pair.first, pair.second));
    }

    bool search(const Key& key)
    {
        return search(root, key) != nullptr;
    }

    Value get(const Key& key)
    {
        Node< Key, Value >* node = search(root, key);
        if (node != nullptr)
        {
            return node->data.second;
        }
        else
        {
            throw runtime_error("Ключ не найден");
        }
    }

    void remove(const Key& key)
    {
        root = remove(root, key);
    }

    void clear()
    {
        while (root != nullptr)
        {
            remove(root, root->data.first);
        }
    }

    class InorderIterator
    {
    private:
        Node< Key, Value >* current;

        Node< Key, Value >* nextNode()
        {
            if (current->right != nullptr)
            {
                current = current->right;
                while (current->left != nullptr)
                {
                    current = current->left;
                }
                return current;
            }
            else
            {
                Node< Key, Value >* parent = current->parent;
                while (parent != nullptr && current == parent->right)
                {
                    current = parent;
                    parent = parent->parent;
                }
                return parent;
            }
        }

    public:
        InorderIterator(Node< Key, Value >* node) : current(node) {}

        pair< Key, Value > operator*() const
        {
            return current->data;
        }

        InorderIterator& operator++()
        {
            current = nextNode();
            return *this;
        }

        bool operator==(const InorderIterator& other) const
        {
            return current == other.current;
        }

        bool operator!=(const InorderIterator& other) const
        {
            return current != other.current;
        }
    };

    InorderIterator begin()
    {
        if (root == nullptr)
        {
            return InorderIterator(nullptr);
        }

        Node< Key, Value >* node = root;
        while (node->left != nullptr)
        {
            node = node->left;
        }
        return InorderIterator(node);
    }

    InorderIterator end()
    {
        return InorderIterator(nullptr);
    }

    InorderIterator find(const Key& key)
    {
        return InorderIterator(search(root, key));
    }

    bool empty()
    {
        return root == nullptr;
    }
};

#endif
