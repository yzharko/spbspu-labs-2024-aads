#ifndef BIANRYSEARCHTREE
#define BIANRYSEARCHTREE
#include <iostream>
#include <utility>
#include <limits>
#include <stdexcept>
#include <memory>
#include <vector>
#include "node_t.hpp"
#include "Stack.hpp"
#include "Queue.hpp"

namespace zasulsky
{
  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class AVL;

  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class ConstBidIter;

  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class RevBidIter;

  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class ConstRevBidIter;

  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class BidirectionalIterator : public std::iterator< std::bidirectional_iterator_tag, std::pair< Key, Value > >
  {
  public:
    friend class AVL< Key, Value, Compare >;
    friend class ConstBidIter< Key, Value, Compare >;
    friend class RevBidIter< Key, Value, Compare >;
    friend class ConstRevBidIter< Key, Value, Compare >;
    using node = detail::node_t< std::pair< Key, Value > >;
    using T = std::pair< Key, Value >;
    using constIterator = ConstBidIter< Key, Value, Compare >;

    BidirectionalIterator() noexcept :
      m_ptr(nullptr)
    {}

    BidirectionalIterator(node* other) :
      m_ptr(nullptr)
    {
      m_ptr = other;
    }

    BidirectionalIterator& operator++() noexcept
    {
      if (isEmpty(m_ptr))
      {
        return *this;
      }

      if (!isEmpty(m_ptr->right))
      {
        m_ptr = m_ptr->right;
        while (!isEmpty(m_ptr->left))
        {
          m_ptr = m_ptr->left;
        }
      }
      else
      {
        node* parent = m_ptr->parent;
        while (!isEmpty(parent) && (m_ptr == parent->right))
        {
          m_ptr = parent;
          parent = parent->parent;
        }
        m_ptr = parent;
      }
      return *this;
    }

    BidirectionalIterator operator++(int) noexcept
    {
      BidirectionalIterator prev(m_ptr);
      ++(*this);

      return prev;
    }

    BidirectionalIterator& operator--() noexcept
    {
      if (isEmpty(m_ptr))
      {
        return *this;
      }

      if (!isEmpty(m_ptr->left))
      {
        m_ptr = m_ptr->left;
        while (!isEmpty(m_ptr->right))
        {
          m_ptr = m_ptr->right;
        }
      }
      else
      {
        node* parent = m_ptr->parent;
        while (!isEmpty(parent) && m_ptr == parent->left)
        {
          m_ptr = parent;
          parent = parent->parent;
        }
        m_ptr = parent;
      }
      return *this;
    }

    BidirectionalIterator operator--(int) noexcept
    {
      BidirectionalIterator prev(m_ptr);
      --(*this);

      return prev;
    }

    bool operator==(const BidirectionalIterator& other) const noexcept
    {
      return (m_ptr == other.m_ptr);
    }

    bool operator!=(const BidirectionalIterator& other) const noexcept
    {
      return !(m_ptr == other.m_ptr);
    }

    T& operator*()
    {
      return m_ptr->data;
    }

    T* operator->()
    {
      return std::addressof(m_ptr->data);
    }

    void assignNewValue(node* pt)
    {
      m_ptr = pt;
    }

    node* getCur()
    {
      return m_ptr;
    }

    node* m_ptr;

    BidirectionalIterator(const constIterator& other) :
      m_ptr(const_cast<node*>(other.m_ptr))
    {}

    BidirectionalIterator(constIterator&& other) :
      m_ptr(const_cast<node*>(other.m_ptr))
    {}
  };

  template< typename Key, typename Value, typename Compare >
  class ConstBidIter : public std::iterator< std::bidirectional_iterator_tag, const std::pair< Key, Value > >
  {
  public:
    friend class AVL< Key, Value, Compare >;
    friend class BidirectionalIterator< Key, Value, Compare >;

    using T = std::pair< Key, Value >;
    using node = typename AVL< Key, Value, Compare >::node;
    using iterator = BidirectionalIterator< Key, Value, Compare >;

    ConstBidIter() noexcept :
      m_ptr(nullptr)
    {}

    ConstBidIter(const node* other) noexcept :
      m_ptr(other)
    {}

    ConstBidIter(const iterator& other) noexcept :
      m_ptr(other.m_ptr)
    {}

    ConstBidIter(iterator&& other) noexcept :
      m_ptr(other.m_ptr)
    {}

    ConstBidIter& operator++() noexcept
    {
      iterator res(m_ptr);
      res++;
      m_ptr = res.m_ptr;
      return *this;
    }

    ConstBidIter operator++(int) noexcept
    {
      ConstBidIter prev(m_ptr);
      ++(*this);

      return prev;
    }

    ConstBidIter& operator--() noexcept
    {
      iterator res(m_ptr);
      res--;
      m_ptr = res.m_ptr;
      return *this;
    }

    ConstBidIter operator--(int) noexcept
    {
      ConstBidIter prev(m_ptr);
      --(*this);

      return prev;
    }

    bool operator==(const ConstBidIter& other) const noexcept
    {
      return (m_ptr == other.m_ptr);
    }

    bool operator!=(const ConstBidIter& other) const noexcept
    {
      return !(*this == other);
    }

    const T& operator*() const
    {
      return m_ptr->data;
    }

    const T* operator->() const
    {
      return std::addressof(m_ptr->data);
    }

    node& getCur()
    {
      return m_ptr;
    }

    void assignNewValue(node* pt)
    {
      m_ptr = pt;
    }

    const node* m_ptr;

  };

  template< typename Key, typename Value, typename Compare >
  class RevBidIter : public std::iterator< std::bidirectional_iterator_tag, std::pair< Key, Value > >
  {
  public:
    friend class AVL< Key, Value, Compare >;
    friend class ConstRevBidIter< Key, Value, Compare >;

    using T = std::pair< Key, Value >;
    using node = typename AVL< Key, Value, Compare >::node;
    using basicIterator = BidirectionalIterator< Key, Value, Compare >;
    using constIterator = ConstRevBidIter< Key, Value, Compare >;

    RevBidIter() noexcept :
      m_ptr(nullptr)
    {}

    explicit RevBidIter(node* other) noexcept :
      m_ptr(other)
    {}

    RevBidIter& operator++() noexcept
    {
      basicIterator res(m_ptr);
      res--;
      m_ptr = res.m_ptr;
      return *this;
    }

    RevBidIter operator++(int) noexcept
    {
      RevBidIter prev(m_ptr);
      ++(*this);

      return prev;
    }

    RevBidIter& operator--() noexcept
    {
      basicIterator res(m_ptr);
      res++;
      m_ptr = res.m_ptr;
      return *this;
    }

    RevBidIter operator--(int) noexcept
    {
      RevBidIter prev(m_ptr);
      --(*this);

      return prev;
    }

    bool operator==(const RevBidIter& other) const noexcept
    {
      return (m_ptr == other.m_ptr);
    }

    bool operator!=(const RevBidIter& other) const noexcept
    {
      return !(*this == other);
    }

    T& operator*()
    {
      return m_ptr->data;
    }

    T* operator->()
    {
      return std::addressof(m_ptr->data);
    }

    node* m_ptr;

    RevBidIter(const constIterator& other) :
      m_ptr(const_cast<node*>(other.m_ptr))
    {}

    RevBidIter(constIterator&& other) :
      m_ptr(const_cast<node*>(other.m_ptr))
    {}
  };

  template< typename Key, typename Value, typename Compare >
  class ConstRevBidIter :public std::iterator<std::bidirectional_iterator_tag, const std::pair<Key, Value>>
  {
  public:
    friend class AVL< Key, Value, Compare >;
    friend class RevBidIter< Key, Value, Compare >;

    using T = std::pair<Key, Value >;
    using node = typename AVL< Key, Value, Compare >::node;
    using iterator = RevBidIter< Key, Value, Compare >;
    using basicIterator = BidirectionalIterator< Key, Value, Compare >;

    ConstRevBidIter() noexcept :
      m_ptr(nullptr)
    {}

    ConstRevBidIter(const node* other) noexcept :
      m_ptr(other)
    {}

    ConstRevBidIter(const iterator& other) noexcept :
      m_ptr(other.m_ptr)
    {}

    ConstRevBidIter(iterator&& other) noexcept :
      m_ptr(other.m_ptr)
    {}

    ConstRevBidIter& operator++() noexcept
    {
      basicIterator res(m_ptr);
      res--;
      m_ptr = res.m_ptr;
      return *this;
    }

    ConstRevBidIter operator++(int) noexcept
    {
      ConstRevBidIter prev(m_ptr);
      ++(*this);

      return prev;
    }

    ConstRevBidIter& operator--() noexcept
    {
      basicIterator res(m_ptr);
      res++;
      m_ptr = res.m_ptr;
      return *this;
    }

    ConstRevBidIter operator--(int) noexcept
    {
      ConstRevBidIter prev(m_ptr);
      --(*this);

      return prev;
    }

    bool operator==(const ConstRevBidIter& other) const noexcept
    {
      return (m_ptr == other.m_ptr);
    }

    bool operator!=(const ConstRevBidIter& other) const noexcept
    {
      return !(*this == other);
    }

    const T& operator*() const
    {
      return m_ptr->data;
    }

    const T* operator->() const
    {
      return std::addressof(m_ptr->data);
    }

    const node* m_ptr;
  };

  template< class Key, class Value, class Compare >
  class AVL
  {
  public:
    using pair = std::pair< Key, Value >;
    using node = detail::node_t< pair >;
    using iterator = BidirectionalIterator< Key, Value, Compare >;
    using constIterator = ConstBidIter< Key, Value, Compare >;
    using reverseIterator = RevBidIter< Key, Value, Compare >;
    using reverseConstIterator = ConstRevBidIter< Key, Value, Compare >;

    AVL() :
      root_(nullptr),
      comp_()
    {}

    AVL(const AVL& other) :
      root_(copy(other.root_)),
      comp_()
    {}

    AVL(AVL&& other) noexcept :
      root_(other.root_),
      comp_()
    {
      other.root_ = nullptr;
    }

    AVL(std::initializer_list< std::pair< Key, Value > > initList) :
      root_(),
      comp_()
    {
      insert(initList);
    }

    ~AVL()
    {
      clear();
    }

    AVL& operator = (const AVL& other)
    {
      if (this == std::addressof(other))
      {
        return *this;
      }
      else
      {
        clear();
        root_ = copy(other.root_);
        return *this;
      }
    }

    AVL& operator = (AVL&& other)
    {
      if (this == std::addressof(other))
      {
        return *this;
      }
      else
      {
        clear();
        root_ = other.root_;
        other.root_ = nullptr;
      }
    }

    Value& operator[](Key key)
    {
      auto it = begin();
      while (it != end())
      {
        if (it->first == key)
        {
          return it->second;
        }
        else
        {
          it++;
        }
      }
      insert(make_pair(key, Value{}));
      auto p = find(key);
      return p->second;
    }

    iterator begin()
    {
      node* pt = min();
      return iterator(pt);
    }

    iterator end()
    {
      return iterator();
    }

    constIterator cbegin() const
    {
      return constIterator(min());
    }

    constIterator cend() const
    {
      return constIterator();
    }

    reverseIterator reverseBegin()
    {
      return reverseIterator(max());
    }

    reverseIterator reverseEnd()
    {
      return reverseIterator();
    }

    reverseConstIterator reverseConstBegin() const
    {
      return reverseConstIterator(max());
    }

    reverseConstIterator reverseConstEnd() const
    {
      return reverseConstIterator();
    }

    void clear()
    {
      clearN(root_);
      root_ = nullptr;
    }

    node* max() const noexcept
    {
      return findMax(root_);
    }

    node* min() const noexcept
    {
      return findMin(root_);
    }

    node* findMax(node* node) const noexcept
    {
      if (isEmpty(node))
      {
        return nullptr;
      }
      while (!isEmpty(node->right))
      {
        node = node->right;
      }

      return node;
    }

    static node* findMin(node* node)
    {
      if (isEmpty(node))
      {
        return nullptr;
      }
      while (!isEmpty(node->left))
      {
        node = node->left;
      }

      return node;
    }

    iterator find(Key& key)
    {
      iterator res = begin();
      while (res != end())
      {
        if (res->first == key)
        {
          return res;
        }
        else
        {
          res++;
        }
      }
      return res;
    }

    constIterator find(const Key& key)
    {
      constIterator res = cbegin();
      while (res != end())
      {
        if (res->first == key)
        {
          return res;
        }
        else
        {
          res++;
        }
      }
      return res;
    }

    static bool isEqual(Key k1, Key k2)
    {
      return k1 == k2;
    }

    void toInsert(zasulsky::detail::node_t< std::pair< Key, Value > >*& root, std::pair< Key, Value > value)
    {
      if (root == nullptr)
      {
        root = new detail::node_t< std::pair< Key, Value > >(value);
        root->height = getHeight(root);
      }
      else if (comp_(value.first, root->data.first))
      {
        toInsert(root->left, value);
        root->left->parent = root;
        balance(root);
        updateHeight(root);
      }
      else if (!comp_(value.first, root->data.first))
      {
        toInsert(root->right, value);
        root->right->parent = root;
        balance(root);
        updateHeight(root);
      }
      else
      {
        throw std::runtime_error("Duplicate value");
      }
    }

    void insert(pair value)
    {
      toInsert(root_, value);
    }

    void erase(const Key key)
    {
      node* ptr = remove(root_, key);
    }

    static int getHeight(node* node)
    {
      if (node == nullptr)
      {
        return 0;
      }
      else
      {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        return 1 + std::max(leftHeight, rightHeight);
      }
    }

    static int height(node* node)
    {
      if (node == nullptr)
      {
        return 0;
      }
      else
      {
        return node->height;
      }
    }

    int getMaxHeight()
    {
      return root_->height;
    }

    const Value& at(Key key) const
    {
      auto it = cbegin();
      while (it != cend())
      {
        if (it->first == key)
        {
          return it->second;
        }
        else
        {
          it++;
        }
      }
      throw std::out_of_range("no such key");
    }

    bool empty()
    {
      return root_ == nullptr;
    }

    static int balanceFactor(node* node)
    {
      if (node == nullptr)
      {
        return 0;
      }
      return height(node->left) - height(node->right);
    }

    static int balanceFactor(const node* node)
    {
      if (node == nullptr)
      {
        return 0;
      }
      return height(node->left) - height(node->right);
    }

    static void updateHeight(node* node) noexcept
    {
      node->height = 1 + std::max(height(node->left), height(node->right));
    }

    node* turnRight(node* ptr)
    {
      if (ptr == nullptr)
      {
        return ptr;
      }
      if (ptr->left == nullptr)
      {
        return ptr;
      }
      ptr->left->parent = ptr->parent;
      ptr->parent = ptr->left;
      if (!isEmpty(ptr->left->parent))
      {
        if (comp_(ptr->left->parent->data.first, ptr->left->data.first))
        {
          ptr->left->parent->right = ptr->left;
        }
        else if (!comp_(ptr->left->parent->data.first, ptr->left->data.first))
        {
          ptr->left->parent->left = ptr->left;
        }
      }
      else
      {
        root_ = ptr->left;
      }

      node* pt = ptr->left;
      ptr->left = ptr->left->right;
      pt->right = ptr;

      updateHeight(ptr);
      if (ptr->left != nullptr)
      {
        updateHeight(ptr->left);
      }
      return pt;
    }

    node* turnLeft(node* ptr)
    {
      if (ptr == nullptr)
      {
        return ptr;
      }
      if (ptr->right == nullptr)
      {
        return ptr;
      }
      ptr->right->parent = ptr->parent;
      ptr->parent = ptr->right;
      if (!isEmpty(ptr->right->parent))
      {
        if (comp_(ptr->right->parent->data.first, ptr->right->data.first))
        {
          ptr->right->parent->right = ptr->right;
        }
        else if (!comp_(ptr->right->parent->data.first, ptr->right->data.first))
        {
          ptr->right->parent->left = ptr->right;
        }
      }
      else
      {
        root_ = ptr->right;
      }

      node* pt = ptr->right;
      ptr->right = ptr->right->left;
      pt->left = ptr;

      updateHeight(ptr);
      if (ptr->right != nullptr)
      {
        updateHeight(ptr->right);
      }
      return pt;
    }

    node* balance(node* node)
    {
      updateHeight(node);
      int bf = balanceFactor(node);

      if (bf < -1 && balanceFactor(node->right) <= 0)
      {
        return turnLeft(node);
      }
      if (bf < -1 && balanceFactor(node->right) > 0)
      {
        turnRight(node->right);
        return turnLeft(node);
      }

      if (bf > 1 && balanceFactor(node->left) >= 0)
      {
        return turnRight(node);
      }
      if (bf > 1 && balanceFactor(node->left) < 0)
      {
        turnLeft(node->left);
        return turnRight(node);
      }

      return node;
    }

    void inorderTraversal()
    {
      infix(root_);
    }

    void preorderTraversal()
    {
      prefix(root_);
    }

    void postorderTraversal()
    {
      postfix(root_);
    }

    bool count(Key key)
    {
      bool isKey = 0;
      countKey(root_, key, isKey);
      return isKey;
    }

    int calculateMax()
    {
      return cal(root_);
    }

    static int cal(node* root)
    {
      if (root == nullptr)
      {
        return 0;
      }

      if (cal(root->right) > cal(root->left))
      {
        return root->data.first + cal(root->right);
      }
      else if (cal(root->right) < cal(root->left))
      {
        return root->data.first + cal(root->left);
      }
      else
      {
        if (cal(root->right) == cal(root->left))
        {
          return root->data.first + cal(root->right);
        }
      }
    }

    int calculate()
    {
      int count = 0;
      calc(root_, count);
      return count;
    }

    static void calc(detail::node_t<std::pair<Key, Value>>* root, int& count)
    {
      if (root != nullptr)
      {
        count++;
        if (root->left != nullptr)
        {
          calc(root->left, count);
        }
        if (root->right != nullptr)
        {
          calc(root->right, count);
        }
      }
    }

    static void countKey(node* root, Key key, bool& isKey)
    {
      if (root == nullptr)
      {
        return;
      }
      countKey(root->left, key, isKey);
      if (root->data.first == key)
      {
        isKey = 1;
      }
      countKey(root->right, key, isKey);
    }

    static void showKey(node* root)
    {
      std::cout << root->data.first << '\n';
    }

    static void visit(node* ptr, void(*foo)(node* pt))
    {
      foo(ptr);
    }

    void breadthTraversal()
    {
      breadth(root_);
    }

    void LNRTraversal()
    {
      LNR(root_);
    }

    void RNLTraversal()
    {
      RNL(root_);
    }

    struct doTravOp
    {
      zasulsky::Queue<std::string> values;
      int res = 0;

      void operator()(node* ptr)
      {
        if (ptr->data.first > 0 && res > std::numeric_limits<int>::max() - ptr->data.first)
        {
          throw std::overflow_error("������������ ��� ������������ ������");
        }
        res += ptr->data.first;
        values.enqueue(ptr->data.second);
      }

      void outputVal()
      {
        while (!values.isEmpty())
        {
          std::cout << values.peek() << ' ';
          values.dequeue();
        }
      }
    };


  private:
    node* root_;
    Compare comp_;

    node* remove(node*& nod, const Key key)
    {
      if (isEmpty(nod))
      {
        return nullptr;
      }

      if (isEqual(nod->data.first, key))
      {
        if (isEmpty(nod->left) && isEmpty(nod->right))
        {
          delete nod;
          return nullptr;
        }
        else if (isEmpty(nod->left))
        {
          node* temp = nod->right;
          delete nod;
          nod = nullptr;
          return temp;
        }
        else if (isEmpty(nod->right))
        {
          node* temp = nod->left;
          delete nod;
          nod = nullptr;
          return temp;
        }
        else
        {
          node* minNode = findMin(nod->right);
          nod->data = minNode->data;
          nod->right = remove(nod->right, minNode->data.first);
          if (!isEmpty(nod->right))
          {
            nod->right->parent = nod;
          }
        }
      }
      else if (key < nod->data.first)
      {
        nod->left = remove(nod->left, key);
        if (!isEmpty(nod->left) && nod->left->parent != nod)
        {
          nod->left->parent = nod;
        }
      }
      else if (key > nod->data.first)
      {
        nod->right = remove(nod->right, key);
        if (!isEmpty(nod->right) && nod->right->parent != nod)
        {
          nod->right->parent = nod;
        }
      }
      return balance(nod);
    }

    static void infix(node* root)
    {
      if (root == nullptr)
      {
        return;
      }
      infix(root->left);
      visit(root, showKey);
      infix(root->right);
    }

    static void prefix(node* root)
    {
      if (root == nullptr)
      {
        return;
      }
      visit(root, showKey);
      prefix(root->left);
      prefix(root->right);
    }

    static void postfix(node* root)
    {
      if (root == nullptr)
      {
        return;
      }
      postfix(root->left);
      postfix(root->right);
      visit(root, showKey);
    }

    void LNR(node* root)
    {
      Stack<node*> stack;
      node* current = root;
      doTravOp operation;

      while (current != nullptr || !stack.isEmpty())
      {
        while (current != nullptr)
        {
          stack.push(current);
          current = current->left;
        }

        current = stack.top();
        stack.pop();
        operation(current);

        current = current->right;
      }
      std::cout << operation.res << " ";
      operation.outputVal();
    }

    void RNL(node* root)
    {
      Stack<node*> stack;
      node* current = root;
      doTravOp operation;

      while (current != nullptr || !stack.isEmpty())
      {
        while (current != nullptr)
        {
          stack.push(current);
          current = current->right;
        }

        current = stack.top();
        stack.pop();
        operation(current);

        current = current->left;

      }
      std::cout << operation.res << " ";
      operation.outputVal();
    }

    void breadth(node* root)
    {
      if (root != nullptr)
      {
        doTravOp operation;
        Queue <node* > q;
        q.enqueue(root);
        while (!q.isEmpty())
        {
          node* current = q.peek();
          q.dequeue();
          operation(current);
          if (current->left != nullptr)
          {
            q.enqueue(current->left);
          }

          if (current->right != nullptr)
          {
            q.enqueue(current->right);
          }

        }
        std::cout << operation.res << ' ';
        operation.outputVal();
      }
    }
  };
}

#endif
