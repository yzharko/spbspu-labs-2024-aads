#ifndef NODE_T_HPP
#define NODE_T_HPP

#include <stdexcept>
namespace zasulsky
{
  namespace detail
  {
    template< class T >
    struct node_t
    {
    public:
      node_t(T dat) :
        data(dat),
        height(1),
        parent(nullptr),
        left(nullptr),
        right(nullptr)
      {}

      node_t(T dat, int hei) :
        data(dat),
        height(1),
        parent(nullptr),
        left(nullptr),
        right(nullptr)
      {}

      T data;
      int height;

      node_t< T >* parent;
      node_t< T >* left;
      node_t< T >* right;
    };

    template< typename T >
    static bool isEmpty(const node_t< T >* node) noexcept
    {
      return node == nullptr;
    }

    template< typename T >
    void clearN(node_t< T >* root)
    {
      if (isEmpty(root))
      {
        return;
      }

      if (!isEmpty(root->left))
      {
        clearN(root->left);
      }

      if (!isEmpty(root->right))
      {
        clearN(root->right);
      }

      delete root;
    }

    template< typename T >
    node_t< T >* copy(node_t< T >* otherRoot)
    {
      if (isEmpty(otherRoot))
      {
        return nullptr;
      }

      node_t< T >* newNode = new node_t< T >{ otherRoot->data,otherRoot->height };

      try
      {
        newNode->left = copy(otherRoot->left);
      }
      catch (const std::exception&)
      {
        delete newNode;
        throw;
      }
      if (!isEmpty(newNode->left))
      {
        newNode->left->parent = newNode;
      }

      try
      {
        newNode->right = copy(otherRoot->right);
      }
      catch (const std::exception&)
      {
        clearN(newNode->left);
        delete newNode;
        throw;
      }
      if (!isEmpty(newNode->right))
      {
        newNode->right->parent = newNode;
      }

      return newNode;
    }
  }
}

#endif
