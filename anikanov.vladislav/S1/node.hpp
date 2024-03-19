#ifndef NODE_HPP
#define NODE_HPP

#include <memory>

namespace anikanov {

  template<typename T>
  struct Node {
    T data;
    std::shared_ptr< Node< T > > prev, next;

    explicit Node(T val) : data(val), prev(nullptr), next(nullptr)
    {
    }

    Node(const Node &other) : data(other.data), prev(other.prev), next(other.next)
    {
    }
  };

}


#endif
