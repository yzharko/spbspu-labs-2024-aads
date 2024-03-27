#ifndef NODE_HPP
#define NODE_HPP

template < typename T >
class Node
{
public:
  Node* nextPoint;
  T  data;
  Node(T data = T(), Node* nextPoint = nullptr)
  {
    this->data = data;
    this->nextPoint = nextPoint;
  }
};

#endif
