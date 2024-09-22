#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <sstream>
#include <iterator>
#include <functional>

enum Color { RED, BLACK };

struct Node {
    std::string key;
    std::vector<std::string> translations;
    Color color;
    Node *left, *right, *parent;

    Node(std::string k)
            : key(std::move(k)), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node *root;
    Node *TNULL;

    void fixInsert(Node *k);

    void leftRotate(Node *x);

    void rightRotate(Node *x);

    void deleteBST(Node *node, const std::string &key);

    void rbTransplant(Node *u, Node *v);

    void fixDelete(Node *x);

    Node* minimum(Node *node) {
        while (node->left != TNULL) {
            node = node->left;
        }
        return node;
    }

public:
    RedBlackTree() {
        TNULL = new Node("");
        TNULL->color = BLACK;
        root = TNULL;
    }

    void insert(const std::string &key);

    void remove(const std::string &key) {
        deleteBST(this->root, key);
    }

    Node * search(const std::string &key) const;

    void inorder(Node* node) const ;

    void show() const {
        inorder(root);
    }

    std::vector<std::string> getAllWords() const ;
    Node* getRoot() {
        return root;
    }
};
