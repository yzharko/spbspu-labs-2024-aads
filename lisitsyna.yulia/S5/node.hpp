#ifndef NODE_HPP
#define NODE_HPP

#include <tuple>

namespace lisitsyna
{
  namespace detail
  {
    template< class Key, class Value >
    struct TNode
    {
      std::pair< Key, Value > data;
      int height;
      TNode *parent;
      TNode *left;
      TNode *right;

      TNode(const Key key, const Value value):
        data(std::pair< Key, Value >(key, value)),
        height(0),
        parent(nullptr),
        left(nullptr),
        right(nullptr)
      {}
    };
  }
}

#endif
