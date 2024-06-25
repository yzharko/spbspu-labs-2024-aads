#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <iostream>
#include <utility>
#include <iterator>
#include <stdexcept>
#include "node_t.hpp"
#include "AVL.hpp"

template< class Key, class Value, class Compare = std::less< Key > >
class Dictionary
{
public:
  using KVPair = std::pair< Key, Value >;
  using fList = AVL< Key, Value, Compare >;
  using iterator = BidirectionalIterator<Key, Value, Compare >;
  using bigPair = std::pair< std::string, Dictionary< Key, Value, Compare > >;
  using constIter = ConstBidIter <Key, Value, Compare>;

  Dictionary() :
    fL(),
    comp()
  {}
  Dictionary(std::initializer_list< KVPair >& inList, const Compare& com = Compare()) :
    fL(),
    comp(com)
  {
    insert(inList);
  }
  Dictionary& operator=(std::initializer_list< KVPair >& inList)
  {
    fL.clear();
    insert(inList);
    return *this;
  }

  iterator begin()
  {
    return fL.begin();
  }
  iterator end()
  {
    return fL.end();
  }

  constIter cbeforeBegin() const
  {
    return fL.cbeforeBegin();
  }
  constIter cbegin() const
  {
    return fL.cbegin();
  }
  constIter cend() const
  {
    return fL.cend();
  }

  iterator findBefore(const Key& key)
  {
    iterator result = end();
    bool isUs = true;

    for (iterator it = begin(); !isEmptyIt(it) && isUs; result++, it++)
    {
      if (key == it->first)
      {
        result = --it;
        isUs = false;
      }
    }

    return result;
  }
  iterator find(const Key& key)
  {
    return ++findBefore(key);
  }

  iterator lookfor(const Key& key)
  {
    bool isUs = true;
    iterator res = end();
    for (iterator it = begin(); (!isEmptyIt(it)) && isUs; it++)
    {
      if (it->first == key)
      {
        res = it;
      }
    }
    return res;
  }
  iterator upperBoundBefore(const Key& key)
  {
    iterator result = end();

    for (iterator it = begin(); (!isEmptyIt(it)) && !comp(key, it->first); result++, it++)
    {
      if (key == it->first)
      {
        result = --it;
      }
    }
    return result;
  }
  iterator lowerBoundBefore(const Key& key)
  {
    iterator result = end();

    for (iterator it = begin(); (!isEmptyIt(it)) && comp(it->first, key); result++, it++)
    {
      if (key == it->first)
      {
        result = --it;
      }
    }
    return result;
  }

  iterator upperBound(const Key key)
  {
    return ++upperBoundBefore(key);
  }

  iterator lowerBound(const Key& key)
  {
    return ++lowerBoundBefore(key);
  }

  void insert(std::initializer_list< KVPair > inList)
  {
    insert(inList.begin(), inList.end());
  }

  template <class inpIt >
  void insert(inpIt begin, inpIt end)
  {
    inpIt temp = begin;
    while (temp != end)
    {
      fL.pushFront(*temp);
      temp++;
    }
  }

  iterator insert(const KVPair& keyValue)
  {
    iterator it = upperBoundBefore(keyValue.first);
    if (it == end())
    {
      fL.insert(keyValue);
      iterator res = fL.find(keyValue.first);
      return res;
    }
    if (isEqual(it->first, keyValue.first))
    {
      return it;
    }
    fL.insert(keyValue);
    iterator res = fL.find(keyValue.first);
    return res;
  }

  iterator eraseAfter(constIter it)
  {
    iterator temp = ++it;
    fL.erase(it);
    return ++temp;
  }

  iterator erase(const Key& key)
  {
    iterator it = findBefore(key);
    iterator finded = it;
    finded++;
    if (isEmptyIt(finded))
    {
      throw std::out_of_range("no reseults with such key");
    }
    fL.erase(key);
    return ++finded;
  }

  Value& operator[](const Key& key)
  {
    iterator it = lookfor(key);
    if (!isEmptyIt(it))
    {
      return it->second;
    }
    return insert({ key, Value() })->second;
  }

  void clear() noexcept
  {
    fL.clear();
  }

  bool isEqual(Key lhs, Key rhs)
  {
    return lhs == rhs;
  }

  bool isEmpty()
  {
    return fL.empty();
  }

  bool isEmptyIt(constIter it) const
  {
    return it == cend();
  }

  size_t size()
  {
    size_t count = 0;
    iterator it = begin();
    if (it == end())
    {
      return 0;
    }
    while (it != end())
    {
      it++;
      count++;
    }
    return count;
  }

  KVPair get()
  {
    return fL.front();
  }

  void pop()
  {
    fL.popFront();
  }
  void print()
  {
    iterator temp = fL.begin();
    while (temp != fL.end())
    {
      std::cout << ' ';
      std::cout << temp->first << ' ';
      std::cout << temp->second;
      temp++;
    }
    std::cout << '\n';
  }

  Dictionary subtract(Dictionary other)
  {
    Dictionary res;
    iterator cur = begin();
    iterator iter;
    while (cur != end() && cur.getCur() != nullptr)
    {
      iter = other.lookfor(cur->first);
      if (isEmptyIt(iter))
      {
        res.insert(*cur);
      }
      cur++;
    }
    return res;
  }

  Dictionary cross(Dictionary& other)
  {
    iterator iter;
    Dictionary res;
    iterator cur = begin();
    while (cur != end() && cur.getCur() != nullptr)
    {
      iter = other.lookfor(cur->first);
      if (!isEmptyIt(iter))
      {
        res.insert(*cur);
      }
      cur++;
    }
    return res;
  }
  void sort()
  {
    if (!isEmpty())
    {
      fList newList;
      for (iterator it = begin(); it != end(); it++)
      {
        newList.insert(*it);
      }
      fL.clear();
      for (iterator it = newList.begin(); it != newList.end(); it++)
      {
        insert(*it);
      }
    }
  }
  Dictionary merge(Dictionary<Key, Value> other)
  {
    iterator it;
    iterator cur = other.begin();
    while (cur != end() && cur.getCur() != nullptr)
    {
      it = lookfor(cur->first);
      if (isEmptyIt(it))
      {
        insert(*cur);
      }
      cur++;
    }
    Dictionary res(*this);
    res.sort();
    return res;
  }
  bool count(const Key& key)
  {
    iterator it = lookfor(key);
    if (isEmptyIt(it))
    {
      return false;
    }
    return true;
  }

private:
  fList fL;
  Compare comp;

};

#endif
