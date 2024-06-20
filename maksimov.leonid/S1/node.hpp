#define NODE_HPP
#ifdef NODE_HPP

namespace maksimov
{
  template < typename T >
  class Node
  {
  public:
    Node(T data): data_(data), next_(nullptr) {};
    ~Node() = default;
    Node< T >* next_;
  private:
    T data_;
  };
}

#endif