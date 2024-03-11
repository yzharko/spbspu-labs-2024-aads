#ifndef NODE_HPP
#define NODE_HPP
namespace litsinger
{
  template< typename T >
  struct Node
  {
  public:
    Node();
    Node(T data);
    ~Node() = default;
    T data;
    Node< T > * prev;
    Node< T > * next;
    template<typename T>
    inline Node<T>::Node(T data)
    {
      this->data = data;
      this->next = this->prev = nullptr;
    }
  };
}
#endif
