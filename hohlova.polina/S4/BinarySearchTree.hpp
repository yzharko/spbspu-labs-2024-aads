#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP
#include <iostream>
#include <stack>
#include <functional>

template <typename Key, typename Value, typename Compare = std::less<Key>>
class BinarySearchTree {
private:
    struct Node {
        Key key;
        Value value;
        Node* left;
        Node* right;

        Node(const Key& k, const Value& v) : key(k), value(v), left(nullptr), right(nullptr) {}
    };

    Node* root;
    Compare comp;

public:
    BinarySearchTree() : root(nullptr) {}

    void push(const Key& k, const Value& v) {
        root = insert(root, k, v);
    }
    bool empty()
    {
        return root == nullptr ? true : false;
    }
    Value get(const Key& k) {
        Node* node = find(root, k);
        if (node) {
            return node->value;
        }
        std::cout << "<INVALID COMMAND>\n";
        return;
    }

    bool contains(const Key& k)
    {
        Node* node = find(root, k);
        if (node) {
            return true;
        }
        return false;
    }

    Value drop(const Key& k) {
        Node* node = remove(root, k);
        if (node) {
            if (root == nullptr)
            {
                root = node;
            }
            Value val = node->value;
            //delete node;
            return val;
        }
        throw std::out_of_range("Key not found");
    }
    ~BinarySearchTree() {
        clear(root);
    }

    class iterator {
    private:
        std::stack<Node*> stack;

    public:
        iterator() {}

        iterator(Node* node) {
            if (node)
                pushLeftBranch(node);
        }

        bool operator!=(const iterator& other) const {
            return !stack.empty() || !other.stack.empty();
        }

        iterator& operator++() {
            Node* current = stack.top();
            stack.pop();
            pushLeftBranch(current->right);
            return *this;
        }

        std::pair<const Key&, const Value&> operator*() const {
            if (stack.empty()) {
                throw std::runtime_error("Dereferencing end iterator");
            }
            return std::make_pair(std::cref(stack.top()->key), std::cref(stack.top()->value));
        }

    private:
        void pushLeftBranch(Node* node) {
            while (node) {
                stack.push(node);
                node = node->left;
            }
        }
    };

    iterator begin() {
        return iterator(root);
    }

    iterator end() {
        return iterator();
    }

private:
    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    Node* insert(Node* node, const Key& k, const Value& v) {
        if (!node) {
            return new Node(k, v);
        }

        if (comp(k, node->key)) {
            node->left = insert(node->left, k, v);
        }
        else if (comp(node->key, k)) {
            node->right = insert(node->right, k, v);
        }
        else {
            node->value = v;
        }

        return node;
    }

    Node* find(Node* node, const Key& k) {
        if (!node) {
            return nullptr;
        }

        if (comp(k, node->key)) {
            return find(node->left, k);
        }
        else if (comp(node->key, k)) {
            return find(node->right, k);
        }
        else {
            return node;
        }
    }

    Node* remove(Node*& node, const Key& k) {
        if (!node) {
            return nullptr;
        }

        if (comp(k, node->key)) {
            node->left = remove(node->left, k);
        }
        else if (comp(node->key, k)) {
            node->right = remove(node->right, k);
        }
        else {
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                node = nullptr;
                return temp;
            }
            else if (!node->right) {
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

    Node* findMin(Node* node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }
};

#endif
